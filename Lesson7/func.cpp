//#include"Classes.h"
#include"func.h"

int charToInt(std::string& str)
{
	int res{};
	int factor{ 1 };
	for (int i{(int)str.size()-1};i>=0;--i)
	{
		res += ((int)str[i] - (int)'0') * factor;
		factor *= 10;
	}

	return res;
}

Date& dateCmp(Date& date1, Date& date2)
{
	std::string str;
	int i_date1{}, i_date2{};

	str = date1.getYear();
	i_date1 = charToInt(str);

	str = date2.getYear();
	i_date2 = charToInt(str);

	if (i_date1 > i_date2)
		return date1;
	else if (i_date1 < i_date2)
		return date2;
	else
	{
		str = date1.getMonth();
		i_date1 = charToInt(str);

		str = date2.getMonth();
		i_date2 = charToInt(str);

		if (i_date1 > i_date2)
			return date1;
		else if (i_date1 < i_date2)
			return date2;
		else
		{
			str = date1.getDay();
			i_date1 = charToInt(str);

			str = date2.getDay();
			i_date2 = charToInt(str);

			if (i_date1 >= i_date2)
				return date1;
			else if (i_date1 <= i_date2)
				return date2;
		}
	}
}

void dateSwap(Date& date1, Date& date2)
{
	Date tmp;
	tmp = date1;
	date1 = date2;
	date2 = tmp;
}