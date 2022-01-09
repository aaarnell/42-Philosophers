/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:41:41 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/09 20:03:55 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	alloc_mem_ph(t_state *vars, int i)
{
	vars->philos[i] = (t_philo *)malloc(sizeof(t_philo));
	if (!vars->philos[i])
		return (clear_mem(vars));
	vars->philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!vars->philos[i]->thread)
		return (clear_mem(vars));
	vars->philos[i]->left_fork = (pthread_mutex_t *) \
		malloc(sizeof(pthread_mutex_t));
	if (!vars->philos[i]->left_fork)
		return (clear_mem(vars));
	vars->philos[i]->death_lock = (pthread_mutex_t *) \
		malloc(sizeof(pthread_mutex_t));
	if (!vars->philos[i]->death_lock)
		return (clear_mem(vars));
	return (0);
}

static int	alloc_mem(t_state *vars)
{
	int	i;

	i = 0;
	vars->philos = (t_philo **)malloc(sizeof(t_philo *) \
		* (vars->num_phils + 1));
	if (!vars->philos)
		return (1);
	vars->philos[vars->num_phils] = NULL;
	while (i < vars->num_phils)
	{
		if (alloc_mem_ph(vars, i))
			return (1);
		i++;
	}
	return (0);
}

int	init_state_strct(t_state *vars, int *argc, char **argv)
{
	int	i;

	i = 0;
	vars->num_phils = short_atoi(argv[1]);
	vars->time_to_die = short_atoi(argv[2]);
	vars->time_to_eat = short_atoi(argv[3]);
	vars->time_to_sleep = short_atoi(argv[4]);
	vars->cnt_must_eat = -1;
	vars->death = 0;
	if (*argc == 6)
		vars->cnt_must_eat = short_atoi(argv[5]);
	vars->start = 0;
	if (vars->num_phils == -1 || vars->time_to_die == -1 || \
		vars->time_to_eat == -1 || vars->time_to_sleep == -1 || \
		(*argc == 6 && vars->cnt_must_eat == -1))
		return (error("Error in type arguments.\n"));
	//if (alloc_mem(vars))
		//return (error("Memory allocation error.\n"));
	vars->pid = (pid_t *) malloc(sizeof(pid_t) * vars->num_phils);
	if (!vars->pid)
		return (error("Memory allocation error.\n"));
	return (0);
}

int	init_philosophers(t_state *vars)
{
	int	i;
	int	ret;

	i = 0;
	while (i < vars->num_phils)
	{
		vars->philos[i]->id = i + 1;
		ret = pthread_mutex_init(vars->philos[i]->left_fork, NULL);
		if (ret)
			return (1);
		ret = pthread_mutex_init(vars->philos[i]->death_lock, NULL);
		if (ret)
			return (1);
		vars->philos[i]->right_fork = vars->philos[(i + 1) \
			% vars->num_phils]->left_fork;
		vars->philos[i]->last_eat = 0;
		vars->philos[i]->vars = vars;
		i++;
	}
	return (0);
}
