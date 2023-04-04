/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 23:10:16 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/20 23:10:16 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <cmath>

class BitcoinExchange
{
protected:
	BitcoinExchange();

public:
	BitcoinExchange(std::string tabelle);

	~BitcoinExchange();

	void	calcValue(void);

private:
	std::string	get_nline();
	bool check_date(std::string date);
	bool is_digits(const std::string &str);
	float get_factor(std::string date);
	bool valid_first(const std::string tmp);

	std::string						_tab;
	std::map<std::string, float>	_data;

};
