/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:05:28 by hectfern          #+#    #+#             */
/*   Updated: 2022/10/13 16:16:07 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
	t_mutex			lock;
	t_mutex			meal;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int			n_philos;
	int			tm_sleep;
	int			num_eats;
	int			time_eat;
	int			time_die;
	int			has_dead;
	long		tm_start;
	t_mutex		*forks;
	t_mutex		print;
	t_mutex		dead;
	t_mutex		wait;
	t_philo		*philos;
	pthread_t	monitor;
}	t_table;

int		ft_isdigit(int c);
int		ft_atoi(const char	*str);
long	ft_atol(const char	*str);

int		init_mutex(t_table *table);
int		init_philos(t_table *table);
int		init_thread(t_table *table);
int		init_args(int argc, char **argv, t_table *table);

long	now(void);
void	burn(t_table *t);
void	take_salt(int id);
int		has_dead(t_table *t);
void	set_last_meal(t_philo *ph);
void	print(t_philo *ph, char *msg);

void	*monitor(void *arg);

void	eat(t_philo *ph);
void	think(t_philo *ph);
void	ph_sleep(t_philo *ph);
void	take_fork(t_philo *ph);

#endif