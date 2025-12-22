
#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	cleanup_all(t_philosopher **philosophers, t_constants *consts)
{
	int	i;

	i = 0;
	while (i < consts->num_philosophers)
	{
		pthread_join(philosophers[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < consts->num_philosophers)
	{
		pthread_mutex_destroy(&consts->forks[i]);
		pthread_mutex_destroy(&consts->data_locks[i]);
		free(philosophers[i]);
		i++;
	}
	pthread_mutex_destroy(&consts->print_lock);
	pthread_mutex_destroy(&consts->stop_lock);
	free(consts->forks);
	free(consts->data_locks);
	free(philosophers);
}

int	vida_filosofo(t_philosopher *filo)
{
	t_constants	*consts;

	consts = filo->consts;
	set_last_meal(filo, consts, get_current_time());
	if (consts->num_philosophers == 1)
	{
		safe_print("is thinking", filo->id, consts);
		pthread_mutex_lock(filo->left_fork);
		safe_print("has taken a fork", filo->id, consts);
		my_sleep(consts->time_to_die);
		pthread_mutex_unlock(filo->left_fork);
		return (0);
	}
	while (!is_simulation_stopped(consts))
	{
		safe_print("is thinking", filo->id, consts);
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
		if (is_simulation_stopped(consts))
		{
			pthread_mutex_unlock(filo->left_fork);
			pthread_mutex_unlock(filo->right_fork);
			break ;
		}
		set_last_meal(filo, consts, get_current_time());
		increment_meals(filo, consts);
		safe_print("is eating", filo->id, consts);
		my_sleep(consts->time_to_eat);
		pthread_mutex_unlock(filo->left_fork);
		pthread_mutex_unlock(filo->right_fork);
		if (consts->num_meals != -1 && get_meals_eaten(filo, consts) >= consts->num_meals)
		{
			set_has_finished(filo, consts, 1);
			break ;
		}
		if (is_simulation_stopped(consts))
			break ;
		safe_print("is sleeping", filo->id, consts);
		my_sleep(consts->time_to_sleep);
	}
	return (0);
}

void	check_finish(t_philosopher **philosophers, t_constants *consts)
{
	int		i;
	int		done;
	long	last_meal;

	while (!is_simulation_stopped(consts))
	{
		i = 0;
		done = 0;
		while (i < consts->num_philosophers)
		{
			last_meal = get_last_meal(philosophers[i], consts);
			if (last_meal + consts->time_to_die < get_current_time())
			{
				safe_print("died", philosophers[i]->id, consts);
				stop_simulation(consts);
				return ;
			}
			if (consts->num_meals != -1 && get_has_finished(philosophers[i], consts) 
				&& get_meals_eaten(philosophers[i], consts) >= consts->num_meals)
			{
				done++;
			}
			i++;
		}
		if (consts->num_meals != -1 && done == consts->num_philosophers)
		{
			pthread_mutex_lock(&consts->print_lock);
			printf("All philosophers have finished their meals\n");
			pthread_mutex_unlock(&consts->print_lock);
			stop_simulation(consts);
			return ;
		}
		usleep(1000);
	}	
}

int init_all(t_constants *constants)
{
    int				i;
	t_philosopher	**philosophers;
	long			start_time;

	philosophers = malloc(sizeof(t_philosopher *) * constants->num_philosophers);
	if (!philosophers)
		return (0);
	start_time = get_current_time();
	constants->start_time = start_time;
	i = 0;
	while (i < constants->num_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		philosophers[i]->id = i + 1;
		philosophers[i]->left_fork = &constants->forks[i];
		philosophers[i]->right_fork = &constants->forks[(i + 1) % constants->num_philosophers];
		philosophers[i]->meals_eaten = 0;
		philosophers[i]->has_finished = 0;
		philosophers[i]->last_meal_time = start_time;
		philosophers[i]->consts = constants;
		pthread_create(&philosophers[i]->thread, NULL, (void *)vida_filosofo, (void *)philosophers[i]);
		i++;
	}
	check_finish(philosophers, constants);
	cleanup_all(philosophers, constants);
	return (1);
}