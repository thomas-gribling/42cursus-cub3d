/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:59:36 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/27 08:53:45 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include "cub3d.h"

char	*get_next_line(int fd);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void	*free_null(void *ptr1, void *ptr2);
char	*ft_strchr(const char *s, int c);

#endif