/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_manage_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:39 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/18 17:33:43 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	*manager(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *) arg;
	while (phil->times_eaten < phil->arg.times_each_philosopher_must_eat || \
		phil->arg.times_each_philosopher_must_eat == -1)
	{
		if (die (phil))
			return (0);
	}
	return (0);
}

int	die(t_phil *phil)
{
	long			elasped;
	struct timeval	s_ct;

	gettimeofday (&s_ct, 0);
	elasped = (s_ct.tv_sec - phil->arg.s_st.tv_sec) * 1000 + \
		(s_ct.tv_usec - phil->arg.s_st.tv_usec) / 1000;
	if ((elasped - phil->time_ate) >= phil->arg.time_to_die)
	{
		if (sem_wait(phil->dead))
			exit(DEAD);
		sem_wait(phil->write);
		printf("%lu [%d] died\n", elasped, phil->id);
		exit(DEAD);
	}
	return (0);
}

void	create_phil_man(t_phil *phil)
{
	if (pthread_create(&phil->man, NULL, &manager, phil) != 0)
	{
		printf("pthread create error");
		return ;
	}
	pthread_detach(phil->man);
	return ;
}
