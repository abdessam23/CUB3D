/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:06:00 by abdo              #+#    #+#             */
/*   Updated: 2025/10/02 10:55:02 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*read_line(char *s)
{
	char	buf[10];
	int		fd;
	int		rbyt;
	char	*str;

	str = NULL;
	if (!s)
		return (NULL);
	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while ((rbyt = read(fd, buf, 10)) > 0)
	{
		// rbyt = read(fd, buf, 10);
		// if (rbyt == 0)
		// 	break ;
		buf[rbyt] = '\0';
		str = ft_strjoin(str, buf);
	}
	close(fd);
	return (str);
}

int	ft_whitespace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_identif(int c)
{
	if (c == 'S' || c == 'W' || c == 'N' || c == 'E' || c == 'F' || c == 'C')
		return (1);
	return (0);
}

int	iswhitespace(char *s)
{
	while (*s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (1);
}

int	is_valid(int c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ')
	{
		return (1);
	}
	return (0);
}
