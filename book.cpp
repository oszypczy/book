#include "book.h"
#include <algorithm>
#include <numeric>
#include <iostream>

Book::Book(std::string newTitle, std::vector<Author> newAuthors, unsigned long newISBN, std::string newPublisher, Date newDate, std::string newPlace, std::vector<Chapter> newChapters){
    checkData(newTitle, newAuthors, newISBN, newPublisher, newPlace, newChapters);
    bookTitle = newTitle;
    bookAuthors = newAuthors;
    ISBN = newISBN;
    bookPublisher = newPublisher;
    releaseDate = newDate;
    releasePlace = newPlace;
    bookChapters = newChapters;
    sortChaptersbyNumber();
}

void Book::checkData(std::string newTitle, std::vector<Author> newAuthors, unsigned long newISBN, std::string newPublisher, std::string newPlace, std::vector<Chapter> newChapters) const {
    if (newTitle.empty()) {
        throw std::invalid_argument("Title cannot be empty!");
    }
    if (newAuthors.empty()) {
        Author newAuthor("Anonymous", "Anonymous");
        newAuthors.push_back(newAuthor);
    }
    if (std::to_string(newISBN).length() != 13) {
        throw std::invalid_argument("ISBN number must have 13 digits!");
    }
    if (!isISBNValid(std::to_string(newISBN))) {
        throw std::invalid_argument("ISBN number is invalid - check sum does not match!");
    }
    if (newPublisher.empty()) {
        throw std::invalid_argument("Book must have a publisher!");
    }
    if (newPlace.empty()) {
        throw std::invalid_argument("Book must have a place of release!");
    }
    if (!(areChapterValid(newChapters))) {
        throw std::invalid_argument("Two chapters cannot have the same number!");
    }
}

bool Book::isISBNValid(std::string newISBN) const{
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        if (!isdigit(newISBN[i])) {
            return false;
        }
        sum += (i % 2 == 0) ? (newISBN[i] - '0') : (newISBN[i] - '0') * 3;
    }
    int check_digit = (10 - sum % 10) % 10;
    return (newISBN[12] - '0') == check_digit;
}

bool Book::areChapterValid(std::vector<Chapter> newChapters) const{
    std::vector<ushort> chapterNumbers;
    for (auto& chapter : bookChapters) {
        chapterNumbers.push_back(chapter.getChapterNumber());
        if (std::count(chapterNumbers.begin(), chapterNumbers.end(), chapter.getChapterNumber()) > 1) {
            return false;
        }
    }
    return true;
}

std::string Book::getTitle() const{
    return bookTitle;
}

unsigned long Book::getISBN() const{
    return ISBN;
}

std::string Book::getPublisher() const{
    return bookPublisher;
}

Date Book::getDate() const{
    return releaseDate;
}

std::string Book::getReleasePlace() const{
    return releasePlace;
}

std::vector<Chapter> Book::getChapters() const{
    return bookChapters;
}

void Book::setTitle(std::string newTitle){
    checkData(newTitle, bookAuthors, ISBN, bookPublisher, releasePlace, bookChapters);
    bookTitle = newTitle;
}

void Book::setISBN(unsigned long newISBN){
    checkData(bookTitle, bookAuthors, newISBN, bookPublisher, releasePlace, bookChapters);
    ISBN = newISBN;
}

void Book::setPublisher(std::string newPublisher){
    checkData(bookTitle, bookAuthors, ISBN, newPublisher, releasePlace, bookChapters);
    bookPublisher = newPublisher;
}

void Book::setDate(ushort newDay, ushort newMonth, int newYear){
    if (newMonth > 12 || newMonth == 0){
        throw std::domain_error("Months numbers must be between 1-12");
    }
    Date newDate(newDay, static_cast<Month>(newMonth), newYear);
    releaseDate = newDate;
}

void Book::setReleasePlace(std::string newPlace){
    checkData(bookTitle, bookAuthors, ISBN, bookPublisher, newPlace, bookChapters);
    releasePlace = newPlace;
}

bool Book::operator<(const Book& secondBook) const {
    return (getTotalPages() < secondBook.getTotalPages());
}

bool Book::operator>(const Book& secondBook) const {
    return (getTotalPages() > secondBook.getTotalPages());
}

bool Book::operator<=(const Book& secondBook) const {
    return !(getTotalPages() > secondBook.getTotalPages());
}

bool Book::operator>=(const Book& secondBook) const {
    return !(getTotalPages() < secondBook.getTotalPages());
}

uint Book::getTotalPages() const{
    return std::accumulate(bookChapters.begin(), bookChapters.end(), 0,
        [](uint total, const Chapter& chapter) { return total + chapter.getChapterPages(); });
}

short Book::findChapterPosition(std::string key) const {
    for (size_t i = 0; i < bookChapters.size(); i++) {
        if (bookChapters[i].getChapterTitle().find(key) != std::string::npos) {
            return i;
        }
    }
    return -1;
}

void Book::editChapter(std::string key, ushort newNumber, uint newPages, std::string newTitle){
    if (findChapterPosition(key) == -1){
        throw std::domain_error("Could not find chapter by given key!");
    } else {
        Chapter& chapter = bookChapters[findChapterPosition(key)];
        ushort old_number = chapter.getChapterNumber();
        chapter.setChapterTitle(newTitle != "" ? newTitle : chapter.getChapterTitle());
        chapter.setChapterPages(newPages != 0 ? newPages : chapter.getChapterPages());
        chapter.setChapterNumber(newNumber != 0 ? newNumber : old_number);
        try{
            checkData(bookTitle, bookAuthors, ISBN, bookPublisher, releasePlace, bookChapters);
        } catch (const std::invalid_argument&) {
            chapter.setChapterNumber(old_number);
        }
    }
    sortChaptersbyNumber();
}

void Book::removeChapter(std::string key){
    if (findChapterPosition(key) == -1){
        throw std::domain_error("Could not remove chapter that does not exist!");
    } else {
        bookChapters.erase(bookChapters.begin() + findChapterPosition(key));
    }
}

void Book::addChapter(ushort newNumber, uint newPages, std::string newTitle){
    if (findChapterPosition(newTitle) != -1){
       throw std::domain_error("Cannot dupicate chapters!");
    }
    Chapter chapter(newNumber, newPages, newTitle);
    bookChapters.push_back(chapter);
    try{
        checkData(bookTitle, bookAuthors, ISBN, bookPublisher, releasePlace, bookChapters);
    } catch (const std::invalid_argument&) {
        removeChapter(newTitle);
    }
    sortChaptersbyNumber();
}

ushort Book::getNumChaptersWithKey(std::string key) const{
    ushort result = 0;
    for (auto& chapter : bookChapters){
        if (chapter.getChapterTitle().find(key) != std::string::npos)
            result++;
    }
    return result;
}

void Book::sortChaptersbyNumber(){
    std::sort(bookChapters.begin(), bookChapters.end(),
        [](const Chapter& chapter1, const Chapter& chapter2) {return chapter1.getChapterNumber() < chapter2.getChapterNumber(); });
}

void Book::sortChaptersbyTitle(){
    std::sort(bookChapters.begin(), bookChapters.end(),
        [](const Chapter& chapter1, const Chapter& chapter2) {return chapter1.getChapterTitle() < chapter2.getChapterTitle(); });
}

std::ostream& operator<<(std::ostream& os, const Book& book){
    return os;
}