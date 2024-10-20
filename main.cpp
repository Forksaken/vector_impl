#include "vector.h"

int main() {
    Vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "Vector elements: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    vec.push_back(6);
    vec.push_back(7);

    std::cout << "Element at index 2: " << vec.at(2) << std::endl;
    std::cout << "Element at index 5: " << vec[5] << std::endl;

    Vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "vec == vec2: " << (vec == vec2 ? "true" : "false") << std::endl;

    vec.pop_back();
    std::cout << "Vector size after pop_back: " << vec.get_size() << std::endl;

    std::cout << "Vector elements: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

