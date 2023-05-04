/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <niclaw@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:21:46 by niclaw            #+#    #+#             */
/*   Updated: 2023/05/02 15:48:35 by niclaw           ###   ########.fr       */
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
	while (str[start] >= '0' && str[start] <= '9')
	{
		sigma = (str[start] - '0') + (sigma * 10);
		start++;
	}
	return (sigma);
}

int	ft_atoi(char *str)
{
	return (rec_atoi(str, 0));
}
