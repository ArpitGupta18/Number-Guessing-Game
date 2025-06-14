#include <iostream>
#include <fstream>
#include <limits>
#include <filesystem>

void playGame(int maxNumber, int maxTries, const std::string &highscoreFile);

int readHighScore(const std::string &filename);

void writeHighScore(const std::string &filename, int score);

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string name;
    std::cout << "Welcome to the number guessing game!!\n";
    std::cout << "Please enter your name: ";
    std::getline(std::cin, name);

    std::filesystem::create_directory("highscores");
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
        std::string highscoreFile;
        switch (choice) {
            case 1:
                maxNumber = 20;
                maxTries = 7;
                highscoreFile = "highscores/highscore_easy.txt";
                break;
            case 2:
                maxNumber = 50;
                maxTries = 6;
                highscoreFile = "highscores/highscore_medium.txt";
                break;
            case 3:
                maxNumber = 100;
                maxTries = 5;
                highscoreFile = "highscores/highscore_hard.txt";
                break;
            default:
                std::cout << "Invalid choice. Using default (Hard).\n";
                highscoreFile = "highscores/highscore_hard.txt";
        }

        int highScore = readHighScore(highscoreFile);

        if (highScore == std::numeric_limits<int>::max()) {
            std::cout << "\nNo high score yet for this difficulty. Be the first to set in!\n";
        } else {
            std::cout << "\nCurrent high score: " << highScore << " attempts\n";
        }

        playGame(maxNumber, maxTries, highscoreFile);

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
        std::cin.ignore();
    } while (playAgain == 'y' || playAgain == 'Y');
}

int readHighScore(const std::string &filename) {
    std::ifstream file(filename);
    int score;
    if (file >> score) {
        return score;
    }
    return std::numeric_limits<int>::max();
}


void writeHighScore(const std::string &filename, int score) {
    std::ofstream file(filename);
    file << score;
}

void playGame(const int maxNumber, const int maxTries, const std::string &highscoreFile) {
    const int secretNumber = std::rand() % maxNumber + 1;
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
    } else {
        int highScore = readHighScore(highscoreFile);
        if (attempts < highScore) {
            std::cout << "NEW HIGH SCORE! You beat the previous best of " << highScore << " attempts!\n";
            writeHighScore(highscoreFile, attempts);
        } else {
            std::cout << "Your score: " << attempts << " attempts. High score remains at " << highScore << "\n";
        }
    }
}
