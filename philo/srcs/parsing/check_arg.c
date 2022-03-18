/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:49:43 by user42            #+#    #+#             */
/*   Updated: 2022/02/28 20:49:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	isnt_digit(char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp("", s))
		error_msg(2, s);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			error_msg(2, s);
		++i;
	}
	return (0);
}

void	is_unsigned_long(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (ft_atoi(s[i]) <= 0 || ft_atoi(s[i]) > INT_MAX)
			error_msg(2, s[i]);
		++i;
	}
}

void	check_arg(t_data *d, char **s, int ac)
{
	int	i;

	i = 0;
	while (s[i])
		isnt_digit(s[i++]);
	is_unsigned_long(s);
	d->nb_philo = ft_atoi(s[0]);
	d->time_to_die = ft_atoi(s[1]);
	d->time_to_eat = ft_atoi(s[2]);
	d->time_to_sleep = ft_atoi(s[3]);
	if (ac == 5)
		d->max_dinner = ft_atoi(s[4]);
	d->start = t_time();
}
