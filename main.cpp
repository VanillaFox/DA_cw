#include<iostream>
#include<fstream>
#include<ostream>
#include<vector>
#include"funcs.h"

void Input(){
    std::string str;
    bool newline = false;
    std::ofstream test("input.txt");
    std::cin >> str;
    test << str;
    if(str=="compress"){
        while(std::cin >> str){
            test << "\n" << str;
        }
    }
    else if(str=="decompress"){
        newline = true;
        while(std::cin >> str){
            if(str=="code" || str=="num"){
                newline = true;
                continue;
            }
            if(newline){
                test << "\n";
                test << str;
                newline = false;
                continue;
            }
            test << " " << str;
        }
    }
    else{
        std::cout << "Unknown command for text conversion: \'" << str << "\'\n";
    }
    test.close();
}


int main(int argc, char *argv[]){
    if(argc!=3){
        std::cout << "Usage: ./curswork mode filename/-c\n";
        exit(-1);
    }
    int mode = std::atoi(argv[1]);
    if(mode > 2 || mode < 1){
        std::cout << "Select mode: BWT+MTF[1] or BWT+RlE[2]\n";
        exit(-1);
    }
   
    std::string str(argv[2]);
    if(str[0]=='-'){
        if(str=="-p"){
            Input();            
            std::ifstream input("input.txt");
            Start(input, mode);
            input.close();
        }
        else{
            std::cout << "Invalid flag\n";
            exit(-1);
        }
    }
    else{
        std::ifstream input(str);
        if(!input.is_open()){
            std::cout << "File opening problem\n";
            exit(-1);
        }
        std::ofstream output("modified_"+str);
        Start(input, output, mode);
        output.close();
        input.close();
    }
}