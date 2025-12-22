/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/12/22 13:05:28 by jmiguele          #+#    #+#             */
/*   Updated: 2025/12/22 13:05:28 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	cleanup_all(t_philo **philos, t_constants *consts)
{
	int i;

	i = 0;
	while (i < consts->num_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < consts->num_philos)
	{
		pthread_mutex_destroy(&consts->forks[i]);
		pthread_mutex_destroy(&consts->data_locks[i]);
		free(philos[i]);
		i++;
	}
	pthread_mutex_destroy(&consts->print_lock);
	pthread_mutex_destroy(&consts->stop_lock);
	free(consts->forks);
	free(consts->data_locks);
	free(philos);
}

int	handle_single_philo(t_philo *filo, t_constants *consts)
{
	safe_print("is thinking", filo->id, consts);
	pthread_mutex_lock(filo->left_fork);
	safe_print("has taken a fork", filo->id, consts);
	my_sleep(consts->time_td);
	pthread_mutex_unlock(filo->left_fork);
	return (0);
}

int	philosopher_eat(t_philo *filo, t_constants *consts)
{
	take_forks(filo, consts);
	if (is_simulation_stopped(consts))
	{
		pthread_mutex_unlock(filo->left_fork);
		pthread_mutex_unlock(filo->right_fork);
		return (1);
	}
	set_last_meal(filo, consts, get_current_time());
	increment_meals(filo, consts);
	safe_print("is eating", filo->id, consts);
	my_sleep(consts->time_te);
	pthread_mutex_unlock(filo->left_fork);
	pthread_mutex_unlock(filo->right_fork);
	if (consts->num_meals != -1 && get_meals_eaten(filo,
			consts) >= consts->num_meals)
	{
		set_has_finished(filo, consts, 1);
		return (1);
	}
	return (0);
}

int	vida_filosofo(t_philo *filo)
{
	t_constants *consts;

	consts = filo->consts;
	set_last_meal(filo, consts, get_current_time());
	if (consts->num_philos == 1)
		return (handle_single_philo(filo, consts));
	while (!is_simulation_stopped(consts))
	{
		safe_print("is thinking", filo->id, consts);
		if (philosopher_eat(filo, consts))
			break ;
		if (is_simulation_stopped(consts))
			break ;
		safe_print("is sleeping", filo->id, consts);
		my_sleep(consts->time_ts);
	}
	return (0);
}
