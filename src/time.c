/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:53:12 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/26 00:53:44 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	curr_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * (long long)1000) + (tp.tv_usec / 1000));
}

int	ft_usleep(long long start_time, long long sleeping_time, t_phil *phil)
{
	while ((curr_time() - start_time) <= sleeping_time)
	{
		if (!phil->env->no_deads)
			return (unlock_forks(phil));
		if ((curr_time() - phil->last_eated) >= phil->env->die_time)
			return (kill(phil));
	}
	return (0);
}
