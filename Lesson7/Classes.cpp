#include"Classes.h"

void Date::setDay(std::string _day)
{
	day = _day;
}

void Date::setMonth(std::string _month)
{
	month = _month;
}

void Date::setYear(std::string _year)
{
	year = _year;
}

std::string Date::getDay()
{
	return day;
}

std::string Date::getMonth()
{
	return month;
}

std::string Date::getYear()
{
	return year;
}

std::ostream& operator<< (std::ostream& out,Date& date)
{
	out << "Date: " << date.getDay() << '.' << date.getMonth()<< '.' << date.getYear() << '\n';
	return out;
}