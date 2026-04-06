/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokyrand <tokyrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:49:27 by tokyrand          #+#    #+#             */
/*   Updated: 2026/04/06 15:58:10 by tokyrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef SEP
#  define SEP '\n'
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen_bonus(const char *s);
void	*ft_memmove_bonus(void *dest, const void *src, size_t n);
char	*ft_strjoin_bonus(char const *s1, char const *s2);
char	*ft_substr_bonus(char const *s, unsigned int start, size_t len);

#endif