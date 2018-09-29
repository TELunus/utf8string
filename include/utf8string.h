#ifndef UTF8STRING_H
#define UTF8STRING_H

class utf8string;

class utf8string
{
    public:
        utf8string(char const *input);
        virtual ~utf8string();
        bool operator<(const utf8string& other) const;
        bool operator>(const utf8string& other) const;
        bool operator<=(const utf8string& other) const;
        bool operator>=(const utf8string& other) const;
        bool operator==(const utf8string& other) const;
        bool operator!=(const utf8string& other) const;

    protected:

    private:
};

#endif // UTF8STRING_H
