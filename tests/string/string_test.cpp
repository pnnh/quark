/**
 * Unit tests for quark/core/string/string.h
 * Covers both the C interface (QKString* API) and the C++ quark::MTString class.
 */

#include <gtest/gtest.h>
#include "quark/core/string/string.h"

// ============================================================
//  C Interface — QKStringCreate / QKStringGetData / QKStringDelete
// ============================================================

TEST(QKStringCreate, BasicAscii) {
    QKString *s = QKStringCreate("hello");
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(QKStringGetData(s), "hello");
    QKStringDelete(s);
}

TEST(QKStringCreate, EmptyString) {
    QKString *s = QKStringCreate("");
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(QKStringGetData(s), "");
    QKStringDelete(s);
}

TEST(QKStringCreate, UnicodeString) {
    QKString *s = QKStringCreate("你好世界");
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(QKStringGetData(s), "你好世界");
    QKStringDelete(s);
}

TEST(QKStringCreate, StringWithSpaces) {
    QKString *s = QKStringCreate("  hello world  ");
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(QKStringGetData(s), "  hello world  ");
    QKStringDelete(s);
}

TEST(QKStringDelete, ReturnsZeroOnSuccess) {
    QKString *s = QKStringCreate("test");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(QKStringDelete(s), 0);
}

// ============================================================
//  C++ Interface — quark::MTString constructors & toStdString/getCString
// ============================================================

TEST(MTStringConstructor, DefaultConstructorProducesEmptyString) {
    quark::MTString s;
    EXPECT_EQ(s.toStdString(), "");
    EXPECT_STREQ(s.getCString(), "");
}

TEST(MTStringConstructor, StringConstructorStoresValue) {
    quark::MTString s("hello");
    EXPECT_EQ(s.toStdString(), "hello");
    EXPECT_STREQ(s.getCString(), "hello");
}

TEST(MTStringConstructor, StdStringConstructor) {
    std::string src = "world";
    quark::MTString s(src);
    EXPECT_EQ(s.toStdString(), "world");
}

TEST(MTStringConstructor, CopyAssignment) {
    quark::MTString a("original");
    quark::MTString b;
    b = a;
    EXPECT_EQ(b.toStdString(), "original");
    // Ensure independence
    EXPECT_EQ(a.toStdString(), "original");
}

// ============================================================
//  IsBlank
// ============================================================

TEST(MTStringIsBlank, EmptyStringIsBlank) {
    EXPECT_TRUE(quark::MTString::IsBlank(""));
}

TEST(MTStringIsBlank, SpacesOnlyIsBlank) {
    EXPECT_TRUE(quark::MTString::IsBlank("   "));
}

TEST(MTStringIsBlank, TabAndNewlineIsBlank) {
    EXPECT_TRUE(quark::MTString::IsBlank("\t\n\r "));
}

TEST(MTStringIsBlank, NormalStringIsNotBlank) {
    EXPECT_FALSE(quark::MTString::IsBlank("hello"));
}

TEST(MTStringIsBlank, StringWithLeadingSpaceIsNotBlank) {
    EXPECT_FALSE(quark::MTString::IsBlank("  hi"));
}

// ============================================================
//  StartsWith
// ============================================================

TEST(MTStringStartsWith, MatchesPrefix) {
    EXPECT_TRUE(quark::MTString::StartsWith("hello world", "hello"));
}

TEST(MTStringStartsWith, DoesNotMatchWrongPrefix) {
    EXPECT_FALSE(quark::MTString::StartsWith("hello world", "world"));
}

TEST(MTStringStartsWith, EmptyPrefixAlwaysMatches) {
    EXPECT_TRUE(quark::MTString::StartsWith("hello", ""));
}

TEST(MTStringStartsWith, PrefixLongerThanStringReturnsFalse) {
    EXPECT_FALSE(quark::MTString::StartsWith("hi", "hello"));
}

TEST(MTStringStartsWith, ExactMatch) {
    EXPECT_TRUE(quark::MTString::StartsWith("abc", "abc"));
}

// ============================================================
//  EndsWith
// ============================================================

TEST(MTStringEndsWith, MatchesSuffix) {
    EXPECT_TRUE(quark::MTString::EndsWith("hello world", "world"));
}

TEST(MTStringEndsWith, DoesNotMatchWrongSuffix) {
    EXPECT_FALSE(quark::MTString::EndsWith("hello world", "hello"));
}

TEST(MTStringEndsWith, EmptySuffixAlwaysMatches) {
    EXPECT_TRUE(quark::MTString::EndsWith("hello", ""));
}

TEST(MTStringEndsWith, SuffixLongerThanStringReturnsFalse) {
    EXPECT_FALSE(quark::MTString::EndsWith("hi", "hello"));
}

TEST(MTStringEndsWith, ExactMatch) {
    EXPECT_TRUE(quark::MTString::EndsWith("abc", "abc"));
}

// ============================================================
//  LeftReplace
// ============================================================

TEST(MTStringLeftReplace, ReplacesMatchingPrefix) {
    EXPECT_EQ(quark::MTString::LeftReplace("hello world", "hello", "hi"),
              "hi world");
}

TEST(MTStringLeftReplace, NoChangeWhenPrefixNotAtStart) {
    EXPECT_EQ(quark::MTString::LeftReplace("hello world", "world", "earth"),
              "hello world");
}

TEST(MTStringLeftReplace, EmptyNewPrefix) {
    EXPECT_EQ(quark::MTString::LeftReplace("prefixRest", "prefix", ""), "Rest");
}

TEST(MTStringLeftReplace, NoMatchReturnsOriginal) {
    EXPECT_EQ(quark::MTString::LeftReplace("abc", "xyz", "ZZZ"), "abc");
}

// ============================================================
//  SplitChar
// ============================================================

TEST(MTStringSplitChar, SplitsByComma) {
    auto parts = quark::MTString::SplitChar("a,b,c", ',');
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");
}

TEST(MTStringSplitChar, SingleTokenNoDelimiter) {
    auto parts = quark::MTString::SplitChar("hello", ',');
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], "hello");
}

TEST(MTStringSplitChar, SplitsBySlash) {
    auto parts = quark::MTString::SplitChar("a/b/c/d", '/');
    ASSERT_EQ(parts.size(), 4u);
    EXPECT_EQ(parts[3], "d");
}

TEST(MTStringSplitChar, TrailingDelimiterNoExtraToken) {
    // std::getline does not generate a trailing empty token when the string
    // ends with the delimiter — this is the documented behaviour of SplitChar.
    auto parts = quark::MTString::SplitChar("a,b,", ',');
    ASSERT_EQ(parts.size(), 2u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
}

// ============================================================
//  SplitString
// ============================================================

TEST(MTStringSplitString, SplitsByMultiCharDelimiter) {
    auto parts = quark::MTString::SplitString("a::b::c", "::");
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");
}

TEST(MTStringSplitString, NoDelimiterReturnsSingleToken) {
    auto parts = quark::MTString::SplitString("hello", "::");
    ASSERT_EQ(parts.size(), 1u);
    EXPECT_EQ(parts[0], "hello");
}

TEST(MTStringSplitString, SingleCharDelimiter) {
    auto parts = quark::MTString::SplitString("x-y-z", "-");
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[1], "y");
}

// ============================================================
//  toLower / toUpper
// ============================================================

TEST(MTStringToLower, AllUpperBecomesAllLower) {
    EXPECT_EQ(quark::MTString::toLower("HELLO"), "hello");
}

TEST(MTStringToLower, MixedCase) {
    EXPECT_EQ(quark::MTString::toLower("HeLLo WoRLd"), "hello world");
}

TEST(MTStringToLower, AlreadyLowerUnchanged) {
    EXPECT_EQ(quark::MTString::toLower("hello"), "hello");
}

TEST(MTStringToLower, EmptyString) {
    EXPECT_EQ(quark::MTString::toLower(""), "");
}

TEST(MTStringToUpper, AllLowerBecomesAllUpper) {
    EXPECT_EQ(quark::MTString::toUpper("hello"), "HELLO");
}

TEST(MTStringToUpper, MixedCase) {
    EXPECT_EQ(quark::MTString::toUpper("HeLLo WoRLd"), "HELLO WORLD");
}

TEST(MTStringToUpper, AlreadyUpperUnchanged) {
    EXPECT_EQ(quark::MTString::toUpper("HELLO"), "HELLO");
}

// ============================================================
//  trimLeft / trimRight / trimAll
// ============================================================

TEST(MTStringTrimLeft, RemovesLeadingSpaces) {
    EXPECT_EQ(quark::MTString::trimLeft("   hello", " "), "hello");
}

TEST(MTStringTrimLeft, NoLeadingSpacesUnchanged) {
    EXPECT_EQ(quark::MTString::trimLeft("hello   ", " "), "hello   ");
}

TEST(MTStringTrimLeft, RemovesCustomChars) {
    EXPECT_EQ(quark::MTString::trimLeft("---abc", "-"), "abc");
}

TEST(MTStringTrimRight, RemovesTrailingSpaces) {
    EXPECT_EQ(quark::MTString::trimRight("hello   ", " "), "hello");
}

TEST(MTStringTrimRight, NoTrailingSpacesUnchanged) {
    EXPECT_EQ(quark::MTString::trimRight("   hello", " "), "   hello");
}

TEST(MTStringTrimRight, RemovesCustomChars) {
    EXPECT_EQ(quark::MTString::trimRight("abc---", "-"), "abc");
}

TEST(MTStringTrimAll, RemovesBothSides) {
    EXPECT_EQ(quark::MTString::trimAll("  hello  ", " "), "hello");
}

TEST(MTStringTrimAll, NoSpacesUnchanged) {
    EXPECT_EQ(quark::MTString::trimAll("hello", " "), "hello");
}

TEST(MTStringTrimAll, OnlySpacesBecomesEmpty) {
    EXPECT_EQ(quark::MTString::trimAll("   ", " "), "");
}

// ============================================================
//  DynamicPrint
// ============================================================

TEST(MTStringDynamicPrint, BasicStringFormat) {
    EXPECT_EQ(quark::MTString::DynamicPrint("{} {}", "hello", "world"),
              "hello world");
}

TEST(MTStringDynamicPrint, IntegerFormat) {
    EXPECT_EQ(quark::MTString::DynamicPrint("val={}", 42), "val=42");
}

TEST(MTStringDynamicPrint, MultipleArguments) {
    EXPECT_EQ(quark::MTString::DynamicPrint("{}-{}-{}", 1, 2, 3), "1-2-3");
}

TEST(MTStringDynamicPrint, NoArguments) {
    EXPECT_EQ(quark::MTString::DynamicPrint("no args"), "no args");
}

// ============================================================
//  quark::strToLower (free function)
// ============================================================

TEST(StrToLower, AllUpperBecomesLower) {
    EXPECT_EQ(quark::strToLower("HELLO"), "hello");
}

TEST(StrToLower, MixedCase) {
    EXPECT_EQ(quark::strToLower("QuArK"), "quark");
}

TEST(StrToLower, EmptyString) {
    EXPECT_EQ(quark::strToLower(""), "");
}

// ============================================================
//  Conversion helpers
// ============================================================

TEST(QKStringToMTString, ConvertsCorrectly) {
    QKString *s = QKStringCreate("quark");
    quark::MTString ms = QKStringToMTString(s);
    EXPECT_EQ(ms.toStdString(), "quark");
    QKStringDelete(s);
}

TEST(QKStringToStdString, ConvertsCorrectly) {
    QKString *s = QKStringCreate("hello");
    EXPECT_EQ(QKStringToStdString(s), "hello");
    QKStringDelete(s);
}

TEST(QKStringToStdString, EmptyString) {
    QKString *s = QKStringCreate("");
    EXPECT_EQ(QKStringToStdString(s), "");
    QKStringDelete(s);
}

TEST(StdStringToQKStringPtr, ConvertsAndReturnsCorrectData) {
    QKString *s = StdStringToQKStringPtr("test_string");
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(QKStringGetData(s), "test_string");
    QKStringDelete(s);
}

TEST(StdStringToQKStringPtr, EmptyStdString) {
    QKString *s = StdStringToQKStringPtr("");
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(QKStringGetData(s), "");
    QKStringDelete(s);
}

TEST(StdStringToQKString, ByValueConvertsCorrectly) {
    QKString qs = StdStringToQKString(std::string("by_value"));
    // Access via QKStringGetData requires a pointer; use address here
    EXPECT_STREQ(QKStringGetData(&qs), "by_value");
    // Manually release the internal MTString (no QKStringDelete for stack objects)
    auto *mtStr = static_cast<quark::MTString *>(qs.mtStr);
    delete mtStr;
    qs.mtStr = nullptr;
}

