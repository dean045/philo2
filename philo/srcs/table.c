/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:16:25 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/13 14:28:38 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_utils *utils, t_philo *philo)
{
	pthread_mutex_lock(&(utils->fchette[philo->num - 1]));
	print(utils, philo->num, 2, philo->utils->start);
	pthread_mutex_lock(&(utils->fchette[philo->num]));
	print(utils, philo->num, 2, philo->utils->start);
	print(utils, philo->num, 3, philo->utils->start);
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
	s_sleep(utils, philo->tteat);
	philo->rot = philo->rot - 1;
	pthread_mutex_unlock(&(utils->fchette[philo->num - 1]));
	pthread_mutex_unlock(&(utils->fchette[philo->num]));
	if (philo->rot != 0)
	{
		print(utils, philo->num, 4, philo->utils->start);
		s_sleep(utils, philo->ttsleep);	
	}
}

void	eat_last(t_utils *utils, t_philo *philo)
{
	pthread_mutex_lock(&(utils->fchette[0]));
	print(utils, philo->num, 2, philo->utils->start);
	pthread_mutex_lock(&(utils->fchette[philo->num - 1]));
	print(utils, philo->num, 2, philo->utils->start);
	print(utils, philo->num, 3, philo->utils->start);
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
	s_sleep(utils, philo->tteat);
	philo->rot--;
	pthread_mutex_unlock(&(utils->fchette[0]));
	pthread_mutex_unlock(&(utils->fchette[philo->num - 1]));
	if (philo->rot != 0)
	{
		print(utils, philo->num, 4, philo->utils->start);
		s_sleep(utils, philo->ttsleep);	
	}
}

void	*table(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	pthread_mutex_lock(&(philo->utils->mute_print));
	pthread_mutex_unlock(&(philo->utils->mute_print));
	pthread_mutex_lock(&(philo->block));
	gettimeofday(&(philo->time), NULL);
	pthread_mutex_unlock(&(philo->block));
	if (philo->num % 2 == 0)
		usleep((philo->tteat / 2) * 1000);
	while (philo->rot != 0 && get_gameover(philo->utils) == 0)
	{
		if (philo->num == philo->nb_philo)
			eat_last(philo->utils, philo);
		else
			eat(philo->utils, philo);
		if (philo->rot == 0)
		{
			pthread_mutex_lock(&(philo->utils->mute_rot));
			philo->utils->rot_done++;
			pthread_mutex_unlock(&(philo->utils->mute_rot));
		}
		if (philo->rot != 0)
			print(philo->utils, philo->num, 1, philo->utils->start);
	}
	return (NULL);
}

int	check_death(t_philo *philos)
{
	int				i;
	int				ret;
	struct timeval	current;

	i = -1;
	ret = -1;
	while (++i < philos->nb_philo && ret == -1)
	{
		gettimeofday(&(current), NULL);
		pthread_mutex_lock(&(philos->block));
		if (convert(philos->time) + philos->ttdie <= convert(current))
		{
			pthread_mutex_lock(&(philos->utils->death));
			ret = (philos->num);
			philos->utils->gameover = 1;
			pthread_mutex_unlock(&(philos->utils->death));
		}
		pthread_mutex_unlock(&(philos->block));
		philos = philos->next;
	}
	if (ret != -1)
		print(philos->utils, ret, 0, philos->utils->start);
	return (ret);
}

void	s_sleep(t_utils *utils, int time)
{
	struct timeval	start;
	struct timeval	current;
	int				i;

	i = 0;
	gettimeofday(&(current), NULL);
	gettimeofday(&(start), NULL);
	while (++i && convert(start) + time > convert(current))
	{
		usleep(1000);
		gettimeofday(&(current), NULL);
		if (i % 10 == 0 && get_gameover(utils) == 1)
			break ;
	}
}
