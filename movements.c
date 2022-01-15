/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/15 12:21:05 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	prnt(t_philo *ph, char *str, long st)
{
	pthread_mutex_lock(&ph->vars->out_lock);
	if (!ph->vars->death)
	{
		printf("%ld %d %s\n", (st - ph->vars->start), ph->id, str);
		pthread_mutex_unlock(&ph->vars->out_lock);
	}
	else
		return (1);
	return (0);
}

void	think_eat(t_philo *ph)
{
	if (prnt(ph, "is thinking", get_time()))
		return ;
	pthread_mutex_lock(ph->right_fork);
	if (prnt(ph, "has taken a fork", get_time()))
		return ;
	pthread_mutex_lock(ph->left_fork);
	if (prnt(ph, "has taken a fork", get_time()))
		return ;
	pthread_mutex_lock(ph->death_lock);
	ph->last_eat = get_time();
	pthread_mutex_unlock(ph->death_lock);
	if (prnt(ph, "is eating", ph->last_eat))
		return ;
	my_usleep(ph->last_eat + (long)ph->vars->time_to_eat);
	if (ph->vars->cnt_must_eat >= 0)
		ph->eat_cnt++;
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	sleeping(t_philo *ph)
{
	if (prnt(ph, "is sleeping", get_time()))
		return ;
	my_usleep(get_time() + (long)ph->vars->time_to_sleep);
}
