/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokyrand <tokyrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:51:50 by tokyrand          #+#    #+#             */
/*   Updated: 2026/04/06 14:06:45 by tokyrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line_bonus(char **cloud)
{
	char	*new_cloud;
	int		i;
	char	*temp;

	i = 0;
	while ((*cloud)[i] && (*cloud)[i] != SEP)
		i++;
	if ((*cloud)[i] == SEP)
		i++;
	new_cloud = ft_substr_bonus(*cloud, 0, i);
	temp = ft_substr_bonus(*cloud, i, ft_strlen_bonus(*cloud) - i);
	free(*cloud);
	*cloud = temp;
	return (new_cloud);
}

static char	*ft_strchr_bonus(const char *s)
{
	size_t		i;
	char		*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (char)SEP)
			return (&(str[i]));
		i++;
	}
	if ((char)SEP == '\0')
		return (&str[i]);
	return (NULL);
}

static char	*get_everything_bonus(int fd, char *cloud)
{
	ssize_t		read_byte;
	char		*buff;
	char		*temp;

	read_byte = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (read_byte > 0 && !ft_strchr_bonus(cloud))
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte < 0)
		{
			free(buff);
			free(cloud);
			return (NULL);
		}
		buff[read_byte] = '\0';
		temp = ft_strjoin_bonus(cloud, buff);
		free(cloud);
		cloud = temp;
	}
	free(buff);
	return (cloud);
}

char	*get_next_line(int fd)
{
	static char	*cloud[1024];
	char		*buff;

	if ((fd < 0 || fd > 1024) || BUFFER_SIZE <= 0)
		return (NULL);
	cloud[fd] = get_everything_bonus(fd, cloud[fd]);
	if (!cloud[fd])
		return (NULL);
	buff = extract_line_bonus(&cloud[fd]);
	return (buff);
}
