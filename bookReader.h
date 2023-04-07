#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "book.h"

class BookReader{
    private:
        std::ifstream file_;
    public:
        BookReader(const std::string& filename);
        ~BookReader();
        Book getBook();
};