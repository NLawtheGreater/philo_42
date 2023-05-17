/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:22:31 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/17 16:57:45 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_phil	phil;

	if (!philo_check (argc, argv))
	{
		printf("you dumb\n");
		return (0);
	}
	arg = philo_set(argc, argv);
	//check one philo
	//if (arg.number_of_philosophers == 1)
	//	run_philo_one (arg);
	//else
	//{
		
		create_phil (&phil, arg);
		wait_phil(&phil);
		sem_close(phil.dead);
		sem_close(phil.write);
		sem_close(phil.forks);
	//}
	return (0);
}

static void	init_phil(t_phil *phil, t_arg arg)
{
	gettimeofday(&arg.s_st, 0);
	phil->arg = arg;
	phil->times_eaten = 0;
	phil->time_ate = 0;
	return ;
}

void	create_phil(t_phil *phil, t_arg arg)
{
	int	i;
	
	sem_unlink ("dead");
	sem_unlink ("write");
	sem_unlink ("fork");
	phil->dead = sem_open("dead", O_CREAT, 0660, 1);
	if (phil->dead == SEM_FAILED)
		return ;
	phil->write = sem_open("write", O_CREAT, 0660, 1);
	if (phil->write == SEM_FAILED)
		return ;
	i = 0;
	while (i < arg.number_of_philosophers)
	{
		//many fork naming problem
		phil->forks = sem_open("fork", O_CREAT, 0660, arg.number_of_philosophers);
		if (phil->forks == SEM_FAILED)
			return ;
	}	
	
	init_phil(phil, arg);
	pid_t pid;
	while (i < arg.number_of_philosophers)
	{
		phil->id = (i + 1);
		pid = fork();
		if (pid < 0)
			return ;
		else if (pid == 0)
			philo_child(phil);
		i++;
	}
	return ;
}
void philo_child(t_phil* phil)
{
	create_phil_man(phil);
	routine(phil);
}

static void	clear(t_phil *phil)
{
	pthread_mutex_unlock(&phil->fork);
	pthread_mutex_unlock(&phil->r_phil->fork);
	pthread_mutex_destroy(&(phil->fork));
	return ;
}

void	routine(t_phil *phil)
{
	//No need for delay
	//if (!(phil->id % 2))
	//	usleep(600);
	while (1)
	{
		ph_fork (phil);
		eat (phil);
		ph_sleep (phil);
		think (phil);
	}
	return (NULL);
}
