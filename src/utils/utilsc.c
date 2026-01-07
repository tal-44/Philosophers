/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:32:25 by jmiguele          #+#    #+#             */
/*   Updated: 2026/01/07 13:36:45 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_stopped(t_constants *consts)
{
	int	result;

	pthread_mutex_lock(&consts->stop_lock);
	result = consts->stopped;
	pthread_mutex_unlock(&consts->stop_lock);
	return (result);
}

void	stop_simulation(t_constants *consts)
{
	pthread_mutex_lock(&consts->stop_lock);
	consts->stopped = 1;
	pthread_mutex_unlock(&consts->stop_lock);
}
