/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 23:10:20 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/20 23:10:20 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string tabelle):_tab(tabelle), _data()
{
	std::cout << "BitcoinExchange called" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{}

std::string	BitcoinExchange::get_nline()
{
	std::string line;
	size_t pos = _tab.find('\n');

	if (pos != std::string::npos)
	{
		std::string line = _tab.substr(0, pos);
		_tab.erase(0, pos + 1);
		return (line);
	} 
	else
	{
		return ("");
	}
}

bool BitcoinExchange::valid_first(const std::string tmp)
{
	if (tmp.compare("date | value\r") == 0 || tmp.compare("date | value") == 0)
		return (1);
	return (0);
}

float BitcoinExchange::get_factor(std::string date)
{
    float ret = 0;
    std::ifstream list("data.csv");
    if (!list.is_open())
	{
        std::cout << "data.csv file error" << std::endl;
        return (1);
    }
    std::string line;
	std::getline(list, line);
	std::string closest_date;
	size_t comma_pos = 0;
	float closest_factor_diff = std::numeric_limits<float>::max();
    while (std::getline(list, line)) 
	{
        comma_pos = line.find(',');
        std::string line_date = line.substr(0, comma_pos);
        if (line_date == date)
		{
            std::string line_factor = line.substr(comma_pos + 1);
            ret = atof(line_factor.c_str());
			list.close();
            return (ret);
        }
		else
        {
			int line_year = atoi(line_date.substr(0,4).c_str());
            int line_month = atoi(line_date.substr(5,2).c_str());
            int line_day = atoi(line_date.substr(8,2).c_str());
			int date_year = atoi(date.substr(0,4).c_str());
			int date_month = atoi(date.substr(5,2).c_str());
			int date_day = atoi(date.substr(8,2).c_str());
			int year_diff = line_year - date_year;
			int month_diff = line_month - date_month;
			int day_diff = line_day - date_day;
			int total_diff = std::abs(year_diff * 365 + month_diff * 30 + day_diff);
			if (total_diff < closest_factor_diff)
			{
				closest_factor_diff = total_diff;
				closest_date = line_date;
				ret = atof(line.substr(comma_pos + 1).c_str());
			}
        }
    }
	list.close();
    return (ret);
}

bool BitcoinExchange::is_digits(const std::string &str)
{
	bool digit = false;
	int i = 0;
	while (str[i])
	{
		if (std::isdigit(str[i]))
            digit = true;
		if (!std::isdigit(str[i]) && !std::isspace(str[i]) && str[i] != '.' && str[i] != '-')
    		return false;
		i++;
	}
	if (digit)
		return (true);
	return (false);
}

bool BitcoinExchange::check_date(std::string date)
{
	if (date.length() < 10)
		return (false);
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
	if ((year > 2023 || year < 1997) || (month < 1 || month > 12) || (day < 1 || day > 31))
		return (false);
	else if (month % 2 == 0 && day > 30)
		return (false);
	else if ((year == 2000 || year == 2004 || year == 2008 || year == 2012 || year == 2016 || year == 2020) && (month == 2 && day > 28))
		return (false);
	else if (month == 2 && day > 29)
		return (false);
	return (true);
}

void	BitcoinExchange::calcValue(void)
{
	std::string tmp = get_nline();
	std::string date;
	float		val;
	size_t 		pos;

	if (!valid_first(tmp))
	{
		std::cout << "Error: file format" << std::endl;
		return;
	}
	tmp = get_nline();
	long long maxValue = 0;
	while (!tmp.empty())
	{
		pos = tmp.find('|');
		if (pos != std::string::npos && is_digits(tmp.substr(pos + 1)))
		{
			date = tmp.substr(0, pos - 1);
			val = atof((tmp.substr(pos + 1).c_str()));
			maxValue = strtoll((tmp.substr(pos + 1)).c_str(), NULL, 10);
			_data.insert(std::make_pair(date, val));
			if (maxValue >= 2147483648LL)
				std::cout << "Error: too large a number." << std::endl;
			else
			{
				if (check_date(date))
				{
					if (val >= 0)
						std::cout << date << " => " << _data[date] << " = " << get_factor(date) * _data[date] << std::endl;
					else
						std::cout << "Error: not a positiv number." << std::endl;
				}
				else
				{
					std::cout << "Error: bad input => " << date << std::endl;
				}
			}
			_data.clear();
		}
		else
		{
			if (tmp.length() >= 10 && !check_date(tmp.substr(0, 10)))
				std::cout << "Error: bad input => " << tmp.substr(0, 10) << std::endl;
			else
				std::cout << "invalid format! 'date | val'" << std::endl; 
		}
		tmp = get_nline();
	}
}
