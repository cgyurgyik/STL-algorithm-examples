# About
As I listened to quite a few talks about the importance of using C++ STL algorithms, I realized I needed to practice using them myself. This repository will provide simple examples for each algorithm. The target audience is C++ beginners, in hopes to show them the simplicity and power of these algorithms. Use this not as a replacement, but as another source of examples that can be quickly read and understood.

## Example
Given a std::vector ```v``` of integers:

```
// Determines whether 'v' contains 4.
bool contains_four = false;
for (int i = 0; i < v.size(); ++i) {
  if (i == 4) { 
    contains_four = true;
    break;
  }
}
```
This could be improved upon by using a range-based loop:
```
// Determines whether 'v' contains 4.
bool contains_four = false;
for (const int i : v) {
  if (i == 4) {
    contains_four = true;
    break;
  }
}
```

Even better though, is using ```std::any_of```: 

```
// Determines whether 'v' contains 4.
const bool contains_four = std::any_of(v.cbegin(), v.cend(), [](int i)->bool{ return i == 4; });
```

Here, we've taken a raw ```for loop``` and replaced it with an STL algorithm that, in one line, tells us more clearly what is occurring. This improves readability, minimizes number of lines of code, and provides (likely) the best algorithm for what you're trying to do.

With the release of C++20, this will simplify even further using ranges:
```
const bool contains_four = std::ranges::any_of(v, [](int i)->bool{ return i == 4; }); 
```

## Related STL Talks
- [Meeting C++ 2019: Connor Hoekstra "Better Algorithm Intuition](https://www.youtube.com/watch?v=TSZzvo4htTQ)
- [CppCon 2019: Connor Hoekstra "Algorithm Intuition" Part 1](https://www.youtube.com/watch?v=pUEnO6SvAMo)
- [CppCon 2019: Connor Hoekstra "Algorithm Intuition" Part 2](https://www.youtube.com/watch?v=sEvYmb3eKsw)
- [CppCon 2019: Mathieu Ropert "This Videogame Programmer Used the STL and You Will Never Guess What Happened Next"](https://www.youtube.com/watch?v=6hC9IxqdDDw)
- [CppCon 2018: Jonathan Boccara "105 STL Algorithms in Less Than an Hour"](https://www.youtube.com/watch?v=2olsGf6JIkU&t=2459s)
- [GoingNative C++ 2013: Sean Parent "C++ Seasoning"](https://www.youtube.com/watch?v=W2tWOdzgXHA)

## References
- [cppreference.com](https://en.cppreference.com/w/cpp/algorithm)
- [Google Test Suite](https://github.com/google/googletest)
