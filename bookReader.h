#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "book.h"

class BookReader{
    private:
        std::string fileName;
        std::ifstream file;
        void checkFile(std::string newFileName);
    public:
        BookReader(std::string filename);
        Book getBook();
};