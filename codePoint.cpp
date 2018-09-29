#include "codePoint.h"
#include <iostream>

codePoint::codePoint(const unsigned long& input):m_data(input)
{
    //
}

std::string codePoint::toUTF8()const
{
    const char lowByteMask     = 0b00111111;
    const char lowBytePrefix   = 0b10000000;
    const char highByte2Prefix = 0b11000000;
    const char highByte2Mask   = 0b00011111;
    const char highByte3Prefix = 0b11100000;
    const char highByte3Mask   = 0b00001111;
    const char highByte4Prefix = 0b11110000;
    const char highByte4Mask   = 0b00000111;

    const unsigned long oneByteThreshold =         0b01111111;
    const unsigned long twoByteThreshold =   0b0000011111111111;
    const unsigned long threeByteThreshold = 0b1111111111111111;

    const char lastByte = m_data;
    const char SecondLastByte = m_data/(1<<(6));
    const char ThirdLastByte = m_data/(1<<(12));
    const char FourthLastByte = m_data/(1<<(18));

    std::string result;
    //std::cout<<"U+"<<std::hex<<m_data<<std::endl;
    if(m_data <= oneByteThreshold)//single byte codepoint
    {
        //std::cout<<"one byte"<<std::endl;
        char byte = lastByte;
        result.append({byte,0});
    }
    else if(m_data <= twoByteThreshold)//two byte codepoint
    {
        //std::cout<<"two bytes"<<std::endl;
        char lowByte = lowBytePrefix | (lastByte & lowByteMask);
        char highByte = highByte2Prefix | (SecondLastByte & highByte2Mask);
        result.append({highByte,lowByte,0});
    }
    else if(m_data <= threeByteThreshold)//three byte codepoint
    {
        //std::cout<<"three bytes"<<std::endl;
        char lowByte1 = lowBytePrefix | (lastByte & lowByteMask);
        char lowByte2 = lowBytePrefix | (SecondLastByte & lowByteMask);
        char highByte = highByte3Prefix | (ThirdLastByte & highByte3Mask);
        long first = (char)highByte;
        //std::cout<<"First: "<<std::hex<<(first);
        result.append({highByte,lowByte2,lowByte1,0});
    }
    else//four byte codepoint
    {
        //std::cout<<"four bytes"<<std::endl;
        char lowByte1 = lowBytePrefix | (lastByte & lowByteMask);
        char lowByte2 = lowBytePrefix | (SecondLastByte & lowByteMask);
        char lowByte3 = lowBytePrefix | (ThirdLastByte & lowByteMask);
        char highByte = highByte4Prefix | (FourthLastByte & highByte4Mask);
        result.append({highByte,lowByte3,lowByte2,lowByte1,0});
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const codePoint& input)
{
    out<<"U+"<<std::hex<<input.m_data;
    //out<<": \""<<input.toUTF8()<<"\"";
    //out<<", length="<<input.toUTF8().length();
    //system("PAUSE");
    return out;
}

std::vector<codePoint> makeCodepointSequence(std::vector<std::string> input)
{
    std::vector<codePoint> result;
    for(auto i = input.begin();i != input.end(); i++)
    {
        std::stringstream converter;
        unsigned long point;
        converter<<std::hex<<*i;
        converter>>point;
        result.push_back(codePoint(point));
    }
    return result;
}
