/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:33 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/13 15:30:06 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo(t_utils *utils, int av5, t_philo *philos, char **av)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (++i <= ft_atoi(av[1]))
	{
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return (NULL);
		tmp->nb_philo = ft_atoi(av[1]);
		tmp->ttdie = ft_atoi(av[2]);
		tmp->tteat = ft_atoi(av[3]);
		tmp->ttsleep = ft_atoi(av[4]);
		tmp->num = i;
		tmp->rot = av5;
		tmp->next = NULL;
		tmp->utils = utils;
		if (philos != NULL)
			ft_lstlast((philos))->next = tmp;
		else
			philos = tmp;
		if (i != 1 && i == tmp->nb_philo)
			ft_lstlast(philos)->next = philos;
	}
	return (philos);
}

t_philo	*init(t_utils **utils, char **av, int ac)
{
	int		rot;
	t_philo	*philos;

	rot = -1;
	philos = NULL;
	if (ac == 6)
		rot = ft_atoi(av[5]);
	(*utils) = calloc(sizeof(t_utils), 1);
	if (!utils)
		return (NULL);
	(*utils)->rot_done = 0;
	pthread_mutex_init(&((*utils)->death), NULL);
	pthread_mutex_init(&((*utils)->mute_rot), NULL);
	pthread_mutex_init(&((*utils)->mute_print), NULL);
	(*utils)->gameover = 0;
	(*utils)->fchette = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1])));
	if (!(*utils)->fchette)
		return (NULL);
	philos = init_philo(*utils, rot, philos, av);
	return (philos);
}

int	start_th(t_philo *philos)
{
	int	ret;

	pthread_mutex_init(&(philos->block), NULL);
	pthread_mutex_init(&(philos->utils->fchette[philos->num - 1]), NULL);
	gettimeofday(&(philos->time), NULL);
	ret = pthread_create(&(philos->philo), NULL, table, (void *)philos);
	return (ret);
}

int	join_death(t_philo *philos)
{
	int	i;

	i = -1;
	usleep((philos->ttdie - 1) * 1000);
	while (get_gameover(philos->utils) == 0
		&& get_rot(philos->utils, philos->nb_philo) == 0)
	{
		check_death(philos);
		usleep(8000);
	}
	while (++i < philos->nb_philo)
	{
		pthread_join((philos->philo), NULL);
		philos = philos->next;
	}
	return (ft_free(philos, philos->nb_philo));
}

int	main(int ac, char **av)
{
	t_utils			*utils;
	t_philo			*philos;
	t_philo			*tmp_philos;
	int				i;

	while ((ac == 5 || ac == 6) && check_args(av, ac))
	{
		i = -1;
		philos = init(&utils, av, ac);
		if (!philos)
			break ;
		tmp_philos = philos;
		if (philos->nb_philo == 1)
			return (one_philo(philos, ac, av));
		pthread_mutex_lock(&(utils->mute_print));
		while (++i < philos->nb_philo)
			if (start_th(philos) == -1)
				return (ft_free(philos, philos->nb_philo));
		else
				philos = philos->next;
		gettimeofday(&((philos)->utils->start), NULL);
		pthread_mutex_unlock(&(utils->mute_print));
		return (join_death(tmp_philos));
	}
	printf("Invalid args\n");
}
