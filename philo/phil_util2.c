/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:01:16 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/16 15:18:19 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_check(int arg_num, char **arg)
{
	int	tmp;
	int	x;

	if (!(arg_num == 5 || arg_num == 6))
		return (0);
	x = 1;
	tmp = ft_atoi(arg[1]);
	if (tmp < 1 || tmp > 250)
		return (0);
	x = 2;
	while (x <= 5)
	{
		if (arg_num == 6 && x == 5)
		{
			tmp = ft_atoi(arg[x]);
			if (tmp < 1)
				return (0);
		}
		if (x == 5)
			break ;
		tmp = ft_atoi(arg[x++]);
		if (tmp < 60)
			return (0);
	}
	return (1);
}

void	create_phil_man(t_phil *phil)
{
	if (pthread_create(&phil->man, NULL, &manager, phil) != 0)
	{
		printf("pthread create error");
		return ;
	}
	return ;
}

t_arg	philo_set(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 5)
		arg.times_each_philosopher_must_eat = -1;
	else if (argc == 6)
		arg.times_each_philosopher_must_eat = ft_atoi(argv[5]);
	arg.number_of_philosophers = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	return (arg);
}
