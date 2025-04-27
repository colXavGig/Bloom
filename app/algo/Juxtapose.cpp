#include "Juxtapose.h"

void Juxtapose::parseMetadata(const char *sign1, const char *sign2,std::string p){
    //li le folder file et sort les folders et files
    std::string p1 = path.getFlowerPath(sign1).string();
    std::string p2 = path.getFlowerPath(sign2).string();

    fillqueues(parentQueue, p1.c_str());
    fillqueues(headQueue,   p2.c_str());


    std::cout <<"about to parse file\n";
    parsefile(p);
    std::cout <<"about to parse folder\n";
    parsefolder(p);
}

/**
 * Gerer la queue de folder
 * 
 */
void Juxtapose::parsefolder(std::string p){  
    while (true) {


        if (parentQueue.folderQueue.empty() && headQueue.folderQueue.empty())
            break;
        
    
        bool flowParent = !parentQueue.folderQueue.empty();
        bool flowHead = !headQueue.folderQueue.empty();
    
        MetaDataFOS_S pf = (flowParent) ?  parentQueue.folderQueue.front() : MetaDataFOS_S_NULLSTATE();
        MetaDataFOS_S hf = (flowHead) ?  headQueue.folderQueue.front()   : MetaDataFOS_S_NULLSTATE(); 
    
        if (!flowParent) { headQueue.folderQueue.pop(); continue;}
        if (!flowHead)   { parentQueue.folderQueue.pop(); continue;}
    
        int cmp = safe_strcmp(pf.fosname, hf.fosname);   
        if (cmp > 0) { headQueue.folderQueue.pop(); continue;}
        if (cmp < 0) { parentQueue.folderQueue.pop(); continue;}
    
        if (strcmp(pf.signature, hf.signature) != 0) {
            parseMetadata(pf.signature, hf.signature, p +"/"+ std::string(pf.fosname));
        }
    
        parentQueue.folderQueue.pop();
        headQueue.folderQueue.pop();
    }
}





void Juxtapose::fillqueues(FOS_MD_QUEUE& fos, const char *sign1){

    FILE *parent  = fopen(sign1,"r");
    if (!parent) {
        return;
    }

    std::vector<MetaDataFOS_S> tempVec;
    char parentOut[200];
    while((fgets(parentOut, sizeof(parentOut), parent) != NULL)){
        MetaDataFOS_S md = MetaDataFOS_init(parentOut); 
        tempVec.push_back(md);
    }
    fclose(parent);
    std::sort(tempVec.begin(), tempVec.end(), [](const MetaDataFOS_S& a, const MetaDataFOS_S& b) {
        return strcmp(a.fosname, b.fosname) < 0;
    });

    for (const auto& elem : tempVec) {
        fos.addToQueue(elem);
    }
}

/**
 * Gerer la queue de file
 * 
 * 
 */
void Juxtapose::parsefile(std::string p){
    printf("entering parsefile while loop\n");
    while (true) {

        if (parentQueue.fileQueue.empty() && headQueue.fileQueue.empty())
            break;

        bool flowParent = !parentQueue.fileQueue.empty();
        bool flowHead = !headQueue.fileQueue.empty();
        //initialisation; 
        MetaDataFOS_S pf = (flowParent) ?  parentQueue.fileQueue.front() : MetaDataFOS_S_NULLSTATE();
        MetaDataFOS_S hf = (flowHead) ?  headQueue.fileQueue.front()   : MetaDataFOS_S_NULLSTATE(); 

        int cmp = safe_strcmp(pf.fosname, hf.fosname); 

        if (cmp > 0) {
            std::cout<< "in cmp >0\n";
            compareSingleValidFile(&pf,false, p);
            parentQueue.fileQueue.pop();
            continue;
        }
        if (cmp < 0) {
            std::cout<< "in cmp <0";
            compareSingleValidFile(&hf,true, p);
            headQueue.fileQueue.pop();
            continue;
        }
        
        if (safe_strcmp(pf.signature, hf.signature) != 0) {
            std::cout<< "signature ==0";
            compareBothValidFiles(&pf,&hf, p);
        }
        headQueue.fileQueue.pop();
        parentQueue.fileQueue.pop();
    }

}

void Juxtapose::compareBothValidFiles(MetaDataFOS_S* pmd, MetaDataFOS_S* cmd,std::string  p) {

    FILE *fptr1 = fopen(path.getFlowerPath(pmd->signature).string().c_str(), "r");
    if(!fptr1)
        printf("invalide file path");

    FILE *fptr2 = fopen(path.getFlowerPath(cmd->signature).string().c_str(), "r");
    if(!fptr2)
        printf("invalide file path");
    char pstr[1024] = {0};
    char cstr[1024] = {0};
    int lineNb = 0;
    FILE_S *file = FILE_createFile(pmd->fostype,pmd->fosname, p.c_str()); 
    while (true) {
        bool flowParent = (fgets(pstr, sizeof(pstr), fptr1) != NULL);
        bool flowHead = (fgets(cstr, sizeof(cstr), fptr2) != NULL);

        if (!flowParent && !flowHead) {
            break;
        }

        if (!flowParent) pstr[0] = '\0';
        if (!flowHead)   cstr[0] = '\0';

        if (strcmp(pstr, cstr) != 0) {
            LINE* line = LINE_init(lineNb, pstr, cstr);
            FILE_AddLine(file, line);
        }

        lineNb++;
    }
    FILE_READ(file);
    fclose(fptr1);
    fclose(fptr2);
}



void Juxtapose::compareSingleValidFile(MetaDataFOS_S* md, bool isParent, std::string p) {
    FILE *fptr = fopen(path.getFlowerPath(md->signature).string().c_str(), "r");
    if(!fptr)
        printf("invalide file path");

    char buffer[1024] = {0};
    int lineNb = 0;
    FILE_S *file = FILE_createFile(md->fostype,md->fosname, p.c_str()); 


    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (isParent) {
            LINE* line = LINE_init(lineNb, buffer, "");
            FILE_AddLine(file, line);
        } else {
            LINE* line = LINE_init(lineNb, "", buffer);
            FILE_AddLine(file, line);
        }
        lineNb++;
    }
    FILE_READ(file);
    fclose(fptr);
}



