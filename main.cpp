#include<iostream>
#include<fstream>
#include<ostream>
#include<vector>
#include"funcs.h"

int main(int argc, char *argv[]){
    if(argc<3){
        std::cout << "Usage: ./curswork mode filename/-c\n";
        exit(-1);
    }
    int mode = std::atoi(argv[1]);
    if(mode > 2 || mode < 1){
        std::cout << "Select mode: BWT+MTF[1] or BWT+RlE[2]\n";
        exit(-1);
    }
   
    std::string str(argv[2]);
    bool newline = false;
    if(str[0]=='-'){
        if(str=="-p"){
            std::ofstream test("input.txt");
            while(std::cin >> str){
                if(str=="word" || str=="num"){
                    newline = true;
                    continue;
                }
                if(str=="compress" || str=="decompress"){
                    test << str;
                    newline = true;
                    continue;
                }
                if(newline){
                    test << "\n";
                    newline = false;
                }
                test << str << " ";
            }
            
            test.close();
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