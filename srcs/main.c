/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <niclaw@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:22:31 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/02 15:48:09 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_phil	*phil;

	if (argc == 5)
		arg.times_each_philosopher_must_eat = -1;
	else if (argc == 6)
		arg.times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		return (0);
	arg.number_of_philosophers = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	if (arg.number_of_philosophers == 1)
		run_philo_one (arg);
	else
	{
		phil = malloc (sizeof(t_phil) * (arg.number_of_philosophers));
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
	if (pthread_create(&phil->man, NULL, &manager, phil) != 0)
	{
		printf("pthread create error");
		return ;
	}
	return ;
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *) arg;
	if (!((phil->id) % 2))
		usleep(600);
	while (*(phil->end) != phil->arg.number_of_philosophers)
	{
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		else
			ph_fork (phil);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		else
			eat (phil);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		else
			ph_sleep (phil);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			break ;
		else
			think (phil);
	}
	pthread_mutex_unlock(&phil->fork);
	pthread_mutex_unlock(&phil->r_phil->fork);
	pthread_mutex_destroy(&(phil->fork));
	return (NULL);
}
/*void *time(void *arg)
{
	t_phil
	phil ()
	struct timeval s_st;
	gettimeofday(&s_st, 0);
	eat()
}
*/

void	wait_phil(t_phil *phil)
{
	int	i;

	i = 0;
	while (i < phil->arg.number_of_philosophers)
	{
		pthread_join((phil + i)->ph, NULL);
		i++;
	}
	pthread_join(phil->man, NULL);
	return ;
}
