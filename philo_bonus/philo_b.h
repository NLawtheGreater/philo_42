/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:39 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/18 16:11:38 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

//define MACRO
# define DONE 2
# define FAILED 4
# define DEAD 5

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
	sem_t			*forks;
	pid_t			*pid;
	pthread_t		man;
	t_arg			arg;
}					t_phil;

void	run_philo_one(t_arg arg);
int		create_phil(t_phil *phil, t_arg arg);
void	routine(t_phil *phil);
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
void	philo_child(t_phil* phil);

#endif