/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:28:06 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/13 14:14:00 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	pthread_mutex_t	block;
	pthread_t		philo;
	struct s_philo	*next;
	struct timeval	time;
	int				num;
	int				nb_philo;
	int				tteat;
	int				ttdie;
	int				ttsleep;
	int				rot;
	struct s_utils	*utils;
}	t_philo;

typedef struct s_utils
{
	pthread_mutex_t	*fchette;
	pthread_mutex_t	death;
	pthread_mutex_t	mute_rot;
	pthread_mutex_t	mute_print;

	struct timeval	start;
	int				gameover;
	int				rot_done;
}	t_utils;

int			ft_atoi(const char *str);
t_philo		*ft_lstlast(t_philo *lst);
void		print(t_utils *utils, int philo, int etat, struct timeval time);
t_philo		*get_philo(t_utils *utils, int x);
long int	maj(struct timeval start);

//utils
void		s_sleep(t_utils *utils, int time);
int			get_gameover(t_utils *utils);
long int	convert(struct timeval tmp);
int			ft_free(t_philo *philos, int size);
int			one_philo(t_philo *philos, int ac, char **av);
int			check_args(char **av, int ac);

//table.c
void		eat(t_utils *utils, t_philo *philo);
void		eat_last(t_utils *utils, t_philo *philo);
void		*table(void *param);
void		ft_usleep(int time);
int			check_death(t_philo *philos);
int			get_rot(t_utils *utils, int nb_philo);

#endif