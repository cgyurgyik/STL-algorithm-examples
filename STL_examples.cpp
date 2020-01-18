#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <iterator>

// Examples for each STL algorithm. Verified with Google test suite. While code duplication is rampant,
// The goal is to provide self-fulfilling examples that can be pulled individually
// for others to use and look at.

// To find a specific function example,
// simply use the find feature and type:
//        TEST(<function_name>
//
// For example, if I want to see stable_sort,
// I would hit (command + f) on my keyboard and type:
//       TEST(stable_sort

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
    std::vector v1{1, 2, 3, 4, 5};
    std::vector v2{-1, -2, -3, -4, -5};

    // swaps the first element in v1 and v2.
    std::iter_swap(v1.begin(), v2.begin());
    std::vector<int> new_v1{-1, 2, 3, 4, 5};
    std::vector<int> new_v2{1, -2, -3, -4, -5};
    EXPECT_EQ(v1, new_v1);
    EXPECT_EQ(v2, new_v2);

    // swaps the first element in v1 and 3rd element in v2.
    std::iter_swap(v1.begin(), v2.begin() + 2);
    new_v1 = {-3, 2, 3, 4, 5};
    new_v2 = {1, -2, -1, -4, -5};
    EXPECT_EQ(v1, new_v1);
    EXPECT_EQ(v2, new_v2);
}


// Note that reverse_copy() also exists, which
// makes a copy of the reversed range.
TEST(reverse, ExampleOne) {
    std::vector<int> v{1,2,3,4,5};
    std::reverse(v.begin(), v.end());

    const std::vector<int> reversed_v{5,4,3,2,1};
    EXPECT_EQ(v, reversed_v);
}

// Note that rotate_copy also exists, which
// makes a copy first and then rotates.
TEST(rotate, ExampleOne) {
    std::vector<int> v{1,2,3,4,5};

    // Element in the middle, v.begin() + 1
    // becomes first element.
    std::rotate(v.begin(), v.begin() + 1, v.end());

    const std::vector<int> rotated_v{2,3,4,5,1};
    EXPECT_EQ(v, rotated_v);
}

// C++20
// TEST(shift_left, ExampleOne) {}
// TEST(shift_right, ExampleOne) {}

TEST(shuffle, ExampleOne) {
    std::vector<int> v{1,2,3,4,5};
    std::random_device random_device;
    std::mt19937 gen(random_device());

    std::shuffle(v.begin(), v.end(), gen);
    // Since shuffle is randomly generated, one can just print the elements
    // instead to verify. One should expect a vector of the same size
    // with the elements randomly shuffled.

    // const auto printElement = [](int i)->int{ printf("\n%d\n", i); return i; };
    // std::transform(v.begin(), v.end(), v.begin(), printElement);
}

TEST(sample, ExampleOne) {
    std::string s = "0123456789";
    std::string destination;
    std::random_device random_device;
    std::mt19937 gen(random_device());

    std::sample(s.begin(), s.end(), std::back_inserter(destination), 5, gen);
    // Since sample is randomly generated, one can just print the elements
    // instead to verify. One should expect 5 random characters from 's' to
    // be placed in destination.

    // const auto printElement = [](unsigned char c)->unsigned char{ printf("\n%c\n", c); return c; };
    // std::transform(destination.begin(), destination.end(), destination.begin(), printElement);
}

// Note: unique_copy also exists.
TEST(unique, ExampleOneSorted) {
    std::vector<int> v{1,1,1,2,2,2,3,3,3,4,4,5,5,5};
    const auto iterator = std::unique(v.begin(), v.end());
    v.erase(iterator, v.end());

    // std::unique will shift extra equivalent elements
    // in groups. Since 'v' is sorted, this will produce
    // the vector below.
    // We then use erase() to remove them.
    const std::vector<int> new_v{1,2,3,4,5};
    EXPECT_EQ(v, new_v);
}

TEST(unique, ExampleTwoUnsorted) {
    //
    std::vector<int> v{1,1,2,1,3,3,4,4,5};
    const auto iterator = std::unique(v.begin(), v.end());
    v.erase(iterator, v.end());

    // Since 1 is unique element in the group [2,1,3]
    // it remains in the vector.
    // We then use erase() to remove them.
    const std::vector<int> new_v{1,2,1,3,4,5};
    EXPECT_EQ(v, new_v);
}

// Partitioning operations.
TEST(is_partitioned, ExampleOne) {
    const auto isLessThanZero = [](int i)->bool{ return i < 0; };
    std::vector<int> v{-1,-2,-3,1,2,3};
    const bool is_partitioned = std::is_partitioned(v.cbegin(), v.cend(), isLessThanZero);
    EXPECT_TRUE(is_partitioned);
}

// Note: partition_copy() exists as well.
TEST(partition, ExampleOne) {
    const auto isLessThanZero = [](int i)->bool{ return i < 0; };
    std::vector<int> v{-1,1,-2,2,-3,3};

    // While we're guaranteed that the negative elements are on the left,
    // there is no guarantee about the order of these elements.
    // To guarantee order, use stable_partition().
    std::partition(v.begin(), v.end(), isLessThanZero);

    const bool is_partitioned = std::is_partitioned(v.cbegin(), v.cend(), isLessThanZero);
    EXPECT_TRUE(is_partitioned);
}

TEST(stable_partition, ExampleOne) {
    const auto isLessThanZero = [](int i)->bool{ return i < 0; };
    std::vector<int> v{-1,1,-2,2,-3,3};
    std::stable_partition(v.begin(), v.end(), isLessThanZero);

    const bool is_partitioned = std::is_partitioned(v.cbegin(), v.cend(), isLessThanZero);
    EXPECT_TRUE(is_partitioned);

    // With stable_partition(), we are guaranteed relative order.
    const std::vector<int> new_v{-1, -2, -3, 1, 2, 3};
    EXPECT_EQ(v, new_v);

}

TEST(partition_point, ExampleOne) {
    const auto isLessThanZero = [](int i)->bool{ return i < 0; };
    std::vector<int> v{-1,1,-2,2,-3,3, -4};
    std::stable_partition(v.begin(), v.end(), isLessThanZero);

    auto p_point = std::partition_point(v.begin(), v.end(), isLessThanZero);

    const bool is_partitioned = std::is_partitioned(v.cbegin(), v.cend(), isLessThanZero);
    EXPECT_TRUE(is_partitioned);

    EXPECT_EQ(*p_point, 1);
    std::vector<int> positives;
    std::vector<int> negatives;
    std::copy(v.begin(), p_point, std::back_inserter(negatives));
    std::copy(p_point, v.end(), std::back_inserter(positives));

    const std::vector<int> expected_positives{1,2,3};
    const std::vector<int> expected_negatives{-1,-2,-3,-4};
    EXPECT_EQ(positives, expected_positives);
    EXPECT_EQ(negatives, expected_negatives);
}

// Sorting operations.
TEST(is_sorted, ExampleOne) {
    const std::vector<int> v1{1,2,3,4,5};
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));

    const std::vector<int> v2{5,2,3,4,1};
    EXPECT_FALSE(std::is_sorted(v2.begin(), v2.end()));
}

TEST(sort, ExampleOne) {
    std::vector<int> v{1,3,2,4,4,5};
    std::sort(v.begin(), v.end());

    const std::vector<int> sorted_v{1,2,3,4,4,5};
    EXPECT_EQ(v, sorted_v);
}

TEST(sort, ExampleTwoWithPredicate) {
    std::vector<int> v{1,3,2,4,4,5};
    std::sort(v.begin(), v.end(), std::greater<int>());

    const std::vector<int> sorted_v{5,4,4,3,2,1};
    EXPECT_EQ(v, sorted_v);
}

TEST(is_sorted_until, ExampleOne) {
    std::vector<int> v{1, 2, 3, 4, 3, 5, 6};
    const auto iterator1 = std::is_sorted_until(v.cbegin(), v.cend());
    // Points to the last sorted element.
    EXPECT_EQ(*iterator1, 3);
    EXPECT_EQ(iterator1 - v.cbegin(), 4);

    std::sort(v.begin(), v.end());
    const auto iterator2 = std::is_sorted_until(v.cbegin(), v.cend());
    EXPECT_EQ(iterator2, v.cend()); // All elements are sorted.
    EXPECT_EQ(iterator2 - v.cbegin(), 7);
}

// Note: partial_sort_copy() exists as well.
TEST(partial_sort, ExampleOne) {
    std::vector<int> v{1,8,3,2,8,9,4};
    std::partial_sort(v.begin(), v.begin() + 3, v.end());

    const std::vector<int> partial_sorted_v{1,2,3,8,8,9,4};
    EXPECT_EQ(v, partial_sorted_v);
}

// A simple struct encapsulating the the name
// and age of a person. This will be used in stable_sort.
struct Person {
    int age;
    std::string name;

    bool operator==(const Person& other) const {
        return this->name == other.name && this->age == other.age;
    }
};

// Less than comparison is completed only by age.
bool operator<(const Person& lhs, const Person& rhs) {
    return lhs.age < rhs.age;
}

TEST(stable_sort, ExampleOne) {
    // This examples follows closely the one on
    // cppreference.com
    // Here, the persons are sorted by age, but if two
    // persons have the same age, their relative order is maintained.

    std::vector<Person> v = {
            {108, "Zaphod"},
            {32, "Arthur"},
            {108, "Ford"},
    };

    std::stable_sort(v.begin(), v.end());

    std::vector<Person> sorted_v = {
            {32, "Arthur"},
            {108, "Zaphod"},
            {108, "Ford"},
    };
    EXPECT_EQ(v, sorted_v);
}

TEST(nth_element, ExampleOne) {
    // Similar to partial_sort(), it'll get the first 5 elements
    // according to the provided comparator. The only difference
    // here is that they won't be sorted.
    std::vector<int> v{1, 3, 9, 9, 3, 2, 5, 8, 7, 3, 2};
    std::nth_element(v.begin(), v.begin() + 5, v.end(), std::greater<int>());

    const std::vector<int> greatest_five { 8, 5, 9, 9, 7, 3, 3, 3, 2, 2, 1 };
    EXPECT_EQ(v, greatest_five);
}

// Binary search operations (on sorted ranges).
TEST(lower_bound, ExampleOne) {
    const std::vector<int> data{1,2,3,4,5,6,7,8,9,9,10};
    const auto lower = std::lower_bound(data.cbegin(), data.cend(), 4);
    EXPECT_EQ(*lower, 4);
    // Lower bound includes the current element.
    EXPECT_EQ(lower - data.cbegin(), 3);
}

TEST(upper_bound, ExampleOne) {
    const std::vector<int> data{1,2,3,4,5,6,7,8,9,9,10};
    const auto upper = std::upper_bound(data.cbegin(), data.cend(), 9);
    EXPECT_EQ(*upper, 10);
    // Upper bound goes one past the current element.
    EXPECT_EQ(upper - data.cbegin(), 10);
}

TEST(binary_search, ExampleOne) {
    const std::vector<int> data{1,2,3,4,5,6,7,8,9,9,10};
    const bool found = std::binary_search(data.cbegin(), data.cend(), 3);
    EXPECT_TRUE(found);

    const bool not_found = std::binary_search(data.cbegin(), data.cend(), 11);
    EXPECT_FALSE(not_found);
}

TEST(equal_range, ExampleOne) {
    // This is useful when you want an upper and a lower bound.
    const std::vector<int> data{1,2,3,3,4,4,5,5,5,6,7,8};
    const auto [lower, upper] = std::equal_range(data.cbegin(), data.cend(), 5);
    EXPECT_EQ(*lower, 5);
    EXPECT_EQ(lower - data.cbegin(), 6);

    EXPECT_EQ(*upper, 6);
    EXPECT_EQ(upper - data.cbegin(), 9);
}

// Other operations (on sorted ranges).
TEST(merge, ExampleOne) {
    std::vector<int> v1{0, 1, 2, 3, 3, 4, 5};
    std::vector<int> v2{0, 2, 3, 4, 4, 5};
    std::vector<int> destination;
    destination.reserve(v1.size() + v2.size());
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(destination));

    const std::vector<int> merged{0,0,1,2,2,3,3,3,4,4,4,5,5};
    EXPECT_EQ(destination, merged);
}

// Taken from cppreference.com, we can use std::merge_sort and
// std::inplace_merge to implement the sorting algorithm merge_sort.
template<class Iter>
void merge_sort(Iter first, Iter last) {
    if (last - first > 1) {
        const Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        // Merges two consecutive sorted ranges into one range.
        std::inplace_merge(first, middle, last);
    }
}

TEST(inplace_merge, ExampleOne) {
    std::vector<int> v{9, 3, -4, 4, 8, 9, 2, 2};
    // See implementation above.
    merge_sort(v.begin(), v.end());

    const std::vector<int> v_sorted{-4, 2, 2, 3, 4, 8, 9, 9};
    EXPECT_EQ(v, v_sorted);
}

// Set operations (on sorted ranges).
TEST(includes, ExampleOne) {
    // std::includes returns true if the first sorted range
    // is a non-contiguous subsequence of the second sorted range.
    const std::vector<char> v{'a', 'b', 'c', 'd', 'e', 'f'};

    const std::vector<char> sub_v1{'a', 'b', 'c'};
    const bool v1_is_included = std::includes(v.cbegin(), v.cend(), sub_v1.cbegin(), sub_v1.cend());
    EXPECT_TRUE(v1_is_included);

    const std::vector<char> sub_v2{'a', 'c', 'f'};
    const bool v2_is_included = std::includes(v.cbegin(), v.cend(), sub_v2.cbegin(), sub_v2.cend());
    EXPECT_TRUE(v2_is_included);

    const std::vector<char> sub_v3{'a', 'c', 'x'};
    const bool v3_is_included = std::includes(v.cbegin(), v.cend(), sub_v3.cbegin(), sub_v3.cend());
    EXPECT_FALSE(v3_is_included);
}

TEST(set_difference, ExampleOne) {
    // Takes the difference between the two sorted ranges.
    const std::vector<char> v1{'a', 'b', 'c', 'd', 'e', 'f'};
    const std::vector<char> v2{'b', 'c', 'd'};
    std::vector<char> difference;
    std::set_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), std::back_inserter(difference));

    const std::vector expected_difference{'a', 'e', 'f'};
    EXPECT_EQ(difference, expected_difference);
}

TEST(set_intersection, ExampleOne) {
    // Takes the intersection between two sorted ranges.
    const std::vector<int> v1{1,2,3,4,5,6};
    const std::vector<int> v2{4,5,6,7,8,9};
    std::vector<int> intersection;

    std::set_intersection(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), std::back_inserter(intersection));

    const std::vector<int> expected_intersection{4,5,6};
    EXPECT_EQ(intersection, expected_intersection);
}

TEST(set_symmetric_difference, ExampleOne) {
    // Takes the symmetric difference between two sorted ranges.
    const std::vector<int> v1{1,2,3,4,5,6};
    const std::vector<int> v2{4,5,6,7,8,9};
    std::vector<int> symmetric_difference;

    std::set_symmetric_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                                  std::back_inserter(symmetric_difference));

    const std::vector<int> expected_symmetric_difference{1,2,3,7,8,9};
    EXPECT_EQ(symmetric_difference, expected_symmetric_difference);
}

TEST(set_union, ExampleOne) {
    // Takes the union between two sorted ranges.
    const std::vector<int> v1{1,2,3,4,5,6};
    const std::vector<int> v2{4,5,6,7,8,9};
    std::vector<int> union_t;

    std::set_union(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), std::back_inserter(union_t));

    const std::vector<int> expected_union{1,2,3,4,5,6,7,8,9};
    EXPECT_EQ(union_t, expected_union);
}

TEST(set_union, ExampleTwoWithDuplicates) {
    // Takes the union between two sorted ranges.
    const std::vector<int> v1{1,1,2,3,4,5,6};
    const std::vector<int> v2{1,1,1,4,5,6,7,8,9};
    std::vector<int> union_t;

    std::set_union(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), std::back_inserter(union_t));

    const std::vector<int> expected_union{1,1,1,2,3,4,5,6,7,8,9};
    EXPECT_EQ(union_t, expected_union);
}

// Heap operations.
TEST(is_heap, ExampleOne) {
    // Checks if the elements in the range are a max heap.
    const std::vector<int> v{9, 5, 4, 1, 1, 3};
    const bool v_is_heap = std::is_heap(v.cbegin(), v.cend());
    EXPECT_TRUE(v_is_heap);
}

TEST(is_heap_until, ExampleOne) {
    // Finds largest subsequence in the range that make a max heap.
    const std::vector<int> v1{9, 5, 4, 1, 1, 3};
    const auto iterator = std::is_heap_until(v1.cbegin(), v1.cend());
    EXPECT_EQ(iterator, v1.cend());

    const std::vector<int> v2{9, 5, 4, 1, 1, 3, 2, 6};
    const auto iterator2 = std::is_heap_until(v2.cbegin(), v2.cend());
    EXPECT_EQ(iterator2, v2.cend() - 1);
}

TEST(make_heap, ExampleOne) {
    // Constructs a max heap.
    std::vector<int> v{1,2,3,4,5,6,5,4};
    std::make_heap(v.begin(), v.end());

    const std::vector<int> expected_heap{6,5,5,4,2,3,1,4};
    EXPECT_EQ(v, expected_heap);

}

TEST(push_heap, ExampleOne) {
    std::vector<int> v{1,2,3,4,5,6,5,4};
    std::make_heap(v.begin(), v.end());

    v.push_back(9);
    // Pushes 9 onto the heap while maintaining max heap conditions.
    std::push_heap(v.begin(), v.end());

    const std::vector<int> expected_heap{9,6,5,5,2,3,1,4,4};
    EXPECT_EQ(v, expected_heap);
}

TEST(pop_heap, ExampleOne) {
    // Removes the largest element.
    std::vector<int> v{1,2,3,4,5,6,5,4};
    std::make_heap(v.begin(), v.end());

    std::pop_heap(v.begin(), v.end());

    const std::vector<int> expected_heap{5,4,5,4,2,3,1,6};
    EXPECT_EQ(v, expected_heap);
}

TEST(sort_heap, ExampleOne) {
    // Converts the max heap into a sorted range in ascending order.
    std::vector<int> v{1,2,3,4,5,6,5,4};
    std::make_heap(v.begin(), v.end());

    const std::vector<int> expected_heap{6,5,5,4,2,3,1,4};
    EXPECT_EQ(v, expected_heap);

    std::sort_heap(v.begin(), v.end());
    const std::vector<int> sorted_v{1,2,3,4,4,5,5,6};
    EXPECT_EQ(v, sorted_v);
}

// Minimum, maximum operations.
TEST(max, ExampleOne) {
    EXPECT_EQ(std::max(1,2), 2);
    EXPECT_EQ(std::max('a', 'z'), 'z');
}

TEST(max_element, ExampleOne) {
    const std::vector<int> v{1,1,2,3,4,5,6};
    const auto iterator = std::max_element(v.cbegin(), v.cend());
    EXPECT_EQ(*iterator, 6);
    EXPECT_EQ(iterator, v.cend() - 1);
}

TEST(min, ExampleOne) {
    EXPECT_EQ(std::min(1,2), 1);
    EXPECT_EQ(std::min('a', 'z'), 'a');
}

TEST(min_element, ExampleOne) {
    const std::vector<int> v{1,1,2,3,4,5,6};
    const auto iterator = std::min_element(v.cbegin(), v.cend());
    EXPECT_EQ(*iterator, 1);
    EXPECT_EQ(iterator, v.cbegin());
}

TEST(minmax, ExampleOne) {
    const auto bounds = std::minmax({3,8,4,4,2,1});
    EXPECT_EQ(bounds.first, 1);
    EXPECT_EQ(bounds.second, 8);
}

TEST(minmax_element, ExampleOne) {
    const std::vector<int> v{1,1,2,3,4,5,6};
    const auto [min, max] = std::minmax_element(v.cbegin(), v.cend());
    EXPECT_EQ(*min, 1);
    EXPECT_EQ(*max, 6);
}

TEST(clamp, ExampleOne) {
    int i = 11;
    const int max_bound = 10;
    const int min_bound = 1;

    int new_i = std::clamp(new_i, min_bound, max_bound);
    EXPECT_EQ(new_i, 10);

    i = -1;
    new_i = std::clamp(i, min_bound, max_bound);
    EXPECT_EQ(new_i, 1);

    i = 5;
    new_i = std::clamp(i, min_bound, max_bound);
    EXPECT_EQ(new_i, 5);
}

// Comparison operations.
TEST(equal, ExampleOne) {
    const std::vector<int> v1{1,2,3,4,5};
    const std::vector<int> v2{1,2,3,4,5};
    const bool is_equal1 = std::equal(v1.cbegin(), v1.cend(), v2.cbegin());
    EXPECT_TRUE(is_equal1);

    const std::vector<int> diff{-1,2,3,4,5};
    const bool is_equal2 = std::equal(v1.cbegin(), v1.cend(), diff.cbegin());
    EXPECT_FALSE(is_equal2);
}

TEST(lexicographical_compare, ExampleOne) {
    const std::vector<char> v1 {'a', 'b', 'b'};
    const std::vector<char> v2 {'a', 'b', 'c'};
    const bool compare_words = std::lexicographical_compare(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
    EXPECT_TRUE(compare_words);
}

// Permutation operations.
TEST(is_permutation, ExampleOne) {
    const std::vector<int> v1{1,2,3};
    const std::vector<int> v2{2,1,3};

    bool is_permutation = std::is_permutation(v1.cbegin(), v1.cend(), v2.cbegin());
    EXPECT_TRUE(is_permutation);

    const std::vector<int> v3{1,2,2};
    is_permutation = std::is_permutation(v1.cbegin(), v1.cend(), v3.cbegin());
    EXPECT_FALSE(is_permutation);
}

TEST(next_permutation, ExampleOne) {
    std::vector<int> v{1,2,3,4,5};
    std::next_permutation(v.begin(), v.end());

    const std::vector<int> permuted_v{1,2,3,5,4};
    EXPECT_EQ(v, permuted_v);
}

TEST(prev_permutation, ExampleOne) {
    std::vector<int> v{1,2,3,5,4};
    std::prev_permutation(v.begin(), v.end());

    const std::vector<int> permuted_v{1,2,3,4,5};
    EXPECT_EQ(v, permuted_v);
}

// Numeric operations.
TEST(iota, ExampleOne) {
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);

    const std::vector<int> iota_v{1,2,3,4,5,6,7,8,9,10};
    EXPECT_EQ(v, iota_v);
}

TEST(accumulate, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};

    const int sum = std::accumulate(v.cbegin(), v.cend(), 0);
    EXPECT_EQ(sum, 15);

    const int product = std::accumulate(v.cbegin(), v.cend(), 1, std::multiplies<int>());
    EXPECT_EQ(product, 120);
}

TEST(inner_product, ExampleOne) {
    const std::vector<int>v1{1,2,3,4,5};
    const std::vector<int>v2{1,2,3,4,5};

    const int inner_product = std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), 0);
    EXPECT_EQ(inner_product, 55);
}

TEST(adjacent_difference, ExampleOne) {
    const std::vector<int> v{2, 4, 6, 8, 10, 12};
    std::vector<int> differences;
    std::adjacent_difference(v.cbegin(), v.cend(), std::back_inserter(differences));

    const std::vector<int> twos(v.size(), 2);
    EXPECT_EQ(differences, twos);
}

TEST(partial_sum, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    std::vector<int> sums;
    std::partial_sum(v.begin(), v.end(), std::back_inserter(sums));

    const std::vector<int> expected_sums{1,3,6,10,15};
    EXPECT_EQ(sums, expected_sums);
}

TEST(partial_sum, ExampleTwoWithMultiply) {
    const std::vector<int> v{2,2,2,2,2};
    std::vector<int> powers;
    std::partial_sum(v.begin(), v.end(), std::back_inserter(powers), std::multiplies<int>());

    const std::vector<int> expected_powers{2,4,8,16,32};
    EXPECT_EQ(powers, expected_powers);
}

TEST(exclusive_scan, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    std::vector<int> sums;
    std::exclusive_scan(v.begin(), v.end(), std::back_inserter(sums), 0);

    const std::vector<int> expected_sums{0,1,3,6,10};
    EXPECT_EQ(sums, expected_sums);
}

TEST(inclusive_scan, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    std::vector<int> sums;
    std::inclusive_scan(v.begin(), v.end(), std::back_inserter(sums));

    const std::vector<int> expected_sums{1,3,6,10,15};
    EXPECT_EQ(sums, expected_sums);
}

TEST(reduce, ExampleOne) {
    // Similar to std::accumulate, but the elements may be grouped
    // and rearranged in arbitrary order. This allows for parallelization.
    // See: https://blog.tartanllama.xyz/accumulate-vs-reduce/
    const std::vector<int> v{1,2,3,4,5};

    const int sum = std::reduce(v.cbegin(), v.cend(), 0);
    EXPECT_EQ(sum, 15);

    const int product = std::reduce(v.cbegin(), v.cend(), 1, std::multiplies<int>());
    EXPECT_EQ(product, 120);
}

TEST(transform_reduce, ExampleOne) {
    std::vector<int> v{1,2,3,4,5};
    const int result = std::transform_reduce(v.cbegin(), v.cend(), 0, std::plus<>(), [](int a){return a * a;});
    // Multiples (transformation):
    // {1,2,3,4,5} -> {1,4,9,16,25}
    // Then adds (reduction):
    // 1 + 4 + 9 + 16 + 25
    // = 55
    EXPECT_EQ(result, 55);
}

TEST(transform_exclusive_scan, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    std::vector<int> sums;
    std::transform_exclusive_scan(v.cbegin(), v.cend(), std::back_inserter(sums), 0, std::plus<int>{},
                                  [](int i){return i * 2;});

    // Multiplies by 2 (transformation)
    // {1,2,3,4,5} -> {2, 4, 6, 8, 10}
    // Then adds (exclusive sum):
    // -> {0, 2, 6, 12, 20}
    const std::vector<int> expected_sums{0,2,6,12,20};
    EXPECT_EQ(sums, expected_sums);
}

TEST(transform_inclusive_scan, ExampleOne) {
    const std::vector<int> v{1,2,3,4,5};
    std::vector<int> sums;
    std::transform_inclusive_scan(v.cbegin(), v.cend(), std::back_inserter(sums), std::plus<int>{},
                                  [](int i){return i * 2;});

    // Multiplies by 2 (transformation)
    // {1,2,3,4,5} -> {2, 4, 6, 8, 10}
    // Then adds (inclusive sum):
    // -> {2, 6, 12, 20, 30}
    const std::vector<int> expected_sums{2,6,12,20,30};
    EXPECT_EQ(sums, expected_sums);
}

// C library.
TEST(qsort, ExampleOne) {
    int a[] = {-10, 1, 14, 3, 2, 2, 5};
    constexpr std::size_t size = sizeof(a) / sizeof(int);

    const auto compare = [](const void* a, const void* b)->int {
        return ( *(int*)a - *(int*) b);
    };
    std::qsort(a, size, sizeof(int), compare);

    int expected_a[] = {-10, 1, 2, 2, 3, 5, 14};
    EXPECT_EQ(*a, *expected_a);
}

TEST(bsearch, ExampleOne) {
    int a[] = {-2,-1,1,2,3,4,5};
    constexpr std::size_t size = sizeof(a) / sizeof(int);

    const auto compare = [](const void* a, const void* b)->int {
        const int* aa = (int *)a;
        const int* bb = (int *)b;
        if (*aa < *bb) return -1;
        else if (*aa > *bb) return 1;
        return 0;
    };
    int key = 4;
    int *find = (int *)std::bsearch(&key, a, size, sizeof(int), compare);
    EXPECT_EQ(*find, 4);
    EXPECT_EQ(find - a, 5);
}

