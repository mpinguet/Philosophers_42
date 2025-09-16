/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:12:46 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/26 15:22:54 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_prog(t_prog *prog, char **argv)
{
	prog->nb_philo = ft_atoi(argv[1]);
	prog->time_to_death = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->death = 0;
	prog->count = 0;
}

void	manage_fork(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->prog->fork[left_fork]);
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
		printf("%ld %d has taken a fork\n", actual_time(philo->prog),
			philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
	pthread_mutex_lock(&philo->prog->fork[right_fork]);
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
		printf("%ld %d has taken a fork\n", actual_time(philo->prog),
			philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
}

void	manage_fork2(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_lock(&philo->prog->fork[right_fork]);
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
		printf("%ld %d has taken a fork\n", actual_time(philo->prog),
			philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
	pthread_mutex_lock(&philo->prog->fork[left_fork]);
	pthread_mutex_lock(&philo->prog->protect_death);
	if (philo->prog->death == 0)
		printf("%ld %d has taken a fork\n", actual_time(philo->prog),
			philo->id);
	pthread_mutex_unlock(&philo->prog->protect_death);
}

int	number_meals_filled(t_philo *philo)
{
	if (philo->prog->nbr_repas != 0
		&& philo->nbr_meal == philo->prog->nbr_repas)
	{
		free_fork(philo);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	return (0);
}

int	time_sleep(t_philo *philo)
{
	long	start;

	start = actual_time_2();
	while (actual_time_2() - start < philo->prog->time_to_eat)
	{
		if (check_time_eat(philo) == 1)
		{
			free_fork(philo);
			return (1);
		}
		usleep(500);
	}
	return (0);
}
