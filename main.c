/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/07 19:55:57 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_state	vars;

	if (argc < 5 || argc > 6)
		return (error("Error in the number arguments.\n"));
	if (init_state_strct(&vars, &argc, argv))
		return (1);
	if (init_philosophers(&vars))
	{
		clear_mem(&vars);
		return (error("Mutex initialization error.\n"));
	}
	if (simulation(&vars))
	{
		clear_mem(&vars);
		return (error("Error creating threads.\n"));
	}
	clear_mem(&vars);
	return (0);
}
