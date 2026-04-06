/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokyrand <tokyrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:12:33 by tokyrand          #+#    #+#             */
/*   Updated: 2026/04/06 14:10:17 by tokyrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **cloud)
{
	char	*new_cloud;
	int		i;
	char	*temp;

	i = 0;
	while ((*cloud)[i] && (*cloud)[i] != SEP)
		i++;
	if ((*cloud)[i] == SEP)
		i++;
	new_cloud = ft_substr(*cloud, 0, i);
	temp = ft_substr(*cloud, i, ft_strlen(*cloud) - i);
	free(*cloud);
	*cloud = temp;
	return (new_cloud);
}

static char	*ft_strchr(const char *s)
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

static char	*get_everything(int fd, char *cloud)
{
	ssize_t		read_byte;
	char		*buff;
	char		*temp;

	read_byte = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (read_byte > 0 && !ft_strchr(cloud))
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte < 0)
		{
			free(buff);
			free(cloud);
			return (NULL);
		}
		buff[read_byte] = '\0';
		temp = ft_strjoin(cloud, buff);
		free(cloud);
		cloud = temp;
	}
	free(buff);
	return (cloud);
}

char	*get_next_line(int fd)
{
	static char	*cloud;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cloud = get_everything(fd, cloud);
	if (!cloud)
		return (NULL);
	buff = extract_line(&cloud);
	if (buff && *buff == '\0')
	{
		free(cloud);
		free(buff);
		buff = NULL;
	}
	return (buff);
}
