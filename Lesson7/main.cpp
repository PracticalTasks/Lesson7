//#include <iostream>
#include"Classes.h"
#include<memory>
#include"func.h"

using namespace std;

int main()
{
	//Task 1
	{
		cout << "Task 1\n";
		auto today = std::make_shared<Date>();
		shared_ptr<Date> date;
		today->setDay("18");
		today->setMonth("09");
		today->setYear("2021");
		cout << *today;
		cout << "Pointer date: " << date << " Pointer today: " << today << '\n';
		date = move(today);
		cout << "Pointer date: " << date << " Pointer today: " << today << '\n';
	}

	//Task 2
	{
		cout << "\n\nTask 2\n";
		auto date1 = std::make_shared<Date>();
		auto date2 = std::make_shared<Date>();
		date1->setDay("12");
		date1->setMonth("11");
		date1->setYear("2019");

		date2->setDay("18");
		date2->setMonth("9");
		date2->setYear("2021");

		cout<< dateCmp(*date1, *date2);

		cout << '\n';
		cout << *date1 << *date2;
		dateSwap(*date1, *date2);
		cout << '\n';
		cout << *date1 << *date2;
	}

	//Task 5
	{
		cout << "\n\nTask 5\n";
	}

}