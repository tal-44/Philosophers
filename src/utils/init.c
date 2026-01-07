/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:05:28 by jmiguele          #+#    #+#             */
/*   Updated: 2026/01/07 14:18:09 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosopher(t_philo **philos, int i, t_constants *constants,
		long start_time)
{
	philos[i] = malloc(sizeof(t_philo));
	philos[i]->id = i + 1;
	philos[i]->left_fork = &constants->forks[i];
	philos[i]->right_fork = &constants->forks[(i + 1) % constants->num_philos];
	philos[i]->meals_eaten = 0;
	philos[i]->has_finished = 0;
	philos[i]->last_meal_time = start_time;
	philos[i]->consts = constants;
	pthread_create(&philos[i]->thread, NULL, (void *)vida_filosofo,
		(void *)philos[i]);
}

int	init_all(t_constants *constants)
{
	int		i;
	t_philo	**philos;
	long	start_time;

	philos = malloc(sizeof(t_philo *) * constants->num_philos);
	if (!philos)
		return (0);
	start_time = get_current_time();
	constants->start_time = start_time;
	i = 0;
	while (i < constants->num_philos)
	{
		init_philosopher(philos, i, constants, start_time);
		i++;
	}
	check_finish(philos, constants);
	cleanup_all(philos, constants);
	return (1);
}
