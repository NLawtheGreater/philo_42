/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_util_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:46 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/18 17:35:46 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	routine(t_phil *phil)
{
	if (!(phil->id % 2))
		usleep(600);
	create_phil_man(phil);
	while (phil->times_eaten < phil->arg.times_each_philosopher_must_eat || \
		phil->arg.times_each_philosopher_must_eat == -1)
	{
		ph_fork (phil);
		eat (phil);
		ph_sleep (phil);
		think (phil);
	}
	exit(DONE);
}

long	time_stamp(t_phil *phil)
{
	long			elasped;
	struct timeval	s_ct;

	gettimeofday(&s_ct, 0);
	elasped = (s_ct.tv_sec - phil->arg.s_st.tv_sec) * 1000 + \
		(s_ct.tv_usec - phil->arg.s_st.tv_usec) / 1000;
	return (elasped);
}

static int	rec_atoi(char *str, int start)
{
	long long	sigma;

	sigma = 0;
	while (str[start])
	{
		if (str[start] < '0' || str[start] > '9')
			return (-1);
		sigma = (str[start] - '0') + (sigma * 10);
		start++;
	}
	if (sigma > 2147483647)
		return (-1);
	return (sigma);
}

int	ft_atoi(char *str)
{
	return (rec_atoi(str, 0));
}

void	wait_phil(t_phil *phil)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i < phil->arg.number_of_philosophers)
	{
		waitpid(-1, &wstatus, 0);
		if (WEXITSTATUS(wstatus) == DEAD)
		{
			i = 0;
			while (i < phil->arg.number_of_philosophers)
				kill(phil->pid[i++], SIGTERM);
			break ;
		}
		i++;
	}
	return ;
}
