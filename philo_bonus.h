/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:10:47 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/13 19:17:27 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>	//для создания и работы с тредами
# include <sys/time.h>	//для получения текущего времени и работы с временем
# include <limits.h>
# include <stdio.h>		//для printf
# include <stdlib.h>	//для malloc
# include <errno.h>		//проверка ошибок разблокировки мютекс
# include <unistd.h>	//для usleep
# include <fcntl.h>		//для констант O_ во втором арг. sem_open
# include <semaphore.h>
# include <signal.h>	//для kill()

typedef struct s_state
{
	int		num_phils;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		cnt_must_eat;
	long	start;
	int		dth;
	pid_t	*pid;
	sem_t	*death;
	sem_t	*forks;
	int		ph_id;
	long	last_eat;
	int		eat_cnt;
}	t_state;

int		error(char *message);
int		clear_mem(t_state *vars);
int		short_atoi(const char *str);
void	my_usleep(long finish);
long	get_time(void);
int		init_state_strct(t_state *vars, int *argc, char **argv);
int		init_philosophers(t_state *vars);
void	think_eat(t_state *vars);
void	sleeping(t_state *vars);
int		simulation(t_state *vars);

#endif
