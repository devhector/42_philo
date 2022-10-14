/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:07:43 by hectfern          #+#    #+#             */
/*   Updated: 2022/10/13 16:18:12 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *ph)
{
	if (!has_dead(ph->table))
	{
		if (ph->id % 2)
		{
			pthread_mutex_lock(ph->l_fork);
			print(ph, "has taken a fork");
			pthread_mutex_lock(ph->r_fork);
			print(ph, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(ph->r_fork);
			print(ph, "has taken a fork");
			pthread_mutex_lock(ph->l_fork);
			print(ph, "has taken a fork");
		}
	}
}

void	set_meal(t_philo *ph)
{
	pthread_mutex_lock(&ph->meal);
	ph->meals++;
	pthread_mutex_unlock(&ph->meal);
}

void	eat(t_philo *ph)
{
	set_meal(ph);
	print(ph, "is eating");
	set_last_meal(ph);
	usleep(ph->table->time_eat * 1000);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
}

void	think(t_philo *ph)
{
	t_table	*t;
	long	t_eat;
	long	t_die;
	long	t_sleep;

	t = ph->table;
	t_eat = t->time_eat;
	t_die = t->time_die;
	t_sleep = t->tm_sleep;
	if (!has_dead(ph->table))
	{
		print(ph, "is thinking");
		if (t_die - (t_eat + t_sleep) > 10)
			usleep(((t_die - (t_eat + t_sleep)) * 1000) - (10 * 1000));
	}
}

void	ph_sleep(t_philo *ph)
{
	if (!has_dead(ph->table))
	{
		print(ph, "is sleeping");
		usleep(ph->table->tm_sleep * 1000);
	}
}
