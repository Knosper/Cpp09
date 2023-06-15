/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:18:55 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/27 15:18:55 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <sstream>
#include <cfloat>

#define _operators "+-/*"
#define _OVERFLOW	10
#define _WRONGCHAR	11
#define _INVALID	12
#define _OUTOFRANGE	13

class RPN
{
protected:
	RPN();
public:
	std::string		_args;
	std::stack<double> _stack;

	RPN(std::string arg);
	~RPN();
	void start_polish(void);

private:
	RPN(const RPN &cp);
	RPN	&operator=(const RPN &src);
	int input_check(std::string arg);
	long long	ft_atoll(const std::string str);
};
