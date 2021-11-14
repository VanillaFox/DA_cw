#include"funcs.h"

const std::vector<char> baseCode = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z'
};
std::vector<char> alphabet;


std::pair<std::string, long long> EncodeBWT(std::string text){
    std::vector<std::string> strs;
    long long textsize = text.size();
    for(long long i = 0; i < textsize; i++){
        text.append(text, 0, 1);
        text.erase(text.begin());
        strs.push_back(text);
    }
    std::sort(strs.begin(), strs.end());
    std::string result;
    int textnum;
    
    for(long long i = 0; i < textsize; i++){
        if(strs[i]==text){
            textnum=i;
        }
        result.push_back(strs[i][textsize-1]);
    }
    return std::make_pair(result, textnum);
}


std::string DecodeBWT(std::pair<std::string, long long> pair){
    std::string text = pair.first;
    long long textsize = text.size();
    std::map<long long, std::pair<char, long long>> decodearr;
    std::sort(text.begin(), text.end());
    for(long long i = 0; i < textsize; i++){
        char a = pair.first[i];
        for(long long j = 0; j < textsize; j++){
            if(a == text[j]){
                text[j] = '*';
                decodearr[j] = std::make_pair(a, i);
                break;
            }
        }
    }
    long long cur = pair.second;
    for(long long i = 0; i < textsize; i++){
        text[i] = decodearr[cur].first;
        cur = decodearr[cur].second;
    }
    return text;
}


std::string EncodeMTF(std::string& text){
    std::vector<char>::iterator it;
    int alphid, size = text.size();
    alphabet = baseCode;
    std::string res;
    for(long long i = 0; i < size; i++){
        alphid = 0;
        it = alphabet.begin();
        while(text[i]!=*it){
            alphid++;
            it++;
        }
        if(alphid){
            alphabet.erase(it);
            alphabet.insert(alphabet.begin(), text[i]);
        }
        res += std::to_string(alphid) + " ";
    }
    return res;
}


std::string DecodeMTF(std::vector<int>& text){
    std::string result;
    result.resize(text.size());
    char sym;
    alphabet = baseCode;
    for(long long i = 0; i < text.size(); i++){
        sym = alphabet[text[i]];
        if(text[i]){
            alphabet.erase(alphabet.begin()+text[i]);
            alphabet.insert(alphabet.begin(), sym);
        }
        result[i] = sym;
    }
    return result;
}


std::string EncodeRLE(std::string& text){
    long long count = 0;
    long long size = text.size();
    std::string res;
    for(long long i = 1; i <= size; i++){
        count++;
        if(i!=size){
            if(text[i]==text[i-1]){
                continue;
            }
        }
        res += text[i-1];
        if(!(count==1)){
           res += std::to_string(count); 
        }
        count = 0;
    }
    return res;
}


std::string DecodeRLE(std::string& text){
    std::string result;
    long long count = 0;
    char prevsym = text[0];
    char cur;
    for(long long i = 1; i <= text.size(); i++){
        if(i!=text.size()){
            cur = text[i];
        }
        if(cur > 57 || cur < 48 || i==text.size()){
            if(!count){
                count++;
            }
            for(long long j = 0; j < count; j++){
                result += prevsym;
            }
            count = 0;
            prevsym = cur;
        }
        else{
            if(count){
                count *= 10;
            }
            count += cur - '0';
        }        
    }
    return result;
}


std::vector<std::pair<std::string, long long>> Compress(std::ifstream& input, int mode){
    std::string str;
    std::vector<std::pair<std::string, long long>> res;
    while(!input.eof()){
        getline(input, str);
        std::pair<std::string, int> pair = EncodeBWT(str);
        if(mode==1){
            res.push_back(std::make_pair(EncodeMTF(pair.first), pair.second));
        }
        else{
            res.push_back(std::make_pair(EncodeRLE(pair.first), pair.second));
        }        
    }
    return res;
}


std::vector<std::string> Decompress(std::ifstream& input, int mode){
    std::string str, numstr;
    std::string curres;
    std::vector<std::string> res;
    long long num;
    while(!input.eof()){
        getline(input, str);
        getline(input, numstr);
        if(mode==1){
            std::stringstream iss(str);
            std::vector<int> curvec;
            int p;
            while(iss >> p){
                curvec.push_back(p);
            }
            curres = DecodeMTF(curvec);
            curvec.clear();
        }
        else{
            curres = DecodeRLE(str);
        }

        num = std::stoll(numstr);
        res.push_back(DecodeBWT(std::make_pair(curres, num)));
    }
    return res;
}


void Start(std::ifstream& input, std::ofstream& output, int mode){
    std::string str;
    getline(input, str);
    int num;
    if(str=="compress"){
        output << "decompress";
        str = mode==1 ? "\nBWT+MTF" : "\nBWT+RLE"; 
        output << str;
        std::vector<std::pair<std::string, long long>> res = Compress(input, mode);
        for(auto vec: res){
            output << "\n" << vec.first;
            output << "\n" << vec.second;
        }
    }
    else if(str=="decompress"){
        getline(input, str);
        if(str!="BWT+RLE" && str!="BWT+MTF"){
            std::cout << "Incorrect file format\n";
            exit(-1);
        }
        if(mode==1 && str=="BWT+RLE" || mode==2 && str=="BWT+MTF"){
            std::cout << "This file must be decompressed by algorithm " + str + "\n";
            exit(-1);
        }
        output << "compress";
        std::vector<std::string> res = Decompress(input, mode);
        for(auto vec: res){
            output << "\n" << vec;            
        }
    }
    else{
        std::cout << "Incorrect file content\n";
    }
}


void Start(std::ifstream& input, int mode){
    std::string str;
    getline(input, str);
    int num;

    if(str=="compress"){
        std::vector<std::pair<std::string, long long>> res = Compress(input, mode);
        for(auto vec: res){
            std::cout << vec.first << "\n";
            std::cout << vec.second << "\n";
        }
    }
    else if(str=="decompress"){
        getline(input, str);
        if(mode==1 && str=="BWT+RLE" || mode==2 && str=="BWT+MTF"){
            std::cout << "This file must be decompressed by algorithm " + str + "\n";
            exit(-1);
        }
        std::vector<std::string> res = Decompress(input, mode);
        for(auto vec: res){
            std::cout << vec << std::endl;            
        }
    }
    else{
        std::cout << "Incorrect input content\n";
    }
}