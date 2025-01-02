
#include "philo.h"

long long	ft_atoll(const char *str)
{
	long long	nb;
	int			i;
	int			sign;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + ((str[i] - '0') * sign);
		i++;
	}
	return (nb);
}
