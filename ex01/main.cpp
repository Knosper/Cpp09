/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:17:15 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/27 15:17:15 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string arg(argv[1]);
		try
		{
			RPN tmp(arg);
			tmp.start_polish();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return (1);
		}
	}
	else
		std::cout << "Error: Only 1 argument! Use quotes: \"2 3 +\"" << std::endl;
	return (0);
}