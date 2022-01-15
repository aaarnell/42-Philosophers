/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:41:41 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/15 13:49:58 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sem_initial(t_state *vars)
{
	sem_unlink("dSem");
	sem_unlink("fSem");
	sem_unlink("oSem");
	vars->death = sem_open("dSem", O_CREAT, 0666, 0);
	vars->forks = sem_open("fSem", O_CREAT, 0666, \
		(unsigned int)vars->num_phils);
	vars->out = sem_open("oSem", O_CREAT, 0666, 1);
}

int	init_state_strct(t_state *vars, int *argc, char **argv)
{
	vars->num_phils = short_atoi(argv[1]);
	vars->time_to_die = short_atoi(argv[2]);
	vars->time_to_eat = short_atoi(argv[3]);
	vars->time_to_sleep = short_atoi(argv[4]);
	vars->cnt_must_eat = -1;
	vars->dth = 0;
	if (*argc == 6)
		vars->cnt_must_eat = short_atoi(argv[5]);
	vars->start = 0;
	if (vars->num_phils == -1 || vars->time_to_die == -1 || \
		vars->time_to_eat == -1 || vars->time_to_sleep == -1 || \
		(*argc == 6 && vars->cnt_must_eat == -1))
		return (error("Error in type arguments.\n"));
	vars->pid = (pid_t *)malloc(sizeof(pid_t) * vars->num_phils);
	if (!vars->pid)
		return (error("Memory allocation error.\n"));
	sem_initial(vars);
	vars->ph_id = 0;
	vars->eat_cnt = 0;
	return (0);
}
