#pragma once
#include "date.h"
#include "chapter.h"
#include "author.h"
#include <string>
#include <vector>

class Book{
    private:
        std::string bookTitle;
        std::vector<Author> bookAuthors;
        unsigned long ISBN;
        std::string bookPublisher;
        Date releaseDate;
        std::string releasePlace;
        std::vector<Chapter> bookChapters;
        void checkData(std::string newTitle, std::vector<Author> newAuthors, unsigned long newISBN, std::string newPublisher, std::string newPlace, std::vector<Chapter> newChapters) const;
        bool isISBNValid(std::string newISBN) const;
        bool areChapterValid(std::vector<Chapter> newChapters) const;
    public:
        Book(std::string newTitle, std::vector<Author> newAuthors, unsigned long newISBN, std::string newPublisher, Date newDate, std::string newPlace, std::vector<Chapter> newChapters = {});
        std::string getTitle() const;
        unsigned long getISBN() const;
        std::string getPublisher() const;
        Date getDate() const;
        std::vector<Chapter> getChapters() const;
        std::string getReleasePlace() const;
        void setTitle(std::string newTitle);
        void setISBN(unsigned long newISBN);
        void setPublisher(std::string newPublisher);
        void setDate(ushort newDay, ushort newMonth, int newYear);
        void setReleasePlace(std::string newPlace);
        bool operator<(const Book& secondBook) const;
        bool operator>(const Book& secondBook) const;
        bool operator<=(const Book& secondBook) const;
        bool operator>=(const Book& secondBook) const;
        uint getTotalPages() const;
        short findChapterPosition(std::string key) const;
        ushort getNumChaptersWithKey(std::string key) const;
        void sortChaptersbyTitle();
        void sortChaptersbyNumber();
        void addChapter(ushort newNumber, uint newPages, std::string newTitle);
        void removeChapter(std::string key);
        void editChapter(std::string key, ushort newNumber = 0, uint newPages = 0, std::string newTitle = "");
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

// Czy wydawca to ma być też osobna klasa?
// Czy miejsce wydania to też ma być osobna klasa?
// We wszystkich klasach przeciążyć operatory "!=" , "==" ? (treść zadania inna niż pdf)?