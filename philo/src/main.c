/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:30 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/02 14:56:46 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if (get_time() - philo->starving_time >= philo->lifetime)
		philo->dead[0]++;
	pthread_mutex_unlock(philo->mutex);
}

void	eat(t_philo *philo)
{
	int	left_fork;

	check_death(philo);
	if (philo->id == 0)
		left_fork = philo->philo - 1;
	else
		left_fork = philo->id - 1;
	pthread_mutex_lock(&philo->fork[philo->id]);
	print_action(philo, "took a fork.");
	pthread_mutex_lock(&philo->fork[left_fork]);
	philo->starving_time = get_time();
	print_action(philo, "took a fork.");
	print_action(philo, "is eating.");
	ft_sleep(philo->eatime);
	pthread_mutex_unlock(&philo->fork[philo->id]);
	pthread_mutex_unlock(&philo->fork[left_fork]);
	print_action(philo, "is sleeping.");
	ft_sleep(philo->sleeptime);
	print_action(philo, "is thinking.");
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				alive;

	philo = (t_philo *) arg;
	alive = 1;
	if (philo->id % 2)
		ft_sleep(1);
	while (philo->cycle != 0)
	{
		eat(philo);
		philo->cycle--;
	}
	return (NULL);
}

int	init_philo(t_data *data, t_philo *philo)
{
	int	i;
	int	start_time;

	i = 0;
	start_time = get_time();
	while (i < data->philo)
	{
		philo[i].id = i;
		philo[i].starving_time = start_time;
		philo[i].meal_ate = 0;
		philo[i].philo = data->philo;
		philo[i].lifetime = data->lifetime;
		philo[i].eatime = data->eatime;
		philo[i].sleeptime = data->sleeptime;
		philo[i].cycle = data->cycle;
		philo[i].fork = data->fork;
		philo[i].start_time = start_time;
		philo[i].dead = data->dead;
		philo[i].mutex = data->mutex;
		i++;
	}
	return (0);
}

int	thread_philo(t_data *data, t_philo *philo)
{
	int			i;
	int			verif;

	i = 0;
	while (i < data->philo)
	{
		verif = pthread_create(&philo[i].thread, NULL, &routine, philo + i);
		if (verif != 0)
			return (create_thread_error(i));
		i++;
	}
	//check if dead as a value
	i = 0;
	while (i < data->philo)
	{
		verif = pthread_join(philo[i].thread, NULL);
		if (verif != 0)
			return (join_thread_error(i));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int		verif;

	if (ac == 5 || ac == 6)
	{
		verif = init_data(ac, av, &data);
		if (verif == 1)
			return (1);
		verif = init_mutex(&data);
		if (verif == 1)
			return (1);
		philo = malloc(sizeof(t_philo) * data.philo);
		if (!philo)
			return (1);
		init_philo(&data, philo);
		thread_philo(&data, philo);
	}
	else
		philo = NULL;
	ft_free_all(&data, philo);
	return (0);
}
