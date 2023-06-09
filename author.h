#pragma once
#include <string>

class Author{
    private:
        std::string name;
        std::string surname;
        void checkData(std::string newName, std::string newSurname) const;
    public:
        Author(std::string newName, std::string newSurname);
        std::string getName() const;
        std::string getSurname() const;
        void setName(std::string newName);
        void setSurname(std::string newSurname);
        bool operator==(const Author& secondAuthor) const;
        bool operator!=(const Author& secondAuthor) const;
    friend std::ostream& operator<<(std::ostream& os, const Author& author);
};