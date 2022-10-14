/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:43:24 by hectfern          #+#    #+#             */
/*   Updated: 2022/10/13 15:49:32 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digits(char *argv)
{
	int	i;

	if (ft_atol(argv) <= 0)
	{
		printf("The argument must be greater than zero\n");
		return (1);
	}
	i = 0;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
		{
			printf("The argument %s must only contain numbers.\n", argv);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_args(int argc, char **argv, t_table *table)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s ", argv[0]);
		printf("<number_of_philosophers> <time_to_die> <time_to_eat> "
			"<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
		if (check_digits(argv[i]))
			return (1);
	table->has_dead = 0;
	table->num_eats = -42;
	table->n_philos = ft_atoi(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->tm_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_eats = ft_atoi(argv[5]);
	table->forks = malloc(table->n_philos * sizeof(t_mutex));
	table->philos = malloc(table->n_philos * sizeof(t_philo));
	return (0);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			printf("Error: mutex init\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&table->print, NULL)
		|| pthread_mutex_init(&table->dead, NULL)
		|| pthread_mutex_init(&table->wait, NULL))
	{
		printf("Error: mutex init\n");
		return (1);
	}
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	if (!table->philos || !table->forks)
	{
		printf("Malloc error\n");
		return (1);
	}
	if (init_mutex(table))
		return (1);
	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i].id = i;
		table->philos[i].meals = 0;
		table->philos[i].last_meal = now();
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].r_fork = &table->forks[(i + 1) % table->n_philos];
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].lock, NULL);
		pthread_mutex_init(&table->philos[i].meal, NULL);
	}
	return (0);
}
