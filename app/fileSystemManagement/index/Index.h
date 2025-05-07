#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include "Index_struct.h"
#include "../utilz/GardenProtocol/GardenProtocol.h"
#include "../utilz/PathManagement/StaticPath.h"

using namespace std;
namespace  fs =  std::filesystem;

using GP = gp::GardenProtocol;
using SP = staticpath::_staticPath;
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
* La class Index permet la manipulation du fichier index afin de garder l'integriter du fichier
*/
class Index {
    public:
        Index();
        ~Index();
        
  
        /**
         *  writes change to the index file
         *  any change made to the index needs to be save if change need to be registered
         */
        void save(void);

        operator Index_s &(void);
        operator Index_s *(void);

        //public getters
        string   getTagHash(void);
        string   getCurrentName(void);
        Index_s *getStructuralValue(void);
        //branch functions

        /**TODO :: check if should take a Tree root
         * commit new current hash to the Index
         */
        void updateHeadHash(const string& signature);
        
        /**
         * Allows to set the main branch safely
         */
        void setCurrent(const string&);

        /**
         * Allows to create the new branch safely
         */
        void plant(const string& branch_name);

        /**
         * list all index
         */
        void ls();
        /**
         * read Index_s
         */
        void read();  
         /**
         * initialise Index_s
         */
        void init(const string&);  
    private:
        Index_s  index;
            
       
        /**
         * Allows to set a branch and add a branch safely to index
         * @throw bad_alloc
         */
        void addBranch(const string& branch_name, const string& signature);
        //private setters

        void defaultConfig();
        // private getters
        /**
         * Allows to get branch from the branch list
         */
        Branch* getBranch(const string&name) const;


};



