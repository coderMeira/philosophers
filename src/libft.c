#include "../inc/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return i;
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

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static	long long	ft_stoi(char *str)
{
	long long	signal;
	long long	result;
	char		*p;

	p = (char *)str;
	signal = 1;
	result = 0;
	while (*p == ' ' || *p == '\t' || *p == '\n'
		|| *p == '\r' || *p == '\v' || *p == '\f')
		p++;
	if (*p == '+')
		p++;
	else if (*p == '-')
	{
		p++;
		signal = -1;
	}
	while (*p > 47 && *p < 58)
		result = result * 10 + *p++ - 48;
	result = result * signal;
	return (result);
}

t_bool	not_int(char *s)
{
	int			i;
	int			len;
	char		*tmp;
	long long	check_size;
	long long	max_int;

	i = 0;
	len = ft_strlen(s);
	tmp = s;
	check_size = ft_stoi(tmp);
	max_int = 2147483647;
	if (check_size > max_int)
		return (true);
	if (s[i] == '-' && ft_isdigit(s[1]))
		i++;
	while (i < len)
	{
		if (!(ft_isdigit(s[i++])))
			return (true);
	}
	return (false);
}

