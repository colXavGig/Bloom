#include "Juxtapose.h"

void Juxtapose::parseMetadata(const char *sign1, const char *sign2,std::string p){
    //li le folder file et sort les folders et files
    fillqueues(parentQueue, path.getFlowerPath(sign1).string().c_str());
    fillqueues(headQueue,   path.getFlowerPath(sign2).string().c_str());
    parsefile(p);
    parsefolder(p);
}

/**
 * Gerer la queue de folder
 * 
 */
void Juxtapose::parsefolder(std::string p){  
    while (true) {
        if (parentQueue.folderQueue.empty() && headQueue.folderQueue.empty()) {
            break;
        }
    
        bool flowParent = !parentQueue.folderQueue.empty();
        bool flowHead = !headQueue.folderQueue.empty();
    
        MetaDataFOS_S pf = MetaDataFOS_S_Invalid();
        MetaDataFOS_S hf = MetaDataFOS_S_Invalid();
    
        if (flowParent) pf = parentQueue.folderQueue.front();
        if (flowHead) hf = headQueue.folderQueue.front();
    
        if (!flowParent) { headQueue.folderQueue.pop(); continue;}
        if (!flowHead)   { parentQueue.folderQueue.pop(); continue;}
    
        int cmp = strcmp(pf.fosname, hf.fosname);   
        if (cmp > 0) { headQueue.folderQueue.pop(); continue;}
        if (cmp < 0) { parentQueue.folderQueue.pop(); continue;}
    
        if (strcmp(pf.signature, hf.signature) != 0) {
            parseMetadata(pf.signature, hf.signature, p + std::string(pf.fosname));
        }
    
        parentQueue.folderQueue.pop();
        headQueue.folderQueue.pop();
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
        MetaDataFOS_S pf = MetaDataFOS_S_Invalid();
        MetaDataFOS_S hf = MetaDataFOS_S_Invalid();

        if (flowParent) pf = parentQueue.fileQueue.front();
        if (flowHead)   hf = headQueue.fileQueue.front();  
        int cmp = strcmp(pf.fosname, hf.fosname); 

        if (cmp > 0) {
            compare(path.getFlowerPath(pf.signature).string().c_str(), 
                    " ",
                    "[-]",
                    pf.fosname,
                    p);
                    headQueue.fileQueue.pop();
            continue;
        }
        if (cmp < 0) {
            compare(" ", 
                    path.getFlowerPath(hf.signature).string().c_str(),
                    "[+]",
                    hf.fosname,
                    p);
                    parentQueue.fileQueue.pop();
            continue;
        }
        
        if (strcmp(pf.signature, hf.signature) != 0) {
            compare(path.getFlowerPath(pf.signature).string().c_str(), 
                    path.getFlowerPath(hf.signature).string().c_str(),
                    "[~]",
                    pf.fosname,
                    p);
        }
        parentQueue.fileQueue.pop();
        headQueue.fileQueue.pop();
    }
}

void Juxtapose::compare(const char *sign1, const char *sign2,const char *type,const char *filename, std::string p){
    bool flowParent = true;
    bool flowHead   = true;

    FILE *parent  = fopen(sign1,"r");
    if (!parent) {
        fclose(parent); 
        flowParent = false;
    }
    FILE *head  = fopen(sign2,"r");
    if (!head) {
        fclose(head); 
        flowHead   = false;
    }
    char pstr[1024];
    char cstr[1024];
    int lineNb=0;
    FILE_S *file = FILE_createFile(type, filename, p.c_str());
    while(true){

        flowParent = (fgets(pstr, sizeof(pstr), parent) != NULL);
        flowHead   = (fgets(cstr, sizeof(cstr), head)   != NULL);

        if(flowParent= false) pstr[0]='\0';
        if(flowHead= false)   cstr[0]='\0';

        if(!flowParent && !flowHead){lineNb++; break;} 

        if(strcmp(pstr,cstr)!=0){
            LINE * line = LINE_init(lineNb,pstr,cstr);  
            FILE_AddLine(file, line);
        }
        lineNb++;
    }
    FILE_READ(file);
    root.add(file);
    fclose(parent);
    fclose( head );
}




void Juxtapose::fillqueues(FOS_MD_QUEUE& fos, const char *sign1){

    FILE *parent  = fopen(sign1,"r");
    if (!parent) {
        fclose(parent); 
        throw std::runtime_error("Failed to open file: parent");
    }

    std::vector<MetaDataFOS_S> tempVec;
    char parentOut[200];
    while((fgets(parentOut, sizeof(parentOut), parent) != NULL)){
        MetaDataFOS_S md = MetaDataFOS_init(parentOut); 
        tempVec.push_back(md);
    }

    std::sort(tempVec.begin(), tempVec.end(), [](const MetaDataFOS_S& a, const MetaDataFOS_S& b) {
        return a.fosname < b.fosname;
    });

    for (const auto& elem : tempVec) {
        fos.addToQueue(elem);
    }
}









