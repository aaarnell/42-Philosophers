/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/09 18:00:35 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think_eat(t_philo *ph)
{
	if (!ph->vars->death)
		printf("%ld %d is thinking\n", (get_time() - ph->vars->start), ph->id);
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->death_lock);
	if (!ph->vars->death)
		printf("%ld %d has taken a fork\n", \
			(get_time() - ph->vars->start), ph->id);
	ph->last_eat = get_time();
	pthread_mutex_unlock(ph->death_lock);
	if (!ph->vars->death)
		printf("%ld %d is eating\n", (ph->last_eat - ph->vars->start), ph->id);
	my_usleep(ph->last_eat + (long)ph->vars->time_to_eat);
	if (ph->vars->cnt_must_eat >= 0)
		ph->eat_cnt++;
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	sleeping(t_philo *ph)
{
	if (!ph->vars->death)
		printf("%ld %d is sleeping\n", (get_time() - ph->vars->start), ph->id);
	my_usleep(get_time() + (long)ph->vars->time_to_sleep);
}
