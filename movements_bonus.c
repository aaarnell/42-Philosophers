/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/13 20:15:00 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think_eat(t_state *vars)
{
	printf("%ld %d is thinking\n", (get_time() - vars->start), vars->ph_id);
	sem_wait(vars->forks);
	sem_wait(vars->forks);
	printf("%ld %d has taken a fork\n", \
		(get_time() - vars->start), vars->ph_id);
	vars->last_eat = get_time();
	printf("%ld %d is eating\n", (vars->last_eat - vars->start), vars->ph_id);
	my_usleep(vars->last_eat + (long)vars->time_to_eat);
	if (vars->cnt_must_eat >= 0)
		vars->eat_cnt++;
	sem_post(vars->forks);
	sem_post(vars->forks);
}

void	sleeping(t_state *vars)
{
	printf("%ld %d is sleeping\n", (get_time() - vars->start), vars->ph_id);
	my_usleep(get_time() + (long)vars->time_to_sleep);
}
