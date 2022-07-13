/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:10:17 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/13 14:34:26 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print(t_utils *utils, int philo, int etat, struct timeval time)
{
	long int	now;

	pthread_mutex_lock(&(utils->mute_print));
	now = maj(time);
	if (etat == 0)
		printf("%li %i died\n", now, philo);
	else if (get_gameover(utils) == 0)
	{
		if (etat == 1)
			printf("%ld %i is thinking\n", now, philo);
		else if (etat == 2)
			printf("%ld %i has taken a fork\n", now, philo);
		else if (etat == 3)
			printf("%ld %i is eating\n", now, philo);
		else if (etat == 4)
			printf("%ld %i is sleeping\n", now, philo);
	}
	pthread_mutex_unlock(&(utils->mute_print));
}

long int	maj(struct timeval start)
{
	struct timeval	tmp;

	gettimeofday(&(tmp), NULL);
	return (convert(tmp) - convert(start));
}

long int	convert(struct timeval tmp)
{
	return ((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000));
}

int	get_gameover(t_utils *utils)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&(utils->death));
	if (utils->gameover == 1)
		x = 1;
	pthread_mutex_unlock(&(utils->death));
	return (x);
}

int	get_rot(t_utils *utils, int nb_philo)
{
	int	x;

	x = 0;
	pthread_mutex_lock(&(utils->mute_rot));
	if (utils->rot_done == nb_philo)
		x = 1;
	pthread_mutex_unlock(&(utils->mute_rot));
	return (x);
}
