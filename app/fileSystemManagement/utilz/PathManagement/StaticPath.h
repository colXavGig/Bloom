#pragma once
#include "../../../paths/GardenPath.h"

namespace staticpath{

    class _staticPath{
        private:
        static std::unique_ptr<GardenPath> _staticpath;

        public:
            static void SET(std::unique_ptr<GardenPath> p);
            static fs::path _GARDEN();
            static fs::path _INDEX();
            static fs::path _TAG();
            static fs::path _TAGROOT(std::string string);
            static fs::path _SEED();
            static fs::path _SEEDROOT(std::string string);
            static fs::path _TESTPATH();

    };
}