#include <iostream>
#include <filesystem>
#include <fstream>
//#include "../garden_tags/gardenTags.h"
#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"

using namespace std;
namespace fs = std::filesystem;

/*
    Env that must be setup is gardenpath(database) through a json
    it takes the node checks the states and create the appropriate file.
*/
class fileWriter{
    public:
        //HashNode* node;
        fs::path gardenpath;
        
        //gardenTags tag;
        void createFileStructure(string s,string &folder,string &file);

        void savingFile(const FileNode *node);
        //convertit en txt pour l'instant jsp c quoi le meilleur ouvert a des propositions

        void savingFolder(const FolderNode *node);
        
    public:

        fileWriter(fs::path gardenlocation)/*: tag(node)*/ {
            this->gardenpath=gardenlocation;   
        };

        void createGarden(FolderNode *current);

};

