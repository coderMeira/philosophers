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

// int	grab_forks(t_phil *phil)
// {
// 	t_bool			right_phil;
// 	t_bool			left_phil;

// 	right_phil = phil->env->phil[phil->nbr - 1].right;
// 	left_phil = phil->env->phil[phil->nbr + 1].left;
// 	if (!right_phil && !phil->right && !(pthread_mutex_lock(phil->right_fork)))
// 	{
// 		if(print_msg("has taken a fork", phil))
// 			return (1);
// 		phil->right = true;
// 	}
// 	if (!left_phil && !phil->left && !(pthread_mutex_lock(phil->left_fork)))
// 	{
// 		if(print_msg("has taken a fork", phil))
// 			return (1);
// 		phil->left = true;
// 	}
// 	return (0);
// }
