/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:05:59 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/12 19:01:21 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_free(t_philo *philos, int size)
{
	t_philo	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if (philos && philos->utils &&  philos->utils->fchette)
		free(philos->utils->fchette);
	if (philos && philos->utils)
		free(philos->utils);
	while (++i < size)
	{
		tmp = philos->next;
		if (philos)
		{
			free(philos);
			philos = NULL;
		}
		philos = tmp;
	}
	return (0);
}

int	check_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	if ((ac == 6 && ft_atoi(av[5]) <= 0) || ft_atoi(av[1]) <= 0
		|| ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (0);
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
		}
	}
	return (1);
}

int	one_philo(t_philo *philos, int ac, char **av)
{
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (ft_free(philos, philos->nb_philo));
	printf("0 1 has taken a fork\n");
	usleep(philos->ttdie * 1000);
	printf("%i 1 died\n", philos->ttdie);
	return (ft_free(philos, philos->nb_philo));
}
