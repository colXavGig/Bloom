#pragma once
#include <fstream>
#include <istream>
#include"../paths/GardenPath.h"
#include <string.h>
#include <vector>
#define DELIMITER ' '

namespace gp{
/**
 * est responsable pour ecrire et lire une line
 * 
 */
class GardenProtocol{
    public:
        static std::vector<std::string> GardenDecode(char **line);
        static std::vector<std::string> GardenDecode(const std::string&line);

        static std::string GardenEncode(const std::vector<char*>&);       
        static std::string GardenEncode(const std::vector<std::string>&);
    private:      
        //c++ doesnt have built in trim function
        static std::string trimEndSpecial(const std::string& str);
};
}