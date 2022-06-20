/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:46:50 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 21:37:49 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_dead(t_philo *philo)
{
	if (ft_time() - philo->lastmeal >= philo->data->time_die)
	{
		ft_log(philo, "died");
		pthread_mutex_lock(&philo->data->death);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	return (0);
}

static int	ft_full(t_philo *philo)
{
	if (philo->data->must_eat > 0)
	{
		if (philo->ate >= philo->data->must_eat)
			return (1);
	}
	return (0);
}

void	*ft_status(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->status[philo->n]);
		if (ft_dead(philo) || ft_full(philo))
		{
			pthread_mutex_unlock(&philo->data->status[philo->n]);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->status[philo->n]);
		usleep(10);
	}
	return (NULL);
}
