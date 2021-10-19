/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:00:32 by jlong             #+#    #+#             */
/*   Updated: 2021/10/19 15:39:58 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <sys/types.h>
#include <signal.h>

typedef struct s_strct
{
	int		i_size;
	pid_t	pid;
	int		size;
	int		bit;
}				t_strct;

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
		res = (res * 10) + str[i++] - '0';
	res = sign * res;
	return (res);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	check_string(char **av, t_strct bit)
{
	int	res;
	int	n;
	int	j;

	j = -1;
	while (++j <= bit.size)
	{
		n = (int)av[2][j];
		if (j == bit.size)
			n = 10;
		bit.i_size = 64;
		while (bit.i_size > 0)
		{
			res = n / bit.i_size;
			if (res == 0)
				kill(bit.pid, SIGUSR2);
			else if (res >= 1)
			{
				kill(bit.pid, SIGUSR1);
				n = n - bit.i_size;
			}
			bit.i_size = bit.i_size / 2;
			usleep(50);
		}
	}
}

void	error(int argc, char **av)
{
	int	j;
	int	n;

	j = -1;
	if (argc != 3)
		exit(EXIT_FAILURE);
	if (av[2][0] == '\0')
		exit(EXIT_FAILURE);
	while (av[1][++j])
	{
		n = (int)av[1][j];
		if (n < 48 || n > 57)
		{
			exit(EXIT_FAILURE);
		}
	}
	j = -1;
	while (av[2][++j])
		if (av[2][j] < 0 && av[2][j] > 127)
			exit(EXIT_FAILURE);
}

int	main(int argc, char **av)
{
	static t_strct	bit;

	error(argc, av);
	bit.pid = ft_atoi(av[1]);
	bit.size = ft_strlen(av[2]);
	bit.i_size = 0;
	check_string(av, bit);
	return (0);
}
