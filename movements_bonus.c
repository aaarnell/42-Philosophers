/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/15 12:15:47 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	prnt(t_state *vars, char *str, long st)
{
	sem_wait(vars->out);
	printf("%ld %d %s\n", (st - vars->start), vars->ph_id, str);
	sem_post(vars->out);
}

void	think_eat(t_state *vars)
{
	prnt(vars, "is thinking", get_time());
	sem_wait(vars->forks);
	prnt(vars, "has taken a fork", get_time());
	sem_wait(vars->forks);
	prnt(vars, "has taken a fork", get_time());
	vars->last_eat = get_time();
	prnt(vars, "is eating", vars->last_eat);
	my_usleep(vars->last_eat + (long)vars->time_to_eat);
	if (vars->cnt_must_eat >= 0)
		vars->eat_cnt++;
	sem_post(vars->forks);
	sem_post(vars->forks);
}

void	sleeping(t_state *vars)
{
	prnt(vars, "is sleeping", get_time());
	my_usleep(get_time() + (long)vars->time_to_sleep);
}
