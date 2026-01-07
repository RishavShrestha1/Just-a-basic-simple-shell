#include "features.h"

int main(){
    std::string line;
    bool is_running = true;

    while(is_running){
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;

        std::cout << "$ ";
        if(!std::getline(std::cin, line)) break;
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if(cmd == "exit"){
            is_running = false;
            continue;
        }

        else if(!is_builtin(cmd)) {
            run_exe_file(cmd, line);
        }

        else if(cmd == "echo"){
            run_echo(ss);
        }

        else if(cmd == "pwd"){
            run_pwd();
        }

        else if(cmd == "cd") {
            run_change_directory();
        }

        else if(cmd == "ls" || cmd == "dir") {
            show_dir_content();
        }

        else if(cmd == "type"){
            std::string arg;
            ss >> arg;
            if(!arg.empty()){
                run_type(arg);
            } else {
                std::cout << "type: missing argument" << std::endl;
            }
        }

        else if(cmd == "clear") {
            run_clear();
        }
        else{
            std::cout << cmd << ": command not found" << std::endl;
        }
    }

    return 0;
}
