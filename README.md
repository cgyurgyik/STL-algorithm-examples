# About
As I listened to quite a few talks about the importance of using C++ STL algorithms, I realized I needed to practice using them myself. This repository will provide simple examples for each algorithm. The target audience is C++ beginners, in hopes to show them the simplicity and power of these algorithms. For example, given a vector ```v``` of integers:

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
Could be improved upon by using a range-based loop:
```
TODO
```
Even better though, is using ```std::any_of```. 
```
// Determines whether 'v' contains 4.
const bool equals_four = std::any_of(v.cbegin(), v.cend(), 
                         [](int i)->int{ return i == 4; });
```

## Related STL Talks
- [CppCon 2018: Jonathan Boccara "105 STL Algorithms in Less Than an Hour"](https://www.youtube.com/watch?v=2olsGf6JIkU&t=2459s)
- [CppCon 2019: Connor Hoekstra "Algorithm Intuition" Part 1](https://www.youtube.com/watch?v=pUEnO6SvAMo)
- [CppCon 2019: Connor Hoekstra "Algorithm Intuition" Part 2](https://www.youtube.com/watch?v=sEvYmb3eKsw)
- [CppCon: Mathieu Ropert "This Videogame Programmer Used the STL and You Will Never Guess What Happened Next](https://www.youtube.com/watch?v=6hC9IxqdDDw)

## References
- [cppreference.com](https://en.cppreference.com/w/cpp/algorithm)
