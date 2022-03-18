/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:47:53 by user42            #+#    #+#             */
/*   Updated: 2022/02/28 21:03:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_var(t_data *d, int i)
{
	d->philo[i].nb_dinner = 0;
	d->philo[i].index = i;
	d->philo[i].last_dinner_time = d->start;
	d->philo[i].mom = d;
	d->philo[i].__finish_routine = 0;
}

void	init_thread(t_data *d)
{
	unsigned int	i;

	d->philo = malloc(sizeof(t_philo) * d->nb_philo);
	if (d->philo == NULL)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&d->msg, NULL)
		|| pthread_mutex_init(&d->died, NULL))
	{
		clean (d);
		exit (EXIT_FAILURE);
	}
	i = -1;
	while (++i < d->nb_philo)
	{
		init_var(d, i);
		if (pthread_mutex_init(&d->philo[i].fork, NULL)
			|| pthread_mutex_init(&d->philo[i].finish_routine, NULL)
			|| pthread_mutex_init(&d->philo[i].check_time, NULL))
			clean(d);
	}
}

int	time_is_over(t_data *d, unsigned int i)
{
	if (d->time_to_die < t_time() - d->philo[i].last_dinner_time)
	{
		pthread_mutex_unlock(&d->philo[i].check_time);
		pthread_mutex_unlock(&d->philo[i].finish_routine);
		msg(d, i, "died");
		d->dead = 1;
		return (1);
	}
	return (0);
}

void	monitoring(t_data *d, unsigned int i)
{
	while (1)
	{
		i = -1;
		d->philo_finish = 0;
		while (++i < d->nb_philo)
		{
			pthread_mutex_lock(&d->philo[i].finish_routine);
			if (!d->philo[i].__finish_routine)
			{
				pthread_mutex_lock(&d->philo[i].check_time);
				if (time_is_over(d, i))
					break ;
				pthread_mutex_unlock(&d->philo[i].check_time);
			}
			else
				d->philo_finish++;
			pthread_mutex_unlock(&d->philo[i].finish_routine);
		}
		if ((d->max_dinner && d->philo_finish == d->nb_philo) || d->dead)
			break ;
		if (d->nb_philo > 10)
			usleep(5000);
	}
}

int	main(int ac, char *av[])
{
	t_data			d;
	unsigned int	i;

	if (ac < 5 || ac > 6)
		error_msg(1, NULL);
	memset(&d, 0, sizeof(t_data));
	check_arg(&d, &av[1], ac - 1);
	init_thread(&d);
	i = -1;
	if (d.nb_philo == 1)
	{
		msg(&d, 0, "has taken a fork");
		while (current_time(&d) < d.time_to_die)
			usleep(1);
		msg(&d, 0, "died");
	}
	else
		while (++i < d.nb_philo)
			if (pthread_create(&d.philo[i].thread, NULL, routine, &d.philo[i]))
				clean (&d);
	monitoring(&d, i);
	clean(&d);
	return (0);
}
