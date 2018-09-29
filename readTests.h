#ifndef READ_TESTS_H
#define READ_TESTS_H

#include <string>
#include <sstream>
#include <fstream>
#include "normalizationTestCase.h"

std::vector<normalizationTestCase> processTestLine(const std::string& input);
normalizationTestCase proccessTestCase(const std::string& input);
std::vector<normalizationTestCase> readTests();

#endif // READ_TESTS_H
