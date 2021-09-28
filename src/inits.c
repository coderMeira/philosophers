#include "../inc/philosophers.h"

static	t_bool init_philosophers(t_environment	*env)
{
	int	i;

	i = 0;
	while (i < env->nbr_philos)
	{
		env->phil[i].nbr = i;
		if (pthread_create(env->phil[i].th, NULL, &routine, NULL))
            return (false);

}

int	init(t_environment *env, char **av)
{
	env->nbr_philos = ft_atoi(av[0]);
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if (av[5])
		env->max_eat_times = ft_atoi(av[5]);
	if (!(init_philosophers(env)))
		return (0);
	if (env->nbr_philos < 2 || env->die_time < 0 || env->eat_time < 0
		|| env->sleep_time < 0 || env->nbr_philos > 200)
		return (-1);
	return (1);
}
