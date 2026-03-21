/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokyrand <tokyrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:48:57 by tokyrand          #+#    #+#             */
/*   Updated: 2026/03/06 13:58:52 by tokyrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_bonus(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	*ft_memmove_bonus(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}

void	*ft_calloc_bonus(size_t nmemb, size_t size)
{
	void			*str;
	size_t			max_nmemb;
	unsigned long	i;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	max_nmemb = (size_t)-1 / size;
	if (max_nmemb < nmemb)
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
		((unsigned char *)str)[i++] = 0;
	return (str);
}

char	*ft_strjoin_bonus(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen_bonus(s1);
	s2_len = ft_strlen_bonus(s2);
	join = ft_calloc_bonus(sizeof(char), (s1_len + s2_len + 1));
	if (!join)
		return (NULL);
	if (s1)
		ft_memmove_bonus(join, s1, s1_len);
	if (s2)
		ft_memmove_bonus(join + s1_len, s2, s2_len);
	return (join);
}

char	*ft_substr_bonus(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen_bonus(s);
	if (start >= s_len)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[start + i] = '\0';
	return (sub);
}
