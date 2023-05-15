/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <nicklaw@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:46 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/15 22:01:33 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_philo_one(t_arg arg)
{
	printf("0 [%d] has taken a fork\n", 1);
	usleep(arg.time_to_die * 1000);
	printf("%ld [%d] died\n", arg.time_to_die, 1);
	return ;
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
		if (str[start] < '0' && str[start] > '9')
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
