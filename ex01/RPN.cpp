/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:19:40 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/27 15:19:40 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN():_args(), _stack() {}

RPN::RPN(std::string arg):_args(arg), _stack()
{
	int tmp = input_check(arg);
	if (tmp != 1)
	{
		if (tmp == _OVERFLOW)
			throw std::invalid_argument("Error: Invalid nb (int overflow)");
		else if (tmp == _INVALID)
			throw std::invalid_argument("Error: Invalid arg");
		else if (tmp == _WRONGCHAR)
			throw std::invalid_argument("Error: Invalid char found");
		else if (tmp == _OUTOFRANGE)
			throw std::invalid_argument("Error: nb must be (nb < 10 && nb >= 0)");
		else
			throw std::invalid_argument("Error: ???");
	}
}

RPN::RPN(const RPN &cp)
{
	*this = cp;
}

RPN::~RPN() {}

RPN	&RPN::operator=(const RPN &src)
{
	_args = src._args;
	_stack = src._stack;
	return (*this);
}

long long	RPN::ft_atoll(const std::string str)
{
	long long		sign;
	size_t			i;
	long long		sum;

	sum = 0LL;
	sign = 1LL;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
	|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = sign * -1;
		}
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10LL) + (str[i++] - '0');
	}
	return (sign * sum);
}

/*
 * is not counting operator and numbers!!
 * syntax controll missing 
 */
int RPN::input_check(std::string arg)
{
	size_t i = 0;
	size_t j = 0;
	bool digit = true;
	long long tmp;
	if (arg.length() < 2)
		return (_INVALID);
	while (arg[i])
	{
		if (!std::isdigit(arg[i]) && arg[i] != ' ')
		{
			j = 0;
			while (_operators[j])
			{
				if (arg[i] == _operators[j] && i < arg.length() && (arg[i + 1] == ' ' || arg[i + 1] == '\0'))
					break ;
				j++;
				if (j == 4 && !std::isdigit(arg[i + 1]))
					return (_WRONGCHAR);
				else if (arg[i] == '-')
				{
					tmp = ft_atoll(arg.substr(i));
					if (tmp < -2147483648LL)
						return (_OVERFLOW);
					else if (tmp > 9 || tmp < 0)
						return (_OUTOFRANGE);
				}
			}
		}
		else if (arg[i] != ' ' && digit)
		{
			digit = false;
			tmp = ft_atoll(arg.substr(i));
			if (tmp > 2147483647LL)
				return (_OVERFLOW);
			else if (tmp > 9 || tmp < 0)
				return (_OUTOFRANGE);
		}
		else if (arg[i] == ' ')
			digit = true;
		i++;
	}
	return (true);
}

void RPN::start_polish(void)
{
	std::istringstream iss(_args);
    std::string token;

    while (iss >> token)
    {
        if (std::isdigit(token[0]))
        {
            double num = std::atof(token.c_str());
            _stack.push(num);
        }
		else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (_stack.size() < 2)
                throw std::invalid_argument("Error: Not enough operands for operator");
            double rhs = _stack.top();
            _stack.pop();
            double lhs = _stack.top();
            _stack.pop();
            double result = 0.0;
            if (token == "+")
                result = lhs + rhs;
            else if (token == "-")
                result = lhs - rhs;
            else if (token == "*")
                result = lhs * rhs;
            else if (token == "/")
            {
                if (rhs == 0)
                    throw std::invalid_argument("Error: Division by zero");
                result = lhs / rhs;
            }
            if (result >= DBL_MAX || result <= -DBL_MAX)
                throw std::overflow_error("Error: Calculation caused an overflow");
            _stack.push(result);
        }
        else
            throw std::invalid_argument("Error: Invalid token");
    }
    if (_stack.size() != 1)
		throw std::invalid_argument("Error: Too many operands");
	std::cout << _stack.top() << std::endl;
}
