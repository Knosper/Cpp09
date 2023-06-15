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

/*
 * Regarding the time comparison between std::list and std::vector.
 * This is because std::list is implemented as a doubly-linked list... (more pointers)
 * if you need to insert or remove elements frequently in the middle of a container, std::list may be a better choice.
 * 
*/
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
		if (a.valid_digits())
			a.start_pmerge();
		else
			std::cout << "Error: invalid char found" << std::endl;
	}
	return (0);
}
