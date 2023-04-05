#include <sstream>
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc < 8){
        std::cerr << "Incorrect number of command line arguments - expected at least 7, got " << argc - 1 << std::endl;
        return 1;
    }
    return 0;
}