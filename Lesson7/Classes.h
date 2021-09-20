#pragma once
#include<iostream>

class Date
{
	std::string day;
	std::string month;
	std::string year;
public:
	void setDay(std::string day);
	void setMonth(std::string month);
	void setYear(std::string year);
	std::string getDay();
	std::string getMonth();
	std::string getYear();
	friend std::ostream& operator<<(std::ostream& out,Date& date);
};