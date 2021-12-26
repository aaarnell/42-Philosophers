/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:38:06 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/26 20:46:03 by aarnell          ###   ########.fr       */
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

static int	cng_var(char a, unsigned long *res, int *cnt_sin, int *emp)
{
	if (a >= '0' && a <= '9')
		*res = (*res * 10) + ((unsigned long)a - 48);
	if (a == ' ' || (a >= 9 && a <= 13))
		*emp = *emp + 1;
	if (a == '-')
	{
		*cnt_sin = *cnt_sin + 1;
		return (1);
	}
	if (a == '+')
		*cnt_sin = *cnt_sin + 1;
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	r;
	int				s;
	int				cs;
	int				e;

	r = 0;
	s = 1;
	cs = 0;
	e = 0;
	while (*str)
	{
		if ((*str != ' ' && *str != '-' && *str != '+' && (*str < 9 || *str \
		> 13) && (*str < '0' || *str > '9')) || ((r != 0 || cs != 0) && (*str \
		== ' ' || *str == '-' || *str == '+' || (*str >= 9 && *str <= 13))))
			break ;
		if (cng_var(*str, &r, &cs, &e) == 1)
			s *= (-1);
		str++;
	}
	if (r > LONG_MAX && s > 0)
		r = LONG_MAX;
	if (r - 1 > LONG_MAX && s < 0)
		r = 0;
	return ((int)r * s);
}

static void	*trap(void *ph)
{
	while()
	return (NULL);
}

void	death_catcher(t_state *vars)
{
	int ret;
	pthread_t traps[vars->num_phils];

	while(i < vars->num_phils)
	{
		ret = pthread_create(&traps[i], NULL, trap, vars->philos[i]);
		if (ret)
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		ret = pthtread_detach(traps[i]);
		if (ret)
			return ;		//Прописать завершение программы (вывод ошибки, очистка, выход)
		i++;
	}

}
