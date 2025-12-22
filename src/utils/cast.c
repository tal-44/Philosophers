/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:23:42 by jmiguele          #+#    #+#             */
/*   Updated: 2025/12/22 13:23:42 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int cast_args(int argc, char **argv, t_constants *constants)
{
	int	i;

	constants->num_philos = ft_atoi(argv[1]);
	constants->time_td = ft_atoi(argv[2]);
	constants->time_te = ft_atoi(argv[3]);
	constants->time_ts = ft_atoi(argv[4]);
	if (argc == 6)
		constants->num_meals = ft_atoi(argv[5]);
	else
		constants->num_meals = -1;
	if (constants->num_philos <= 0 || constants->time_td < 0 ||
		constants->time_te < 0 || constants->time_ts < 0 ||
		(argc == 6 && constants->num_meals <= 0))
		return (0);
	constants->forks = malloc(sizeof(pthread_mutex_t) * constants->num_philos);
	if (!constants->forks)
		return (0);
	constants->data_locks = malloc(sizeof(pthread_mutex_t)
			* constants->num_philos);
	if (!constants->data_locks)
	{
		free(constants->forks);
		return (0);
	}
	i = 0;
	while (i < constants->num_philos)
	{
		pthread_mutex_init(&constants->forks[i], NULL);
		pthread_mutex_init(&constants->data_locks[i], NULL);
		i++;
	}
	pthread_mutex_init(&constants->print_lock, NULL);
	pthread_mutex_init(&constants->stop_lock, NULL);
	constants->stopped = 0;
	return (1);
}
