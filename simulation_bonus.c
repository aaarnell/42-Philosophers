/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:28:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/13 21:18:26 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	catch(t_state *vars)
{
	vars->dth++;
	sem_post(vars->death);
	printf("%ld %d die\n", (get_time() - vars->start), \
		vars->ph_id);
	exit(0);
}

static void	*death_catcher(void *vars)
{
	t_state	*tmp;

	tmp = (t_state *)vars;
	if (!tmp->ph_id)
	{
		sem_wait(tmp->death);
		tmp->dth = 1;
	}
	else
	{
		while (1)
		{
			if (tmp->last_eat && \
				tmp->last_eat + tmp->time_to_die < get_time())
				catch(tmp);
			if (tmp->cnt_must_eat >= 0 && \
				tmp->eat_cnt >= tmp->cnt_must_eat)
				exit(0);
			usleep(500);
		}
	}
	return (NULL);
}

static int	call_child(t_state *vars)
{
	int			i;
	int			ret;
	pthread_t	catch;

	vars->last_eat = vars->start;
	ret = pthread_create(&catch, NULL, death_catcher, vars);
	if (ret)
		return (1);
	i = 0;
	while (!vars->dth)
	{
		if (!i && ((vars->ph_id == 1 && (vars->num_phils % 2)) \
			|| !(vars->ph_id % 2)))
			;
		else
			think_eat(vars);
		sleeping(vars);
		i++;
	}
	pthread_join(catch, NULL);
	return (0);
}

static int	call_father(t_state *vars)
{
	pid_t		pid;
	int			ret;
	pthread_t	catch;

	ret = pthread_create(&catch, NULL, death_catcher, vars);
	if (ret)
		return (1);
	while (!vars->dth)
	{
		pid = waitpid(-1, NULL, WUNTRACED);
		if (pid > 0)
			vars->eat_cnt++;
		if (vars->eat_cnt == vars->num_phils)
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
	int	i;

	vars->start = get_time();
	i = 0;
	while (i < vars->num_phils)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] == -1)
			return (1);
		if (!vars->pid[i])
		{
			vars->ph_id = i + 1;
			call_child(vars);
			return (0);
		}
		i++;
	}
	call_father(vars);
	i = 0;
	while (i < vars->num_phils)
		kill(vars->pid[i++], SIGTERM);
	return (0);
}
