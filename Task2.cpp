#include <iostream>

// Meta-function to calculate sumsequence F(n, k)
template <int n, int k>
struct SumSequence {
    static constexpr int value = n * SumSequence<n, k - 1>::value + n * (k == 1 ? 0 : 1);
};

// Base of Recursion
template <int n>
struct SumSequence<n, 1> {
    static constexpr int value = n;
};

int main() {
    constexpr int result = SumSequence<3, 2>::value;
    std::cout << "Result: " << result << std::endl;
    return 0;
}