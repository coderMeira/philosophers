/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 22:54:52 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/25 21:17:35 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	he_died_sleeping(t_phil *phil)
{
	if (print_msg("is sleeping", phil))
		return (1);
	if (ft_usleep(curr_time(), phil->env->sleep_time, phil))
		return (1);
	return (0);
}

static int	he_died_eating(t_phil *phil)
{
	phil->left_hand = true;
	phil->right_hand = true;
	if (print_msg("has taken a fork", phil))
		return (1);
	if (print_msg("has taken a fork", phil))
		return (1);
	phil->times_eated++;
	phil->last_eated = curr_time();
	if (print_msg("is eating", phil))
		return (1);
	if (ft_usleep(curr_time(), phil->env->eat_time, phil))
		return (1);
	phil->left_hand = false;
	phil->right_hand = false;
	return (0);
}

void	*routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	phil->last_eated = phil->env->start_time;
	if (phil->nbr % 2)
		usleep(phil->env->eat_time * 1000);
	while (phil->env->no_deads)
	{
		if (he_is_starving(phil))
			return (NULL);
		pthread_mutex_lock(phil->left_fork);
		pthread_mutex_lock(phil->right_fork);
		if (he_died_eating(phil))
			return (NULL);
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
		if (he_died_sleeping(phil))
			return (NULL);
		if (print_msg("is thinking", phil))
			return (NULL);
	}
	return (NULL);
}
