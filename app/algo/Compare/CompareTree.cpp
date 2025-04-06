#include "CompareTree.h"
#define EQUAL 0
#define SMALLER -1
#define BIGGER 1

void CompareTree::printChange(){
    for(CompareFile file : FileChange){
        cout<< file<<"\n";
    }
}


void CompareTree::compareFolder(string rootPath1,string rootPath2){
    //variable 
    FolderIterator *folderIt1 = new FolderIterator(rootPath1);//jvais faire en sorte que a linitialisation next se fait call
    FolderIterator *folderIt2 = new FolderIterator(rootPath2);
    folderIt1->Next(),folderIt2->Next();//ignore name for the moment of folder
    folderIt1->Next(),folderIt2->Next();
    cout<<"entering filemanagement\n";
    FileManagement(folderIt1,folderIt2);
    //FolderManagement();
    
    
}



void CompareTree::FileManagement(FolderIterator *folderIt1, FolderIterator *folderIt2){
    int i =0;
    while(folderIt1->getToken()=="[FILE]" && folderIt2->getToken()=="[FILE]"){
        cout<< i++<<"\n";
        int resultat = GradientFilename(folderIt1->getFilename(), folderIt2->getFilename());
        HandleFileComparison(resultat, folderIt1, folderIt2);
    }
    equalise(folderIt1,folderIt2);
}


void CompareTree::HandleFileComparison(int resultat, FolderIterator *folderIt1, FolderIterator *folderIt2){
    cout<<"\n\n Current iterator status\n\t"<<
                "Iterator 1: "<<folderIt1->getFilename()<<" "<<folderIt1->getSignature()<<"\n\t"<<
                "Iterator 2: "<<folderIt2->getFilename()<<" "<<folderIt2->getSignature()<<"\n\n\n";
    switch(resultat){
        case SMALLER:{
            //initialisation
            CompareFile comp= CompareFile("[-]",folderIt1->getFilename(),folderIt1->getSignature());
            //analyse des differences
            comp.compareLines(folderIt1->getSignature()," ");
            //enregistrement
            this->FileChange.push_back(comp);
            //iteration
            folderIt1->Next();
            break;
        }
        case BIGGER:{
            //initialisation
            CompareFile comp= CompareFile("[+]",folderIt2->getFilename(),folderIt2->getSignature());
            //enregistrement dans compareTree
            this->FileChange.push_back(comp);
            
            //iteration
            folderIt2->Next();
            break;
        }
        case EQUAL:{
            if( ! checkSignature(folderIt1->getSignature(),folderIt2->getSignature())){
                CompareFile comp= CompareFile("[~]",folderIt2->getFilename(),folderIt2->getSignature());
                //analyse des differences
                comp.compareLines(folderIt1->getSignature(),folderIt2->getSignature());
                
                //enregistrement dans compareTree
                this->FileChange.push_back(comp);
            }
            //iteration
            folderIt1->Next() ; folderIt2->Next();
            break;
        }
        default: cout<<"error HandleFileComparison: something went wrong";
    }
}




int CompareTree::GradientFilename(string filename1, string filename2){
    if(filename1 == filename2)      return EQUAL;
    else if(filename1 < filename2)  return SMALLER;
    else  return BIGGER;
}

bool CompareTree::checkSignature(string signature1, string signature2){
    return signature1 == signature2;
}


void CompareTree::equalise(FolderIterator *folderIt1, FolderIterator *folderIt2){
    while(folderIt1->getToken()!="[FOLDER]" || folderIt2->getToken()!="[FOLDER]"){
        if(folderIt1->getToken()=="[FILE]"){ 
            //initialisation
            CompareFile comp = CompareFile("[-]",folderIt1->getFilename(),folderIt1->getSignature());
            //analyse des differences
            comp.compareLines(folderIt1->getSignature(),"");
            //enregistrement
            this->FileChange.push_back(comp);
            //iteration
            folderIt1->Next();

        }
   else if(folderIt2->getToken()=="[FILE]"){
            //initialisation
            CompareFile comp= CompareFile("[+]",folderIt2->getFilename(),folderIt2->getSignature());
            //enregistrement dans compareTree
            this->FileChange.push_back(comp);
            //iteration
            folderIt2->Next();
        }
    }

}

//--------------------------CompareFile

CompareFile::CompareFile(string stat,string file, string sign): status(stat), filename(file), signature(sign) {}

void CompareFile::compareLines(std::string path ,std::string path2){
    //initialisation
    cout<<"in compare lines\n";
    FileIterator *it1 = new FileIterator(path);
    FileIterator *it2 = new FileIterator(path2);

    while(it1->Next() | it2->Next()){

        if(it1->getLine() == it2->getLine()) continue;
        lineChanged.push_back(createString(it1->getIndex(), it1->getLine(), it2->getIndex(), it2->getLine()) );
    } 
};
// void CompareFile::createPath(std::string path){
 
//     return "./.garden/"+
// }


std::string CompareFile::createString(int index1,std::string line1,int index2, std::string line2){
    return to_string(index1) + " [-] "+ ((line1.size()==NULL) ? " ":line1) + "\n"+
           to_string(index2) + " [+] "+ ((line2.size()==NULL) ? " ":line2) + "\n";
}
