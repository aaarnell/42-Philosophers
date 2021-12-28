/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/28 21:45:32 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *ph)
{
	printf("%ld %d is thinking\n", (get_time() - ph->vars->start), ph->id);
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->left_fork);
	printf("%ld %d has taken a fork\n", (get_time() - ph->vars->start), ph->id);
}

static void	eating(t_philo *ph)
{
	long finish;

	finish = get_time() + ph->vars->time_to_eat;
	printf("%ld %d is eating\n", (get_time() - ph->vars->start), ph->id);
	while(1)
		if(get_time() >= finish)
			break ;
	ph->last_eat = get_time();
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

static void	sleeping(t_philo *ph)
{
	long finish;

	finish = get_time() + ph->vars->time_to_sleep;
	printf("%ld %d is sleeping\n", (get_time() - ph->vars->start), ph->id);
	while(1)
		if(get_time() >= finish)
			break ;
}

static void	*philosopher(void *ph)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = (t_philo *)ph;
	tmp->last_eat = tmp->vars->start;
	while(!tmp->vars->death)
	{
		//if (!i && (tmp->id % 2) && (tmp->vars->num_phils % 2 || tmp->id != tmp->vars->num_phils))
		if (!i && ((tmp->id == 1 && (tmp->vars->num_phils % 2)) || !(tmp->id % 2)))
			;
		else
		{
			thinking(tmp);
			eating(tmp);
		}
		sleeping(tmp);
		i++;
	}
	return (NULL);
}

void	simulation(t_state *vars)
{
	int i;
	int ret;
	pthread_t catch;

	i = 0;
	vars->start = get_time();
	ret = pthread_create(&catch, NULL, death_catcher, vars);
	if (ret)
		return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
	while(i < vars->num_phils)
	{
		ret = pthread_create(vars->philos[i]->thread, NULL, philosopher, vars->philos[i]);
		if (ret)
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		pthread_detach(*vars->philos[i]->thread);
		i++;
	}
	pthread_join(catch, NULL);
}
