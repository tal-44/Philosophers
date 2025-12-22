/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanm <juanm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:31:36 by jmiguele          #+#    #+#             */
/*   Updated: 2025/12/22 20:17:48 by juanm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_meal(t_philo *philo, t_constants *consts)
{
	long	result;

	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	result = philo->last_meal_time;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
	return (result);
}

void	set_last_meal(t_philo *philo, t_constants *consts, long time)
{
	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
}

int	get_meals_eaten(t_philo *philo, t_constants *consts)
{
	int	result;

	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	result = philo->meals_eaten;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
	return (result);
}

void	increment_meals(t_philo *philo, t_constants *consts)
{
	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	philo->meals_eaten++;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
}

void	take_forks(t_philo *filo, t_constants *consts)
{
	if (filo->id % 2 == 0)
	{
		pthread_mutex_lock(filo->right_fork);
		safe_print("has taken a fork", filo->id, consts);
		pthread_mutex_lock(filo->left_fork);
		safe_print("has taken a fork", filo->id, consts);
	}
	else
	{
		pthread_mutex_lock(filo->left_fork);
		safe_print("has taken a fork", filo->id, consts);
		pthread_mutex_lock(filo->right_fork);
		safe_print("has taken a fork", filo->id, consts);
	}
}