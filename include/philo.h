/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chideyuk <chideyuk@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:40:24 by chideyuk          #+#    #+#             */
/*   Updated: 2022/05/19 21:35:29 by chideyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct philo
{
	int					n;
	int					ate;
	int					eating;
	int					rfork;
	unsigned long long	lastmeal;
	pthread_t			thread;
	pthread_t			monitor;
	struct s_data		*data;
}					t_philo;

typedef struct s_data
{
	int									nphilo;
	int									dead;
	unsigned long long					created;
	unsigned long long					time_die;
	unsigned long long					time_eat;
	unsigned long long					time_sleep;
	int									must_eat;
	t_philo								*philo;
	pthread_mutex_t						print;
	pthread_mutex_t						death;
	pthread_mutex_t						*status;
	pthread_mutex_t						*fork;
}						t_data;

long				ft_atoi(const char *nptr);
unsigned long long	ft_time(void);
void				ft_log(t_philo *philo, char *str);
void				ft_start(t_data *data);
void				*ft_philo(void *arg);		
void				ft_end(t_data *data);
void				*ft_status(void *arg);

#endif
