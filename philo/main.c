/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:22:31 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/15 22:45:22 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_phil	*phil;

	if (!philo_check (argc, argv))
	{
		printf("you dumb\n");
		return (0);
	}
	arg = philo_set(argc, argv);
	if (arg.number_of_philosophers == 1)
		run_philo_one (arg);
	else
	{
		phil = malloc (sizeof(t_phil) * (arg.number_of_philosophers));
		if (!phil)
			return (0);
		create_phil (phil, arg);
		wait_phil(phil);
		free(phil->end);
		free(phil);
	}
	return (0);
}

static void	init_phil(t_phil *phil, t_arg arg, int i)
{
	pthread_mutex_init(&(phil[i].fork), NULL);
	phil[i].id = i + 1;
	phil[i].arg = arg;
	phil[i].r_phil = phil + ((i + 1) % (arg.number_of_philosophers));
	phil[i].times_eaten = 0;
	phil[i].time_ate = 0;
	return ;
}

void	create_phil(t_phil *phil, t_arg arg)
{
	int	i;
	int	*end;

	gettimeofday(&arg.s_st, 0);
	i = 0;
	end = malloc(sizeof(int *));
	if (!end)
		return ;
	*end = 0;
	pthread_mutex_init(&(arg.mutex), NULL);
	while (i < arg.number_of_philosophers)
	{
		init_phil(phil, arg, i);
		phil[i].end = end;
		if (pthread_create(&phil[i].ph, NULL, &routine, (phil + i)) != 0)
		{
			printf("pthread create error");
			return ;
		}
		i++;
	}
	create_phil_man(phil);
	return ;
}

static void	clear(t_phil *phil)
{
	pthread_mutex_unlock(&phil->fork);
	pthread_mutex_unlock(&phil->r_phil->fork);
	pthread_mutex_destroy(&(phil->fork));
	return ;
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *) arg;
	if (!(phil->id % 2))
		usleep(600);
	while (*(phil->end) != phil->arg.number_of_philosophers)
	{
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		ph_fork (phil);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		eat (phil);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		ph_sleep (phil);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		think (phil);
	}
	clear (phil);
	return (NULL);
}
