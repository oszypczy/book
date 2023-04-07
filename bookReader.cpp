#include "bookReader.h"

BookReader::BookReader(const std::string& filename) {
    file_.open(filename);
    if (!file_) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }
}

BookReader::~BookReader() {
    if (file_.is_open()) {
        file_.close();
    }
}

Book BookReader::getBook() {
    std::string line;
    std::string bookTitle = "";
    unsigned long ISBN = 0;
    std::string bookPublisher = "";
    Date releaseDate;
    std::string releasePlace = "";
    std::vector<Author> bookAuthors = {};
    std::vector<Chapter> bookChapters = {};
    while (std::getline(file_, line)) {
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
            std::stringstream ss(value);
            std::string dayStr, monthStr, yearStr;
            std::getline(ss, dayStr, '/');
            std::getline(ss, monthStr, '/');
            std::getline(ss, yearStr);
            releaseDate.setDay(std::stoi(dayStr));
            releaseDate.setMonth(static_cast<Month>(std::stoi(monthStr)));
            releaseDate.setYear(std::stoi(yearStr));
        }
        else if (key == "Release Place")
            releasePlace = value;
        else if (key == "Authors"){
            std::istringstream ss(value);
            std::string authorName;
            while (std::getline(ss, authorName, ',')) {
                authorName.erase(0, authorName.find_first_not_of(' '));
                size_t spacePos = authorName.find_last_of(' ');
                std::string firstName = authorName.substr(0, spacePos);
                std::string lastName = authorName.substr(spacePos + 1);
                bookAuthors.push_back(Author(firstName, lastName));
            }
        }
        else if (key == "Chapters"){
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
    }
    return Book(bookTitle, bookAuthors, ISBN, bookPublisher, releaseDate, releasePlace, bookChapters);
}