#include "utf8string.h"
#include <cstdint>

extern uint8_t unicode[]      asm("_binary_unicode_hex_start");
extern uint8_t unicode_size[] asm("_binary_unicode_hex_size");
extern uint8_t unicode_end[]  asm("_binary_unicode_hex_end");

utf8string::utf8string(char const *input)
{
    //ctor
}

utf8string::~utf8string()
{
    //dtor
}

bool utf8string::operator<(const utf8string& other) const
{
    return false;
}

bool utf8string::operator>(const utf8string& other) const
{
    return other<*this;
}

bool utf8string::operator<=(const utf8string& other) const
{
    return !(*this<other);
}

bool utf8string::operator>=(const utf8string& other) const
{
    return !(other<*this);
}

bool utf8string::operator==(const utf8string& other) const
{
    return (!(other<*this))&&(!(*this<other));
}

bool utf8string::operator!=(const utf8string& other) const
{
    return (other<*this)||(*this<other);
}
