/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:16:22 by hectfern          #+#    #+#             */
/*   Updated: 2022/10/14 09:20:01 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_salt(int id)
{
	if (id % 2 == 0)
		usleep(542);
}

void	dinner_one(t_philo *ph)
{
	pthread_mutex_lock(ph->l_fork);
	print(ph, "has taken a fork");
	pthread_mutex_unlock(ph->l_fork);
	while (!has_dead(ph->table))
		usleep(542);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->n_philos == 1)
	{
		dinner_one(philo);
		return (NULL);
	}
	take_salt(philo->id);
	while (!has_dead(philo->table) && philo->table->num_eats != philo->meals)
	{
		take_fork(philo);
		eat(philo);
		ph_sleep(philo);
		think(philo);
	}
	usleep(1000);
	return (NULL);
}

int	init_thread(t_table *table)
{
	int		i;
	t_philo	*philos;

	if (init_philos(table))
		return (1);
	i = -1;
	philos = table->philos;
	table->tm_start = now();
	pthread_create(&table->monitor, NULL, monitor, table);
	while (++i < table->n_philos)
	{
		pthread_mutex_lock(&table->philos[i].lock);
		philos[i].last_meal = table->tm_start;
		pthread_mutex_unlock(&table->philos[i].lock);
		pthread_create(&philos[i].thread, NULL, dinner, &philos[i]);
	}
	i = -1;
	while (++i < table->n_philos)
		pthread_join(philos[i].thread, NULL);
	pthread_join(table->monitor, NULL);
	return (0);
}
