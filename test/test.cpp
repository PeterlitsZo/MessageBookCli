#include <gtest/gtest.h>
#include <gtest/gtest_pred_impl.h>
#include "../src/info.h"
#include "../src/messagebook.h"
#include "../src/units.h"

// ----------------------------------------------------------------------------
// ---[ print and info ]-------------------------------------------------------
// ----------------------------------------------------------------------------

// TEST: print out the meun
TEST(Tests, MEUN) {
    EXPECT_STREQ(info::meun, " Main Meun of Message Book Version(v0.0.1)\n"
                             " 1. Add Info\n 2. Search Info\n 3. View All Info\n"
                             " 4. Change Info\n 5. Delete Info\n 6. Exit\n\n"
                             " Please Enter a Index For Next (q for quit) > ");
}

// TEST: print the version
TEST(Tests, VERSION) {
    EXPECT_STREQ(info::version, "ver 0.0.1\n");
}

// TEST: Add Person
TEST(Tests, AddPerson) {
    MessageBook mb;
    mb.addPerson("Peter", "M", "17623321234", "China",
                 "123456", "abc@abc.abc", "12345", {"men"});
    mb.addPerson("Allen", "M", "17623325764", "China",
                 "000000", "123@123.com", "123456", {"this"});
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
