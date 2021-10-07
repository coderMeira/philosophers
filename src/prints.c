#include "../inc/philosophers.h"

int	print_msg(char *msg, t_phil *phil)
{
	int	time;

	//time = timefunc();
	if (!phil->env->no_deads || phil->last_eated > phil->env->die_time)
		return (1);
	printf("%d %s\n", phil->nbr, msg);
	return (0);
}
