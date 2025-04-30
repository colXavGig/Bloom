#include "GardenProtocol.h"

using namespace std;

namespace gp{
//read a line and seperates it by delimiter trims the special ends to 
vector<string> GardenProtocol::GardenDecode(char **line){
    vector<string> vec;
    string token="";
    while(**line != '\n' && **line != '\0'){
        token += **line;
        if(**line == DELIMITER){
            vec.push_back(trimEndSpecial(token));
            token="";
        }
        (*line)++;
    }

    if (!token.empty()) {
        vec.push_back(trimEndSpecial(token));
    }
    
    return vec;
};

vector<string> GardenProtocol::GardenDecode(const string&line){
    vector<string> vec;
    string token="";
    for(int i=0; i < line.size(); i++){
        if(line[i] == '\n' || line[i] =='\0') break;
        token += line[i];

        if(line[i]== DELIMITER){
            vec.push_back(trimEndSpecial(token));
            token="";
        }
    }

    if (!token.empty()) {
        vec.push_back(trimEndSpecial(token));
    }

    return vec;
};

string GardenProtocol::GardenEncode(const vector<string>& vec){
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {

        result += vec[i];

        if (i != vec.size() - 1) {
            result += DELIMITER;
        }
    }

    return trimEndSpecial(result);
};

string GardenProtocol::GardenEncode(const vector<char *>& vec){
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i]) result += vec[i];
        if (i != vec.size() - 1) {
            result += DELIMITER;
        }
    }

    return trimEndSpecial(result);
};


string GardenProtocol::trimEndSpecial(const std::string& str){
    size_t end = str.find_last_not_of(" \n\r\t");
    if (end == string::npos) return "";
    return str.substr(0, end + 1);
}
}