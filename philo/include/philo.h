/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:19:50 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/02 13:29:15 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				philo;
	int				lifetime;
	int				eatime;
	int				sleeptime;
	int				cycle;
	int				*dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				philo;
	int				start_time;
	int				lifetime;
	int				eatime;
	int				sleeptime;
	int				meal_ate;
	int				cycle;
	int				starving_time;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutex;
}	t_philo;

//parsing :
int		init_data(int ac, char **av, t_data *data);
int		init_mutex(t_data *data);

//utils :
int		ft_check_atoi(char *str);
void	ft_free_all(t_data *data, t_philo *philo);
int		get_time(void);
void	ft_sleep(int time);
void	print_action(t_philo *philo, char *s);

//error :

int		negative_error(char *str);
int		max_value_error(char *str);
int		create_thread_error(int i);
int		join_thread_error(int i);
int		thread_malloc_error(t_data *data);

#endif