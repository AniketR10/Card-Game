#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <ctime>

class Random {
public:
    // Create a static random number generator (Mersenne Twister)
    static std::mt19937 mt; // Mersenne Twister instance

    // Constructor that seeds the Mersenne Twister generator with current time
    Random() : generator(static_cast<unsigned int>(std::time(nullptr))) {}

    // Generate a random integer between min and max (inclusive)
    int getInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    // Generate a random floating-point number between min and max (inclusive)
    double getDouble(double min, double max) {
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }

    // Generate a random boolean value (true/false)
    bool getBool() {
        return getInt(0, 1) == 1;
    }

private:
    std::mt19937 generator;  // Mersenne Twister generator
};

// Define the static random generator
std::mt19937 Random::mt{ static_cast<unsigned int>(std::time(nullptr)) };

#endif // RANDOM_H
