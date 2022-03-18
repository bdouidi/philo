/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:48:37 by user42            #+#    #+#             */
/*   Updated: 2022/02/28 20:48:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	msg(t_data *d, int index, char *msg)
{
	pthread_mutex_lock(&d->died);
	if (!d->a_philo_died)
	{
		pthread_mutex_lock(&d->msg);
		if (!ft_strcmp(msg, "died"))
		{
			d->a_philo_died = 1;
			printf("\033[1;31m");
		}
		printf("%ld\t%d %s\n", current_time(d), index + 1, msg);
		pthread_mutex_unlock(&d->msg);
		pthread_mutex_unlock(&d->died);
		return ;
	}
	pthread_mutex_unlock(&d->died);
}

void	error_msg(int error, char *arg)
{
	if (error == 1)
	{
		printf("Usage: program [nb_philo_and_fork] [time_to_die] [time_to_eat]\
[time_to_sleep] (optionnal)[nb_of_dinners]\n");
	}
	else if (error == 2)
		printf("philo : %s : it's not a correctly formatted number\n", arg);
	exit (EXIT_FAILURE);
}
