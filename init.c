/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:41:41 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/28 19:45:55 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_state_strct(t_state *vars, int *argc, char **argv)
{
	int i;

	i = 0;
	vars->num_phils = short_atoi(argv[1]);
	vars->time_to_die = short_atoi(argv[2]);
	vars->time_to_eat = short_atoi(argv[3]);
	vars->time_to_sleep = short_atoi(argv[4]);
	vars->cnt_must_eat = 0;
	vars->death = 0;
	if(*argc == 6)
		vars->cnt_must_eat = short_atoi(argv[5]);
	vars->start = 0;
	vars->philos = (t_philo **)malloc(sizeof(t_philo *) * (vars->num_phils + 1));
	if (!vars->philos)
		return ;			//Прописать завершение программы (вывод ошибки, очистка, выход)
	vars->philos[vars->num_phils] = NULL;
	while(i < vars->num_phils)
	{
		vars->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!vars->philos[i])
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		vars->philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!vars->philos[i]->thread)
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		vars->philos[i]->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!vars->philos[i]->left_fork)
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		i++;
	}
}

void init_philosophers(t_state *vars)
{
	int i;
	int ret;

	i = 0;
	while(i < vars->num_phils)
	{
		vars->philos[i]->id = i + 1;
		ret = pthread_mutex_init(vars->philos[i]->left_fork, NULL);
		if (ret)
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		vars->philos[i]->right_fork = vars->philos[(i + 1) % vars->num_phils]->left_fork;
		vars->philos[i]->last_eat = 0;
		vars->philos[i]->vars = vars;
		i++;
	}
}
