#include<iostream>
#include<fstream>
#include<vector>
#include"funcs.h"

int main(int argc, char *argv[]){
    if(argc<2){
        std::cout << "Usage: ./curswork filename mode\n";
        exit(-1);
    }
    int mode = std::atoi(argv[2]);
    if(mode > 2 || mode < 1){
        std::cout << "Select mode: BWT+MTF[1] or BWT+RlE[2]\n";
        exit(-1);
    }
    std::string filename = argv[1];
    std::ifstream input(filename);
    if(!input.is_open()){
        std::cout << "File opening problem\n";
        exit(-1);
    }

    if(argc==4){
        std::string s(argv[3]);
        if(s=="-p")
            Start(input, mode);
        // std::cout << (argv[3].c_str()=="-p" ? "true\n" : "false\n");
    }
    else{
        std::ofstream output("modified_"+filename);
        Start(input, output, mode);
        output.close();
    }
    input.close();
}