/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiguele <jmiguele@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:01:18 by jmiguele          #+#    #+#             */
/*   Updated: 2025/12/22 13:01:18 by jmiguele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_constants	constants;

	if (argc == 5 || argc == 6)
	{
		if (cast_args(argc, argv, &constants) == 0)
			return (1);
		if (init_all(&constants) == 0)
			return (1);
	}
	else
	{
		printf("Se esperan los siguientes argumentos:\n\n");
		printf("./philo (numeros de filosofos) (tiempo que se tarda en morir)");
		printf(" tiempo que se tarda en comer) ");
		printf("tiempo que se tarda en dormir)");
		printf(" [numero de veces que cada filosofo debe comer]\n");
		return (1);
	}
	return (0);
}
