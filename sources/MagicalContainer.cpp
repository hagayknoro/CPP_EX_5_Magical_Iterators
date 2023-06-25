#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {

    // Function to check if a number is prime
    bool isPrime(int elem) {
        if (elem < 2) {
            return false;
        }
        for (int i = 2; i * i <= elem; ++i) {
            if (elem % i == 0) {
                return false;
            }
        }
        return true;
    }

    // MagicalContainer implementation

    // Add an element to the container
    void MagicalContainer::addElement(int element) {
        originalElement.push_back(element);
        originalElementSort();
        sortedFix();
        primeFix();
        crossFix();
    }

    // Remove an element from the container
    void MagicalContainer::removeElement(int element) {
        // Make sure the element is in the originalElement
        bool inList = false;
        for (auto itr = originalElement.begin(); itr != originalElement.end(); itr++) {
            if (*itr == element) {
                inList = true;
                break;
            }
        }
        if (!inList)
            throw runtime_error("You can't remove an element that is not in the list.");

        originalElement.erase(remove(originalElement.begin(), originalElement.end(), element), originalElement.end());
        sortedFix();
        primeFix();
        crossFix();
    }

    // Get the size of the container
    int MagicalContainer::size() {
        return originalElement.size();
    }

    // Fix the crossElement vector based on the originalElement vector
    void MagicalContainer::crossFix() {
        crossElement.clear();
        auto begin = originalElement.begin();
        auto end = --originalElement.end();

        while (begin < end) {
            crossElement.push_back(&(*begin));
            crossElement.push_back(&(*end));
            begin++;
            end--;
        }
        if (begin == end)
            crossElement.push_back(&(*begin));
    }

    // Fix the primeElement vector based on the originalElement vector
    void MagicalContainer::primeFix() {
        primeElement.clear();
        for (auto itr = originalElement.begin(); itr != originalElement.end(); ++itr) {
            if (isPrime(*itr))
                primeElement.push_back(&(*itr));
        }
    }

    // Fix the sortedElement vector based on the originalElement vector
    void MagicalContainer::sortedFix() {
        sortedElement.clear();
        for (auto itr = originalElement.begin(); itr != originalElement.end(); ++itr) {
            sortedElement.push_back(&(*itr));
        }
    }

    // Sort the originalElement vector in ascending order
    void MagicalContainer::originalElementSort() {
        for (unsigned long i = 0; i < originalElement.size(); ++i) {
            for (unsigned long j = 0; j < originalElement.size() - i - 1; j++) {
                if (originalElement[j] > originalElement[j + 1]) {
                    int tmp = originalElement[j];
                    originalElement[j] = originalElement[j + 1];
                    originalElement[j + 1] = tmp;
                }
            }
        }
    }

    // AscendingIterator implementation

    // Constructor for AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
        : container(container), iter(container.sortedElement.begin())
    {}

    // Copy constructor for AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
        : container(other.container), iter(other.iter)
    {}

    // Assignment operator for AscendingIterator
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
        if (&container != &other.container)
            throw runtime_error("You can't assign iterators from different containers.");
        iter = other.iter;
        return *this;
    }

    // Set the iterator to the beginning
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin() {
        iter = container.sortedElement.begin();
        return *this;
    }

    // Set the iterator to the end
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end() {
        iter = container.sortedElement.end();
        return *this;
    }

    // Increment the iterator to the next element
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if (iter == container.sortedElement.end())
            throw runtime_error("Iterator out of range");
        ++iter;
        return *this;
    }

    // Dereference the iterator to get the value
    int MagicalContainer::AscendingIterator::operator*() {
        if (iter == container.sortedElement.end())
            throw out_of_range("Iterator out of range");

        return **iter;
    }

    // Compare two AscendingIterators for equality
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        if (&container != &other.container)
            throw invalid_argument("You can't compare iterators from different containers.");
        return iter == other.iter;
    }

    // Compare two AscendingIterators for inequality
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }

    // Compare two AscendingIterators for greater than
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
        if (&container != &other.container) {
            throw invalid_argument("You can't compare iterators from different containers.");
        }
        return iter > other.iter;
    }

    // Compare two AscendingIterators for less than
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
        if (&container != &other.container) {
            throw invalid_argument("You can't compare iterators from different containers.");
        }
        return iter < other.iter;
    }

    // SideCrossIterator implementation

    // Constructor for SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
        : container(container), iter(container.crossElement.begin())
    {}

    // Copy constructor for SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
        : container(other.container), iter(other.iter)
    {}

    // Set the iterator to the beginning
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() {
        iter = container.crossElement.begin();
        return *this;
    }

    // Set the iterator to the end
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end() {
        iter = container.crossElement.end();
        return *this;
    }

    // Assignment operator for SideCrossIterator
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
        if (&container != &other.container)
            throw runtime_error("You can't assign iterators from different containers.");
        iter = other.iter;
        return *this;
    }

    // Increment the iterator to the next element
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (iter == container.crossElement.end())
            throw runtime_error("Iterator out of range");
        ++iter;
        return *this;
    }

    // Dereference the iterator to get the value
    int& MagicalContainer::SideCrossIterator::operator*() {
        if (iter == container.crossElement.end())
            throw out_of_range("Iterator out of range");

        return **iter;
    }

    // Compare two SideCrossIterators for equality
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        if (&container != &other.container)
            throw invalid_argument("You can't compare iterators from different containers.");
        return iter == other.iter;
    }

    // Compare two SideCrossIterators for inequality
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }

    // Compare two SideCrossIterators for greater than
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
        if (&container != &other.container) {
            throw invalid_argument("You can't compare iterators from different containers.");
        }
        return iter > other.iter;
    }

    // Compare two SideCrossIterators for less than
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
        if (&container != &other.container) {
            throw invalid_argument("You can't compare iterators from different containers.");
        }
        return iter < other.iter;
    }

    // PrimeIterator implementation

    // Constructor for PrimeIterator
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
        : container(container), iter(container.primeElement.begin())
    {}

    // Copy constructor for PrimeIterator
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
        : container(other.container), iter(other.iter)
    {}

    // Assignment operator for PrimeIterator
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
        if (&container != &other.container)
            throw runtime_error("You can't assign iterators from different containers.");
        iter = other.iter;
        return *this;
    }

    // Set the iterator to the beginning
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin() {
        iter = container.primeElement.begin();
        return *this;
    }

    // Set the iterator to the end
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end() {
        iter = container.primeElement.end();
        return *this;
    }

    // Increment the iterator to the next element
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if (iter == container.primeElement.end())
            throw runtime_error("Iterator out of range");
        ++iter;
        return *this;
    }

    // Dereference the iterator to get the value
    int& MagicalContainer::PrimeIterator::operator*() {
        if (iter == container.primeElement.end())
            throw out_of_range("Iterator out of range");

        return **iter;
    }

    // Compare two PrimeIterators for equality
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        if (&container != &other.container)
            throw invalid_argument("You can't compare iterators from different containers.");
        return iter == other.iter;
    }

    // Compare two PrimeIterators for inequality
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        return !(*this == other);
    }

    // Compare two PrimeIterators for greater than
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw invalid_argument("You can't compare iterators from different containers.");
        }
        return iter > other.iter;
    }

    // Compare two PrimeIterators for less than
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw invalid_argument("You can't compare iterators from different containers.");
        }
        return iter < other.iter;
    }
}
