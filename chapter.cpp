#include "chapter.h"
#include <stdexcept>

Chapter::Chapter(ushort newNumber, uint newPages, std::string newTitle) : chapterNumber(newNumber), chapterPages(newPages), chapterTitle(newTitle){
    checkData(newNumber, newPages, newTitle);
}

void Chapter::checkData(ushort newNumber, uint newPages, std::string newTitle) const{
    if (newNumber == 0){
        throw std::invalid_argument("Chapter number cannot be equal 0!");
    }
    if (newPages == 0){
        throw std::invalid_argument("Chapter cannot have 0 pages!");
    }
    if (newTitle.empty()){
        throw std::invalid_argument("Chapter title cannot be empty!");
    }
}

ushort Chapter::getChapterNumber() const{
    return chapterNumber;
}

uint Chapter::getChapterPages() const{
    return chapterPages;
}

std::string Chapter::getChapterTitle() const{
    return chapterTitle;
}

void Chapter::setChapterNumber(ushort newNumber){
    checkData(newNumber, chapterPages, chapterTitle);
    chapterNumber = newNumber;
}

void Chapter::setChpaterPages(uint newPages){
    checkData(chapterNumber, newPages, chapterTitle);
    chapterPages = newPages;
}

void Chapter::setChapterTitle(std::string newTitle){
    checkData(chapterNumber, chapterPages, newTitle);
    chapterTitle = newTitle;
}

Chapter& Chapter::operator++(){
    chapterPages += 1;
    return *this;
}

Chapter Chapter::operator++(int){
    Chapter old_value = *this;
    ++(*this);
    return old_value;
}

Chapter& Chapter::operator--(){
    checkData(chapterNumber, chapterPages - 1, chapterTitle);
    --chapterPages;
    return *this;
}

Chapter Chapter::operator--(int){
    Chapter temp(*this);
    --(*this);
    return temp;
}

bool Chapter::operator==(const Chapter& second_argument) const{
    return (chapterPages == second_argument.chapterPages);
}

bool Chapter::operator!=(const Chapter& second_argument) const{
    return !(chapterPages == second_argument.chapterPages);
}

bool Chapter::operator<(const Chapter& second_argument) const{
    return (chapterPages < second_argument.chapterPages);
}

bool Chapter::operator>(const Chapter& second_argument) const{
    return (chapterPages > second_argument.chapterPages);
}

bool Chapter::operator<=(const Chapter& second_argument) const{
    return !(chapterPages > second_argument.chapterPages);
}

bool Chapter::operator>=(const Chapter& second_argument) const{
    return !(chapterPages < second_argument.chapterPages);
}
