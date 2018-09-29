#include "splitStream.h"
#include <sstream>
#include <iostream>

std::vector<std::string> splitStream(std::istream& input,char delimiter)
{
    std::vector<std::string> segments;
    std::string segment;
    while(std::getline(input,segment,delimiter))
    {
        segments.push_back(segment);
    }
    return segments;
}

std::vector<std::string> splitString(const std::string& input, char delimiter)
{
    std::stringstream stream(input);
    return splitStream(stream,delimiter);
}
