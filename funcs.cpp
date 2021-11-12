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


void DecodeBWT(std::pair<std::string, long long> pair, std::ofstream& file){
    std::string text = pair.first;
    long long textsize = text.size();
    std::map<long long, std::pair<char, long long>> decodearr;
    std::sort(text.begin(), text.end());
    //получение исходной матрицы
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
    //восстановление слова
    long long cur = pair.second;
    for(long long i = 0; i < textsize; i++){
        text[i] = decodearr[cur].first;
        cur = decodearr[cur].second;
    }
    file << text << "\n";
}


void EncodeMTF(std::string& text, std::ofstream& file){
    std::vector<char>::iterator it;
    int alphid, size = text.size();
    alphabet = baseCode;

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
        file << alphid << " ";
    }
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


void EncodeRLE(std::string& text, std::ofstream& file){
    long long count = 0;
    long long size = text.size();
    for(long long i = 1; i <= size; i++){
        count++;
        if(i!=size){
            if(text[i]==text[i-1]){
                continue;
            }
        }
        file << text[i-1];
        if(!(count==1)){
            file << count;
        }
        count = 0;
    }
}


std::string DecodeRLE(std::string& text){
    std::string result;
    long long count = 0;
    char prevsym = text[0];
    for(long long i = 1; i < text.size(); i++){
        char cur = text[i];
        if(cur < 58 && cur > 47){
            if(count){
                count *= 10;
            }
            count += cur - '0';
        }
        if(cur > 57 || cur < 48 || i==(text.size()-1)){
            if(!count){
                count++;
            }
            for(long long j = 0; j < count; j++){
                result += prevsym;
            }
            count = 0;
            prevsym = cur;
        }
    }
    return result;
}

void Compress(std::ifstream& input, std::ofstream& output, int mode){
    std::string str;
    output << "decompress\n";
    str = mode==1 ? "BWT+MTF\n" : "BWT+RLE\n"; 
    output << str;
    while(!input.eof()){
        getline(input, str);
        std::pair<std::string, int> pair = EncodeBWT(str);
        if(mode==1){
            EncodeMTF(pair.first, output);
        }
        else{
            EncodeRLE(pair.first, output);
        }
        output << "\n" << pair.second << "\n";
    }
}


void Decompress(std::ifstream& input, std::ofstream& output, int mode){
    std::string str, num;
    std::string curres;
    getline(input, str);
    if(mode==1 && str=="BWT+RLE" || mode==2 && str=="BWT+MTF"){
        std::cout << "This file must be decompressed by algorithm " + str + "\n";
        exit(-1);
    }
    while(!input.eof()){
        getline(input, str);
        getline(input, num);
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
        DecodeBWT(std::make_pair(curres, std::stoll(num)), output);
    }
}

void Start(std::ifstream& input, std::ofstream& output, int mode){
    std::string str;
    getline(input, str);
    if(str=="compress"){
        Compress(input, output, mode);
    }
    else if(str=="decompress"){
        Decompress(input, output, mode);
    }
    else{
        std::cout << "Incorrect file content\n";
    }
}