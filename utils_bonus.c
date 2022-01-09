/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:38:06 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/09 18:00:29 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
}

int	short_atoi(const char *str)
{
	unsigned long	r;
	int				i;

	r = 0;
	i = 0;
	while (*str && i < 10)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		r = (r * 10) + ((unsigned long)*str - 48);
		str++;
		i++;
	}
	if (r > INT_MAX)
		return (-1);
	return ((int)r);
}

void	my_usleep(long finish)
{
	while (get_time() < finish)
		usleep(500);
}

int	error(char *message)
{
	int	i;

	i = 0;
	while (message[i])
		i++;
	write(1, message, i);
	return (1);
}

int	clear_mem(t_state *vars)
{
	int	i;

	i = 0;
	while (vars->philos[i])
	{
		if (vars->philos[i]->thread)
			free(vars->philos[i]->thread);
		if (vars->philos[i]->left_fork)
			free(vars->philos[i]->left_fork);
		if (vars->philos[i]->death_lock)
			free(vars->philos[i]->death_lock);
		free(vars->philos[i]);
		i++;
	}
	if (vars->philos)
		free(vars->philos);
	return (1);
}
