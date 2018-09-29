#include "utf8string.h"
#include "gtest/gtest.h"
#include "readTests.h"
#include <iostream>

TEST(comparisons, AEqualsA)
{
    utf8string A1("A");
    utf8string A2("A");
    EXPECT_TRUE(A1==A2);
    EXPECT_TRUE(A2==A1);
    EXPECT_FALSE(A1!=A2);
    EXPECT_FALSE(A2!=A1);
    EXPECT_FALSE(A1<A2);
    EXPECT_FALSE(A2<A1);
    EXPECT_FALSE(A1>A2);
    EXPECT_FALSE(A2>A1);
    EXPECT_TRUE(A1<=A2);
    EXPECT_TRUE(A2<=A1);
    EXPECT_TRUE(A1>=A2);
    EXPECT_TRUE(A2>=A1);
}

TEST(comparisons, ALessThanB)
{
    utf8string A("A");
    utf8string B("B");
    EXPECT_FALSE(A==B);
    EXPECT_FALSE(B==A);
    EXPECT_TRUE(A!=B);
    EXPECT_TRUE(B!=A);
    EXPECT_TRUE(A<B);
    EXPECT_FALSE(B<A);
    EXPECT_FALSE(A>B);
    EXPECT_TRUE(B>A);
    EXPECT_TRUE(A<=B);
    EXPECT_FALSE(B<=A);
    EXPECT_FALSE(A>=B);
    EXPECT_TRUE(B>=A);
}

TEST(comparisons, unicodeConformance)
{
    std::vector<normalizationTestCase> tests = readTests();
    for(auto i = tests.begin();i!=tests.end();i++)
    {
        const normalizationTestCase& currentTestCase = *i;
        EXPECT_TRUE(currentTestCase());
        //std::cout<<currentTestCase<<std::endl;
        //system("PAUSE");
    }
}

void createUTF8String(const char input[])
{
    utf8string testString(input);
}

TEST(validation, noInitial01)
{
    const char A[] = {(char)0b10110010,(char)0b01101001,0};
    const char B[] = {'A',(char)0b10110010,(char)0b01101001,0};
    EXPECT_ANY_THROW(createUTF8String(A));
    EXPECT_ANY_THROW(createUTF8String(B));
}

TEST(validation, nothingOutsideValidRanges)
{
    const char case1[] = {(char)0xE0,(char)0x9F,(char)0x80,0};
    const char case2[] = {(char)0xED,(char)0xA0,(char)0x80,0};
    const char case3[] = {(char)0xF0,(char)0x80,(char)0xBF,(char)0xBF,0};
    const char case4[] = {(char)0xF4,(char)0x90,(char)0x80,(char)0x80,0};
    EXPECT_ANY_THROW(createUTF8String(case1));
    EXPECT_ANY_THROW(createUTF8String(case2));
    EXPECT_ANY_THROW(createUTF8String(case3));
    EXPECT_ANY_THROW(createUTF8String(case4));
}

TEST(validation, acceptValidCodepoints)
{
    const char case1[]="A";
    const char case2[]={(char)0xDF,(char)0xBF,0};
    const char case3[]={(char)0xE0,(char)0xA0,(char)0x80,0};
    const char case4[]={(char)0xED,(char)0x9F,(char)0xBF,0};
    const char case5[]={(char)0xF0,(char)0x90,(char)0x80,(char)0x80,0};
    const char case6[]={(char)0xF4,(char)0x8F,(char)0xBF,(char)0xBF,0};
    const char case7[]="Ḋ";

    EXPECT_NO_THROW(createUTF8String(case1));
    EXPECT_NO_THROW(createUTF8String(case2));
    EXPECT_NO_THROW(createUTF8String(case3));
    EXPECT_NO_THROW(createUTF8String(case4));
    EXPECT_NO_THROW(createUTF8String(case5));
    EXPECT_NO_THROW(createUTF8String(case6));
    EXPECT_NO_THROW(createUTF8String(case7));
}

int main(int argc, char* argv[])
{
    system("chcp 65001");
    ::testing::InitGoogleTest(&argc, argv);
    //std::string characterTest = "Ḋ";
    //unsigned int first = (unsigned char) characterTest.at(0);
    //unsigned int second = (unsigned char) characterTest.at(1);
    //unsigned int third = (unsigned char) characterTest.at(2);
    //std::cout<<"char = : "<<std::hex<<first<<", "<<second<<", "<<third;
    //std::cout<<tests;
    return RUN_ALL_TESTS();
}
