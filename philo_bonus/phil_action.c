/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <niclaw@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:27 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/02 15:52:14 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_fork(t_phil *phil)
{
	if (*(phil->end) == phil->arg.number_of_philosophers)
		return ;
	if (pthread_mutex_lock(&phil->fork) != 0)
		return ;
	else
	{
		if (*(phil->end) == phil->arg.number_of_philosophers)
			return ;
		printf("\033[0;33m%lu [%d] has taken a fork\033[0m\n", \
			time_stamp(phil), phil->id);
	}
	if (*(phil->end) == phil->arg.number_of_philosophers)
		return ;
	if (pthread_mutex_lock(&(phil->r_phil->fork)) != 0)
		return ;
	else
	{
		if (*(phil->end) == phil->arg.number_of_philosophers)
			return ;
		printf("\033[0;33m%lu [%d] has taken a fork\033[0m\n", \
			time_stamp(phil), phil->id);
	}
	return ;
}

void	eat(t_phil *phil)
{
	long			tmp_time;

	phil->time_ate = time_stamp(phil);
	if (*(phil->end) == phil->arg.number_of_philosophers)
		return ;
	printf("\033[0;32m%lu [%d] is eating\033[0m\n", phil->time_ate, phil->id);
	phil->times_eaten++;
	if (phil->arg.times_each_philosopher_must_eat > 0 && \
		phil->times_eaten >= phil->arg.times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&phil->arg.mutex);
		*(phil->end) += 1;
		pthread_mutex_unlock(&phil->arg.mutex);
	}
	tmp_time = phil->time_ate;
	while (time_stamp(phil) <= (tmp_time + phil->arg.time_to_eat) && \
		*(phil->end) != phil->arg.number_of_philosophers)
	{
		usleep(200);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			return ;
	}
	pthread_mutex_unlock(&phil->fork);
	pthread_mutex_unlock(&phil->r_phil->fork);
	return ;
}

void	ph_sleep(t_phil *phil)
{
	long			elasped;
	struct timeval	s_ct;
	long			tmp_time;

	gettimeofday(&s_ct, 0);
	elasped = (s_ct.tv_sec - phil->arg.s_st.tv_sec) * 1000 + \
			(s_ct.tv_usec - phil->arg.s_st.tv_usec) / 1000;
	if (*(phil->end) == phil->arg.number_of_philosophers)
		return ;
	printf("\033[0;36m%lu [%d] is sleeping\033[0m\n", elasped, phil->id);
	if (*(phil->end) == phil->arg.number_of_philosophers)
		return ;
	tmp_time = elasped;
	while (elasped <= (tmp_time + phil->arg.time_to_sleep) && \
		*(phil->end) != phil->arg.number_of_philosophers)
	{
		usleep(200);
		if (*(phil->end) == phil->arg.number_of_philosophers)
			return ;
		gettimeofday(&s_ct, 0);
		elasped = (s_ct.tv_sec - phil->arg.s_st.tv_sec) * 1000 + \
			(s_ct.tv_usec - phil->arg.s_st.tv_usec) / 1000;
	}
	return ;
}

void	think(t_phil *phil)
{
	long			elasped;
	struct timeval	s_ct;

	gettimeofday(&s_ct, 0);
	elasped = (s_ct.tv_sec - phil->arg.s_st.tv_sec) * 1000 + \
			(s_ct.tv_usec - phil->arg.s_st.tv_usec) / 1000;
	if (*(phil->end) == phil->arg.number_of_philosophers)
		return ;
	printf("\033[0;35m%lu [%d] is thinking\033[0m\n", elasped, phil->id);
	return ;
}
