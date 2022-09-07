/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolland <qrolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:14:00 by qrolland          #+#    #+#             */
/*   Updated: 2022/07/05 13:31:58 by qrolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_str(int fd, char *str, char *buf)
{
	int		len;
	char	*tmp;

	len = BUFFER_SIZE;
	while (!str || (len > 0 && !(ft_strchr(str, '\n'))))
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[len] = '\0';
		if (!str)
			str = ft_substr(buf, 0, len);
		else
		{
			tmp = str;
			str = ft_strjoin(tmp, buf);
			free (tmp);
		}
	}
	free (buf);
	return (str);
}

static char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_new_str(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}			

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[1024];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	str[fd] = ft_read_str(fd, str[fd], buf);
	if (!str[fd])
		return (NULL);
	line = ft_get_line(str[fd]);
	str[fd] = ft_new_str(str[fd]);
	return (line);
}
