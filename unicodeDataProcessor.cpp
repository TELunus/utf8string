#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <fstream>

std::vector<std::string> splitStream(std::istream& input,char delimiter = '\n')
{
    std::vector<std::string> segments;
    std::string segment;
    while(std::getline(input,segment,delimiter))
    {
        segments.push_back(segment);
    }
    return segments;
}

std::vector<std::string> splitString(const std::string& input, char delimiter = '\n')
{
    std::stringstream stream(input);
    return splitStream(stream,delimiter);
}

class codepoint
{
public:
    codepoint()
    {
        //
    }
    codepoint(std::string input)
    {
        std::stringstream converter(input);
        converter<<std::hex;
        converter>>m_data;
    }
    std::ostream& write(std::ostream& out)const
    {
        out.write((char const*)&m_data,sizeof(m_data));
        return out;
    }
    friend std::ostream& operator<<(std::ostream& out, const codepoint& input);
private:
    uint32_t m_data;
};

std::ostream& operator<<(std::ostream& out, const codepoint& input)
{
    out<<input.m_data;
    out<<' ';
    return out;
}

class codeSequence
{
public:
    codeSequence()
    {
        //
    }
    codeSequence(std::string input)
    {
        auto points = splitString(input,' ');
        for(auto i=points.begin();i!=points.end();i++)
        {
            const std::string& point = *i;
            if(point.length()>0&&point.at(0)!='<')
            {
                m_data.push_back(codepoint(point));
            }
        }
    }
    unsigned long length()const
    {
        return m_data.size();
    }
    std::ostream& write(std::ostream& out)const
    {
        for(unsigned char i = 0; i < 4; i++)
        {
            if(length()>i)
            {
                m_data.at(i).write(out);
            }
            else
            {
                uint32_t zero = 0;
                out.write((char const *) &zero,sizeof(zero));
            }
        }
        return out;
    }
    friend std::ostream& operator<<(std::ostream& out, const codeSequence& input);
private:
    std::vector<codepoint> m_data;
};

std::ostream& operator<<(std::ostream& out, const codeSequence& input)
{
    for(auto i=input.m_data.begin();i!=input.m_data.end();i++)
    {
        const codepoint& point = *i;
        out<<point;
    }
    out<<"length="<<input.length()<<", ";
    return out;
}

class unicodeLine
{
public:
    unicodeLine(std::string input)
    {
        auto fields = splitString(input,';');
        m_codeValue = codepoint(fields.at(0));
        std::stringstream converter(fields.at(3));
        converter<<std::dec;
        converter>>m_combiningClass;
        if((fields.at(5).length()>0)&&(fields.at(5).at(0) == '<'))
        {
            m_formatingDecomosition = true;
        }
        else
        {
            m_formatingDecomosition = false;
        }
        m_decompositionSequence = codeSequence(fields.at(5));
    }
    std::ostream& write(std::ostream& out)const
    {
        if(m_combiningClass>0||(m_decompositionSequence.length()&&(!m_formatingDecomosition)))
        {
            m_codeValue.write(out);
            out.write((char const*)&m_combiningClass,sizeof(m_combiningClass));
            m_decompositionSequence.write(out);
            out.write("<(^__^)>",8);
        }
        return out;
    }
    friend std::ostream& operator<<(std::ostream& out, const unicodeLine& input);
private:
    codepoint m_codeValue;
    uint32_t m_combiningClass;
    codeSequence m_decompositionSequence;
    bool m_formatingDecomosition;
};

std::ostream& operator<<(std::ostream& out, const unicodeLine& input)
{
    if(input.m_combiningClass>0||(input.m_decompositionSequence.length()&&(!input.m_formatingDecomosition)))
    {
        out<<"U+"<<std::hex;
        out<<input.m_codeValue;
        out<<", C:"<<std::dec;
        out<<input.m_combiningClass;
        out<<", map:"<<std::hex;
        out<<input.m_decompositionSequence;
        out<<std::endl;
    }
    return out;
}

class unicodeFile
{
public:
    unicodeFile(std::string fileName)
    {
        std::ifstream file(fileName);
        std::vector<std::string> lines = splitStream(file);
        for(auto i=lines.begin();i!=lines.end();i++)
        {
            const std::string& line = *i;
            m_data.push_back(unicodeLine(line));
        }
    }
    std::ostream& write(std::ostream& out)const
    {
        for(auto i=m_data.begin();i!=m_data.end();i++)
        {
            const unicodeLine& line = *i;
            line.write(out);
        }
        return out;
    }
    friend std::ostream& operator<<(std::ostream& out, const unicodeFile& input);
private:
    std::vector<unicodeLine> m_data;
};

std::ostream& operator<<(std::ostream& out, const unicodeFile& input)
{
    for(auto i=input.m_data.begin();i!=input.m_data.end();i++)
    {
        const unicodeLine& line = *i;
        out<<line;
    }
    return out;
}

int main()
{
    unicodeFile data("./unicode/UnicodeData.txt");
    std::ofstream processed("./unicode.hex",std::ofstream::trunc|std::ofstream::binary|std::ofstream::out);
    data.write(processed);
    processed.close();
    std::cout<<data<<std::endl;
    return 0;
}
