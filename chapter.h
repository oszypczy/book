#pragma once
#include <string>

class Chapter{
    private:
        ushort chapterNumber;
        uint chapterPages;
        std::string chapterTitle;
        void checkData(ushort newNumber, uint newPages, std::string newTitle) const;
    public:
        Chapter(ushort newNumber, uint newPages, std::string newTitle);
        ushort getChapterNumber() const;
        uint getChapterPages() const;
        std::string getChapterTitle() const;
        void setChapterNumber(ushort newNumber);
        void setChapterPages(uint newPages);
        void setChapterTitle(std::string newTitle);
        Chapter& operator++();
        Chapter operator++(int);
        Chapter& operator--();
        Chapter operator--(int);
        bool operator==(const Chapter& secondChapter) const;
        bool operator!=(const Chapter& secondChapter) const;
        bool operator<(const Chapter& secondChapter) const;
        bool operator>(const Chapter& secondChapter) const;
        bool operator<=(const Chapter& secondChapter) const;
        bool operator>=(const Chapter& secondChapter) const;
    friend std::ostream& operator<<(std::ostream& os, const Chapter& chapter);
};