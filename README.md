*This project has been created as part of the 42 curriculum by jmiguele.*

# Philosophers

## Description

The #Philosophers# project is a concurrency exercise with the following requeriments:

 - Philosophers sit in a circle around a table with spaghetti, each numbered from 1 to N, where N wraps back to 1.
 - Each philosopher alternates between **eating**, **thinking**, and **sleeping** (only one activity at a time).
 - There are as many forks as philosophers; a philosopher must hold both adjacent forks to eat.
 - After eating, a philosopher puts the forks back and sleeps; after sleeping, they think again.
 - Philosophers don't communicate and don't know if another is about to die.
 - Every philosopher must eat and should never starve.
 - The simulation stops when a philosopher dies of starvation.

### Key Features

- One thread per philosopher, running concurrently.
- Mutex-protected forks to prevent data races.
- Dedicated mutexes for per-philosopher data and printing, guaranteeing clean log output.
- Precise timing using `gettimeofday` and a custom `my_sleep` helper.
- Graceful handling of edge cases (e.g., a single philosopher).

## Instructions

### Prerequisites

- A Unix-like operating system (Linux / macOS).
- `cc` (or any C compiler) with support for `-pthread`.
- `make`.

### Compilation

```bash
make        # Compiles the project
make clean  # Removes object files
make fclean # Removes object files and the executable
make re     # Full recompile
```

### Execution

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table. |
| `time_to_die` (ms) | Time in milliseconds a philosopher can survive without eating. |
| `time_to_eat` (ms) | Time in milliseconds it takes for a philosopher to eat. |
| `time_to_sleep` (ms) | Time in milliseconds a philosopher spends sleeping. |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops when every philosopher has eaten at least this many times. |

### Usage Examples

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Same as above, but each philosopher must eat at least 7 times
./philo 5 800 200 200 7

# Single philosopher (will die after time_to_die)
./philo 1 800 200 200
```

### Log Format

Each state change is printed as:

```
<timestamp_in_ms> <philosopher_id> <action>
```

Where `<action>` is one of: `is thinking`, `has taken a fork`, `is eating`, `is sleeping`, or `died`.

## Resources

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads (pthreads) — man7.org](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [pthread_mutex_lock — man7.org](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [Understand Philosophers — 42 Cursus Guide](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers/understand-philosophers)

### AI Usage

AI was used exclusively for gathering general information about threads and mutexes, and for identifying bugs during development. No AI-generated code was incorporated into the project.