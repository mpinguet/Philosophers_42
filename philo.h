/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinguet <mpinguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:18:19 by mpinguet          #+#    #+#             */
/*   Updated: 2025/06/26 15:20:06 by mpinguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_program	t_prog;

typedef struct s_philo
{
	int				nbr_meal;
	int				death_philo;
	int				id;
	long			time_last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_prog			*prog;
}	t_philo;

typedef struct s_program
{
	int				count;
	int				death;
	int				nb_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	protect_death;
	pthread_mutex_t	protect_count;
	long			start_time;
	long			nbr_repas;
	t_philo			*philos;

}	t_prog;

int		ft_atoi(char *str);
int		eat_function(t_philo *philo);
int		sleep_function(t_philo *philo);
int		think_function(t_philo *philo);
int		number_meals_filled(t_philo *philo);
int		time_sleep(t_philo *philo);
int		protect_death_philo(t_philo *philo);
int		error_eat(t_philo *philo);
int		check_time_eat(t_philo *philo);
int		error_management(int argc, char **argv, t_prog *prog);
void	try_catch_fork(t_philo *philo);
void	time_start_prog(t_prog *prog);
void	wait_thread(t_prog *prog);
void	init_fork(t_prog *prog);
void	destroy_fork(t_prog *prog);
void	free_fork(t_philo *philo);
void	init_prog(t_prog *prog, char **argv);
int		one_philo(t_prog *prog, char **argv);
void	manage_fork(t_philo *philo, int left_fork, int right_fork);
void	manage_fork2(t_philo *philo, int left_fork, int right_fork);
long	actual_time(t_prog *prog);
long	actual_time_2(void);

#endif
