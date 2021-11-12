#include<iostream>
#include<fstream>
#include<vector>
#include"funcs.h"

int main(int argc, char *argv[]){
    if(argc!=3){
        std::cout << "Usage: ./curswork filename mode\n";
        exit(-1);
    }
    int mode = std::atoi(argv[2]);
    if(mode > 2 || mode < 1){
        std::cout << "Select mode: BWT+MTF[1] or BWT+RlE[2]\n";
        exit(-1);
    }
    std::string filename = argv[1];
    std::ifstream input(filename+".txt");
    if(!input.is_open()){
        std::cout << "File opening problem\n";
        exit(-1);
    }
    std::ofstream output(filename+"_modified.txt");
    Start(input, output, mode);
    input.close();
    output.close();
}