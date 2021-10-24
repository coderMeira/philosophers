/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:40:14 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/24 23:01:02 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	unlock_forks(t_phil *phil)
{
	if (phil->right_hand)
		pthread_mutex_unlock(phil->right_fork);
	if (phil->left_hand)
		pthread_mutex_unlock(phil->left_fork);
	return (1);
}

static int	starve(t_phil *phil)
{
	long long	starve;

	starve = curr_time() - phil->last_eated;
	if (starve > phil->env->die_time)
		return (kill(phil));
	return (0);
}

int	he_is_starving(t_phil *phil)
{
	if (phil->nbr == phil->env->nbr_philos)
	{
		while (phil->env->phil[phil->nbr - 2].left_hand
			|| phil->env->phil[0].right_hand)
		{
			if (starve(phil))
				return (1);
		}
	}
	else
	{
		while (phil->env->phil[phil->nbr - 2].left_hand
			|| phil->env->phil[phil->nbr].right_hand)
		{
			if (starve(phil))
				return (1);
		}
	}
	return (0);
}

int	kill(t_phil *phil)
{
	pthread_mutex_lock(&phil->env->die);
	if (phil->env->no_deads)
	{
		phil->env->no_deads = false;
		printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time),
			phil->nbr, "died");
	}
	unlock_forks(phil);
	pthread_mutex_unlock(&phil->env->die);
	return (1);
}
