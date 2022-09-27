//
// Created by Abd-El-Aziz Zayed on 2022-09-24.
//

#include "cas/util/StringUtils.h"
#include "gtest/gtest.h"

TEST(StringUtilsTest, testReplaceAll) {
    std::string str = "Hello World Hello World";
    replaceAll(str, "Hello", "Hi");
    ASSERT_EQ(str, "Hi World Hi World");

    str = "HI Hi my name is HI";
    replaceAll(str, "HI", "Hello");
    ASSERT_EQ(str, "Hello Hi my name is Hello");
}

TEST(StringUtilsTest, testContains) {
    std::string str = "Hello World Hello World";
    ASSERT_TRUE(contains(str, "Hello"));
    ASSERT_TRUE(contains(str, "World"));
    ASSERT_FALSE(contains(str, "Hi"));
}

TEST(StringUtilsTest, testSplit) {
    std::string str = "Hello World Hello World";
    std::vector<std::string> sp = split(str, " ");
    ASSERT_EQ(sp.size(), 4);
    ASSERT_EQ(sp[0], "Hello");
    ASSERT_EQ(sp[1], "World");
    ASSERT_EQ(sp[2], "Hello");
    ASSERT_EQ(sp[3], "World");
}

TEST(StringUtilsTest, testReplaceOnce) {
    std::string str = "Hello World Hello World";
    replaceOnce(str, "Hello", "Hi");
    ASSERT_EQ(str, "Hi World Hello World");
}

TEST(StringUtilsTest, testCountMatches) {
    std::string str = "Hello World Hello World";
    ASSERT_EQ(countMatches(str, "Hello"), 2);
    ASSERT_EQ(countMatches(str, "World"), 2);
    ASSERT_EQ(countMatches(str, "Hi"), 0);
}

TEST(StringUtilsTest, testStartsWith) {
    std::string str = "Hello World Hello World";
    ASSERT_TRUE(startsWith(str, "Hello"));
    ASSERT_FALSE(startsWith(str, "World"));
}

TEST(StringUtilsTest, testIsNumber) {
    ASSERT_TRUE(isNumber("123"));
    ASSERT_TRUE(isNumber("123.123"));
    ASSERT_TRUE(isNumber("-123"));
    ASSERT_TRUE(isNumber("-123.123"));
    ASSERT_TRUE(isNumber("0"));
    ASSERT_TRUE(isNumber("0.0"));
    ASSERT_TRUE(isNumber("-0"));
    ASSERT_TRUE(isNumber("-0.0"));
    ASSERT_FALSE(isNumber("Hello"));
    ASSERT_FALSE(isNumber("Hello World"));
    ASSERT_FALSE(isNumber("Hello World 123"));
    ASSERT_FALSE(isNumber("123 Hello World"));
    ASSERT_FALSE(isNumber("123 Hello World 123"));
    ASSERT_FALSE(isNumber("123.123.123"));
}
