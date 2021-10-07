
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef	enum	s_bool
{
	false,
	true
}				t_bool;

typedef	struct	s_env
{
	int				nbr_philos;
	t_bool			no_deads;
	int				start_time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat_times;
	pthread_mutex_t	fork[200];
}				t_environment;

typedef	struct	s_phil
{
	int				nbr;
	int				last_eated;
	int				times_eated;
	t_environment	*env;
	pthread_t		th;
}				t_phil;

//LIBFT
int		ft_strlen(char *str);
void	terminate(char *error);
int		ft_atoi(const char *str);
t_bool	not_int(char *s);

//INITS
int		init(t_environment *env, char **av, t_phil **phils);

#endif
