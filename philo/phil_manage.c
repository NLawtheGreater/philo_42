/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <niclaw@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:39 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/02 15:48:47 by niclaw           ###   ########.fr       */
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
	int				i;

	gettimeofday (&s_ct, 0);
	elasped = (s_ct.tv_sec - phil->arg.s_st.tv_sec) * 1000 + \
		(s_ct.tv_usec - phil->arg.s_st.tv_usec) / 1000;
	i = 0;
	while (i < phil->arg.number_of_philosophers)
	{
		if ((elasped - (phil + i)->time_ate) >= phil->arg.time_to_die)
		{
			pthread_mutex_lock(&phil->arg.mutex);
			*(phil->end) = phil->arg.number_of_philosophers;
			pthread_mutex_unlock(&phil->arg.mutex);
			printf("%lu [%d] died\n", elasped, (phil + i)->id);
			pthread_mutex_unlock(&((phil + i)->fork));
			pthread_mutex_unlock(&((phil + i)->r_phil->fork));
			return (1);
		}
	i++;
	}
	return (0);
}
