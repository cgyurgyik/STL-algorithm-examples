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

TEST(any_of, ExampleTwoEmptySet) {
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

TEST(all_of, ExampleTwoEmptySet) {
    // Given the empty set, std::all_of will return true.
    const std::vector<int> numbers;
    const bool equals_four = std::all_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 4; });
    EXPECT_TRUE(equals_four);
    const bool equals_zero = std::all_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 0; });
    EXPECT_TRUE(equals_zero);
}

TEST(none_of, ExampleOne) {
    const std::vector<int> v1{1,5,1,1};
    const bool does_not_contain_two = std::none_of(v1.cbegin(), v1.cend(), [](int i)->int{ return i == 2; });
    EXPECT_TRUE(does_not_contain_two);

    const std::vector<int> v2{1,1,1,1,1,2};
    const bool does_not_contain_three = std::none_of(v2.cbegin(), v2.cend(),
                                                     [](int i)->int{ return i == 3; });
    EXPECT_TRUE(does_not_contain_three);
}

TEST(none_of, ExampleTwoEmptySet) {
    // Given the empty set, std::none_of will return true.
    const std::vector<int> numbers;
    const bool equals_three = std::none_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 3; });
    EXPECT_TRUE(equals_three);
    const bool equals_zero = std::none_of(numbers.cbegin(), numbers.cend(), [](int i)->int{ return i == 0; });
    EXPECT_TRUE(equals_zero);
}

TEST(for_each, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    int accumulator = 0;
    const auto accumulate = [&accumulator](int i)->void{ accumulator += i; };
    std::for_each(v.cbegin(), v.cend(), accumulate);
    EXPECT_EQ(accumulator, 1+2+3+4+5);
}

TEST(for_each_n, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    int accumulator = 0;
    const auto accumulate = [&accumulator](int i)->void{ accumulator += i; };
    std::for_each_n(v.cbegin(), /*n=*/3, accumulate);
    EXPECT_EQ(accumulator, 1+2+3);
}

TEST(count, ExampleOne) {
    const std::vector<char> v{'a', 'a', 'b', 'b', 'c'};
    const int num_alphas = std::count(v.cbegin(), v.cend(), 'a');
    EXPECT_EQ(num_alphas, 2);

    const int num_charlies = std::count(v.cbegin(), v.cend(), 'c');
    EXPECT_EQ(num_charlies, 1);
}

TEST(count_if, ExampleOne) {
    const std::vector<char> v{'1', '2', '3', 'a', 'b', 'c', '4', '5'};
    const auto isLowercaseLetter = [](char ch)->bool{ return ch >= 'a' && ch <= 'z'; };
    const int num_lowercase_letters = std::count_if(v.cbegin(), v.cend(), isLowercaseLetter);
    EXPECT_EQ(num_lowercase_letters, 3);
}

TEST(mismatch, ExampleOneUsingInequality) {
    const std::vector<int> v1{1,2,3,4,42};
    const std::vector<int> v2{1,2,3,4,5};
    // When no function is provided, checks only for first inequality case.
    const auto [v1_miss, v2_miss] = std::mismatch(v1.cbegin(), v1.cend(), v2.cbegin());
    EXPECT_EQ(*v1_miss, 42);
    EXPECT_EQ(*v2_miss, 5);
}

TEST(mismatch, ExampleTwoUsingComparator) {
    const std::vector<int> v1{0,1,2,3,42};
    const std::vector<int> v2{1,2,3,4,41};
    const auto lessThan = [](int a, int b)->bool{ return a < b; };
    // Here, we use a comparator so the mismatch will only return when
    // a 'v2' value is less than a 'v1' value.
    const auto [v1_miss, v2_miss] = std::mismatch(v1.cbegin(), v1.cend(), v2.cbegin(), lessThan);
    EXPECT_EQ(*v1_miss, 42);
    EXPECT_EQ(*v2_miss, 41);
}

TEST(find, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    const auto value = std::find(v.cbegin(), v.cend(), 3);
    EXPECT_EQ(*value, 3);
}

TEST(find, ExampleTwoEmptySet) {
    const std::vector<int> v;
    // If the element is not found, it returns an iterator to
    // the end of the collection. Note that the end of the
    // collection is NOT the last element.
    const auto value = std::find(v.cbegin(), v.cend(), 1);
    EXPECT_TRUE(value == v.cend());
}

TEST(find_if, ExampleOne) {
    const std::vector<int> v{-1,-2,3,-4,-5};
    auto isGreaterThanZero = [](int i)->bool{ return i > 0; };
    const auto value = std::find_if(v.cbegin(), v.cend(), isGreaterThanZero);
    EXPECT_EQ(*value, 3);
}

TEST(find_if_not, ExampleOne) {
    const std::vector<int> v{1,2,-3,4,5};
    auto isGreaterThanZero = [](int i)->bool{ return i > 0; };
    const auto value = std::find_if_not(v.cbegin(), v.cend(), isGreaterThanZero);
    EXPECT_EQ(*value, -3);
}

TEST(find_end, ExampleOne) {
    // This is going to find the last sub-sequence inside a container,
    // and return an iterator to it.
    const std::vector<int> v{1,2,3,4,1,2,3,4,1,2,3,4};
    const std::vector<int> sequence{1,2,3,4};
    const auto last_sequence_iterator = std::find_end(v.cbegin(), v.cend(), sequence.cbegin(), sequence.cend());
    EXPECT_EQ(*last_sequence_iterator, 1);
    EXPECT_EQ(last_sequence_iterator - v.cbegin(), 8); // Iterator begins at last sub-sequence.
}

TEST(find_first_of, ExampleOne) {
    const std::vector<char> v{'1', '2', 'w', 'o', 'r', 'd', '3', '3'};
    const std::vector<char> sequence = {'w', 'o', 'r', 'd'};
    const auto iterator = std::find_first_of(v.cbegin(), v.cend(), sequence.cbegin(), sequence.cend());
    EXPECT_EQ(*iterator, 'w');
    EXPECT_EQ(iterator - v.cbegin(), 2);
}

TEST(find_first_of, ExampleTwoWithPredicate) {
    const std::vector<char> v{'w', 'o', 'r', 'd', '1', 'W', 'O', 'R', 'D', '3', '3'};
    const std::vector<char> sequence = {'w', 'o', 'r', 'd'};
    const auto isCapitalized = [](char c1, char c2)->bool {
        return std::tolower(c1) == std::tolower(c2) && c1 >= 'A' && c1 <= 'Z';
    };
    const auto iterator = std::find_first_of(v.cbegin(), v.cend(), sequence.cbegin(), sequence.cend(), isCapitalized);
    EXPECT_EQ(*iterator, 'W');
    EXPECT_EQ(iterator - v.cbegin(), 5);
}

TEST(adjacent_find, ExampleOne) {
    const std::vector<int> v{1,2,3,4,4,5};
    // Given no predicate, this will find the first adjacent pair and return
    // an iterator to the first element of the pair.
    const auto iterator = std::adjacent_find(v.cbegin(), v.cend());
    EXPECT_EQ(*iterator, 4);
    EXPECT_EQ(*(iterator + 1), 4);
    EXPECT_EQ(iterator - v.cbegin(), 3);
}

TEST(adjacent_find, ExampleTwoWithPredicate) {
    const std::vector<int> v{8,7,6,5,92,3};
    const auto iterator = std::adjacent_find(v.cbegin(), v.cend(), std::less_equal<int>());
    // Iterator provided to first element before that is not less than or equal.
    EXPECT_EQ(*iterator, 5);
    EXPECT_EQ(*(iterator + 1), 92);
    EXPECT_EQ(iterator - v.cbegin(), 3);
}

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

