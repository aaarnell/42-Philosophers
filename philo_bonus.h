/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:10:47 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/09 18:16:48 by aarnell          ###   ########.fr       */
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

typedef struct s_state	t_state;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	//pthread_t		*thread;
	//pthread_mutex_t	*left_fork;
	//pthread_mutex_t	*right_fork;
	//pthread_mutex_t	*death_lock;
	long			last_eat;
	int				eat_cnt;
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
	//t_philo			**philos;
	pid_t			*pid;
	int				death;
}	t_state;

int		error(char *message);
int		clear_mem(t_state *vars);
int		short_atoi(const char *str);
void	my_usleep(long finish);
long	get_time(void);
int		init_state_strct(t_state *vars, int *argc, char **argv);
int		init_philosophers(t_state *vars);
void	think_eat(t_philo *ph);
void	sleeping(t_philo *ph);
int		simulation(t_state *vars);

#endif
