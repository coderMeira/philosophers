#include "../inc/philosophers.h"

long long	curr_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * (long long)1000) + (tp.tv_usec / 1000));
}

long long	time_diff(long long start_time, long long end_time)
{
	long long	start_time_ms;
	long long	end_time_ms;

	start_time_ms = start_time * 1000 + (start_time / 1000);
	end_time_ms = end_time * 1000 + (end_time / 1000);
	return (end_time_ms - start_time_ms);
}
