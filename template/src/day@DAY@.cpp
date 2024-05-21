#include "../include/aocutils.h"

int main(int argc, char const *argv[])
{
    const std::string input_path{argc <= 1 ? "../input.txt" : argv[1]};
    const auto input =  aoc::parseFileAsStringVector(input_path);
    
    /*
        Code
    */
    
    return EXIT_SUCCESS;
}
