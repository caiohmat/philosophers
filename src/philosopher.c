/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:01:44 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 21:34:26 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_eat(t_philo *philo)
{
	if (philo->n % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork[philo->n]);
		ft_log(philo, "has taken a fork");
	}
	if (philo->data->nphilo == 1)
	{
		usleep(philo->data->time_die);
		pthread_mutex_unlock(&philo->data->fork[philo->n]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->fork[philo->rfork]);
	ft_log(philo, "has taken a fork");
	if (philo->n % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->fork[philo->n]);
		ft_log(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->data->status[philo->n]);
	ft_log(philo, "is eating");
	philo->lastmeal = ft_time();
	philo->ate++;
	pthread_mutex_unlock(&philo->data->status[philo->n]);
	return (0);
}

static void	ft_sleep(t_philo *philo)
{
	unsigned long long	sleeptime;

	ft_log(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->fork[philo->n]);
	pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
	sleeptime = ft_time();
	usleep(philo->data->time_sleep * 1000 - 14000);
	while (ft_time() - sleeptime < philo->data->time_sleep)
		;
	ft_log(philo, "is thinking");
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->n % 2 == 0)
		usleep(100);
	while ((philo->data->must_eat <= 0
			|| philo->ate < philo->data->must_eat))
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death);
		if (ft_eat(philo))
			return (NULL);
		usleep(philo->data->time_eat * 1000 - 14000);
		while (ft_time() - philo->lastmeal < philo->data->time_eat)
			;
		ft_sleep(philo);
	}
	return (NULL);
}
