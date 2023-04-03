#include "date.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
#include <stdexcept>


Date::Date(ushort newDay, Month newMonth, int newYear) : day(newDay), month(newMonth), year(newYear){
    daysInMonth = {{Month::Jan, 31},
                   {Month::Feb, 28},
                   {Month::Mar, 31},
                   {Month::Apr, 30},
                   {Month::May, 31},
                   {Month::June, 30},
                   {Month::July, 31},
                   {Month::Aug, 31},
                   {Month::Sep, 30},
                   {Month::Oct, 31},
                   {Month::Nov, 30},
                   {Month::Dec, 31}};
    checkDate(newDay, newMonth, newYear);
}

void Date::checkDate(ushort newDay, Month newMonth, int newYear) {
    if ((newYear % 4 == 0 && newYear % 100 != 0) || newYear % 400 == 0) {
        daysInMonth[Month::Feb] = 29;
    }
    if (newDay > daysInMonth[newMonth] || newDay == 0) {
        throw std::domain_error("Given day is not valid");
    }
    if (newYear < 0) {
        throw std::domain_error("Given year cannot be negative");
    }
}

ushort Date::getDay() const{
    return day;
}

Month Date::getMonth() const{
    return month;
}

int Date::getYear() const{
    return year;
}

void Date::setDay(ushort newDay) {
    checkDate(newDay, month, year);
    day = newDay;
}

void Date::setMonth(Month newMonth) {
    checkDate(day, newMonth, year);
    month = newMonth;
}

void Date::setYear(int newYear) {
    checkDate(day, month, newYear);
    year = newYear;
}

std::string Date::str() {
    std::stringstream stream;
    stream << std::setw(2) << std::setfill('0') << day << "."
           << std::setw(2) << std::setfill('0') << static_cast<ushort>(month) << "."
           << year;
    return stream.str();
}