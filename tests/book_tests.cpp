#include "catch_amalgamated.hpp"
#include "../book.h"

TEST_CASE("book simple tests", "[book]")
{

    Author author1("Norbert", "Gierczak");
    Date date1(6, Month::July, 2003);
    Chapter chapter1(1, 10, "Chapter 1: JD");
    Chapter chapter2(2, 20, "Chapter 2: KD");

    Book book1("Jest Dobrze!", {author1}, 9783161484100, "KD sp. z o.o.", date1, "Kraków", {chapter1, chapter2});
    CHECK(book1.getTitle() == "Jest Dobrze!");
    CHECK(book1.getISBN() == 9783161484100);
    CHECK(book1.getPublisher() == "KD sp. z o.o.");
    CHECK(book1.getDate().getDay() == 6);
    CHECK(book1.getDate().getMonth() == Month::July);
    CHECK(book1.getDate().getYear() == 2003);
    CHECK(book1.getReleasePlace() == "Kraków");
    CHECK(book1.getTotalPages() == 30);

    Date date2(10, Month::May, 1999);
    Chapter chapter3(3, 30, "Chapter 3: AA");
    Chapter chapter4(4, 45, "Chapter 4: BB");

    Book book2("Biblia", {}, 9783161484100, "JMS", date2, "Toruń", {chapter3, chapter4});
    CHECK(book2.getTitle() == "Biblia");
    CHECK(book2.getISBN() == 9783161484100);
    CHECK(book2.getPublisher() == "JMS");
    CHECK(book2.getDate().getDay() == 10);
    CHECK(book2.getDate().getMonth() == Month::May);
    CHECK(book2.getDate().getYear() == 1999);
    CHECK(book2.getReleasePlace() == "Toruń");
    CHECK(book2.getTotalPages() == 75);

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

    SECTION("testing operators")
    {
        CHECK((book1 < book2) == true);
        CHECK((book1 <= book2) == true);
        CHECK((book2 > book1) == true);
        CHECK((book2 >= book1) == true);
    }

    SECTION("testing finding position of chapter by key - whole title")
    {
        CHECK(book1.findChapterPosition("Chapter 1: JD") == 0);
        CHECK(book1.findChapterPosition("AAA") == -1);
    }

    SECTION("testing finding position of chapter by key - fragments of title")
    {
        CHECK(book1.findChapterPosition("JD") == 0);
        CHECK(book2.findChapterPosition("BB") == 1);
    }

    SECTION("testing editing chapter")
    {
        book1.editChapter("Chapter 1: JD", 0, 50, "");
        CHECK(book1.findChapterPosition("JD") == 0);
        CHECK(book1.getTotalPages() == 70);
    }

    SECTION("testing editing chapter that does not exist")
    {
        CHECK_THROWS_MATCHES(book2.editChapter("Chapter 1: JD", 3, 50, "ABC"), std::domain_error, Catch::Matchers::Message("Could not find chapter by given key!"));
        CHECK(book2.findChapterPosition("Chapter 3: AA") == 0);
        CHECK(book2.findChapterPosition("Chapter 4: BB") == 1);
        CHECK(book2.getTotalPages() == 75);
    }

    SECTION("testing removing chapter")
    {
        CHECK_THROWS_MATCHES(book2.removeChapter("Chapter 5"), std::domain_error, Catch::Matchers::Message("Could not remove chapter that does not exist!"));
        book2.removeChapter("Chapter 4");
        CHECK(book2.findChapterPosition("Chapter 4") == -1);
        CHECK(book2.findChapterPosition("Chapter 5") == -1);
        CHECK(book2.getTotalPages() == 30);
    }

    SECTION("testing adding chapter")
    {
        book2.addChapter(5, 200, "Chapter 5: CC");
        CHECK(book2.findChapterPosition("Chapter 3: AA") == 0);
        CHECK(book2.findChapterPosition("Chapter 4: BB") == 1);
        CHECK(book2.findChapterPosition("Chapter 5: CC") == 2);
        CHECK(book2.getTotalPages() == 275);
    }

    SECTION("testing adding chapter that already exists")
    {
        CHECK_THROWS_MATCHES(book2.addChapter(5, 200, "Chapter 3: AA"), std::domain_error, Catch::Matchers::Message("Cannot dupicate chapters!"));
        CHECK(book2.findChapterPosition("Chapter 3: AA") == 0);
        CHECK(book2.findChapterPosition("Chapter 4: BB") == 1);
        CHECK(book2.getTotalPages() == 75);
    }

    SECTION("testing adding chapter - duplicating chapter numbers")
    {
        book2.addChapter(4, 200, "Chapter 4: CC");
        CHECK(book2.findChapterPosition("Chapter 3: AA") == 0);
        CHECK(book2.findChapterPosition("Chapter 4: BB") == 1);
        CHECK(book2.findChapterPosition("Chapter 4: CC") == -1);
        CHECK(book2.getTotalPages() == 75);
    }

    SECTION("testing finding key in bookChapters")
    {
        CHECK(book2.getNumChaptersWithKey("Chapter") == 2);
        CHECK(book2.getNumChaptersWithKey("KKKKK") == 0);
        CHECK(book1.getNumChaptersWithKey("KD") == 1);
    }

    SECTION("testing sorting chapters by their number")
    {
        CHECK(book1.getChapters().size() == 2);
        book1.addChapter(20, 100, "Chapter 20: AA");
        book1.addChapter(15, 100, "Chapter 15: BB");
        book1.addChapter(7, 100, "Chapter 7: CC");
        CHECK(book1.getChapters().size() == 5);
        CHECK(book1.findChapterPosition("Chapter 1") == 0);
        CHECK(book1.findChapterPosition("Chapter 2") == 1);
        CHECK(book1.findChapterPosition("Chapter 7") == 2);
        CHECK(book1.findChapterPosition("Chapter 15") == 3);
        CHECK(book1.findChapterPosition("Chapter 20") == 4);
    }

    SECTION("testing sorting chapters by their title")
    {
        CHECK(book1.getChapters().size() == 2);
        book1.removeChapter("Chapter 1");
        book1.removeChapter("Chapter 2");
        CHECK(book1.getChapters().size() == 0);
        book1.addChapter(3, 100, "def");
        book1.addChapter(4, 100, "opr");
        book1.addChapter(5, 100, "abc");
        CHECK(book1.getChapters().size() == 3);
        CHECK(book1.findChapterPosition("def") == 0);
        CHECK(book1.findChapterPosition("opr") == 1);
        CHECK(book1.findChapterPosition("abc") == 2);
        book1.sortChaptersbyTitle();
        CHECK(book1.findChapterPosition("abc") == 0);
        CHECK(book1.findChapterPosition("def") == 1);
        CHECK(book1.findChapterPosition("opr") == 2);
    }
}
