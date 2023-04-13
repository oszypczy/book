#pragma once
#include <string>
#include <map>

enum class Month {Jan=1, Feb, Mar, Apr, May, June, July, Aug, Sep, Oct, Nov, Dec};

class Date {
    private:
        ushort day;
        Month month;
        int year;
        std::map<Month, ushort> daysInMonth;
        void checkDate(ushort newDay, Month newMonth, int newYear);
    public:
        Date(ushort newDay=1, Month newMonth=Month::Jan, int newYear=2000);
        ushort getDay() const;
        Month getMonth() const;
        int getYear() const;
        void setDay(ushort newDay);
        void setMonth(Month newMonth);
        void setYear(int newYear);
        bool operator==(const Date& secondDate) const;
        bool operator!=(const Date& secondDate) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};