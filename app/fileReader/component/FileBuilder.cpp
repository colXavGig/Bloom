#include "FileBuilder.h"

void FileBuilder::buildfile(fs::path source,fs::path destination){  
    if(!fs::exists(destination)){
        fs::copy(source,destination);
       
    }else {
        cout<<"file already exists!!!"<<destination<<"\n";
    }
        
}
void FileBuilder::buildfolder(fs::path source,fs::path destination){  
    if(!fs::exists(destination)){
        fs::create_directory(destination);
    }else {
        cout<<"folder already exists!!!"<<destination<<"\n";
    }
        
}