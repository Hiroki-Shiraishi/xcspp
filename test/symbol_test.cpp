#include <gtest/gtest.h>
#include <xcspp/xcspp.hpp>

TEST(SymbolTest, ConstructWithNumberChar)
{
    // Numbers
    for (int i = 0; i < 10; ++i)
    {
        // Generate '0'--'9' character
        const char c = '0' + i;

        const xcspp::Symbol number(c);
        EXPECT_FALSE(number.isDontCare());
        EXPECT_EQ(number.value(), i);
        EXPECT_TRUE(number.matches(i));
        EXPECT_FALSE(number.matches(i + 1));
    }
}

TEST(SymbolTest, ConstructWithDontCareChar)
{
    // Don't Care
    const xcspp::Symbol dontCare('#');
    EXPECT_TRUE(dontCare.isDontCare());
    EXPECT_TRUE(dontCare.matches(0));
    EXPECT_TRUE(dontCare.matches(1));
}

TEST(SymbolTest, ConstructWithInt)
{
    for (int i = 0; i < 10; ++i)
    {
        const xcspp::Symbol number(i);
        EXPECT_FALSE(number.isDontCare());
        EXPECT_EQ(number.value(), i);
        EXPECT_TRUE(number.matches(i));
        EXPECT_FALSE(number.matches(i + 1));
    }
}

TEST(SymbolTest, CopyConstruct)
{
    const xcspp::Symbol one(1);
    const xcspp::Symbol oneClone(one);
    EXPECT_FALSE(oneClone.isDontCare());
    EXPECT_EQ(oneClone.value(), 1);
    EXPECT_TRUE(oneClone.matches(1));
    EXPECT_FALSE(oneClone.matches(0));
    EXPECT_EQ(one, oneClone);

    const xcspp::Symbol dontCare('#');
    const xcspp::Symbol dontCareClone(dontCare);
    EXPECT_TRUE(dontCareClone.isDontCare());
    EXPECT_TRUE(dontCareClone.matches(0));
    EXPECT_TRUE(dontCareClone.matches(1));
    EXPECT_EQ(dontCare, dontCareClone);
}

TEST(SymbolTest, SetValue)
{
    xcspp::Symbol symbol(1);
    EXPECT_FALSE(symbol.isDontCare());
    EXPECT_EQ(symbol.value(), 1);
    EXPECT_TRUE(symbol.matches(1));
    EXPECT_FALSE(symbol.matches(0));

    symbol.setValue(0);
    EXPECT_FALSE(symbol.isDontCare());
    EXPECT_EQ(symbol.value(), 0);
    EXPECT_TRUE(symbol.matches(0));
    EXPECT_FALSE(symbol.matches(1));

    symbol.setToDontCare();
    EXPECT_TRUE(symbol.isDontCare());
    EXPECT_TRUE(symbol.matches(0));
    EXPECT_TRUE(symbol.matches(1));

    symbol.setValue(1);
    EXPECT_FALSE(symbol.isDontCare());
    EXPECT_EQ(symbol.value(), 1);
    EXPECT_TRUE(symbol.matches(1));
    EXPECT_FALSE(symbol.matches(0));
}

TEST(SymbolTest, AssignmentAndComparison)
{
    xcspp::Symbol symbol(0);
    xcspp::Symbol zero = symbol;

    symbol.setToDontCare();
    xcspp::Symbol dontCare = symbol;

    symbol.setValue(1);
    xcspp::Symbol one = symbol;

    symbol.setValue(0);
    EXPECT_EQ(symbol, zero);
    EXPECT_NE(symbol, dontCare);
    EXPECT_NE(symbol, one);
    EXPECT_NE(zero, dontCare);
    EXPECT_NE(zero, one);
    EXPECT_NE(dontCare, one);
}