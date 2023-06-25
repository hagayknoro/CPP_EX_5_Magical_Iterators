#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <iterator>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>



namespace ariel {
    bool isPrime(int elem);
    class MagicalContainer {
    public:
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;

        void addElement(int element);
        void removeElement(int element);
        int size();
        void crossFix();
        void primeFix();
        void sortedFix();
        void originalElementSort();



    private:
        std::vector<int> originalElement;
        std::vector<int*> sortedElement;
        std::vector<int*> crossElement;
        std::vector<int*> primeElement;

        friend class AscendingIterator;
        friend class SideCrossIterator;
        friend class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator {
    public:
        AscendingIterator(MagicalContainer& container);
        AscendingIterator(const AscendingIterator& other);
        ~AscendingIterator() = default;
        // Copy assignment operator
        AscendingIterator& operator=(const AscendingIterator& other);
        // Move constructor
        AscendingIterator(AscendingIterator&& other) noexcept = default;
        // Move assignment operator
        AscendingIterator& operator=(AscendingIterator&& other) noexcept {return *this;}

        AscendingIterator &begin();
        AscendingIterator &end();

        AscendingIterator& operator++();
        int operator*();
        bool operator==(const AscendingIterator& other) const;
        bool operator!=(const AscendingIterator& other) const;
        bool operator>(const AscendingIterator& other) const;
        bool operator<(const AscendingIterator& other) const;

    private:
        MagicalContainer& container;
        std::vector<int*>::iterator iter;
    };

    class MagicalContainer::SideCrossIterator {
    public:
        SideCrossIterator(MagicalContainer& container);
        SideCrossIterator(const SideCrossIterator& other);
        ~SideCrossIterator() = default;
        // Copy assignment operator
        SideCrossIterator& operator=(const SideCrossIterator& other);
        // Move constructor
        SideCrossIterator(SideCrossIterator&& other) noexcept = default; 
        // Move assignment operator
        SideCrossIterator& operator=(SideCrossIterator&& other) noexcept {return *this;}

        SideCrossIterator &begin();
        SideCrossIterator &end();
        SideCrossIterator& operator++();
        int& operator*();
        bool operator==(const SideCrossIterator& other) const;
        bool operator!=(const SideCrossIterator& other) const;
        bool operator>(const SideCrossIterator& other) const;
        bool operator<(const SideCrossIterator& other) const;

    private:
        MagicalContainer& container;
        std::vector<int*>::iterator iter;
    };

    class MagicalContainer::PrimeIterator {
    public:
        PrimeIterator(MagicalContainer& container);
        PrimeIterator(const PrimeIterator& other);
        ~PrimeIterator() = default;
        // Copy assignment operator
        PrimeIterator& operator=(const PrimeIterator& other);
        // Move constructor
        PrimeIterator(PrimeIterator&& other) noexcept = default;
        // Move assignment operator
        PrimeIterator& operator=(PrimeIterator&& other) noexcept {return *this;}

        PrimeIterator &begin();
        PrimeIterator &end();
        PrimeIterator& operator++();
        int& operator*();
        bool operator==(const PrimeIterator& other) const;
        bool operator!=(const PrimeIterator& other) const;
        bool operator>(const PrimeIterator& other) const;
        bool operator<(const PrimeIterator& other) const;

    private:
        MagicalContainer& container;
        std::vector<int*>::iterator iter;
    };
}

#endif
