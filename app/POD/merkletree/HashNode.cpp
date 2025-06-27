#include "HashNode.h"
#include <cstring>
#include <sstream>

#include "../../utils/hashing/c_hashing.h"

#define LOGGER_STATUS LOGGER_INACTIVE
#include "../../debugging.h"

using namespace std;

    //////////////////////////////
    ///        HASHNODE        ///
    //////////////////////////////

HashNode::~HashNode() {
  delete this->value->path;
  delete this->value->filename;
  delete this->value->signature;
  delete this->value;
}

void HashNode::init(
    const fs::path &path,
    const string filename,
    int type
) {
    LOG("Initializing HashNode");
    value = new HashNode_s;

    LOG(("Path is " + path.string()).c_str());
    setPath(path);
    LOG(("value->path: " + (string)value->path).c_str());

    LOG(("filename: " + filename).c_str());
    setFilename(filename);
    LOG(("value->filename: " + (string)value->filename).c_str());

    LOG(("type: " + to_string(type)).c_str());
    value->type = type;
    LOG(("value->type: " + to_string(value->type)).c_str());


    value->content = new HashNode_content;

}

HashNode_s *HashNode::get_struct_value(){
  return value;
}

void HashNode::setPath(fs::path path) {
    value->path = new char[path.string().size() + 1];
    strcpy( this->value->path , path.string().data() );
}

void HashNode::setFilename(string filename) {
  value->filename = new char[filename.size() + 1];
  strcpy( this->value->filename , filename.data() );
}

void HashNode::setSignature(string signature) {
  value->signature = new char[signature.size() + 1];
  strcpy( this->value->signature , signature.data() );
}

    //////////////////////////////
    ///        FILENODE        ///
    //////////////////////////////

    void FileNode::setContent(string content){
        value->content->file_content = new char[content.size() + 1];
        strcpy(value->content->file_content, content.data() );
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
            if(!file->get_signature().empty())
                ss<<file->get_signature();
        }
        for(FolderNode *folder : this->getFolders()){
            if(!folder->get_signature().empty())
                ss<<folder->get_signature();
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
    void FolderNode::generateSignature(){
        LOG("Generating signature...");
        this->value->signature = new char[41];
        LOG("Memory allocated for signature");
        strcpy(this->value->signature, fullhash().data());
        LOG(("Signature: " + this->getSignature()).c_str());
    }

    /*
     */
    void FileNode::generateSignature(){
        this->value->signature = new char[41];
        fileHash(get_path().string().c_str(),value->signature);
    }
   
    
