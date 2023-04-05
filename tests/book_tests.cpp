#include "catch_amalgamated.hpp"
#include "../book.h"

TEST_CASE("book simple tests", "[book]")
{

    Author author("Norbert", "Gierczak");
    Date date(6, Month::July, 2003);
    Chapter chapter1(1, 10, "Chapter 1: JD");
    Chapter chapter2(2, 20, "Chapter 2: KD");

    Book book1("Jest Dobrze!", {author}, 9783161484100, "KD sp. z o.o.", date, "Kraków", {chapter1, chapter2});
    CHECK(book1.getTitle() == "Jest Dobrze!");
    CHECK(book1.getISBN() == 9783161484100);
    CHECK(book1.getPublisher() == "KD sp. z o.o.");
    CHECK(book1.getDate().getDay() == 6);
    CHECK(book1.getDate().getMonth() == Month::July);
    CHECK(book1.getDate().getYear() == 2003);
    CHECK(book1.getReleasePlace() == "Kraków");
    CHECK(book1.getTotalPages() == 30);

    SECTION("testing valid setters")
    {
        book1.setDate(10, 2, 2023);
        book1.setPublisher("Wydawnictwo XD");
        book1.setReleasePlace("Warszawa");
        book1.setTitle("Nie jest dobrze:(");
        book1.setISBN(9780306406157);
        CHECK(book1.getTitle() == "Nie jest dobrze:(");
        CHECK(book1.getISBN() == 9780306406157);
        CHECK(book1.getPublisher() == "Wydawnictwo XD");
        CHECK(book1.getDate().getDay() == 10);
        CHECK(book1.getDate().getMonth() == Month::Feb);
        CHECK(book1.getDate().getYear() == 2023);
        CHECK(book1.getReleasePlace() == "Warszawa");
    }

    SECTION("testing invalid setters")
    {
        CHECK_THROWS_MATCHES(book1.setTitle(""), std::invalid_argument, Catch::Matchers::Message("Title cannot be empty!"));
        CHECK_THROWS_MATCHES(book1.setISBN(1234567891234), std::invalid_argument, Catch::Matchers::Message("ISBN number is invalid - check sum does not match!"));
        CHECK_THROWS_MATCHES(book1.setISBN(123), std::invalid_argument, Catch::Matchers::Message("ISBN number must have 13 digits!"));
        CHECK_THROWS_MATCHES(book1.setPublisher(""), std::invalid_argument, Catch::Matchers::Message("Book must have a publisher!"));
        CHECK_THROWS_MATCHES(book1.setReleasePlace(""), std::invalid_argument, Catch::Matchers::Message("Book must have a place of release!"));
        CHECK_THROWS_MATCHES(book1.setDate(0, 10, 2023), std::domain_error, Catch::Matchers::Message("Given day is not valid"));
        CHECK_THROWS_MATCHES(book1.setDate(10, 10, -10), std::domain_error, Catch::Matchers::Message("Given year cannot be negative"));
        CHECK_THROWS_MATCHES(book1.setDate(10, 13, 2023), std::domain_error, Catch::Matchers::Message("Months numbers must be between 1-12"));
        CHECK(book1.getTitle() == "Jest Dobrze!");
        CHECK(book1.getISBN() == 9783161484100);
        CHECK(book1.getPublisher() == "KD sp. z o.o.");
        CHECK(book1.getDate().getDay() == 6);
        CHECK(book1.getDate().getMonth() == Month::July);
        CHECK(book1.getDate().getYear() == 2003);
        CHECK(book1.getReleasePlace() == "Kraków");
    }
}
