/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:53:07 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/24 22:38:52 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	print_msg(char *msg, t_phil *phil)
{
	long long	starve;

	starve = curr_time() - phil->last_eated;
	if (!phil->env->no_deads)
		return (unlock_forks(phil));
	if (starve >= phil->env->die_time
		|| phil->times_eated == phil->env->max_eat_times)
		return (kill(phil));
	printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time),
		phil->nbr, msg);
	return (0);
}
