#include "catch_amalgamated.hpp"
#include "../chapter.h"

TEST_CASE("chapter simple tests", "[chapter]")
{

    Chapter chapter1(1, 10, "Chapter: JD");
    Chapter chapter2(2, 20, "Chapter: KD");

    CHECK(chapter1.getChapterNumber() == 1);
    CHECK(chapter1.getChapterPages() == 10);
    CHECK(chapter1.getChapterTitle() == "Chapter: JD");

    CHECK(chapter2.getChapterNumber() == 2);
    CHECK(chapter2.getChapterPages() == 20);
    CHECK(chapter2.getChapterTitle() == "Chapter: KD");

    SECTION("testing postfix operator++")
    {
        chapter1++;
        CHECK(chapter1.getChapterPages() == 11);
    }

    SECTION("testing prefix operator++")
    {
        ++chapter2;
        CHECK(chapter2.getChapterPages() == 21);
    }

    SECTION("testing postfix operator--")
    {
        chapter1--;
        CHECK(chapter1.getChapterPages() == 9);
    }

    SECTION("testing prefix operator--")
    {
        --chapter2;
        CHECK(chapter2.getChapterPages() == 19);
    }

    SECTION("testing illegal postfix operator--")
    {
        chapter1.setChapterPages(1);
        CHECK_THROWS_MATCHES(chapter1--, std::invalid_argument, Catch::Matchers::Message("Chapter cannot have 0 pages!"));
        CHECK(chapter1.getChapterPages() == 1);
    }

    SECTION("testing illegal prefix operator--")
    {
        chapter2.setChapterPages(1);
        CHECK_THROWS_MATCHES(--chapter2, std::invalid_argument, Catch::Matchers::Message("Chapter cannot have 0 pages!"));
        CHECK(chapter2.getChapterPages() == 1);
    }

    SECTION("testing operator==")
    {
        chapter1.setChapterPages(100);
        chapter2.setChapterPages(100);
        chapter1.setChapterTitle("Chapter: XD");
        chapter2.setChapterTitle("Chapter: XD");
        chapter1.setChapterNumber(10);
        chapter2.setChapterNumber(10);
        CHECK((chapter1 == chapter2) == true);
    }

    SECTION("testing operator!=")
    {
        CHECK(chapter1.getChapterPages() == 10);
        CHECK(chapter2.getChapterPages() == 20);
        CHECK((chapter1 != chapter2) == true);
    }

    SECTION("testing operator<=")
    {
        CHECK(chapter1.getChapterPages() == 10);
        CHECK(chapter2.getChapterPages() == 20);
        CHECK((chapter1 <= chapter2) == true);
    }

    SECTION("testing operator>=")
    {
        CHECK(chapter1.getChapterPages() == 10);
        CHECK(chapter2.getChapterPages() == 20);
        CHECK((chapter2 >= chapter1) == true);
    }

    SECTION("testing operator<")
    {
        CHECK(chapter1.getChapterPages() == 10);
        CHECK(chapter2.getChapterPages() == 20);
        CHECK((chapter1 < chapter2) == true);
    }

    SECTION("testing operator>")
    {
        CHECK(chapter1.getChapterPages() == 10);
        CHECK(chapter2.getChapterPages() == 20);
        CHECK((chapter2 > chapter1) == true);
    }

    SECTION("testing valid setters")
    {
        chapter1.setChapterNumber(10);
        chapter1.setChapterTitle("Chapter: XD");
        chapter1.setChapterPages(200);
        CHECK(chapter1.getChapterNumber() == 10);
        CHECK(chapter1.getChapterPages() == 200);
        CHECK(chapter1.getChapterTitle() == "Chapter: XD");
    }

    SECTION("testing invalid setters")
    {
        CHECK_THROWS_MATCHES(chapter2.setChapterNumber(0), std::invalid_argument, Catch::Matchers::Message("Chapter number cannot be equal 0!"));
        CHECK_THROWS_MATCHES(chapter2.setChapterTitle(""), std::invalid_argument, Catch::Matchers::Message("Chapter title cannot be empty!"));
        CHECK_THROWS_MATCHES(chapter2.setChapterPages(0), std::invalid_argument, Catch::Matchers::Message("Chapter cannot have 0 pages!"));
        CHECK(chapter2.getChapterNumber() == 2);
        CHECK(chapter2.getChapterPages() == 20);
        CHECK(chapter2.getChapterTitle() == "Chapter: KD");
    }
}