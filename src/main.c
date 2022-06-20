/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:39:55 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 21:39:44 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_getinfo(t_data *data, int argc, char **argv)
{
	data->nphilo = 0;
	if (ft_atoi(argv[1]) <= 0)
		return (printf("Error: Invalid amount of philosophers\n"));
	data->nphilo = ft_atoi(argv[1]);
	if (ft_atoi(argv[2]) < 0)
		return (printf("Error: Invalid time to die\n"));
	data->time_die = ft_atoi(argv[2]);
	if (ft_atoi(argv[3]) < 0)
		return (printf("Error: Invalid time to eat\n"));
	data->time_eat = ft_atoi(argv[3]);
	if (ft_atoi(argv[4]) < 0)
		return (printf("Error: Invalid time to sleep\n"));
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (printf("Error: Must eat at least once\n"));
		data->must_eat = ft_atoi(argv[5]);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"));
	data = malloc(sizeof(t_data));
	data->must_eat = 0;
	if (ft_getinfo(data, argc, argv))
	{
		free(data);
		return (2);
	}
	ft_start(data);
	ft_end(data);
	return (0);
}
