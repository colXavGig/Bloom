#include <iostream>
#include <filesystem>
#include <fstream>
#include "../paths/GardenPath.h"
#include "../datacollection/hashTree/HashNode.h"
#include "../datacollection/hashTree/HashTree.h"


using namespace std;
namespace fs = std::filesystem;

/**
 * Env that must be setup is gardenpath(database) through a json
 * it takes the node checks the states and create the appropriate file.
*/
class fileWriter {
public:
    /**
     * constructor of the file writer with initialize all the members
     * @param paths path where .garden is located. Typically the root of the project
     */
    fileWriter(GardenPath *paths)/*: tag(node)*/ {
            this->gardenpath = paths;
    }

    /**
     * Write an HashTree into the .garden/ folder of the repo
     * @param tree representing the current repo state
     * @param commit_msg message to keep in the GardenTag
     */
    void writeToFile(HashTree *tree, string tag_msg);;

private:
    /** Collection of path for the .garden/ folder */
    GardenPath *gardenpath;

    /**
     * create the entry in the .garden/ for the current node
     * @param current the node to add into .garden/
     */
    void createGarden(FolderNode *current);
    void createFileStructure(string s,string &folder,string &file);
    void savingFile(const FileNode *node); //convertit en txt pour l'instant jsp c quoi le meilleur ouvert a des propositions
    void savingFolder(const FolderNode *node);
    /**
     * Save the GardenTag into the filesystem
     * @param tree A pointer to the HashTrww the tag should point to
     * @param tag_msg The message that describe the commit
     */
    void savingGardenTag(HashTree *tree, string tag_msg);

};

