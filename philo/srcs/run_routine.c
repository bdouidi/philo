/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:48:28 by user42            #+#    #+#             */
/*   Updated: 2022/02/28 20:48:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_routine(t_data *d, t_philo *p, unsigned int *next)
{
	if (p->index == d->nb_philo - 1)
		*next = 0;
	else
		*next = p->index + 1;
	if (p->index % 2 != 0)
		usleep(15000);
}

int	philo_died(t_data *d)
{			
	pthread_mutex_lock(&d->died);
	if (d->a_philo_died)
	{
		pthread_mutex_unlock(&d->died);
		return (1);
	}
	pthread_mutex_unlock(&d->died);
	return (0);
}

void	*routine(void *philo_ptr)
{
	t_philo			*p;
	t_data			*d;
	unsigned int	next;

	p = (t_philo *)philo_ptr;
	d = p->mom;
	init_routine(d, p, &next);
	while (1)
	{
		if (philo_died(d))
			break ;
		p_eat(d, p->index, next);
		pthread_mutex_lock(&p->finish_routine);
		if (d->max_dinner && d->max_dinner <= p->nb_dinner)
		{
			p->__finish_routine = 1;
			pthread_mutex_unlock(&p->finish_routine);
			break ;
		}
		pthread_mutex_unlock(&p->finish_routine);
		p_sleep(d, p->index);
		msg(d, p->index, "is thinking");
	}
	return (NULL);
}
