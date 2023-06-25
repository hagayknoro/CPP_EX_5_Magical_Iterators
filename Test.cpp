#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("Testing MagicalContainer") {
    MagicalContainer container;

    SUBCASE("Adding elements") {
        container.addElement(5);
        container.addElement(10);
        container.addElement(3);

        CHECK(container.size() == 3);
    }

    SUBCASE("Removing elements") {
        container.addElement(5);
        container.addElement(10);
        container.addElement(3);

        container.removeElement(10);

        CHECK(container.size() == 2);
    }

    SUBCASE("Prime elements") {
        CHECK(isPrime(2) == true);
        CHECK(isPrime(3) == true);
        CHECK(isPrime(4) == false);
        CHECK(isPrime(5) == true);
        CHECK(isPrime(10) == false);
    }
    SUBCASE("Adding and removing elements") {
        container.addElement(5);
        container.addElement(10);
        container.addElement(3);

        CHECK(container.size() == 3);

        CHECK_THROWS_AS(container.removeElement(8), std::runtime_error);
        CHECK_NOTHROW(container.removeElement(10));

        CHECK(container.size() == 2);
    }

    SUBCASE("AscendingIterator") {
        container.addElement(5);
        container.addElement(10);
        container.addElement(3);

        MagicalContainer::AscendingIterator iter_container(container);
        MagicalContainer::AscendingIterator it = iter_container.begin();
        MagicalContainer::AscendingIterator end = iter_container.end();

        CHECK(*it == 3);
        CHECK(it != end);

        ++it;
        CHECK(*it == 5);
        CHECK(it != end);

        ++it;
        CHECK(*it == 10);
        CHECK(it != end);

        ++it;
        CHECK(it == end);
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
     

    SUBCASE("SideCrossIterator") {
        container.addElement(5);
        container.addElement(10);
        container.addElement(3);
        container.addElement(15);
        container.addElement(1);



        MagicalContainer::SideCrossIterator iter_container(container);
        MagicalContainer::SideCrossIterator it = iter_container.begin();
        MagicalContainer::SideCrossIterator end = iter_container.end();

        CHECK(*it == 1);
        CHECK(it != end);

        ++it;
        CHECK(*it == 15);
        CHECK(it != end);

        ++it;
        CHECK(*it == 3);
        CHECK(it != end);

        ++it;
        CHECK(*it == 10);
        CHECK(it != end);

        ++it;
        CHECK(*it == 5);
        CHECK(it != end);

        ++it;
        CHECK(it == end);
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
    SUBCASE("PrimeIterator") {
        container.addElement(5);
        container.addElement(10);
        container.addElement(3);


        MagicalContainer::PrimeIterator iter_container(container);
        MagicalContainer::PrimeIterator it = iter_container.begin();
        MagicalContainer::PrimeIterator end = iter_container.end();

        CHECK(*it == 3);
        CHECK(it != end);

        ++it;
        CHECK(*it == 5);
        CHECK(it != end);

        ++it;
        CHECK(it == end);
        CHECK_THROWS_AS(*it, std::out_of_range);
    }
}
