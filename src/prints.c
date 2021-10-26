/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:53:07 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/26 17:34:42 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	print_msg(char *msg, t_phil *phil)
{
	long long	starve;

	pthread_mutex_lock(&phil->env->print);
	starve = curr_time() - phil->last_eated;
	if (!phil->env->no_deads)
	{
		pthread_mutex_unlock(&phil->env->print);
		return (unlock_forks(phil));
	}
	if (starve >= phil->env->die_time)
	{
		pthread_mutex_unlock(&phil->env->print);
		return (kill(phil));
	}
	printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time),
		phil->nbr, msg);
	pthread_mutex_unlock(&phil->env->print);
	return (0);
}
