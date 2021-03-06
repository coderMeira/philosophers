/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:30:47 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/26 17:16:02 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum s_bool
{
	false,
	true
}				t_bool;

typedef struct s_phil
{
	int						nbr;
	t_bool					left_hand;
	t_bool					right_hand;
	long long				last_eated;
	int						times_eated;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	struct s_environment	*env;
	pthread_t				th;
}				t_phil;

typedef struct s_environment
{
	int				nbr_philos;
	t_bool			no_deads;
	long long		start_time;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	int				max_eat_times;
	t_phil			phil[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	die;
	pthread_mutex_t	print;
}				t_environment;

//LIBFT
int			ft_strlen(char *str);
void		terminate(char *error);
int			ft_atoi(const char *str);
t_bool		not_int(char *s);

//INITS
int			init(t_environment *env, char **av);

//PRINTS
int			print_msg(char *msg, t_phil *phil);

//TIME
long long	curr_time(void);
long long	time_diff(long long start_time, long long end_time);
int			ft_usleep(long long start_time, long long sleeping_time,
				t_phil *phil);

//DEATH
int			kill(t_phil *phil);
int			unlock_forks(t_phil *phil);
int			he_is_starving(t_phil *phil);

//ROUTINE OPERATIONS
void		*routine(void *arg);

#endif
