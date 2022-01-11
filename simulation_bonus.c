/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/11 21:40:23 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
/*
static void	*philosopher(void *ph)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = (t_philo *)ph;
	tmp->last_eat = tmp->vars->start;
	tmp->eat_cnt = 0;
	while (!tmp->vars->death)
	{
		if (!i && ((tmp->id == 1 && (tmp->vars->num_phils % 2)) \
			|| !(tmp->id % 2)))
			;
		else
			think_eat(tmp);
		sleeping(tmp);
		i++;
	}
	return (NULL);
}

static int	catch(t_state *vars, int i)
{
	pthread_mutex_lock(vars->philos[i]->death_lock);
	pthread_mutex_unlock(vars->philos[i]->death_lock);
	if (vars->philos[i]->last_eat && \
		vars->philos[i]->last_eat + vars->time_to_die < get_time())
	{
		vars->death++;
		printf("%ld %d die\n", (get_time() - vars->start), \
			vars->philos[i]->id);
		return (1);
	}
	return (0);
}

static void	*death_catcher(void *vars)
{
	int		i;
	int		eat_cnt;
	t_state	*tmp;

	tmp = (t_state *)vars;
	while (!tmp->death)
	{
		i = 0;
		eat_cnt = 0;
		while (tmp->philos[i])
		{
			if (catch(tmp, i))
				return (NULL);
			if (tmp->cnt_must_eat >= 0 && \
				tmp->philos[i]->eat_cnt >= tmp->cnt_must_eat)
				eat_cnt++;
			i++;
		}
		if (eat_cnt == tmp->num_phils)
			break ;
	}
	return (NULL);
}

int	simulation(t_state *vars)
{
	int			i;
	int			ret;
	pthread_t	catch;

	i = 0;
	vars->start = get_time();
	ret = pthread_create(&catch, NULL, death_catcher, vars);
	if (ret)
		return (1);
	while (i < vars->num_phils)
	{
		ret = pthread_create(vars->philos[i]->thread, \
			NULL, philosopher, vars->philos[i]);
		if (ret)
			return (1);
		pthread_detach(*vars->philos[i]->thread);
		i++;
	}
	pthread_join(catch, NULL);
	return (0);
}*/
static void	*death_catcher(void *vars)
{
	t_state	*tmp;

	tmp = (t_state *)vars;
	sem_wait(tmp->death);
	vars->dth = 1;
	return (NULL);
}

static int call_child(t_state *vars)
{
	long	last_eat;

	last_eat = vars->start;

	return (0);
}

static int call_father(t_state *vars)
{
	pid_t		pid;
	int			eat_cnt;
	int			ret;
	pthread_t	catch;

	ret = pthread_create(&catch, NULL, death_catcher, vars);
	if (ret)
		return (1);
	eat_cnt = 0;
	while (!vars->dth)
	{
		pid = waitpid(-1, NULL, WUNTRACED);
		if (pid > 0)
			eat_cnt++;
		if (eat_cnt == vars->num_phils)
		{
			sem_post(vars->death);
			break ;
		}
	}
	pthread_join(catch, NULL);
	return (0);
}

int	simulation(t_state *vars)
{
	int		i;

	vars->start = get_time();
	vars->death = sem_open("dSem", O_CREAT, 0666, 0);
	vars->forks = sem_open("fSem", O_CREAT, 0666, (unsigned int)vars->num_phils);
	i = 0;
	while(i < vars->num_phils)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] == -1)
			return (1);	//прописать завершение программы
		if (!vars->pid[i])
		{
			//Действия для дочернего процесса
			call_child(vars);
			return (0);		//возможно стоит сделать exit(0);
		}
		i++;
	}
	//действия для родителя
	call_father(vars);
	return (0);
}
