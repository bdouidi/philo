/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:48:42 by user42            #+#    #+#             */
/*   Updated: 2022/02/28 20:48:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	p_eat(t_data *d, int index, int next)
{
	unsigned long	cpylastdinnertime;

	pthread_mutex_lock(&d->philo[index].fork);
	pthread_mutex_lock(&d->philo[next].fork);
	msg(d, index, "has taken a fork");
	msg(d, index, "has taken a fork");
	msg(d, index, "is eating");
	pthread_mutex_lock(&d->philo[index].check_time);
	d->philo[index].last_dinner_time = t_time();
	cpylastdinnertime = d->philo[index].last_dinner_time;
	pthread_mutex_unlock(&d->philo[index].check_time);
	while ((t_time() - cpylastdinnertime) < d->time_to_eat)
		usleep(10);
	pthread_mutex_lock(&d->philo[index].finish_routine);
	d->philo[index].nb_dinner++;
	pthread_mutex_unlock(&d->philo[index].finish_routine);
	pthread_mutex_unlock(&d->philo[next].fork);
	pthread_mutex_unlock(&d->philo[index].fork);
}

void	p_sleep(t_data *d, int index)
{
	unsigned long	time_to_finish_routine;

	msg(d, index, "is sleeping");
	time_to_finish_routine = (t_time() - d->start) + d->time_to_sleep;
	while ((t_time() - d->start) < time_to_finish_routine)
		usleep(10);
}
