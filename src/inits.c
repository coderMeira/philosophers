#include "../inc/philosophers.h"

void timezz()
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);

}

static	void *routine(void *arg)
{
	t_phil	*phil;
	t_bool	left;
	t_bool	right;
	t_bool	first_think;

	phil = (t_phil *)arg;
	left = false;
	right = false;
	first_think = true;

	printf("philo %d\n", phil->nbr);
	//while(phil->env->no_deads)
	//{
	//	if (phil->nbr % 2)
	//		usleep(phil->env->eat_time / 2);
	//	if (!(pthread_mutex_lock(&(phil->env->fork[(phil->nbr - 1)]))) && !right)
	//	{
	//		if (!(print_msg("has taken a fork", phil->nbr, currtime())))
	//			die();
	//		right = true;
	//	}
	//	if (!(pthread_mutex_lock(&(phil->env->fork[phil->env->phil->nbr + 1]))) && !left)
	//	{
	//		if(!(print_msg("has taken a fork", phil->nbr, currtime())))
	//			die();
	//		left = true;
	//	}
	//	if (left && right)
	//	{
	//		if (!(print_msg("is eating", phil->nbr, currtime())))
	//			die();
	//		wait(phil->env->eat_time);
	//		pthread_mutex_unlock(&(phil->env->fork[phil->env->phil->nbr - 1]));
	//		pthread_mutex_unlock(&(phil->env->fork[phil->env->phil->nbr + 1]));
	//		if (!(print_msg("is sleeping", phil->nbr, currtime())))
	//			die();
	//		wait(phil->env->sleep_time);
	//		if(!(print_msg("is thinking", phil->nbr, currtime())))
	//			die();
	//		left = false;
	//		right = false;
	//		phil->times_eated++;
	//	}
	//	if (phil->times_eated == 0 && first_think)
	//	{
	//		print_msg("is thinking", phil->nbr, currtime());
	//		first_think = false;
	//	}
	//}
	return (NULL);
}

static int	init_philosopher(t_phil	*phil, t_environment *env, int i)
{
		phil = malloc(sizeof(t_phil));
		if (!phil)
			return (1);
		phil->nbr = i + 1;
		phil->last_eated = 0;
		phil->times_eated = 0;
		phil->env = env;
		return (0);
}

static int	init_threads(t_environment	*env, t_phil **phils)
{
	int	i;

	i = 0;
	while (i < env->nbr_philos)
	{
		if (init_philosopher(phils[i], env, i))
			return (1);
		if (pthread_mutex_init(&(env->fork[i]), NULL))
			return (1);
		if (pthread_create(phils[i]->th, NULL, &routine, phils[i]))
            return (1);
	}
	return (0);
}

int	init(t_environment *env, char **av, t_phil **phils)
{
	env->nbr_philos = ft_atoi(av[0]);
	env->no_deads = true;
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if (av[5])
		env->max_eat_times = ft_atoi(av[5]);
	if (init_threads(env, phils))
		return (1);
	if (env->nbr_philos < 2 || env->die_time < 0 || env->eat_time < 0
		|| env->sleep_time < 0 || env->nbr_philos > 200)
		return (2);
}
