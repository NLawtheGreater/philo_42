/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:22:31 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/18 17:51:58 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static int	sem_sem(t_phil *phil);

int	sem_fail(t_phil *phil)
{
	if (phil->dead != SEM_FAILED)
		sem_close(phil->dead);
	if (phil->write != SEM_FAILED)
		sem_close(phil->write);
	if (phil->forks != SEM_FAILED)
		sem_close(phil->forks);
	if (phil->table != SEM_FAILED)
		sem_close(phil->forks);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_phil	phil;

	if (!philo_check (argc, argv))
	{
		printf("you dumb\n");
		return (0);
	}
	phil.arg = philo_set(argc, argv);
	if (sem_sem(&phil) == EXIT_FAILURE)
	{
		sem_fail(&phil);
		return (EXIT_FAILURE);
	}
	if (create_phil (&phil) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_phil(&phil);
	clear(&phil);
	return (0);
}

static int	sem_sem(t_phil *phil)
{
	sem_unlink ("dead");
	sem_unlink ("write");
	sem_unlink ("forks");
	sem_unlink ("table");
	phil->dead = sem_open("dead", O_CREAT, 0644, 1);
	phil->write = sem_open("write", O_CREAT, 0644, 1);
	phil->table = sem_open("table", O_CREAT, 0644, 1);
	phil->forks = sem_open("forks", O_CREAT, 0644, \
		phil->arg.number_of_philosophers);
	if (phil->forks == SEM_FAILED || phil->write == SEM_FAILED || \
		phil->dead == SEM_FAILED || phil->table == SEM_FAILED)
		return (sem_fail(phil));
	return (EXIT_SUCCESS);
}

int	create_phil(t_phil *phil)
{
	int	i;

	i = 0;
	gettimeofday(&phil->arg.s_st, 0);
	phil->times_eaten = 0;
	phil->time_ate = 0;
	phil->pid = malloc((phil->arg.number_of_philosophers * sizeof(pid_t *)));
	if (!phil->pid)
		return (clear(phil));
	while (i < phil->arg.number_of_philosophers)
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
