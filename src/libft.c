#include "../inc/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

void	terminate(char *error)
{
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	exit(1);
}

static t_bool	stuff(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f' || c == '+')
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	int		signal;
	int		result;
	char	*p;

	p = (char *)str;
	signal = 1;
	result = 0;
	while (stuff(*p))
		p++;
	if (*p == '-')
	{
		p++;
		signal = -1;
	}
	while (*p > 47 && *p < 58)
	{
		result = result * 10 + *p - 48;
		p++;
	}
	return (result * signal);
}
