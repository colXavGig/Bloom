#pragma once

#include <string>
#include <filesystem>
#include "Index_struct.h"
using namespace std;
namespace  fs =  std::filesystem;
/**
* L'Index est un fichier dans '.garden' contenant un pointer vers
* la branch courante ou le commit courrante.
* L'utilité de cette classe nous permet d'associé facilement
* un nouveau commit à son parent. La signature du tag parent du nouveau
* commit sera automatiquement la signature de l'ìndex.
*
* Voici un exemple de ce qu'un fichier d'index:
* ================================================

    [index]     main
    [main]      <main-head-signature>
    [dev]       <dev-head-signature>
    [feature1]  <feature1-head-sigtnature>

* ================================================
* la commande ' bloom checkout <branch> ' lira l'index pour aller
* chercher le tree du commit puis le recréée dans la repository,
* puis après avoir regénéré le hashtree du commit, la ligne [index]
* devrait être être overwrite avec la branche choisi.
*
* Un nouveau commit devrait toujours avoir comme parents le le head
* de la branch dans l'index puis modifie le fichier index afin de
* remplacer le nouveau head.
*
* La class Index est
*/
class Index {
    public:
        Index(const fs::path& path);
        ~Index();
        
        void addBranch(Branch *branch);
        Index_s *getStructuralValue();

        void save();
        operator Index_s &();
        operator Index_s *();

        //commit event
        void commit(const string& signature);
        string getSignature();

        //branch functions
        void setCurrentBranch(const string& name);
        void createNewBranch(const string& name,const string& signature);
    private:
        Index_s *value;
        fs::path path;

        void init(fs::path path);

        string readToken(char **line);
        Branch *createBranch(const string& branch_name, const string& signature);
};



