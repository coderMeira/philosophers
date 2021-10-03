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
	while(phil->env->no_deads)
	{
		if (phil->nbr % 2)
			waitasec(phil->env->eat_time);
		if (!(pthread_mutex_lock(&(phil->env->fork[(phil->nbr - 1)]))))
		{
			if (!(print_msg("has taken a fork", phil->nbr, currtime())))
				die();
			right = true;
		}
		if (!(pthread_mutex_lock(&(phil->env->fork[phil->env->phil->nbr + 1]))))
		{
			if(!(print_msg("has taken a fork", phil->nbr, currtime())))
				die();
			left = true;
		}
		if (left && right)
		{
			if (!(print_msg("is eating", phil->nbr, currtime())))
				die();
			wait(phil->env->eat_time);
			pthread_mutex_unlock(&(phil->env->fork[phil->env->phil->nbr - 1]));
			pthread_mutex_unlock(&(phil->env->fork[phil->env->phil->nbr + 1]));
			if (!(print_msg("is sleeping", phil->nbr, currtime())))
				die();
			wait(phil->env->sleep_time);
			if(!(print_msg("is thinking", phil->nbr, currtime())))
				die();
			left = false;
			right = false;
			phil->times_eated++;
		}
		if (phil->times_eated == 0 && first_think)
		{
			print_msg("is thinking", phil->nbr, currtime());
			first_think = false;
		}
	}
	return (NULL);
}

static void	init_philosopher(t_phil	*phil, t_environment *env, int i)
{
		phil->nbr = i + 1;
		phil->is_eating = false;
		phil->is_sleeping = false;
		phil->times_eated = 0;
		phil->env = env;
}

static int	init_threads(t_environment	*env)
{
	int	i;

	i = 0;
	while (i < env->nbr_philos)
	{
		init_philosopher(&(env->phil), env, i);
		if (pthread_mutex_init(&(env->fork[i]), NULL))
			return (1);

		if (pthread_create(env->phil[i].th, NULL, &routine, &(env->phil[i])))
            return (1);
	}
	return (0);
}

int	init(t_environment *env, char **av)
{
	env->nbr_philos = ft_atoi(av[0]);
	env->no_deads = true;
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if (av[5])
		env->max_eat_times = ft_atoi(av[5]);
	if (init_threads(env))
		return (1);
	if (env->nbr_philos < 2 || env->die_time < 0 || env->eat_time < 0
		|| env->sleep_time < 0 || env->nbr_philos > 200)
		return (2);
}
