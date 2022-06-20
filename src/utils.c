/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:57:07 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 21:28:05 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(const char *nptr)
{
	long	nbr;
	int		sign;

	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	sign = 1;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			sign = sign * (-1);
		nptr++;
	}
	nbr = 0;
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
	}
	nbr = nbr * sign;
	return (nbr);
}

unsigned long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_log(t_philo *philo, char *str)
{
	unsigned long long	mstime;

	pthread_mutex_lock(&philo->data->print);
	mstime = ft_time() - philo->data->created;
	pthread_mutex_lock(&philo->data->death);
	if (!philo->data->dead && (philo->data->must_eat <= 0
			|| philo->ate < philo->data->must_eat))
		printf("%lld %d %s\n", mstime, (philo->n) + 1, str);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
}
