#include "GardenIterator.h"

content_token convert(string const &str){
    if(str == "[FOLDER]") return FOLDERS;
    else if(str == "[FILE]") return FILES;
    else return INCOMPATIBLE;
}

fs::path Searcher::findpath(string hash){
    string folder="",file="";
    for(int i = 0; i<hash.size();i++){
        if(i < 2){folder+=hash[i];continue;}
        file+=hash[i];
    }
    fs::path temp=this->gardenPath;
    temp/=folder;
    temp/=file;
    return temp;
}

void Searcher::rebuild(fs::path rootNode,fs::path parentnode){
    ifstream ifs;
    string token;
    
    ifs.open(rootNode);
    
    while(!ifs.eof()){
        string line; 
        token="";
        ifs>>token;
        if(convert(token) == INCOMPATIBLE) break; 
        getline(ifs,line);
        process(convert(token),line,parentnode);
    }
}



void Searcher::process(content_token token, string line, fs::path path){
    string signature="",name="";
    getlineData(line,signature,name);
     
   
    if(token == FILES){
        cout<<"comparing file: "<<name<<"\n";
        cout<<"rebuilding file: "<<name<<"\n";
        FileBuilder builder =  FileBuilder(".\\testingReader");
        builder.buildfile(this->findpath(signature),path/name);
    }
    else if(token == FOLDERS){
        cout<<"rebuilding folder: "<<name<<"\n";
        FileBuilder builder =  FileBuilder(".\\testingReader");
        builder.buildfolder(this->findpath(signature),path/name);
        signature+=".txt";
        this->rebuild(this->findpath(signature),path/name);
    }
}

void compareFile(FileNode* projectNode, FileNode gardenNode){




}




void getlineData(const string &line, string &hash, string &name){
    
    int i=0;
    while(line[++i]==' ' && i < line.length());

    while(i < line.length() && line[i] != ' ') hash += line[i++];       
    i++;
    while(i < line.length()) name += line[i++];
}