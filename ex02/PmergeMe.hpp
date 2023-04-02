/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:11:18 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/29 04:11:18 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <sys/time.h>

class PmergeMe
{
protected:
	PmergeMe();
private:
	std::string _args;
	std::vector<unsigned long long> _vec;
	std::list<unsigned long long> _list;
public:
	PmergeMe(std::string s);
	~PmergeMe();
	bool ValidDigits();
	void StartPmerge();
	void SortList();
	void SortVec(std::vector<unsigned long long> &vec);
	unsigned long long	FT_Atoull(const std::string &str);
};
