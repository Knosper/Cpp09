/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:14:42 by jjesberg          #+#    #+#             */
/*   Updated: 2023/03/29 04:14:42 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		int		i = 1;
		std::string tmp;
		while (i < argc)
		{
			tmp += argv[i++];
			tmp += " ";
		}
		PmergeMe a(tmp);
		if (a.ValidDigits())
			a.StartPmerge();
		else
			std::cout << "Error: invalid char found" << std::endl;
	}
	return (0);
}
