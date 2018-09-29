#include "readTests.h"
#include "splitStream.h"
#include <vector>

std::vector<normalizationTestCase> readTests()
{
    const std::string dataPath("./unicode/NormalizationTest.txt");
    std::vector<normalizationTestCase> result;
    std::ifstream dataFile(dataPath);
    std::vector<std::string> segments = splitStream(dataFile);
    for(auto i = segments.begin();i != segments.end();i++)
    {
        std::vector<normalizationTestCase> insertion = processTestLine(*i);
        result.insert(result.end(),insertion.begin(),insertion.end());
    }
    return result;
}

std::vector<normalizationTestCase> processTestLine(const std::string& input)
{
    std::vector<normalizationTestCase> result;
    const char commentDelim = '#';
    std::string preComment = input.substr(0,input.find_first_of(commentDelim));
    if(preComment.length() > 0)
    {
        if(preComment.at(0) != '@')
        {
            result.push_back(proccessTestCase(preComment));
        }
    }
    return result;
}

normalizationTestCase proccessTestCase(const std::string& input)
{
    const char delimiter = ';';
    std::stringstream inputStream(input);
    std::vector<std::string> segments = splitStream(inputStream,delimiter);
    return normalizationTestCase(segments.at(0),segments.at(2));
}
