/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:05:59 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/21 18:15:55 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_free(t_utils *utils)
{
	int		i;
	t_philo	*tmp;

	if (utils)
	{
		i = -1;
		while (++i < utils->nb_philo)
		{
			tmp = utils->philos->next;
			if (utils->philos)
				free(utils->philos);
			utils->philos = tmp;
		}
		if (utils->fchette)
			free(utils->fchette);
		free(utils);
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

int	one_philo(t_utils *utils, int ac, char **av)
{
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (ft_free(utils));
	printf("0 1 has taken a fork\n");
	usleep(utils->ttdie * 1000);
	printf("%i 1 died\n", utils->ttdie);
	return (ft_free(utils));
}
