/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:58:19 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/20 22:58:19 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static bool	valid_path(char *path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Path error\n";
		return (false);
	}
	file.close();
	return (true);
}

static std::string	get_text(char *path)
{
	std::ifstream file(path);
	std::string	text;
	std::string line;
 
	while (std::getline(file, line))
	{
		if (text.empty())
			text = line;
		else
			text += line;
		text += '\n';
	}
	file.close();
	return (text);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Arg error\n";
		return (1);
	}
	if (valid_path(argv[1]))
	{
		BitcoinExchange	ex(get_text(argv[1]));
		ex.calcValue();
	}
	else
		return (1);
	return (0);
}
