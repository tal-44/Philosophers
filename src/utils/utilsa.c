/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:32:18 by jmiguele          #+#    #+#             */
/*   Updated: 2026/01/07 13:32:18 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

void	my_sleep(long ms)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < ms)
		usleep(100);
}

void	set_has_finished(t_philo *philo, t_constants *consts, int value)
{
	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	philo->has_finished = value;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
}

void	safe_print(const char *msg, int id, t_constants *consts)
{
	long	timestamp;
	int		stopped;

	pthread_mutex_lock(&consts->stop_lock);
	stopped = consts->stopped;
	pthread_mutex_unlock(&consts->stop_lock);
	if (!stopped)
	{
		pthread_mutex_lock(&consts->print_lock);
		timestamp = get_current_time() - consts->start_time;
		printf("%ld %d %s\n", timestamp, id, msg);
		pthread_mutex_unlock(&consts->print_lock);
	}
}
