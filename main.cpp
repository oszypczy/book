#include <sstream>
#include <iostream>
#include <string>
#include "bookReader.h"

int main(int argc, char** argv){
    if (argc != 2) {
        std::cerr << "User must give one argument but: " << argc - 1 << "were given!" << std::endl;
        exit(1);
    }
    std::string fileName = argv[1];
    BookReader bookReader(fileName);
    Book book = bookReader.getBook();
    std::cout << book << std::endl;
    return 0;
}