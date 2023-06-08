#include "MagicalContainer.hpp"

namespace ariel {
    
    bool isPrime(int elem) 
    {
    if (elem < 2) {
        return false;
    }
    for (int i = 2; i * i <= elem; ++i) 
    {
        if (elem % i == 0) {
            return false;
        }
    }
    return true;
    }
    
    //MagicalContainer implementation
    void MagicalContainer::addElement(int element)
    {
        originalElement.push_back(element);
        originalElementSort();
        sortedFix();
        primeFix();
        crossFix();
    }

    void MagicalContainer::removeElement(int element) 
    {
        //make sure the elment is in the originalElement
        bool inList = false;
        for(auto itr = originalElement.begin(); itr != originalElement.end(); itr++)
        {
            if(*itr == element)
            {
                inList = true;
                break;
            }
        }
        if(!inList)
            throw runtime_error("You can't remove element that not in the list.");
        
        originalElement.erase(remove(originalElement.begin(), originalElement.end(), element),originalElement.end());
        sortedFix();
        primeFix();
        crossFix();
    }

    int MagicalContainer::size()
    {
        return originalElement.size();
    }

    void MagicalContainer::crossFix()
    {
        crossElement.clear();
        auto begin = originalElement.begin();
        auto end = --originalElement.end();

        while (begin < end)
        {
            crossElement.push_back(&(*begin));
            crossElement.push_back(&(*end));
            begin++;
            end--;
        }
        if(begin == end)
            crossElement.push_back(&(*begin));
    }

    void MagicalContainer::primeFix()
    {
        primeElement.clear();
        for(auto itr = originalElement.begin(); itr != originalElement.end(); ++itr)
        {
            if(isPrime(*itr))
                primeElement.push_back(&(*itr));
        }
    }

    void MagicalContainer::sortedFix()
    {
        sortedElement.clear();
        for(auto itr = originalElement.begin(); itr != originalElement.end(); ++itr)
        {
            sortedElement.push_back(&(*itr));
        }
    }

    void MagicalContainer::originalElementSort()
    {
        for(unsigned long i = 0; i < originalElement.size(); ++i)
        {
            for(unsigned long j = 0; j < originalElement.size() - i -1; j++)
            {
                if(originalElement[j] > originalElement [j+1])
                {
                    int tmp = originalElement[j];
                    originalElement[j] = originalElement[j+1];
                    originalElement[j+1] = tmp;
                }
            }
        }
    }

    // AscendingIterator implementation
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
        : container(container),iter(container.sortedElement.begin()), index(0) 
    {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
        : container(other.container),iter(other.iter), index(other.index) 
    {}

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
    {
        if(&container != &other.container)
            throw runtime_error("you cant '=' they are not the same container");
        iter = other.iter;
        index = other.index;
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin() 
    {
        iter = container.sortedElement.begin();
        index = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end() 
    {
        iter = container.sortedElement.end();
        index = container.sortedElement.size();
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() 
    {
        if (iter == container.sortedElement.end())
            throw runtime_error("out of range");
        ++iter;
        ++index;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*()
    {
        if (iter == container.sortedElement.end()) 
            throw std::out_of_range("Iterator out of range");
    
        return **iter;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const 
    {
        if(&container != &other.container)
            throw invalid_argument("you cant '==' they are not the same container");
        return index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const 
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const 
    {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return index > other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const 
    {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return index < other.index;
    }

    // SideCrossIterator implementation
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
        : container(container), iter(container.crossElement.begin()), index(0)
    {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
        : container(other.container), iter(other.iter), index(other.index)
    {}

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() 
    {
        iter = container.crossElement.begin();
        index = 0;
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end() 
    {
        iter = container.crossElement.end();
        index = container.crossElement.size();
        return *this;
    }

     MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
     {
        if(&container != &other.container)
            throw runtime_error("you cant '=' they are not the same container");
        iter = other.iter;
        index = other.index;
        return *this;
     }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() 
    {
        if (iter == container.crossElement.end())
            throw runtime_error("out of range");
        ++iter;
        ++index;
        return *this;
    }

    int& MagicalContainer::SideCrossIterator::operator*()
    {
        if (iter == container.crossElement.end()) 
            throw std::out_of_range("Iterator out of range");
    
        return **iter;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const 
    {
        if(&container != &other.container)
            throw invalid_argument("you cant '==' they are not the same container");
        return index == other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const 
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const 
    {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return index > other.index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const 
    {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return index < other.index;
    }

    
    // PrimeIterator implementation
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
        : container(container),iter(container.primeElement.begin()), index(0) 
    {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) 
        : container(other.container),iter(other.iter), index(other.index) 
    {}

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
    {
        if(&container != &other.container)
            throw runtime_error("you cant '=' they are not the same container");
        iter = other.iter;
        index = other.index;
        return *this;  
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin() 
    {
         iter = container.primeElement.begin();
        index = 0;
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end() 
    {
        iter = container.primeElement.end();
        index = container.primeElement.size();
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        if (iter == container.primeElement.end())
            throw runtime_error("out of range");
        ++iter;
        ++index;
        return *this;
    }

    int& MagicalContainer::PrimeIterator::operator*()
    {
        if (iter == container.crossElement.end()) 
            throw std::out_of_range("Iterator out of range");
    
        return **iter;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const 
    {
        if(&container != &other.container)
            throw invalid_argument("you cant '==' they are not the same container");
        return index == other.index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const 
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return index > other.index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
        if (&container != &other.container) {
            throw std::invalid_argument("Comparing iterators from different containers");
        }
        return index < other.index;
    }
    

}