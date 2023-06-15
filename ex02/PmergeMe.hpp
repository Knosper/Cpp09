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
#include <ctime>
#include <sys/time.h>

#define VERBOSE 0

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
	bool valid_digits();
	void start_pmerge();
	void sort_list();
	void sort_vec(std::vector<unsigned long long> &vec);
	unsigned long long	ft_atoull(const std::string &str);
};
