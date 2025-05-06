#include <iostream>
#include <filesystem>
#include <fstream>
#include "../paths/GardenPath.h"

//fileSystem management
#include "../fileSystemManagement/seed/HashNode.h"
#include "../fileSystemManagement/seed/HashTree.h"
#include "../fileSystemManagement/garden_tags/GardenTag.h"
#include "../fileSystemManagement/index/Index.h"
#define LOGGER_STATUS LOGGER_ACTIVE
#include "../debugging.h"

using namespace std;
namespace fs = std::filesystem;

/**
 * Env that must be setup is gardenpath(database) through a json
 * it takes the node checks the states and create the appropriate file.
*/
class fileWriter {
public:

    string init(HashTree *tree, string tag_msg, Index *index);
    /**
     * Write an HashTree into the .garden/ folder of the repo
     * @param tree representing the current repo state
     * @param commit_msg message to keep in the GardenTag
     */
    string commit(HashTree *tree, string tag_msg, Index *index);

private:


    /**
     * create the entry in the .garden/ for the current node
     * @param current the node to add into .garden/
     */
    void createGarden(FolderNode *current);
    void savingFile(const FileNode *node); //convertit en txt pour l'instant jsp c quoi le meilleur ouvert a des propositions
    void savingFolder(const FolderNode *node);

};

