/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:17:58 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/27 13:12:49 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*execute_thread(void *arg)
{
	t_philo	*philo;
	t_prog	*prog;

	philo = (t_philo *)arg;
	prog = philo->prog;
	while (1)
	{
		pthread_mutex_lock(&philo->prog->protect_death);
		if (prog->death == 1)
		{
			pthread_mutex_unlock(&philo->prog->protect_death);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->prog->protect_death);
		if (eat_function(philo) == 1)
			return (NULL);
		if (sleep_function(philo) == 1)
			return (NULL);
		if (think_function(philo) == 1)
			return (NULL);
		if (check_time_eat(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	one_philo(t_prog *prog, char **argv)
{
	int		time_to_death;
	int		nb_philo;

	time_to_death = ft_atoi(argv[2]);
	nb_philo = ft_atoi(argv[1]);
	if (nb_philo == 1)
	{
		printf("%ld 1 has taken a fork\n", actual_time(prog));
		usleep(time_to_death * 1000);
		printf("\033[0;31m%ld 1 died\n\033[0m", actual_time(prog));
		free(prog);
		return (1);
	}
	return (0);
}

void	init_philo(char **argv, t_prog *prog)
{
	int	i;

	init_prog(prog, argv);
	prog->fork = malloc(prog->nb_philo * sizeof(pthread_mutex_t));
	prog->philos = malloc((prog->nb_philo) * sizeof(t_philo));
	if (!prog->philos)
		return ;
	i = 0;
	pthread_mutex_init(&prog->protect_death, NULL);
	pthread_mutex_init(&prog->protect_count, NULL);
	init_fork(prog);
	while (i < prog->nb_philo)
	{
		prog->philos[i].time_last_meal = 0;
		prog->philos[i].nbr_meal = 0;
		prog->philos[i].prog = prog;
		prog->philos[i].id = i + 1;
		prog->philos[i].death_philo = 0;
		pthread_mutex_init(&prog->philos[i].meal_mutex, NULL);
		pthread_create(&prog->philos[i].thread, NULL, execute_thread,
			&prog->philos[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	memset(prog, 0, sizeof(t_prog));
	if (error_management(argc, argv, prog) == 1)
	{
		free(prog);
		return (1);
	}
	time_start_prog(prog);
	if (one_philo(prog, argv) == 1)
		return (0);
	init_philo(argv, prog);
	wait_thread(prog);
	destroy_fork(prog);
	return (0);
}
