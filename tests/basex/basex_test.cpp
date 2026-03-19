/**
 * Unit tests for quark/infra/utils/basex.h
 *
 * basex.h exposes a C++ API only (no C wrapper):
 *   quark::encode64(const std::string&) -> std::string
 *   quark::decode64(const std::string&) -> std::string
 *
 * Test vectors follow RFC 4648 §10.
 */

#include <gtest/gtest.h>
#include "quark/infra/utils/basex.h"

// ============================================================
//  encode64 — RFC 4648 standard test vectors
// ============================================================

TEST(Encode64, EmptyString) {
    EXPECT_EQ(quark::encode64(""), "");
}

TEST(Encode64, SingleChar_NoPadding_f) {
    // "f" -> "Zg==" (2 padding chars)
    EXPECT_EQ(quark::encode64("f"), "Zg==");
}

TEST(Encode64, TwoChars_OnePadding_fo) {
    // "fo" -> "Zm8=" (1 padding char)
    EXPECT_EQ(quark::encode64("fo"), "Zm8=");
}

TEST(Encode64, ThreeChars_NoPadding_foo) {
    // "foo" -> "Zm9v" (no padding)
    EXPECT_EQ(quark::encode64("foo"), "Zm9v");
}

TEST(Encode64, FourChars_foob) {
    EXPECT_EQ(quark::encode64("foob"), "Zm9vYg==");
}

TEST(Encode64, FiveChars_fooba) {
    EXPECT_EQ(quark::encode64("fooba"), "Zm9vYmE=");
}

TEST(Encode64, SixChars_foobar) {
    EXPECT_EQ(quark::encode64("foobar"), "Zm9vYmFy");
}

TEST(Encode64, Classic_Man) {
    EXPECT_EQ(quark::encode64("Man"), "TWFu");
}

TEST(Encode64, TwoCharPadding_Ma) {
    EXPECT_EQ(quark::encode64("Ma"), "TWE=");
}

TEST(Encode64, TwoEqualPadding_M) {
    EXPECT_EQ(quark::encode64("M"), "TQ==");
}

TEST(Encode64, HelloWorld) {
    EXPECT_EQ(quark::encode64("hello"), "aGVsbG8=");
}

TEST(Encode64, HelloWorldWithSpace) {
    EXPECT_EQ(quark::encode64("hello world"), "aGVsbG8gd29ybGQ=");
}

TEST(Encode64, NumbersString) {
    EXPECT_EQ(quark::encode64("0123456789"), "MDEyMzQ1Njc4OQ==");
}

TEST(Encode64, OutputOnlyContainsBase64Chars) {
    const std::string b64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    std::string encoded = quark::encode64("The quick brown fox jumps over the lazy dog");
    for (char c : encoded) {
        EXPECT_NE(b64_chars.find(c), std::string::npos)
            << "Unexpected character '" << c << "' in encoded output";
    }
}

TEST(Encode64, LongString) {
    // 60 chars → 80 base64 chars (no padding, 60 % 3 == 0)
    // 'A'(0x41) × 3 → "QUFB", so 60 × 'A' → "QUFB" × 20
    std::string input(60, 'A');
    std::string encoded = quark::encode64(input);
    EXPECT_EQ(encoded.size(), 80u);
    EXPECT_EQ(encoded.substr(0, 4), "QUFB"); // first group
    EXPECT_EQ(encoded.back(), 'B');           // last char of "QUFB"
}

// ============================================================
//  decode64 — RFC 4648 standard test vectors
// ============================================================

TEST(Decode64, EmptyString) {
    EXPECT_EQ(quark::decode64(""), "");
}

TEST(Decode64, SingleChar_f) {
    EXPECT_EQ(quark::decode64("Zg=="), "f");
}

TEST(Decode64, TwoChars_fo) {
    EXPECT_EQ(quark::decode64("Zm8="), "fo");
}

TEST(Decode64, ThreeChars_foo) {
    EXPECT_EQ(quark::decode64("Zm9v"), "foo");
}

TEST(Decode64, SixChars_foobar) {
    EXPECT_EQ(quark::decode64("Zm9vYmFy"), "foobar");
}

TEST(Decode64, Classic_Man) {
    EXPECT_EQ(quark::decode64("TWFu"), "Man");
}

TEST(Decode64, HelloWorld) {
    EXPECT_EQ(quark::decode64("aGVsbG8="), "hello");
}

TEST(Decode64, HelloWorldWithSpace) {
    EXPECT_EQ(quark::decode64("aGVsbG8gd29ybGQ="), "hello world");
}

TEST(Decode64, NumbersString) {
    EXPECT_EQ(quark::decode64("MDEyMzQ1Njc4OQ=="), "0123456789");
}

TEST(Decode64, LongString) {
    std::string input(60, 'A');
    std::string encoded = quark::encode64(input);
    EXPECT_EQ(quark::decode64(encoded), input);
}

// ============================================================
//  Round-trip: decode(encode(x)) == x
// ============================================================

class Base64RoundTrip : public ::testing::TestWithParam<std::string> {};

TEST_P(Base64RoundTrip, EncodeDecodeShouldReturnOriginal) {
    const std::string& original = GetParam();
    EXPECT_EQ(quark::decode64(quark::encode64(original)), original);
}

INSTANTIATE_TEST_SUITE_P(
    RoundTripCases,
    Base64RoundTrip,
    ::testing::Values(
        "",
        "f",
        "fo",
        "foo",
        "foob",
        "fooba",
        "foobar",
        "Man",
        "hello",
        "hello world",
        "The quick brown fox jumps over the lazy dog",
        "0123456789",
        std::string(1, '\x01'),            // single non-printable byte
        std::string("\x00\x01\x02", 3)     // binary bytes including NUL
    )
);


