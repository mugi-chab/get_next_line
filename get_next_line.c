/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svillalv <svillalv@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:00:47 by svillalv          #+#    #+#             */
/*   Updated: 2022/07/07 15:05:41 by svillalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf);
char	*get_line(char *buf);
char	*remove_line(char *buf);

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = ft_read(fd, buf);
	if (!buf)
		return (NULL);
	line = get_line(buf);
	buf = remove_line(buf);
	return (line);
}

char	*ft_read(int fd, char *buf)
{
	char	*aux_buf;
	ssize_t	numbyte;

	aux_buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!aux_buf)
		return (NULL);
	numbyte = 1;
	while (!ft_strchr(buf, '\n') && numbyte != 0)
	{
		numbyte = read(fd, aux_buf, BUFFER_SIZE);
		if (numbyte == -1)
		{
			free(aux_buf);
			return (NULL);
		}
		aux_buf[numbyte] = '\0';
		buf = ft_strjoin(buf, aux_buf);
	}
	free(aux_buf);
	return (buf);
}

char	*get_line(char *buf)
{
	char	*line;
	int		i;
	int		c;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	c = -1;
	while (++c <= i)
		line[c] = buf[c];
	line[c] = '\0';
	return (line);
}

char	*remove_line(char *buf)
{
	char	*aux_buf;
	int		i;
	int		j;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	aux_buf = malloc(sizeof(char) * (ft_strlen(buf) - i) + 1);
	if (!aux_buf)
		return (NULL);
	i++;
	j = 0;
	while (buf[i])
		aux_buf[j++] = buf[i++];
	aux_buf[j] = '\0';
	free(buf);
	return (aux_buf);
}
