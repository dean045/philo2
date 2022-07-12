/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/12 05:32:23 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_utils *utils, int i, int av5)
{
	t_philo	*tmp;

	tmp = malloc(sizeof(t_philo));
	if (!tmp)
		return ;
	tmp->num = i;
	tmp->rot = av5;
	tmp->next = NULL;
	if (utils->philos != NULL)
		ft_lstlast((utils->philos))->next = tmp;
	else
		utils->philos = tmp;
	if (i == utils->nb_philo)
		ft_lstlast((utils)->philos)->next = (utils)->philos;
	pthread_mutex_init(&((utils)->fchette[i - 1]), NULL);
}

void	init(t_utils **utils, char **av, int ac)
{
	int	i;
	int	rot;

	rot = -1;
	if (ac == 6)
		rot = ft_atoi(av[5]);
	i = 0;
	(*utils) = calloc(sizeof(t_utils), 1);
	if (!utils)
		return ;
	(*utils)->nb_philo = ft_atoi(av[1]);
	(*utils)->rot_done = 0;
	(*utils)->ttdie = ft_atoi(av[2]);
	(*utils)->tteat = ft_atoi(av[3]);
	(*utils)->ttsleep = ft_atoi(av[4]);
	pthread_mutex_init(&((*utils)->death), NULL);
	pthread_mutex_init(&((*utils)->mute_rot), NULL);
	pthread_mutex_init(&((*utils)->mute_print), NULL);
	(*utils)->philos = NULL;
	(*utils)->gameover = 0;
	(*utils)->fchette = malloc(sizeof(pthread_mutex_t) * ((*utils)->nb_philo));
	if (!(*utils)->fchette)
		return ;
	while (++i <= (*utils)->nb_philo)
		init_philo(*utils, i, rot);
}

int	start_th(t_utils *utils)
{
	int	ret;

	pthread_mutex_init(&((utils)->philos->block), NULL);
	pthread_mutex_lock(&(utils->philos->block));
	gettimeofday(&(utils->philos->time), NULL);
	pthread_mutex_unlock(&(utils->philos->block));
	ret = pthread_create(&(utils->philos->philo), NULL, table, (void *)utils);
	usleep(10000);
	utils->philos = utils->philos->next;
	return (ret);
}

int	join_death(t_utils *utils)
{
	int	i;

	i = -1;
	usleep((utils->ttdie - 1) * 1000);
	while (get_gameover(utils) == 0 && get_rot(utils) == 0)
	{
		check_death(utils);
		usleep(8000);
	}
	while (++i < utils->nb_philo)
	{
		pthread_join((utils->philos->philo), NULL);
		utils->philos = utils->philos->next;
	}
	return (ft_free(utils));
}

int	main(int ac, char **av)
{
	t_utils			*utils;
	int				i;

	if ((ac == 5 || ac == 6) && check_args(av, ac))
	{
		i = -1;
		init(&utils, av, ac);
		if (utils->nb_philo == 1)
			return (one_philo(utils, ac, av));
		pthread_mutex_lock(&(utils->mute_print));
		while (++i < utils->nb_philo)
			if (start_th(utils) == -1)
				return (ft_free(utils));
		gettimeofday(&((utils)->start), NULL);
		pthread_mutex_unlock(&(utils->mute_print));
		return (join_death(utils));
	}
	else
		printf("Invalid args\n");
}
