#include "../inc/philosophers.h"

int	print_msg(char *msg, t_phil *phil)
{
	long long	starve;

	starve = phil->last_eated - phil->env->start_time;
	if (!phil->env->no_deads)
		return (1);
	if (starve > phil->env->die_time)
	{
		phil->env->no_deads = false;
		if (phil->right)
			pthread_mutex_unlock(phil->right_fork);
		if(phil->left)
			pthread_mutex_unlock(phil->left_fork);
		printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time), phil->nbr, "died");
		return (1);
	}
	if(phil->times_eated == phil->env->max_eat_times)
	{
		if (phil->right)
			pthread_mutex_unlock(phil->right_fork);
		if(phil->left)
			pthread_mutex_unlock(phil->left_fork);
		return (1);
	}
	printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time), phil->nbr, msg);
	return (0);
}
