/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokyrand <tokyrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:44:49 by tokyrand          #+#    #+#             */
/*   Updated: 2026/03/21 14:57:47 by tokyrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	char	*str1;

	
	fd1 = open("test", O_RDONLY);
	str1 = get_next_line(fd1);
	while(str1)
	{
		printf("%s", str1);
		free(str1);
		str1 = get_next_line(fd1);
	}
	close(fd1);
	return 0;
}
