
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef	enum	s_bool
{
	false,
	true
}				t_bool;

typedef	struct	s_phil
{
	int			nbr;
	pthread_t	th;
}				t_phil;


typedef	struct	s_env
{
	int		nbr_philos;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_times;
	t_phil	phil[200];
}				t_environment;

//LIBFT
int		ft_strlen(char *str);
void	terminate(char *error);
int		ft_atoi(const char *str);

//INITS
int		init(t_environment *env, char **av);

#endif
