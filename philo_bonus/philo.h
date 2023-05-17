/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:39 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/17 12:12:13 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>


typedef struct s_arg
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;	
	long			time_to_sleep;
	int				times_each_philosopher_must_eat;
	struct timeval	s_st;
}					t_arg;

typedef struct s_phil
{
	int				id;
	long			times_eaten;
	long			time_ate;
	int				finish;
	int				time_to_think;
	int				end;
	sem_t			*dead;
	sem_t			*write;
	sem_t			**forks;
	pthread_t		man;
	t_arg			arg;
}					t_phil;

void	run_philo_one(t_arg arg);
void	create_phil(t_phil *phil, t_arg arg);
void	*routine(void *arg);
void	ph_fork(t_phil *phil);
void	eat(t_phil *phil);
void	ph_sleep(t_phil *phil);
void	think(t_phil *phil);
void	*manager(void *arg);
int		die(t_phil *phil);
long	time_stamp(t_phil *phil);
void	wait_phil(t_phil *phil);
int		ft_atoi(char *str);
void	create_phil_man(t_phil *phil);
int		philo_check(int arg_num, char **arg);
t_arg	philo_set(int argc, char **argv);

#endif