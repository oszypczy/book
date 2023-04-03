#include "catch_amalgamated.hpp"
#include "../author.h"

TEST_CASE("author simple tests", "[author]")
{

    Author author("Jan", "Kowalski");

    CHECK(author.getName() == "Jan");
    CHECK(author.getSurname() == "Kowalski");

    SECTION("testing valid setters")
    {
        author.setName("Adam");
        CHECK(author.getName() == "Adam");
        author.setSurname("Nowak");
        CHECK(author.getSurname() == "Nowak");
    }

    SECTION("testing invalid setters")
    {
        CHECK_THROWS_MATCHES(author.setName(""), std::invalid_argument, Catch::Matchers::Message("Name cannot be empty!"));
        CHECK_THROWS_MATCHES(author.setSurname(""), std::invalid_argument, Catch::Matchers::Message("Surname cannot be empty!"));
        CHECK(author.getName() == "Jan");
        CHECK(author.getSurname() == "Kowalski");
    }
}
