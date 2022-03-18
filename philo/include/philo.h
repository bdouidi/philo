/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:48:04 by user42            #+#    #+#             */
/*   Updated: 2022/02/28 20:48:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	unsigned int	index;
	unsigned int	nb_dinner;
	unsigned long	last_dinner_time;
	unsigned int	__finish_routine;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	check_time;
	pthread_mutex_t	finish_routine;
	struct s_data	*mom;
}					t_philo;

typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	max_dinner;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	time_to_think;
	unsigned int	a_philo_died;
	unsigned int	philo_finish;
	unsigned int	dead;
	unsigned long	start;
	pthread_mutex_t	died;
	pthread_mutex_t	msg;
	t_philo			*philo;
}					t_data;

/*
*   *   *   *   PARSING		*	*	*	*	*	*	*	*	*	*	*	*		*
*/
void				check_arg(t_data *d, char **av, int ac);
void				error_msg(int error, char *arg);
void				init_thread(t_data *d);
void				clean(t_data *d);
void				*ft_memset(void *str, int c, size_t n);
int					ft_strcmp(char *s1, char *s2);
long				ft_atoi(const char *str);
int					ft_isdigit(int c);
/*
*	*	*	*	MAIN FUNC	*	*	*	*	*	*	*	*	*	*	*	*		*
*/
void				run_philosopher(t_data *d, unsigned int i);
void				*routine(void *philo_ptr);
void				*control(void *philo_ptr);
/*
*	*	*	*	THREADS		*	*	*	*	*	*	*	*	*	*	*	*		*
*/
long				t_time(void);
unsigned long		current_time(t_data *d);
void				msg(t_data *d, int index, char *msg);
void				p_eat(t_data *d, int index, int next);
void				p_sleep(t_data *d, int index);
int					is_success(t_data *d);
#endif