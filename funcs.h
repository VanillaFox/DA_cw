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
std::pair<std::string, long long> EncodeBWT(std::string text);
void EncodeMTF(std::string& text, std::ofstream& file);
void EncodeRLE(std::vector<int>& text, std::ostream& file);
void Compress(std::ifstream& input, std::ofstream& output, int mode);

void DecodeBWT(std::pair<std::string, long long> pair, std::ofstream& file);
std::string DecodeMTF(std::vector<int>& text);
std::string DecodeRLE(std::string& text);
void Decompress(std::ifstream& input, std::ofstream& output, int mode);