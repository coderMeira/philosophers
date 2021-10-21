/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:53:07 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/21 17:39:47 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	print_msg(char *msg, t_phil *phil)
{
	long long	starve;

	if (!phil->last_eated)
		starve = curr_time() - phil->env->start_time;
	else
		starve = curr_time() - phil->last_eated;
	//printf("phil %d starve = %lld\n", phil->nbr, starve);
	if (!phil->env->no_deads)
		return (1);
	if (starve > phil->env->die_time)
		return (kill(phil));
	if(phil->times_eated == phil->env->max_eat_times)
	{
		if (phil->right_hand)
			pthread_mutex_unlock(phil->right_fork);
		if(phil->left_hand)
			pthread_mutex_unlock(phil->left_fork);
		return (1);
	}
	printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time), phil->nbr, msg);
	return (0);
}
