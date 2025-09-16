/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:12:14 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/26 14:31:00 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_catch_fork(t_philo *philo)
{
	int	right_fork;
	int	left_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->prog->nb_philo;
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->nbr_meal == 0 && philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 != 0)
		manage_fork(philo, left_fork, right_fork);
	else
		manage_fork2(philo, left_fork, right_fork);
}

int	check_time_eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->nbr_meal == 0)
	{
		if ((actual_time_2()
				- philo->prog->start_time) >= philo->prog->time_to_death)
		{
			if (protect_death_philo(philo) == 1)
				i = 1;
		}
	}
	else
	{
		if (actual_time_2()
			- philo->time_last_meal >= philo->prog->time_to_death)
		{
			if (protect_death_philo(philo) == 1)
				i = 1;
		}
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (i);
}

int	eat_function(t_philo *philo)
{
	try_catch_fork(philo);
	if (error_eat(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
		printf("\033[0;32m%ld %d is eating\033[0m\n", actual_time(philo->prog),
			philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
	if (time_sleep(philo) == 1)
		return (1);
	if (check_time_eat(philo) == 1)
	{
		free_fork(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->nbr_meal += 1;
	philo->time_last_meal = actual_time_2();
	if (number_meals_filled(philo) == 1)
		return (1);
	pthread_mutex_unlock(&philo->meal_mutex);
	free_fork(philo);
	return (0);
}

int	sleep_function(t_philo *philo)
{
	long	start;

	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 1)
	{
		pthread_mutex_unlock(&philo->prog->protect_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->prog->protect_death);
	start = actual_time_2();
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
		printf("\033[0;34m%ld %d is sleeping\033[0m\n",
			actual_time(philo->prog), philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
	while (actual_time_2() - start < philo->prog->time_to_sleep)
	{
		if (check_time_eat(philo) == 1)
			return (1);
		usleep(500);
	}
	return (0);
}

int	think_function(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 1)
	{
		pthread_mutex_unlock(&philo->prog->protect_death);
		return (1);
	}
	if (philo->prog->death == 0)
		printf("\033[0;33m%ld %d is thinking\033[0m\n",
			actual_time(philo->prog), philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
	usleep(1000);
	if (check_time_eat(philo) == 1)
		return (1);
	return (0);
}
