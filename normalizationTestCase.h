#ifndef NORMALIZATION_TEST_CASE_H
#define NORMALIZATION_TEST_CASE_H

#include <string>
#include <ostream>
#include <vector>

#include "codePoint.h"
#include "utf8string.h"

class normalizationTestCase
{
public:
    normalizationTestCase(const std::string& input,const std::string& normalForm);
    bool operator()()const;
private:
    std::vector<codePoint> m_input;
    std::vector<codePoint> m_normalForm;
    static check(const utf8string& A, const utf8string& B);
    static utf8string sequenceToString(const std::vector<codePoint>& sequence);
    friend std::ostream& operator<<(std::ostream& out, const normalizationTestCase& input);
};

#endif // NORMALIZATION_TEST_CASE_H
