/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:22:31 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/18 16:57:52 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static int sem_fail(t_phil *phil)
{
	if (phil->dead != SEM_FAILED)
		sem_close(phil->dead);
	if (phil->write != SEM_FAILED)
		sem_close(phil->write);
	if (phil->forks != SEM_FAILED)
		sem_close(phil->forks);
	return(EXIT_FAILURE);
}
static int clear(t_phil *phil)
{
	sem_fail(phil);
	free(phil->pid);
	return (EXIT_FAILURE);
}
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
		
	if (create_phil (&phil, arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_phil(&phil);
	clear(&phil);
	//}
	return (0);
}

static int	init_phil(t_phil *phil, t_arg arg)
{
	gettimeofday(&arg.s_st, 0);
	phil->arg = arg;
	phil->times_eaten = 0;
	phil->time_ate = 0;
	phil->pid = malloc((arg.number_of_philosophers * sizeof(pid_t *)));
	if (!phil->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int	create_phil(t_phil *phil, t_arg arg)
{
	int	i;
	
	sem_unlink ("dead");
	sem_unlink ("write");
	sem_unlink ("forks");
	phil->dead = sem_open("dead", O_CREAT, 0644, 1);
	phil->write = sem_open("write", O_CREAT, 0644, 1);
	phil->forks = sem_open("forks", O_CREAT, 0644, arg.number_of_philosophers);
	if (phil->forks == SEM_FAILED || phil->write == SEM_FAILED || phil->dead == SEM_FAILED)
		return (sem_fail(phil));
	i = 0;
	if (init_phil(phil, arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (i < arg.number_of_philosophers)
	{
		phil->id = (i + 1);
		phil->pid[i] = fork();
		if (phil->pid[i] < 0)
			return (clear(phil));
		else if (phil->pid[i] == 0)
			routine(phil);
		i++;
	}
	return (EXIT_SUCCESS);
}
void philo_child(t_phil* phil)
{
	
	routine(phil);
}


void	routine(t_phil *phil)
{
	if (!(phil->id % 2))
		usleep(600);
	create_phil_man(phil);
	while (phil->times_eaten < phil->arg.times_each_philosopher_must_eat || \
		phil->arg.times_each_philosopher_must_eat == -1)
	{
		ph_fork (phil);
		eat (phil);
		ph_sleep (phil);
		think (phil);
	}
	exit(DONE);
}
