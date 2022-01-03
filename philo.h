/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:10:47 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/03 17:23:53 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	//для создания и работы с тредами
# include <sys/time.h>	//для получения текущего времени и работы с временем
# include <limits.h>
# include <stdio.h>		//для printf
# include <stdlib.h>	//для malloc
# include <errno.h>		//проверка ошибок разблокировки мютекс
# include <unistd.h>	//для usleep

typedef struct s_state t_state;
/*
typedef struct s_fork
{
	pthread_mutex_t	*fork;
	int	is_block;
}	t_fork
*/
typedef struct s_philo
{
	int				id;
	pthread_t		*thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	long			last_eat;
	t_state			*vars;
}	t_philo;

typedef struct s_state
{
	int				num_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				cnt_must_eat;
	long			start;
	//pthread_mutex_t	**forks;
	t_philo			**philos;
	//pthread_t		**threads;
	//pthread_t		death_catcher;
	int				death;
}	t_state;

int		short_atoi(const char *str);
void	my_usleep(int mlsec);
long	get_time(void);
void	init_state_strct(t_state *vars, int *argc, char **argv);
void	init_philosophers(t_state *vars);
//void	death_catcher(t_state *vars);
//void	*death_catcher(void *vars);
//void	putstate_1st_fd(long cur_tv, t_philo *ph, char *str);
void	simulation(t_state *vars);

#endif
