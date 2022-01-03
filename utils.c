/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:38:06 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/03 17:30:19 by aarnell          ###   ########.fr       */
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

void my_usleep(int mlsec)
{
	long i;

	i = (long)mlsec * 1000;
	while (i > 0)
	{
		if(i >= 100000)
			usleep(100000);
		else
			usleep((int)i);
		i -= 100000;
	}
}

/*
static void	ft_putnbr_fd(long n, int fd)
{
	char c;

	if (n >= 10)
		ft_putnbr_fd((n / 10), fd);
	c = (int)n % 10 + 48;
	write(fd, &c, 1);
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

void putstate_1st_fd(long cur_tv, t_philo *ph, char *str)
{
	if(!ph->vars->death)
	{
		ft_putnbr_fd(cur_tv, 1);
		write(1, " ", 1);
		ft_putnbr_fd((long)ph->id, 1);
		write(1, str, ft_strlen(str));
	}
}
*/
