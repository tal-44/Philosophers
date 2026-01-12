/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanm <juanm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:00:00 by jmiguele          #+#    #+#             */
/*   Updated: 2026/01/12 17:47:13 by juanm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_safe_print(const char *msg, int id, t_constants *consts, int extra,
	const char *color)
{
	long		timestamp;
	int			stopped;

	pthread_mutex_lock(&consts->stop_lock);
	stopped = consts->stopped;
	pthread_mutex_unlock(&consts->stop_lock);
	if (!stopped)
	{
		pthread_mutex_lock(&consts->print_lock);
		timestamp = get_current_time() - consts->start_time;
		if (extra != -1)
			printf("%ld %s[DEBUG]%s Philosopher %d %s%s #%d%s\n", timestamp,
				"\033[0;31m", "\033[0m", id, color, msg, extra, "\033[0m");
		else
			printf("%ld %s[DEBUG]%s Philosopher %d %s%s%s\n", timestamp,
				"\033[0;31m", "\033[0m", id, color, msg, "\033[0m");
		pthread_mutex_unlock(&consts->print_lock);
	}
}

void	debug_take_forks(t_philo *filo, t_constants *consts)
{
	if (filo->id % 2 == 0)
	{
		pthread_mutex_lock(filo->right_fork);
		debug_safe_print("has taken the fork number", filo->id, consts,
			(filo->id % consts->num_philos) + 1, "\033[0;35m");
		pthread_mutex_lock(filo->left_fork);
		debug_safe_print("has taken the fork number", filo->id, consts,
			filo->id, "\033[0;35m");
	}
	else
	{
		pthread_mutex_lock(filo->left_fork);
		debug_safe_print("has taken the fork number", filo->id, consts,
			filo->id, "\033[0;35m");
		pthread_mutex_lock(filo->right_fork);
		debug_safe_print("has taken the fork number", filo->id, consts,
			(filo->id % consts->num_philos) + 1, "\033[0;35m");
	}
}

static int	handle_single_philo_debug(t_philo *filo, t_constants *consts)
{
	debug_safe_print("is thinking", filo->id, consts, -1, "\033[0;33m");
	pthread_mutex_lock(filo->left_fork);
	debug_safe_print("has taken a fork", filo->id, consts, -1, "\033[0;35m");
	my_sleep(consts->time_td);
	pthread_mutex_unlock(filo->left_fork);
	return (0);
}

int	debug_philosopher_eat(t_philo *filo, t_constants *consts)
{
	debug_take_forks(filo, consts);
	if (is_simulation_stopped(consts))
	{
		pthread_mutex_unlock(filo->left_fork);
		pthread_mutex_unlock(filo->right_fork);
		return (1);
	}
	set_last_meal(filo, consts, get_current_time());
	increment_meals(filo, consts);
	debug_safe_print("is eating. Number of meals eaten:", filo->id, consts,
		get_meals_eaten(filo, consts), "\033[0;32m");
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

int	debug_vida_filosofo(t_philo *filo)
{
	t_constants	*consts;

	consts = filo->consts;
	set_last_meal(filo, consts, get_current_time());
	if (consts->num_philos == 1)
		return (handle_single_philo_debug(filo, consts));
	while (!is_simulation_stopped(consts))
	{
		debug_safe_print("is thinking", filo->id, consts, -1, "\033[0;33m");
		if (debug_philosopher_eat(filo, consts))
			break ;
		if (is_simulation_stopped(consts))
			break ;
		debug_safe_print("is sleeping", filo->id, consts, -1, "\033[0;36m");
		my_sleep(consts->time_ts);
	}
	return (0);
}
