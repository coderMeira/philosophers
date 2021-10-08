#include "../inc/philosophers.h"

int	print_msg(char *msg, t_phil *phil)
{
	long long	starve;

	starve = phil->last_eated - phil->env->start_time;
	if (!phil->env->no_deads || starve > phil->env->die_time)
	{
		phil->env->no_deads = false;
		printf("%lli\t%d %s\n",curr_time(), phil->nbr, "died");
		return (1);
	}
	printf("%lli\t%d %s\n", (curr_time() - phil->env->start_time), phil->nbr, msg);
	return (0);
}
