/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanm <juanm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:05:28 by jmiguele          #+#    #+#             */
/*   Updated: 2026/01/05 15:36:10 by juanm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_philo *philo, t_constants *consts)
{
	long	last_meal;
	long	timestamp;

	if (consts->num_meals != -1 && get_meals_eaten(philo,
			consts) >= consts->num_meals)
		return (0);
	last_meal = get_last_meal(philo, consts);
	if (last_meal + consts->time_td < get_current_time())
	{
		pthread_mutex_lock(&consts->print_lock);
		timestamp = get_current_time() - consts->start_time;
		printf("%ld %d died\n", timestamp, philo->id);
		pthread_mutex_unlock(&consts->print_lock);
		stop_simulation(consts);
		return (1);
	}
	return (0);
}

int	count_finished_philosophers(t_philo **philosophers, t_constants *consts)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (i < consts->num_philos)
	{
		if (consts->num_meals != -1 && get_meals_eaten(philosophers[i],
				consts) >= consts->num_meals)
			done++;
		i++;
	}
	return (done);
}

void	check_finish(t_philo **philosophers, t_constants *consts)
{
	int	i;
	int	done;

	while (!is_simulation_stopped(consts))
	{
		done = count_finished_philosophers(philosophers, consts);
		if (consts->num_meals != -1 && done == consts->num_philos)
		{
			pthread_mutex_lock(&consts->print_lock);
			printf("All philosophers have finished their meals\n");
			pthread_mutex_unlock(&consts->print_lock);
			stop_simulation(consts);
			return ;
		}
		i = 0;
		while (i < consts->num_philos)
		{
			if (check_philosopher_death(philosophers[i], consts))
				return ;
			i++;
		}
		usleep(100);
	}
}
