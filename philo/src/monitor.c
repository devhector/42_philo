/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:05:19 by hectfern          #+#    #+#             */
/*   Updated: 2022/10/13 15:52:36 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_table *t)
{
	pthread_mutex_lock(&t->dead);
	t->has_dead = 1;
	pthread_mutex_unlock(&t->dead);
}

long	get_last_meal(t_philo *ph)
{
	long	l_meal;

	pthread_mutex_lock(&ph->lock);
	l_meal = ph->last_meal;
	pthread_mutex_unlock(&ph->lock);
	return (l_meal);
}

void	check_death(t_philo *ph)
{
	t_table	*t;
	long	time;

	t = ph->table;
	pthread_mutex_lock(&t->wait);
	time = now() - get_last_meal(ph);
	pthread_mutex_unlock(&t->wait);
	if (time > t->time_die)
	{
		print(ph, "died");
		set_dead(t);
	}
}

int	get_meal(t_philo *ph)
{
	int	meal;

	pthread_mutex_lock(&ph->meal);
	meal = ph->meals;
	pthread_mutex_unlock(&ph->meal);
	return (meal);
}

void	*monitor(void *arg)
{
	int		i;
	t_table	*t;

	i = 0;
	t = arg;
	while (!has_dead(t) && get_meal(&t->philos[i]) != t->num_eats)
	{
		check_death(&t->philos[i]);
		i = (i + 1) % t->n_philos;
		usleep(542);
	}
	return (NULL);
}
