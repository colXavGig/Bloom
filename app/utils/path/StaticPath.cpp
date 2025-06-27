#include "StaticPath.h"


namespace staticpath{
    std::unique_ptr<GardenPath> _staticPath::_staticpath = nullptr;
    
    void _staticPath::SET(std::unique_ptr<GardenPath> p) {
        _staticpath = std::move(p);
    };

    fs::path  _staticPath::_GARDEN(){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return _staticpath->getGardenPath();
    } 

    fs::path _staticPath::_INDEX(){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return _staticpath->getIndexFilepath();
    }

    fs::path _staticPath::_TAG(){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return _staticpath->getTagPath();
    }

    fs::path _staticPath::_TAGROOT(std::string string){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return _staticpath->getGardenTagPath(string);
    } 

    fs::path _staticPath::_SEED(){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return _staticpath->getSeedPath();
    } 

    fs::path _staticPath::_SEEDROOT(std::string string){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return _staticpath->getFlowerPath(string);
        }
    fs::path _staticPath::_TESTPATH(){
        if (!_staticpath) throw std::runtime_error("Static path not set.");
            return fs::path("./app/testing");
    }

};
