
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

void	my_sleep(long milliseconds)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < milliseconds)
		usleep(100);
}

long	get_last_meal(t_philosopher *philo, t_constants *consts)
{
	long	result;

	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	result = philo->last_meal_time;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
	return (result);
}

void	set_last_meal(t_philosopher *philo, t_constants *consts, long time)
{
	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
}

int	get_meals_eaten(t_philosopher *philo, t_constants *consts)
{
	int	result;

	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	result = philo->meals_eaten;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
	return (result);
}

void	increment_meals(t_philosopher *philo, t_constants *consts)
{
	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	philo->meals_eaten++;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
}

int	get_has_finished(t_philosopher *philo, t_constants *consts)
{
	int	result;

	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	result = philo->has_finished;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
	return (result);
}

void	set_has_finished(t_philosopher *philo, t_constants *consts, int value)
{
	pthread_mutex_lock(&consts->data_locks[philo->id - 1]);
	philo->has_finished = value;
	pthread_mutex_unlock(&consts->data_locks[philo->id - 1]);
}

void	safe_print(const char *msg, int id, t_constants *consts)
{
	long	timestamp;

	pthread_mutex_lock(&consts->print_lock);
	timestamp = get_current_time() - consts->start_time;
	printf("%ld %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(&consts->print_lock);
}

int	is_simulation_stopped(t_constants *consts)
{
	int	result;

	pthread_mutex_lock(&consts->stop_lock);
	result = consts->simulation_stopped;
	pthread_mutex_unlock(&consts->stop_lock);
	return (result);
}

void	stop_simulation(t_constants *consts)
{
	pthread_mutex_lock(&consts->stop_lock);
	consts->simulation_stopped = 1;
	pthread_mutex_unlock(&consts->stop_lock);
}