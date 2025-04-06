#include<iostream>
#include <vector>
#include "../../fileReader/FileIterator.h"
#include "../../fileReader/FolderIterator.h"
#include "../../paths/GardenPath.h"
using namespace std;
/*
Algo simple une iteration lineaire avec une gradient il a pour but de comparer deux tags
et d'afficher une legende

    Legend: 
           [-] == deleted File:
             condition:  
                 Commit n-1.filename  < Commit n.filename
             action:
                --> Write  [-] filename hash

           [+] == added File:
             condition:
                 Commit n-1.filename  > Commit n.filename
             action:
                --> Write  [+] filename hash 

           [~] == changed occured in file:
             condition:
                 Commit n-1.filename == Commit n.filename  && Commit n-1.Signature != Commit n-1.Signature
             action:
                --> Write  [~] filename hash;
                --> compare the file line;

            no recording:
             condition:
                 Commit n-1.filename == Commit n.filename  && Commit n-1.Signature == Commit n-1.Signature
             action:
                --> ignore

*/
class CompareFile;

class CompareTree{
    private:
        GardenPath path = GardenPath(".");

        vector<CompareFile > FileChange;
        std::string createString(int index, std::string line1, int index2, std::string line2);
        
        int GradientFilename(string filename1,string filename2); 
        bool checkSignature(string signature1, string signature2);
        void HandleFileComparison(int resultat, FolderIterator *folderIt1, FolderIterator *folderIt);
        void equalise(FolderIterator *folderIt1, FolderIterator *folderIt2);
    public:  
        void compareFolder(string path, string path2);   
        void FileManagement(FolderIterator *it1, FolderIterator *it2);
        void printChange();
};

class CompareFile{
    private:
        string status;
        string filename;
        string signature;
        vector<std::string> lineChanged;
    public:
        CompareFile(string status,string filename, string signature);
        void compareLines(string path, string path2);
        std::string createString(int index, std::string line1, int index2, std::string line2);

        friend ostream& operator<<(ostream& os, const CompareFile& comp) {
            os << comp.status << " ";
            os << comp.filename << " ";
            os << comp.signature << "\n";
            os << "Line Changes:\n";
            for (const auto& line : comp.lineChanged) {
                os << line << "\n";
            }
            return os;
        }
};