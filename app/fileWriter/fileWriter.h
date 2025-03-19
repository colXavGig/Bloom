#include <iostream>
#include <filesystem>
#include <fstream>
#include "../garden_tags/gardenTags.h"
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
        HashNode* node;
        fs::path gardenpath;
        gardenTags tag;
        void createFileStructure(const HashNode &node,string &foldername,string &filename);

        void fileToGarden(const HashNode &node);
        //convertit en txt pour l'instant jsp c quoi le meilleur ouvert a des propositions
        
        void FolderToFile(const HashNode &file, string filename);

        void folderToGarden(const HashNode &node);
        
    public:

        fileWriter(HashNode* node,fs::path gardenlocation){
            this->gardenpath=gardenlocation;
             this->tags= gardenTags(node);
        };

        void CreateGarden(HashNode current);

};

