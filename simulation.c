/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/03 17:47:46 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think_eat(t_philo *ph)
{
	if(!ph->vars->death)
		printf("%ld %d is thinking\n", (get_time() - ph->vars->start), ph->id);
		//putstate_1st_fd((get_time() - ph->vars->start), ph, " is thinking\n");
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->left_fork);
	if(!ph->vars->death)
		printf("%ld %d has taken a fork\n", (get_time() - ph->vars->start), ph->id);
		//putstate_1st_fd((get_time() - ph->vars->start), ph, " has taken a fork\n");
	ph->last_eat = get_time();
	if(!ph->vars->death)
		printf("%ld %d is eating\n", (get_time() - ph->vars->start), ph->id);
		//putstate_1st_fd((get_time() - ph->vars->start), ph, " is eating\n");
	usleep(ph->vars->time_to_eat * 1000);
	//my_usleep(ph->vars->time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

static void	sleeping(t_philo *ph)
{
	if(!ph->vars->death)
		printf("%ld %d is sleeping\n", (get_time() - ph->vars->start), ph->id);
	usleep(ph->vars->time_to_sleep * 1000);
	//my_usleep(ph->vars->time_to_sleep);
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
		if (!i && ((tmp->id == 1 && (tmp->vars->num_phils % 2)) || !(tmp->id % 2)))
			;
		else
			think_eat(tmp);
		sleeping(tmp);
		i++;
	}
	return (NULL);
}

static void	*death_catcher(void *vars)
{
	int i;
	t_state *tmp;

	tmp = (t_state *)vars;
	i = 0;
	while(!tmp->death)
	{
		while(tmp->philos[i])
		{
			if(tmp->philos[i]->last_eat && tmp->philos[i]->last_eat + tmp->time_to_die < get_time())
			{
				tmp->death++;
				printf("%ld %d die\n", (get_time() - tmp->start), tmp->philos[i]->id);
				//putstate_1st_fd((get_time() - tmp->start), tmp->philos[i], " die\n");
				return (NULL);
			}
			i++;
		}
		i = 0;
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
