#include <SDL2/SDL.h>
#include <D:/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include/SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sys/stat.h>
#include <sstream>

namespace fs = std::filesystem;

bool is_builtin(const std::string &cmd){
    return cmd == "exit" || cmd == "echo" || cmd == "type" || cmd == "clear" || cmd == "pwd" || cmd == "cd" || cmd == "dir" || cmd == "ls";
}

bool does_file_exist(const fs::path &p){
    return fs::exists(p) && fs::is_regular_file(p);
}

bool file_is_executable(const std::string &path) {
    struct stat sb{};
    if(stat(path.c_str(), &sb )!= 0){
        return false;
    }

    return S_ISREG(sb.st_mode) &&
             (sb.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH));
}

#ifdef _WIN32
constexpr char PATH_LIST_SEPARATOR = ';';
#else
constexpr char PATH_LIST_SEPARATOR = ':';
#endif

bool is_executable_in_path(const std::string &cmd, std::string &fullpath) {
    const char *path_env = std::getenv("PATH");
    if (!path_env) return false;

    std::stringstream ss(path_env);
    std::string dir;

    while (std::getline(ss, dir, PATH_LIST_SEPARATOR)) {
        if (dir.empty()) dir = ".";
        std::string candidate = dir + "/" + cmd;

        if (file_is_executable(candidate)) {
            fullpath = candidate;
            return true;
        }
    }
    return false;
}

void run_exe_file(std::string &cmd, const std::string line){
    std::string fullpath;

    if(is_executable_in_path(cmd, fullpath)) {
    std::system(line.c_str());
    }
    else {
        std::cout << cmd <<": command not found" <<std::endl;
    }
}

void run_type(const std::string &cmd) {
    if (is_builtin(cmd)) {
        std::cout << cmd << " is a shell builtin" << std::endl;
        return;
    }

    std::string fullpath;
    if (is_executable_in_path(cmd, fullpath)) {
        std::cout << cmd << " is " << fullpath << std::endl;
    } else {
        std::cout << cmd << ": not found" << std::endl;
    }
}

void run_pwd() {
    fs::path curr_path = fs::current_path();
    std::cout << curr_path <<std::endl;
}

void run_change_directory() {
    fs::path location;

    std::cout << "Change to :";
    std::cin >> location;

    try{
        fs::current_path(location);
        std::cout << "Path changed to : "<< fs::current_path() <<std::endl;
    }
    catch(const fs::filesystem_error &e){
        std::cerr << e.what()<<std::endl;
    }
}

void show_dir_content(){
    fs::path dir_path;
    std::cout << "Directory : ";
    std::cin >> dir_path;

    try{
        for(auto &content : fs::directory_iterator(dir_path)) {
            std::cout << content.path().filename() <<std::endl;
        }
    }
    catch(const fs::filesystem_error &e) {
        std::cerr << e.what() <<std::endl;
    }
}

void run_clear() {
    system("cls");
}

void run_echo(std::stringstream &ss){
    std::string text;
    std::getline(ss, text);
    if(!text.empty() && text[0] == ' ') text.erase(0,1);
    std::cout << text << std::endl;
}