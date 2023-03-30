/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:11:54 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/29 04:11:54 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe():_args(), _vec(), _list() {}

PmergeMe::PmergeMe(std::string s):_args(s), _vec(), _list() {}

PmergeMe::~PmergeMe()
{
	_vec.clear();
	_args.clear();
	_list.clear();
	std::cout << "PmergeMe destructor called" << std::endl;
}

unsigned long long	PmergeMe::FT_Atoull(const std::string str)
{
	size_t					i;
	unsigned long long		sum;

	sum = 0ULL;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
	|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
	{
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10ULL) + (str[i++] - '0');
	}
	return (sum);
}

bool PmergeMe::ValidDigits()
{
	bool digit = false;
	int i = 0;
	while (_args[i])
	{
		if (std::isdigit(_args[i]))
            digit = true;
		else if (!std::isdigit(_args[i]) && !std::isspace(_args[i]) && _args[i] != '-')
    		return (false);
		i++;
	}
	return (digit);
}

void PmergeMe::SortList()
{
	size_t i = 0;
	while (i < 999999999)
		i++;
	std::cout << "After: ";
	std::list<unsigned long long>::iterator it;
    for (it = _list.begin(); it != _list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::StartPmerge()
{
	size_t i = 0;
	bool digit = false;
	while (_args[i])
	{
		if (((std::isdigit(_args[i]) || _args[i] == '-') && digit) || i == 0)
		{
			_vec.push_back(this->FT_Atoull(_args.substr(i)));
			_list.push_back(this->FT_Atoull(_args.substr(i)));
			digit = false;
		}
		else if (_args[i] == ' ')
		{
			digit = true;
		}
		i++;
	}
    std::cout << "Before: ";
    std::list<unsigned long long>::iterator it;
    for (it = _list.begin(); it != _list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
	struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    this->SortList();
	gettimeofday(&end_time, NULL);
    unsigned long long time_diff_us = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
    std::cout << "Time to process a range of " << _list.size() << "elements with std::list: " << time_diff_us << "us" << std::endl;
    /*std::vector<unsigned long long>::iterator it2;
    std::cout << "Vector before: " << std::endl;
	for (it2 = _vec.begin(); it2 != _vec.end(); ++it2)
    {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;*/
}
