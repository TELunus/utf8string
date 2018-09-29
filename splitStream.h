#ifndef SPLIT_STREAM_H
#define SPLIT_STREAM_H

#include <vector>
#include <string>
#include <istream>

std::vector<std::string> splitStream(std::istream& input, char delimiter = '\n');
std::vector<std::string> splitString(const std::string& input, char delimiter = '\n');

#endif // SPLIT_STRING_H
