#include <iostream>
#include <random>

class NumberGuesser {

private:
    int lowerBound;
    int upperBound;
    int goalNumber;

    int getRandomNumber(int low, int high) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(low, high);
        return distrib(gen);
    }

public:
    NumberGuesser(int low, int high) {
        if (low > high) {
            std::cout << "Switching the bounds" << std::endl;
            std::swap(low, high);
        }

        lowerBound = low;
        upperBound = high;
        goalNumber = getRandomNumber(lowerBound, upperBound);
    }

    int getGuess() {
        while (true) {
            std::cout << "Guess a number between " << lowerBound << " and " << upperBound << ": ";
            int guess;
            std::cin >> guess;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid input. Try again.\n";
                continue;
            }

            return guess;
        }
    }

    bool validateBounds(int guess) {
        return guess > lowerBound && guess < upperBound;
    }

    void updateBounds(int guess) {
        if (guess < goalNumber) {
            lowerBound = guess;
        } else if (guess > goalNumber) {
            upperBound = guess;
        }
    }

    int getGoalNumber() const {
        return goalNumber;
    }

    int getLowerBound() const {
        return lowerBound;
    }

    int getUpperBound() const {
        return upperBound;
    }
};

int main() {
    NumberGuesser n(1, 100);

    while (true) {
        int guess = n.getGuess();

        if (!n.validateBounds(guess)) {
            std::cout << "Guess out of bounds. Try again.\n";
            continue;
        }

        if (guess == n.getGoalNumber()) {
            std::cout << "You guessed the correct number: " << guess << ".\n";
            break;
        }

        n.updateBounds(guess);
        std::cout << "Wrong! Try again. The number is between "
                  << n.getLowerBound() << " and " << n.getUpperBound() << ".\n";
    }

    return 0;
}
