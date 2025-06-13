#include <iostream>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // The number after the mod operator (%) determines the range of the value to generate. So 5 means (0-4)
    int secretNumber = std::rand() % 500 + 1;
    std::cout << secretNumber << "\n";
    return 0;
}