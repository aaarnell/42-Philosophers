/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/26 19:51:50 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_state vars;
	// int i;

	if (argc < 5 || argc > 6)
		return (-1);			//Написать вывод ошибки, очистку (если есть выделение) и выход
	init_state_strct(&vars, &argc, argv);
	init_philosophers(&vars);
	simulation(&vars);
	// i = 0;
	// while (i < vars.num_phils)
	// 	pthread_join(*vars.philos[i++]->thread, NULL);
	return (0);
}
