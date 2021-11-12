#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<fstream>
#include<sstream>


const int countAlph = 31;
extern const std::vector<char> baseCode;

void Start(std::ifstream& input, std::ofstream& output, int mode);
void Start(std::ifstream& input, int mode);

std::pair<std::string, long long> EncodeBWT(std::string text);
std::string EncodeMTF(std::string& text);
std::string EncodeRLE(std::vector<int>& text);
std::vector<std::pair<std::string, long long>> Compress(std::ifstream& input, int mode);

std::string DecodeBWT(std::pair<std::string, long long> pair);
std::string DecodeMTF(std::vector<int>& text);
std::string DecodeRLE(std::string& text);
std::vector<std::string> Decompress(std::ifstream& input, int mode);