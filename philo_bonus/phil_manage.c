/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:39 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/17 16:17:17 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *) arg;
	while (phil->times_eaten != phil->arg.times_each_philosopher_must_eat)
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
			//phil->end = phil->arg.number_of_philosophers;
			if (sem_wait(phil->dead))
				exit(DONE);
			sem_wait(phil->write);
			printf("%lu [%d] died\n", elasped, phil->id);
			return (1);
		}
	return (0);
}
