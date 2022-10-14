/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:19:11 by hectfern          #+#    #+#             */
/*   Updated: 2022/10/13 16:15:49 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	has_dead(t_table *t)
{
	int	status;

	pthread_mutex_lock(&t->dead);
	status = t->has_dead;
	pthread_mutex_unlock(&t->dead);
	return (status);
}

void	print(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->table->print);
	if (!has_dead(ph->table))
		printf("%5ld %d %s\n", now() - ph->table->tm_start, ph->id + 1, msg);
	pthread_mutex_unlock(&ph->table->print);
}

void	set_last_meal(t_philo *ph)
{
	pthread_mutex_lock(&ph->lock);
	ph->last_meal = now();
	pthread_mutex_unlock(&ph->lock);
}

void	burn(t_table *t)
{
	int		i;

	i = -1;
	usleep(542);
	while (++i < t->n_philos)
	{
		pthread_mutex_destroy(&t->forks[i]);
		pthread_mutex_destroy(&t->philos[i].meal);
		pthread_mutex_destroy(&t->philos[i].lock);
	}
	pthread_mutex_destroy(&t->dead);
	pthread_mutex_destroy(&t->print);
	pthread_mutex_destroy(&t->wait);
	free(t->forks);
	free(t->philos);
}
