#include "../inc/philosophers.h"

int	grab_forks(t_phil *phil)
{
	t_bool			right_phil;
	t_bool			left_phil;

	right_phil = phil->env->phil[phil->nbr - 1].right;
	left_phil = phil->env->phil[phil->nbr + 1].left;
	if (!right_phil && !phil->right && !(pthread_mutex_lock(phil->right_fork)))
	{
		if(print_msg("has taken a fork", phil))
			return (1);
		phil->right = true;
	}
	if (!left_phil && !phil->left && !(pthread_mutex_lock(phil->left_fork)))
	{
		if(print_msg("has taken a fork", phil))
			return (1);
		phil->left = true;
	}
	return (0);
}
