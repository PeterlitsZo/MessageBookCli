#include <gtest/gtest.h>
#include <gtest/gtest_pred_impl.h>

#include <vector>
#include <iostream>
#include <string>
#include <exception>

#include "../src/info.h"
#include "../src/units.h"
#include "../src/val.h"

#include "../include/logging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using std::string;
using std::vector;
using std::cout;

// ----------------------------------------------------------------------------
// ---[ print and info ]-------------------------------------------------------
// ----------------------------------------------------------------------------

// TEST: print the version
TEST(Tests, VERSION) {
    EXPECT_STREQ(info::version, "ver 0.0.1");
}

// ----------------------------------------------------------------------------
// ---[ units ]----------------------------------------------------------------
// ----------------------------------------------------------------------------

// TEST: units/is_digit
TEST(Tests, Units_is_digit) {
    // char is digit
    EXPECT_EQ(units::is_digit('0'), true);
    EXPECT_EQ(units::is_digit('1'), true);
    EXPECT_EQ(units::is_digit('8'), true);
    EXPECT_EQ(units::is_digit('9'), true);

    // char is not digit
    EXPECT_EQ(units::is_digit('!'), false);
    EXPECT_EQ(units::is_digit('a'), false);
    EXPECT_EQ(units::is_digit(']'), false);

    // c str is digit
    EXPECT_EQ(units::is_digit("2"), true);
    EXPECT_EQ(units::is_digit("123093423"), true);
}

// TEST: units/is_email
TEST(Tests, Units_is_email) {
    EXPECT_EQ(units::is_email("abc@abc.abc"), true);
    EXPECT_EQ(units::is_email("abcabc.abc"),  false);
    EXPECT_EQ(units::is_email("abc@abcabc"),  false);
    EXPECT_EQ(units::is_email("abcabcabc"),   false);
}

// TEST: units/is_not_empty
TEST(Tests, Units_is_not_empty) {
    EXPECT_EQ(units::is_not_empty(""), false);
    EXPECT_EQ(units::is_not_empty("this"), true);
    EXPECT_EQ(units::is_not_empty("!"), true);
    EXPECT_EQ(units::is_not_empty("~"), true);
}

// TEST: units/repr
TEST(Tests, Units_repr) {
    EXPECT_EQ(units::repr(1), "1");
    EXPECT_EQ(units::repr(123), "123");
    EXPECT_EQ(units::repr("123"), "\'123\'");
    vector<int> temp_01{1, 2, 3, 4};
    EXPECT_EQ(units::repr(temp_01.begin(), temp_01.end()), "[1, 2, 3, 4]");
    vector<int> temp_02{};
    EXPECT_EQ(units::repr(temp_02.begin(), temp_02.end()), "[]");
}

// TEST: units/parser_string_repr
TEST(Tests, Units_parser_string_repr) {
    EXPECT_EQ(units::parse_str_repr(R"('this\n')"), "this\n");
    EXPECT_EQ(units::parse_str_repr(R"('\tthis\n')"), "\tthis\n");
    EXPECT_EQ(units::parse_str_repr(R"('th\vis\n')"), "th\vis\n");
    EXPECT_EQ(units::parse_str_repr(R"('th\\is\n')"), "th\\is\n");
    EXPECT_EQ(units::parse_str_repr(R"('th\is\n')"), "th\\is\n");
}

// TEST: units/parser_vecstr_repr
TEST(Tests, Units_parser_vecstr_repr) {
    int part = 0;
    try {
        part = 1;
        vector<string> temp1{"this\n"};
        EXPECT_EQ(units::parse_vecstr_repr(R"(['this\n'])")
                  , temp1);
        part = 2;
        vector<string> temp2{};
        EXPECT_EQ(units::parse_vecstr_repr(R"([ ])")
                  , temp2);
        part = 3;
        vector<string> temp3{"\n", "", "that", "this"};
        EXPECT_EQ(units::parse_vecstr_repr(R"(["\n", '', 'that', "this"])")
                  , temp3);
    } catch (const char* ex) {
        cout << "[part " << part << "]: " << ex << std::endl;
    }
}


// ----------------------------------------------------------------------------
// ---[ test for val ]---------------------------------------------------------
// ----------------------------------------------------------------------------

// ---[ test for val Str ]-----------------------------------------------------

// TEST: val::Str;
TEST(Tests, Val_Str) {
    using namespace mbc;
    Val::Str s1;
    Val::Str s2([](const string& str){return true;});
    Val::Str s3([](const string& str){return false;});

    s1.set("this");
    s2.set("this");
    s3.set("this");

    EXPECT_EQ(s1.str(), "\'this\'");
    EXPECT_EQ(s2.str(), "\'this\'");
    EXPECT_EQ(s3.str(), "[invaild str]");

    Val::Str s4(s2);
    EXPECT_EQ(s2.str(), "\'this\'");
    s4.set("that");
    EXPECT_EQ(s2.str(), "\'that\'");

    s4.reprset(R"("that")");
    EXPECT_EQ(s2.str(), "\'that\'");

    EXPECT_EQ(s1.type(), Val::Type::STR);
}


// ---[ test for val Vecstr ]--------------------------------------------------

// TEST: val::VecStr;
TEST(Tests, Val_VecStr) {
    using namespace mbc;
    Val::VecStr v1;
    // Val::VecStr v2(v1);

    v1.set(R"(["this", "is", "me"])");
    EXPECT_EQ(v1.str(), "[\'this\', \'is\', \'me\']");

    EXPECT_EQ(v1.type(), Val::Type::VECSTR);
}

// ---[ test for val Vecstr ]--------------------------------------------------

// TEST: val::Person;
TEST(Tests, Val_Person) {
    using namespace mbc;
    Val::Person p1;
    std::cout << p1.str();
    p1.attr("name") -> set("\'peter\'");
    std::cout << p1.str();

    Val::MessageBook mb("temp");
    mb.newPerson()
        .changeAttr("name", units::repr("peter"));
    std::cout << mb.str();
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}





