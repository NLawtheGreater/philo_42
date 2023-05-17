/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:39 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/17 12:12:07 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *) arg;
	while (*(phil->end) != phil->arg.number_of_philosophers)
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
			phil->end = phil->arg.number_of_philosophers;
			pthread_mutex_unlock(&phil->arg.mutex);
			printf("%lu [%d] died\n", elasped, (phil + i)->id);
			pthread_mutex_unlock(&((phil + i)->fork));
			pthread_mutex_unlock(&((phil + i)->r_phil->fork));
			return (1);
		}
	}
	return (0);
}
