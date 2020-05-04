#include <gtest/gtest.h>
#include <gtest/gtest_pred_impl.h>

#include <gtest/internal/gtest-internal.h>
#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <cstdio>
#include <fstream>
#include <sstream>

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
    Val::VecStr v2(v1);

    v1.set(R"(["this", "is", "me"])");
    EXPECT_EQ(v1.str(), "[\'this\', \'is\', \'me\']");

    EXPECT_EQ(v1.type(), Val::Type::VECSTR);
}

// ---[ test for val Vecstr ]--------------------------------------------------

// TEST: val::Person;
TEST(Tests, Val_Person) {
    using namespace mbc;
    Val::Person p1;
    p1.attr("name") -> set("peter");
    EXPECT_EQ(p1.str(),
        "\xE2\x94\x8C------| id: \'54cfaf2e410f7965700dfb941a0b79c3\' |------\n"
        "| name: \'peter\', sex: [invaild str], telephone: [invaild str], mail_"
        "number: [invai\n"
        "| ld str], email: [invaild str],qq_number: [invaild str], location: [i"
        "nvaild str],\n"
        "|  classes: []"
    );
}

// TEST: val::MessageBook
TEST(Tests, Val_MessageBook_1) {
    using namespace mbc;
    remove("temp");
    Val::MessageBook mb("temp");
    remove("temp");
}

// TEST: val::MessageBook
TEST(Tests, Val_MessageBook_2) {
    using namespace mbc;
    remove("temp");
    Val::MessageBook mb("temp");
    mb.newPerson()
        .changeAttr("name", "peter");
    remove("temp");
}

// TEST: val_MessageBook
TEST(Tests, Val_MessageBook_3) {
    using namespace mbc;
    remove("temp");
    {
        Val::MessageBook mb("temp");
        mb.newPerson()
            .changeAttr("name", "peter");
    }
    std::fstream file("temp");
    std::stringstream content_ss;
    content_ss << file.rdbuf();

    std::string content(content_ss.str());
    EXPECT_EQ(
        content, 
        "[{\"name\":{\"valid\":true,\"value\":\"peter\"},\"sex\":{\"valid\""
        ":false,\"value\":\"\"},\"telephone\":{\"valid\":false,\"value\":\""
        "\"},\"location\":{\"valid\":false,\"value\":\"\"},\"mail_number\":"
        "{\"valid\":false,\"value\":\"\"},\"email\":{\"valid\":false,\"valu"
        "e\":\"\"},\"qq_number\":{\"valid\":false,\"value\":\"\"},\"classes"
        "\":{\"valid\":true,\"value\":[]}}]"
    );

    remove("temp");
}

// TEST: val_MessageBook
TEST(Tests, Val_MessageBook_4) {
    using namespace mbc;
    remove("temp");
    Val::MessageBook mb("temp");
    bool PART_1 = false;
    try {
        mb.newPerson()
            .changeAttr("classes", "[");
    } catch (const Val::bad_value& e) {
        // std::cerr << e.what() << std::endl;
        std::cout << "bad value" << std::endl;
        PART_1 = true;
    }
    EXPECT_EQ(PART_1, true);

    bool PART_2 = false;
    try {
        mb.newPerson()
            .changeAttr("fuck", "this");
    } catch (const Val::bad_attr& e) {
        // std::cerr << e.what() << std::endl;
        std::cout << "bad attr" << std::endl;
        PART_2 = true;
    }
    EXPECT_EQ(PART_2, true);

    remove("temp");
}

// TEST: val_MessageBook
TEST(Tests, Val_MessageBook_5) {
    using namespace mbc;
    remove("temp");
    Val::MessageBook mb("temp");
    mb.newPerson()
        .changeAttr("name", "peter")
        .changeAttr("sex",  "")
        .changeAttr("telephone", "")
        .changeAttr("mail_number", "")
        .changeAttr("email", "")
        .changeAttr("qq_number", "")
        .changeAttr("location", "")
        .changeAttr("classes", "[]");
    remove("temp");
    // assert that there is not anything core dumped
}

// TEST: val_MessageBook
TEST(Tests, Val_MessageBook_6) {
    using namespace mbc;
    remove("temp");
    {
        Val::MessageBook mb("temp");
        mb.newPerson()
            .changeAttr("name", "peter");
    }
    {
        Val::MessageBook mb("temp");
    }
    remove("temp");
    // assert that there is not anything core dumped
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}


