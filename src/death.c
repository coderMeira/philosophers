#include "../inc/philosophers.h"

int	kill(t_phil *phil)
{
	pthread_mutex_lock(&phil->env->die);
	if (phil->env->no_deads)
	{
		phil->env->no_deads = false;
		printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time), phil->nbr, "died");
	}
	if (phil->right_hand)
		pthread_mutex_unlock(phil->right_fork);
	if(phil->left_hand)
		pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(&phil->env->die);
	return (1);
}
