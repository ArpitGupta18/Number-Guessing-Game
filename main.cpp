#include <iostream>

void playGame(int maxNumber, int maxTries);

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string name;
    std::cout << "Welcome to the number guessing game!!\n";
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);

    char playAgain;

    do {
        int choice;
        std::cout << "\nHello, " << name << "! Choose a difficulty level:\n";
        std::cout << "1. Easy (1–20, 7 tries)\n";
        std::cout << "2. Medium (1–50, 6 tries)\n";
        std::cout << "3. Hard (1–100, 5 tries)\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        int maxNumber = 100;
        int maxTries = 5;

        switch (choice) {
            case 1:
                maxNumber = 20;
                maxTries = 7;
                break;
            case 2:
                maxNumber = 50;
                maxTries = 6;
                break;
            case 3:
                maxNumber = 100;
                maxTries = 5;
                break;
            default:
                std::cout << "Invalid choice. Using default (Hard).\n";
        }

        playGame(maxNumber, maxTries);

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
        std::cin.ignore();
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}

void playGame(int maxNumber, int maxTries) {
    int secretNumber = std::rand() % maxNumber + 1;
    int guess = 0;
    int attempts = 0;
    bool won = false;

    std::cout << "\nI've picked a number between 1 and " << maxNumber << ". You have " << maxTries << " attempts!\n";

    while (attempts < maxTries) {
        std::cout << "Guess #" << (attempts + 1) << ": ";
        std::cin >> guess;

        attempts++;

        if (guess > secretNumber) {
            std::cout << "Lower\n";
        } else if (guess < secretNumber) {
            std::cout << "Upper\n";
        } else {
            std::cout << "You guess the number (" << secretNumber << ") in " << attempts << " attempts!\n";
            won = true;
            break;
        }
    }

    if (!won) {
        std::cout << "Out of tries! The number was: " << secretNumber << "\n";
    }
}
