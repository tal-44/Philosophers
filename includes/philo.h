

#ifndef PHILO_H
# define PHILO_H



# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_constants
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*data_locks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	int				simulation_stopped;
	long			start_time;
}	t_constants;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time;
	int				meals_eaten;
	int				has_finished;
	t_constants		*consts;
}	t_philosopher;

long			get_current_time(void);
int				ft_atoi(const char *str);
int				cast_args(int argc, char **argv, t_constants *constants);
int				init_all(t_constants *constants);
void			kill_all(t_philosopher **philosophers, t_constants *consts);
void			my_sleep(long milliseconds);
long			get_last_meal(t_philosopher *philo, t_constants *consts);
void			set_last_meal(t_philosopher *philo, t_constants *consts, long time);
int				get_meals_eaten(t_philosopher *philo, t_constants *consts);
void			increment_meals(t_philosopher *philo, t_constants *consts);
int				get_has_finished(t_philosopher *philo, t_constants *consts);
void			set_has_finished(t_philosopher *philo, t_constants *consts, int value);
void			safe_print(const char *msg, int id, t_constants *consts);
int				is_simulation_stopped(t_constants *consts);
void			stop_simulation(t_constants *consts);
void			cleanup_all(t_philosopher **philosophers, t_constants *consts);

#endif