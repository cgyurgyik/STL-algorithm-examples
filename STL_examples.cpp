#include "gtest/gtest.h"
#include <algorithm>
#include <iterator>

// Examples for each STL algorithm. Verified with Google test suite. While code duplication is rampant,
// The goal is to provide self-fulfilling examples that can be pulled individually
// for others to use and look at.

// Non-modifying sequence operations.
TEST(any_of, ExampleOne) {
    const std::vector<int> numbers{1,2,3,4,4,5};
    const bool equals_four = std::any_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 4; });
    EXPECT_TRUE(equals_four);
    const bool equals_zero = std::any_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 0; });
    EXPECT_FALSE(equals_zero);
}

TEST(any_of, ExampleTwo) {
    // Given the empty set, std::any_of will return false.
    const std::vector<int> numbers;
    const bool equals_four = std::any_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 4; });
    EXPECT_FALSE(equals_four);
    const bool equals_zero = std::any_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 10; });
    EXPECT_FALSE(equals_zero);
}

TEST(all_of, ExampleOne) {
    const std::vector<int> all_ones{1,1,1,1};
    const bool equals_one = std::all_of(all_ones.cbegin(), all_ones.cend(), [](int i)->int{ return i == 1; });
    EXPECT_TRUE(equals_one);

    const std::vector<int> not_all_ones{1,1,1,1,1,2};
    const bool last_member_equals_one = std::all_of(not_all_ones.cbegin(), not_all_ones.cend(), [](int i)->int{ return i == 1; });
    EXPECT_FALSE(last_member_equals_one);
}

TEST(all_of, ExampleTwo) {
    // Given the empty set, std::all_of will return true.
    const std::vector<int> numbers;
    const bool equals_four = std::all_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 4; });
    EXPECT_TRUE(equals_four);
    const bool equals_zero = std::all_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 10; });
    EXPECT_TRUE(equals_zero);
}

TEST(none_of, ExampleOne) {}

TEST(for_each, ExampleOne) {}

TEST(for_each_n, ExampleOne) {}

TEST(count, ExampleOne) {}

TEST(count_if, ExampleOne) {}

TEST(mismatch, ExampleOne) {}

TEST(find, ExampleOne) {}

TEST(find_if, ExampleOne) {}

TEST(find_if_not, ExampleOne) {}

TEST(find_end, ExampleOne) {}

TEST(find_first_of, ExampleOne) {}

TEST(adjacent_find, ExampleOne) {}

TEST(search, ExampleOne) {}

TEST(search_n, ExampleOne) {}

// Modifying sequence operations.

// Partitioning operations.

// Sorting operations.

// Binary search operations (on sorted ranges).

// Other operations (on sorted ranges).

// Set operations (on sorted ranges).

// Heap operations.

// Minimum, maximum operations.

// Comparison operations.

// Permutation operations.

// Numeric operations.

// Operations on uninitialized memory.

