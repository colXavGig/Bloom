#include "HashNode.h"

#include "../../processes/Hashing.h"

using namespace std;
    //////////////////////////////
    ///        HASHNODE        ///
    //////////////////////////////

    void HashNode::init(
        const fs::path &path,
        const string filename,
        int type
    ) {
        value = new HashNode_s;
        setPath(path);
        value->filename = (char *)filename.data();
        value->type = type;
        value->content = new HashNode_content;
    }

    HashNode_s *HashNode::getStructValue(){
      return value;
    }

    //////////////////////////////
    ///        FILENODE        ///
    //////////////////////////////

    void FileNode::setContent(char *content){
        value->content->file_content = content;
    }

    void FileNode::setContent(HashNode_content* content){
      setContent(content->file_content);
    }

    //////////////////////////////
    ///        FOLDERNODE      ///
    //////////////////////////////

    void FolderNode::setContent(FolderNode_content* content){
      value->content->folder_contents = content;
    }

    void FolderNode::setContent(HashNode_content* content){
      setContent(content->folder_contents);
    }

    string FolderNode:: fullhash(){
        //mettre toute les signature dans 1 str;
        stringstream ss;
        for(FileNode *file : this->getFiles()){
            if(!file->getSignature().empty())
                ss<<file->getSignature();
        }
        for(FolderNode *folder : this->getFolders()){
            if(!folder->getSignature().empty())
                ss<<folder->getSignature();
        }
        char buffer[41];
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(ss.str().c_str()), ss.str().size(), hash);
        HtoS(hash, buffer);
        return string(buffer);
    }

    //setters
    /*
     */
    void FolderNode::setSignature(){
        this->value->signature = fullhash().data();
    }

    /*
     */
    void FileNode::setSignature(){
        char buffer[41];
        fileHash(getPath().string().c_str(),buffer);
        this->value->signature = string(buffer).data();
    }
   
    
