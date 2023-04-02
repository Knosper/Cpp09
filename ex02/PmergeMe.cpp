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
}

unsigned long long	PmergeMe::FT_Atoull(const std::string &str)
{
	size_t					i;
	unsigned long long		sum;

	sum = 0ULL;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
	|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
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

void insertion_sort_list(std::list<unsigned long long>& arr)
{
    for (std::list<unsigned long long>::iterator i = arr.begin(); i != arr.end(); ++i)
	{
        unsigned long long val = *i;
        std::list<unsigned long long>::iterator j = i;
        while (j != arr.begin())
		{
            std::list<unsigned long long>::iterator prev_j = j;
			prev_j--;
            if (*prev_j > val)
			{
                *j = *prev_j;
                j = prev_j;
            }
			else
                break ;
        }
        *j = val;
    }
}

void merge_list(std::list<unsigned long long>& arr, std::list<unsigned long long>& L, std::list<unsigned long long>& R)
{
    std::list<unsigned long long>::iterator i = L.begin();
    std::list<unsigned long long>::iterator j = R.begin();
    while (i != L.end() && j != R.end())
	{
        if (*i <= *j)
		{
            arr.push_back(*i);
            ++i;
        }
		else
		{
            arr.push_back(*j);
            ++j;
        }
    }
    while (i != L.end())
	{
        arr.push_back(*i);
        ++i;
    }
    while (j != R.end())
	{
        arr.push_back(*j);
        ++j;
    }
}

void merge_insert_list(std::list<unsigned long long>& arr) 
{
    if (arr.size() <= 1)
	{
        return ;
    }
    if (arr.size() <= 10)
	{
        insertion_sort_list(arr);
    }
	else
	{
        std::list<unsigned long long> L, R;
        int mid = arr.size() / 2;
        for (std::list<unsigned long long>::iterator it = arr.begin(); it != arr.end(); ++it)
		{
            if (std::distance(arr.begin(), it) < mid)
			{
                L.push_back(*it);
            }
			else
			{
                R.push_back(*it);
            }
        }
        merge_insert_list(L);
        merge_insert_list(R);
        arr.clear();
        merge_list(arr, L, R);
    }
}

void PmergeMe::SortList()
{
	merge_insert_list(_list);
}

void insertion_sort_vec(std::vector<unsigned long long>& vec)
{
	std::vector<unsigned long long>::iterator i = vec.begin();
	while (i != vec.end())
	{
		unsigned long long val = *i;
        std::vector<unsigned long long>::iterator j = i;
		while (j != vec.begin())
		{
            std::vector<unsigned long long>::iterator prev_j = j;
			prev_j--;
			if (*prev_j > val)
			{
				*j = *prev_j;
				j = prev_j;
			}
			else
				break ;
		}
		*j = val;
		i++;
	}
}

void merge_vec(std::vector<unsigned long long>& arr, std::vector<unsigned long long>& L, std::vector<unsigned long long>& R)
{
	std::vector<unsigned long long>::iterator i = L.begin();
    std::vector<unsigned long long>::iterator j = R.begin();
	while (i != L.end() && j != R.end())
	{
        if (*i <= *j)
		{
            arr.push_back(*i);
            ++i;
        }
		else
		{
            arr.push_back(*j);
            ++j;
        }
    }
	while (i != L.end())
	{
        arr.push_back(*i);
        ++i;
    }
    while (j != R.end())
	{
        arr.push_back(*j);
        ++j;
    }
}

void PmergeMe::SortVec(std::vector<unsigned long long> &vec)
{
	if (vec.size() <= 1)
		return ;
    if (vec.size() <= 10)
	{
        insertion_sort_vec(vec);
    }
	else
	{
        std::vector<unsigned long long> L, R;
		int mid = vec.size() / 2;
		std::vector<unsigned long long>::iterator it = vec.begin();
		while (it != vec.end())
		{
			if (std::distance(vec.begin(), it) < mid)
				L.push_back(*it);
			else
				R.push_back(*it);
			it++;
		}
		SortVec(L);
		SortVec(R);
		vec.clear();
		merge_vec(vec, L, R);
	}
}

void PmergeMe::StartPmerge()
{
	size_t i = 0;
	bool digit = false;
	std::string::const_iterator begin = _args.begin();
	std::string::const_iterator end = _args.end();
	std::string::const_iterator it = begin;
	while (it != end)
	{
		if (((std::isdigit(*it) || *it == '-') && digit) || it == begin)
		{
			std::string::const_iterator num_begin = it;
			_vec.push_back(this->FT_Atoull(std::string(num_begin, end)));
			_list.push_back(this->FT_Atoull(std::string(num_begin, end)));
			digit = false;
		}
		else if (*it == ' ')
		{
			digit = true;
		}
		++it;
	}
    std::cout << "Before: ";
    std::list<unsigned long long>::iterator it2;
    for (it2 = _list.begin(); it2 != _list.end(); ++it2)
    {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

	struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    this->SortList();
	gettimeofday(&end_time, NULL);
    unsigned long long time_diff_us = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
	
	std::cout << "After: ";
	for (std::list<unsigned long long>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
    std::cout << "Time to process a range of " << _list.size() << " elements with std::list: " << time_diff_us << "us" << std::endl;

	gettimeofday(&start_time, NULL);
    this->SortVec(_vec);
	gettimeofday(&end_time, NULL);
    time_diff_us = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector: " << time_diff_us << "us" << std::endl;
   	/*il = 0;
    std::cout << "Vector after: " << std::endl;
	while (il < _vec.size())
	{
        std::cout << _vec.at(il) << " ";
		il++;
	}
    std::cout << std::endl;*/
}
