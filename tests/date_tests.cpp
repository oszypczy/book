#include "catch_amalgamated.hpp"
#include "../date.h"

TEST_CASE("date simple tests", "[date]")
{

    Date date(17, Month::Mar, 2023);

    CHECK(date.getDay() == 17);
    CHECK(date.getMonth() == Month::Mar);
    CHECK(date.getYear() == 2023);

    SECTION("testing str() method")
    {
        CHECK(date.str() == "17.03.2023");
    }

    SECTION("testing valid setters")
    {
        date.setDay(10);
        date.setMonth(Month::Dec);
        date.setYear(1987);
        CHECK(date.getDay() == 10);
        CHECK(date.getMonth() == Month::Dec);
        CHECK(date.getYear() == 1987);
    }

    SECTION("testing invalid day setter")
    {
        CHECK_THROWS_MATCHES(date.setDay(0), std::domain_error, Catch::Matchers::Message("Given day is not valid"));
        CHECK_THROWS_MATCHES(date.setDay(32), std::domain_error, Catch::Matchers::Message("Given day is not valid"));
        CHECK(date.getDay() == 17);
    }

    SECTION("testing negative year setter")
    {
        CHECK_THROWS_MATCHES(date.setYear(-9), std::domain_error, Catch::Matchers::Message("Given year cannot be negative"));
        CHECK(date.getYear() == 2023);
    }

    SECTION("testing valid leap year")
    {
        date.setYear(2008);
        date.setMonth(Month::Feb);
        date.setDay(29);
        CHECK(date.getDay() == 29);
        CHECK(date.getMonth() == Month::Feb);
        CHECK(date.getYear() == 2008);
    }

    SECTION("testing invalid leap year")
    {
        date.setYear(2007);
        date.setMonth(Month::Feb);
        CHECK_THROWS_MATCHES(date.setDay(29), std::domain_error, Catch::Matchers::Message("Given day is not valid"));
    }
}
