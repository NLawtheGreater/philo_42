/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_action_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:27 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/18 16:49:47 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	ph_fork(t_phil *phil)
{
	if (sem_wait(phil->forks) == -1)
		exit(FAILED);
	if (sem_wait(phil->write) == -1)
		exit(FAILED);
	printf("\033[0;33m%lu [%d] has taken a fork\033[0m\n", \
		time_stamp(phil), phil->id);
	if (sem_post(phil->write) == -1)
		exit(FAILED);
	if (sem_wait(phil->forks) == -1)
		exit(FAILED);
	if (sem_wait(phil->write) == -1)
		exit(FAILED);
	printf("\033[0;33m%lu [%d] has taken a fork\033[0m\n", \
		time_stamp(phil), phil->id);
	if (sem_post(phil->write) == -1)
		exit(FAILED);
	return ;
}

void	eat(t_phil *phil)
{
	long			tmp_time;

	phil->time_ate = time_stamp(phil);
	if (sem_wait(phil->write) == -1)
		exit(FAILED);
	printf("\033[0;32m%lu [%d] is eating\033[0m\n", phil->time_ate, phil->id);
	if (sem_post(phil->write) == -1)
		exit(FAILED);
	phil->times_eaten++;
	if (phil->arg.times_each_philosopher_must_eat > 0 && \
		phil->times_eaten >= phil->arg.times_each_philosopher_must_eat)
		exit(DONE);
	tmp_time = phil->time_ate;
	while (time_stamp(phil) <= (tmp_time + phil->arg.time_to_eat))
		usleep(200);
	if (sem_post(phil->forks) == -1)
		exit(FAILED);
	if (sem_post(phil->forks) == -1)
		exit(FAILED);
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
	if (sem_wait(phil->write) == -1)
		exit(FAILED);
	printf("\033[0;36m%lu [%d] is sleeping\033[0m\n", elasped, phil->id);
	if (sem_post(phil->write) == -1)
		exit(FAILED);
	tmp_time = elasped;
	while (elasped <= (tmp_time + phil->arg.time_to_sleep))
	{
		usleep(200);
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
	if (sem_wait(phil->write) == -1)
		exit(FAILED);
	printf("\033[0;35m%lu [%d] is thinking\033[0m\n", elasped, phil->id);
	if (sem_post(phil->write) == -1)
		exit(FAILED);
	return ;
}
