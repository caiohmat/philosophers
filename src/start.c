/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:33:48 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 21:40:04 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_alloc(t_data *data)
{
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nphilo);
	data->status = malloc(sizeof(pthread_mutex_t) * data->nphilo);
	data->philo = malloc(sizeof(t_philo) * data->nphilo);
}

static void	ft_assign(t_data *data)
{
	int	counter;

	data->dead = 0;
	counter = 0;
	while (counter < data->nphilo)
	{
		data->philo[counter].ate = 0;
		data->philo[counter].n = counter;
		data->philo[counter].eating = 0;
		data->philo[counter].data = data;
		data->philo[counter].rfork = (counter + 1) % data->nphilo;
		counter++;
	}
}

static void	ft_startmutex(t_data *data)
{
	int	counter;

	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	counter = 0;
	while (counter < data->nphilo)
	{
		pthread_mutex_init(&data->fork[counter], NULL);
		pthread_mutex_init(&data->status[counter], NULL);
		counter++;
	}
}

static void	ft_startthread(t_data *data)
{
	int			counter;

	data->created = ft_time();
	counter = 0;
	while (counter < data->nphilo)
	{
		data->philo[counter].lastmeal = data->created;
		pthread_create(&data->philo[counter].thread, NULL, \
		ft_philo, &data->philo[counter]);
		counter++;
	}
	counter = 0;
	while (counter < data->nphilo)
	{
		pthread_create(&data->philo[counter].monitor, NULL, \
		ft_status, &data->philo[counter]);
		counter++;
	}
}

void	ft_start(t_data *data)
{
	ft_alloc(data);
	ft_assign(data);
	ft_startmutex(data);
	ft_startthread(data);
}
