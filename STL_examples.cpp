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

// Note that find_first_of() is looking for ANY of the elements
// in the search range. This is different from search(), which is looking
// for the entire sequence.
TEST(find_first_of, ExampleOne) {
    const std::vector<char> v{'1', '2', 'w', 'o', 'r', 'd', '3', '3'};
    const std::vector<char> sequence = {'w', 'r', 'd'};
    const auto iterator = std::find_first_of(v.cbegin(), v.cend(), sequence.cbegin(), sequence.cend());
    EXPECT_EQ(*iterator, 'w');
    EXPECT_EQ(iterator - v.cbegin(), 2);
}

// Note that there exists a search_n() as well,
// that takes in the number of elements to search.
TEST(search, ExampleOne) {
    // This is going to find the first sub-sequence inside a container,
    // and return an iterator to it.
    const std::vector<int> v{1,2,3,4,1,2,3,4,1,2,3,4};
    const std::vector<int> sequence{1,2,3,4};
    const auto sequence_iterator = std::search(v.cbegin(), v.cend(), sequence.cbegin(), sequence.cend());
    EXPECT_EQ(*sequence_iterator, 1);
    EXPECT_EQ(sequence_iterator - v.cbegin(), 0); // Iterator begins at last sub-sequence.
}

TEST(find_first_of, ExampleTwoWithPredicate) {
    const std::vector<char> v{'w', 'o', 'r', 'd', '1', 'W', 'O', 'R', 'D', '3', '3'};
    const std::vector<char> sequence = {'w', 'r', 'd'};
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

TEST(search, ExampleTwoWithPredicate) {
    const std::vector<char> v{'w', 'o', 'r', 'd', '1', 'W', 'O', 'R', 'D', '3', '3'};
    const std::vector<char> sequence = {'w', 'o', 'r', 'd'};
    const auto isCapitalized = [](char c1, char c2)->bool {
        return std::tolower(c1) == std::tolower(c2) && c1 >= 'A' && c1 <= 'Z';
    };
    const auto iterator = std::search(v.cbegin(), v.cend(), sequence.cbegin(), sequence.cend(), isCapitalized);
    EXPECT_EQ(*iterator, 'W');
    EXPECT_EQ(iterator - v.cbegin(), 5);
}

// Modifying sequence operations.

// Note that copy_n() also exists that takes in another
// parameter to copy only the first n elements.
TEST(copy, ExampleOne) {
    const std::vector<int> from{1,2,3,4,5};
    std::vector<int> to;
    to.reserve(from.size());
    std::copy(from.cbegin(), from.cend(), std::back_inserter(to));
    EXPECT_EQ(from, to);
}

TEST(copy_if, ExampleOne) {
    std::vector<int> from{1,2,3,-4,-5};
    std::vector<int> to;
    to.reserve(from.size());
    const auto ElementIsPositive = [](int i)->bool {
        return i > 0;
    };
    std::copy_if(from.cbegin(), from.cend(), std::back_inserter(to), ElementIsPositive);
    from.pop_back(); // Remove -5: { 1, 2, 3, -4 }
    from.pop_back(); // Remove -4: { 1, 2, 3 }
    EXPECT_EQ(from, to);
}

TEST(copy_backward, ExampleOne) {
    const std::vector<int> from{1,2,3,4,5};
    std::vector<int> to(10);
    // This simply copies the elements backwards, but preserves order.
    std::copy_backward(from.cbegin(), from.cend(), to.end());
    const std::vector<int> new_to{0, 0, 0, 0, 0, 1, 2, 3, 4, 5};
    EXPECT_EQ(to, new_to);
}

TEST(move, ExampleOne) {
    std::string s = "Hello, World!";
    std::vector<std::string> v;
    // Contents of 's' are moved rather than copied.
    v.push_back(std::move(s));
    // As a result, 's' is now empty.
    EXPECT_EQ(s, "");
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], "Hello, World!");
}

TEST(move_backward, ExampleOne) {
    // For overlapping ranges, you want to use this when moving
    // right to left (beginning of destination is outside source).
    std::vector<std::string> source{"a", "b", "c"};
    std::vector<std::string> destination(source.size());
    std::move_backward(source.begin(), source.end(), destination.end());

    std::vector<std::string> new_source{"", "", ""};
    std::vector<std::string> new_destination{"a", "b", "c"};
    EXPECT_EQ(source, new_source);
    EXPECT_EQ(destination, new_destination);
}

// Note that fill_n also exists.
TEST(fill, ExampleOne) {
    std::vector<char> v{'a', 'b', 'c', 'd'};
    std::fill(v.begin(), v.end(), 'z');

    std::vector<char> new_v{'z', 'z', 'z', 'z'};
    EXPECT_EQ(v, new_v);
}

// Note that generate_n also exists.
TEST(generate, ExampleOne) {
    const auto randomNumber = []()->double{
        return std::rand();
    };
    std::vector<double> v(5);
    std::generate(v.begin(), v.end(), randomNumber);
}

// Note that remove_copy() also exists, which copies the range,
// omitting anything that doesn't fit the criteria.
TEST(remove, ExampleOne) {
    std::string s = "H_e_l_l_o";
    std::remove(s.begin(), s.end(), '_');
    // Note that remove() will shift all non space characters to the left, but we
    // still have the _l_o leftover. To remove those, we can use erase() as well.
    EXPECT_EQ(s, "Hello_l_o");

    // Using erase-remove idiom:
    std::string s2 = "H_e_l_l_o";
    s2.erase(std::remove(s2.begin(), s2.end(), '_'), s2.end());
    EXPECT_EQ(s2, "Hello");

}

// Note that remove_if_copy() also exists, which copies the range,
// omitting anything that doesn't fit the criteria.
TEST(remove_if, ExampleOne) {
    std::string s = "*h_e_*l_l*_o";
    const auto isNotLowercaseLetter = [](unsigned char c)->bool{ return !(c >= 'a' && c <= 'z'); };
    std::remove_if(s.begin(), s.end(), isNotLowercaseLetter);
    EXPECT_EQ(s, "hello*l_l*_o");

    // Using erase-remove idiom:
    std::string s2 = "*h_e_*l_l*_o";
    s2.erase(std::remove_if(s2.begin(), s2.end(), isNotLowercaseLetter), s2.end());
    EXPECT_EQ(s2, "hello");
}

TEST(transform, ExampleOne) {
    std::string s("R1EM3OV3E N3UMBE3RS");
    const auto turnNumberIntoUnderline = [](unsigned char c)->unsigned char {
        if (c < '9' && c > '0') return '_';
        return c;
    };
    std::transform(s.begin(), s.end(), s.begin(),
                   turnNumberIntoUnderline);
    EXPECT_EQ(s, "R_EM_OV_E N_UMBE_RS");

    // We can even take this a step further and remove the underlines.
    s.erase(std::remove(s.begin(), s.end(), '_'), s.end());
    EXPECT_EQ(s, "REMOVE NUMBERS");
}

// Note: replace_copy() also exists.
TEST(replace, ExampleOne) {
    std::vector<int> v{1,2,3,3,3,4,4,5,5};
    std::replace(v.begin(), v.end(), 3, 42);
    std::vector new_v{1,2,42,42,42,4,4,5,5};
    EXPECT_EQ(v, new_v);
}

// Note: replace_if_copy() also exists.
TEST(replace_if, ExampleOne) {
    std::vector<int> v{-1,-2,-3,4,5};
    const auto isLessThanZero = [](int i)->bool{ return i < 0; };

    std::replace_if(v.begin(), v.end(), isLessThanZero, 42);
    std::vector new_v{42,42,42,4,5};
    EXPECT_EQ(v, new_v);
}

TEST(swap, ExampleOne) {
    int a = 10;
    int b = 42;
    std::swap(a, b);
    EXPECT_EQ(a, 42);
    EXPECT_EQ(b, 10);
}

TEST(swap_ranges, ExampleOne) {
    std::vector<int> ones{1, 1, 1, 1, 1};
    std::vector<int> twos{2, 2, 2, 2, 2};
    std::swap_ranges(ones.begin(), ones.end(), twos.begin());

    const std::vector new_ones{2, 2, 2, 2, 2};
    const std::vector new_twos{1, 1, 1, 1, 1};
    EXPECT_EQ(ones, new_ones);
    EXPECT_EQ(twos, new_twos);
}

TEST(iter_swap, ExampleOne) {

}

// Note that reverse_copy() also exists, which
// makes a copy of the reversed range.
TEST(reverse, ExampleOne) {

}

// Note that rotate_copy also exists, which
// makes a copy first and then rotates.
TEST(rotate, ExampleOne) {

}

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

