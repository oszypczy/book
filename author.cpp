#include "author.h"
#include <iostream>
#include <stdexcept>

Author::Author(std::string newName, std::string newSurname) : name(newName), surname(newSurname){
    checkData(newName, newSurname);
}

void Author::checkData(std::string newName, std::string newSurname) const {
    if (newName.empty()) {
        throw std::invalid_argument("Name cannot be empty!");
    }
    if (newSurname.empty()) {
        throw std::invalid_argument("Surname cannot be empty!");
    }
}

std::string Author::getName() const {
    return name;
}

std::string Author::getSurname() const {
    return surname;
}

void Author::setName(std::string newName) {
    checkData(newName, surname);
    name = newName;
}

void Author::setSurname(std::string newSurname) {
    checkData(name, newSurname);
    surname = newSurname;
}

bool Author::operator==(const Author& secondAuthor) const {
    return (name == secondAuthor.getName() && surname == secondAuthor.getSurname());
}

bool Author::operator!=(const Author& secondAuthor) const {
    return !(*this == secondAuthor);
}

std::ostream& operator<<(std::ostream& os, const Author& author){
    os << "Author: " << author.name << " " << author.surname;
    return os;
}