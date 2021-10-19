/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:30:07 by jlong             #+#    #+#             */
/*   Updated: 2021/10/19 15:39:57 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_bit = 64;

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	nb;

	nb = n;
	if (nb == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-nb, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		ft_putchar_fd((nb + '0'), fd);
}

void	worked(int signum)
{
	static int	nbr;
	char		c;

	if (signum == SIGUSR1)
	{
		nbr = nbr + g_bit;
		g_bit = g_bit / 2;
	}
	else if (signum == SIGUSR2)
	{
		g_bit = g_bit / 2;
	}
	if (g_bit == 0)
	{
		g_bit = 64;
		c = nbr;
		write(1, &c, 1);
		nbr = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	pid = getpid();
	(void)argv;
	if (argc < 1)
		exit(EXIT_FAILURE);
	write (1, "PID : ", 7);
	ft_putnbr_fd(pid, 1);
	write (1, "\n", 1);
	signal(SIGUSR1, worked);
	signal(SIGUSR2, worked);
	while (1)
		pause();
	return (0);
}
