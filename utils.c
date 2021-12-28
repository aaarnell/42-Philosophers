/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:38:06 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/28 20:32:32 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
	long res;
	struct timeval tmp;

	gettimeofday(&tmp, NULL);	//Прописать завершение программы при ошибке (вывод ошибки, очистка, выход)
	res = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	return (res);
}

int	short_atoi(const char *str)
{
	unsigned long	r;
	int i;

	r = 0;
	i = 0;
	while (*str && i < 10)
	{
		if (*str < '0' || *str > '9')
			return (-1); 				//прописать возврат ошибки, т.к. аргумент не явлется числом
		r = (r * 10) + ((unsigned long)*str - 48);
		str++;
		i++;
	}
	if (r > INT_MAX)
		return (-1);
	return ((int)r);
}

void	*death_catcher(void *vars)
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
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
