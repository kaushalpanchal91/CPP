#include <iostream>
#include <vector>

bool isPrime(int num) {
    if (num <= 1) return false; // 0 and 1 are not prime numbers
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false; // Found a divisor, not prime
    }
    return true; // It's a prime number
}

std::vector<int> generatePrimes(int limit) {
    std::vector<int> primes;
    for (int num = 2; num <= limit; ++num) {
        if (isPrime(num)) {
            primes.push_back(num); // Add prime number to the vector
        }
    }
    return primes; // Return the list of prime numbers
}

int main() {
    int limit;
    std::cout << "Enter the limit: ";
    std::cin >> limit;

    std::vector<int> primes = generatePrimes(limit);
    std::cout << "Prime numbers up to " << limit << ": ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
