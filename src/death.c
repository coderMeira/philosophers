/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:40:14 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/26 17:16:01 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	unlock_forks(t_phil *phil)
{
	if (phil->right_hand)
		pthread_mutex_unlock(phil->right_fork);
	if (phil->left_hand)
		pthread_mutex_unlock(phil->left_fork);
	phil->left_hand = false;
	phil->right_hand = false;
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

static int	check_starve(t_bool *left, t_bool *right, t_phil *phil)
{
	while (*(left) || *(right))
	{
		if (starve(phil))
			return (1);
	}
	return (0);
}

int	he_is_starving(t_phil *phil)
{
	t_bool	*left_of_right;
	t_bool	*right_of_left;

	if (phil->nbr == phil->env->nbr_philos)
	{
		left_of_right = &(phil->env->phil[phil->nbr - 2].left_hand);
		right_of_left = &(phil->env->phil[0].right_hand);
	}
	else if (phil->nbr == 1)
	{
		left_of_right = &(phil->env->phil[phil->env->nbr_philos - 1].left_hand);
		right_of_left = &(phil->env->phil[1].right_hand);
	}
	else
	{
		left_of_right = &(phil->env->phil[phil->nbr - 2].left_hand);
		right_of_left = &(phil->env->phil[phil->nbr].right_hand);
	}
	return (check_starve(left_of_right, right_of_left, phil));
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
