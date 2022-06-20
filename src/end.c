/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:51:23 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 19:48:23 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_end(t_data *data)
{
	int	counter;

	counter = 0;
	while (counter < data->nphilo)
	{
		pthread_join(data->philo[counter].thread, NULL);
		pthread_join(data->philo[counter].monitor, NULL);
		counter++;
	}
	counter = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	while (counter < data->nphilo)
	{
		pthread_mutex_destroy(&data->fork[counter]);
		pthread_mutex_destroy(&data->status[counter]);
		counter++;
	}
	free(data->fork);
	free(data->philo);
	free(data->status);
	free(data);
}
