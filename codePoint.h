#ifndef CODEPOINT_H
#define CODEPOINT_H

#include <ostream>
#include <vector>
#include <sstream>
#include <string>

class codePoint
{
public:
    codePoint(const unsigned long& input);
    std::string toUTF8()const;
    friend std::ostream& operator<<(std::ostream& out, const codePoint& input);
private:
    unsigned long m_data;
};

std::vector<codePoint> makeCodepointSequence(std::vector<std::string> input);

#endif // CODEPOINT_H
