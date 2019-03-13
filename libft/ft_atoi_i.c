#include "libft.h"

char		ft_atoi_ci(char *str, int *i)
{
	int sign;
	char nbr;

	nbr = 0;
	sign = 1;
	while (ft_isspace(str[*i]))
		*i = *i + 1;
	if (str[*i] == '-')
		sign = -1;
	while (str[*i] == '0')
		*i = *i + 1;
	if (str[*i] == '-' || str[*i] == '+')
		*i = *i + 1;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		nbr = nbr * 10 + str[*i] - '0';
		*i = *i + 1;
	}
	return (nbr * sign);
}
