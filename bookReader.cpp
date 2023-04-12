#include "bookReader.h"

void setReleaseDate(std::string value, Date& releaseDate){
    std::stringstream ss(value);
    std::string dayStr, monthStr, yearStr;
    std::getline(ss, dayStr, '/');
    std::getline(ss, monthStr, '/');
    std::getline(ss, yearStr);
    releaseDate.setDay(std::stoi(dayStr));
    releaseDate.setMonth(static_cast<Month>(std::stoi(monthStr)));
    releaseDate.setYear(std::stoi(yearStr));
}

void setAuthors(std::string value, std::vector<Author>& bookAuthors){
    std::istringstream ss(value);
    std::string authorName;
    while (std::getline(ss, authorName, ';')) {
        authorName.erase(0, authorName.find_first_not_of(' '));
        size_t spacePos = authorName.find_last_of(' ');
        std::string firstName = authorName.substr(0, spacePos);
        std::string lastName = authorName.substr(spacePos + 1);
        bookAuthors.push_back(Author(firstName, lastName));
    }
}

void setChapters(std::string value, std::vector<Chapter>& bookChapters){
    std::stringstream ss(value);
    std::string chapterData;
    while (std::getline(ss, chapterData, ';')) {
        std::stringstream chapter_ss(chapterData);
        std::string chapterNumberString, chapterTitle, chapterPagesString;
        std::getline(chapter_ss, chapterNumberString, ',');
        std::getline(chapter_ss, chapterTitle, ',');
        chapterTitle.erase(0, chapterTitle.find_first_not_of(' '));
        chapterTitle.erase(chapterTitle.find_last_not_of(' ') + 1);
        std::getline(chapter_ss, chapterPagesString, ',');
        chapterPagesString.erase(0, chapterPagesString.find_first_not_of(' '));
        chapterPagesString.erase(chapterPagesString.find_last_not_of(' ') + 1);
        Chapter chapter(std::stoi(chapterNumberString), std::stoi(chapterPagesString), chapterTitle);
        bookChapters.push_back(chapter);
    }
}

BookReader::BookReader(std::string newFileName) {
    checkFile(newFileName);
    fileName = newFileName;
}

void BookReader::checkFile(std::string newFileName) {
    file.open(newFileName);
    if (!file) {
        std::cerr << "Error: could not open file " << newFileName << std::endl;
        exit(1);
    }
    file.close();
}

Book BookReader::getBook() {
    checkFile(fileName);
    file.open(fileName);
    std::string line;
    std::string bookTitle = "";
    unsigned long ISBN = 0;
    std::string bookPublisher = "";
    Date releaseDate;
    std::string releasePlace = "";
    std::vector<Author> bookAuthors = {};
    std::vector<Chapter> bookChapters = {};
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string key, value;
        std::getline(ss, key, ':');
        std::getline(ss, value);
        value.erase(0, value.find_first_not_of(' '));
        value.erase(value.find_last_not_of(' ') + 1);
        if (key == "Title")
            bookTitle = value;
        else if (key == "ISBN")
            ISBN = std::stoul(value);
        else if (key == "Publisher")
            bookPublisher = value;
        else if (key == "Release Date"){
            setReleaseDate(value, releaseDate);
        }
        else if (key == "Release Place")
            releasePlace = value;
        else if (key == "Authors"){
            setAuthors(value, bookAuthors);
        }
        else if (key == "Chapters"){
            setChapters(value, bookChapters);
        }
        else {
            std::cerr << "Error: unknown key " << key << std::endl;
        }
    }
    file.close();
    return Book(bookTitle, bookAuthors, ISBN, bookPublisher, releaseDate, releasePlace, bookChapters);
}