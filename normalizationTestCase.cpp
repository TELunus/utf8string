#include "normalizationTestCase.h"
#include "splitStream.h"

normalizationTestCase::normalizationTestCase(const std::string& input,const std::string& normalForm):
    m_input(makeCodepointSequence(splitString(input,' '))),
    m_normalForm(makeCodepointSequence(splitString(normalForm,' ')))
{
    std::vector<codePoint> source();

    //
}

bool normalizationTestCase::operator()()const
{
    const utf8string input = sequenceToString(m_input);
    const utf8string normal = sequenceToString(m_normalForm);
    bool inputEqualsNormal = check(input,normal);
    bool normalEqualsInput = check(normal,input);
    return inputEqualsNormal&&normalEqualsInput;
}
    normalizationTestCase::check(const utf8string& A, const utf8string& B)
    {
        bool result = true;
        result = result && (A==B);
        result = result && (A>=B);
        result = result && (A<=B);
        result = result && (!(A!=B));
        result = result && (!(A<B));
        result = result && (!(A>B));
        return result;
    }

    utf8string normalizationTestCase::sequenceToString(const std::vector<codePoint>& sequence)
    {
        std::stringstream accumulator;
        for(auto i=sequence.begin();i!=sequence.end();i++)
        {
            const codePoint& currentPoint = *i;
            accumulator<<currentPoint.toUTF8();
        }
        return utf8string(accumulator.str().c_str());
    }

std::ostream& operator<<(std::ostream& out, const normalizationTestCase& input)
{
    out<<"input: '";
    for(auto i = input.m_input.begin(); i != input.m_input.end(); i++)
    {
        out<<*i<<" ";
    }
    out<<"', normal form: '";
    for(auto i = input.m_normalForm.begin(); i != input.m_normalForm.end(); i++)
    {
        out<<*i<<" ";
    }
    out<<"'"<<std::endl;
    return out;
}
