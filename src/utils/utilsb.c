/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:31:36 by jmiguele          #+#    #+#             */
/*   Updated: 2025/12/22 13:31:48 by jmiguele         ###   ########.fr       */
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
