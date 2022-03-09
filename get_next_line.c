/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:55:59 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/10 02:36:53 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len);

size_t	ft_strlen(const char *str);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_freefile(t_file *ptr)
{
	if (ptr->stream)
	{
		free(ptr->stream);
		ptr->stream = 0;
	}
	ptr->start = 0;
	ptr->newline = 0;
	return (0);
}	

t_file	*read_line(t_file *ptr, int fd)
{
	size_t	newline;
	size_t	i;
	int		rd;
	char	*buff_file;

	rd = 1;
	newline = 0;
	i = ptr->start;
	while (rd)
	{
		buff_file = malloc((BUFFER_SIZE + 1) * sizeof(char));
		rd = read(fd, buff_file, BUFFER_SIZE);
		buff_file[rd] = 0;
		ptr->stream = ft_strjoin(ptr->stream, buff_file);
		while (ptr->stream[i + newline] != '\n' && ptr->stream[i + newline])
			newline++;
		ptr->newline = newline;
		free(buff_file);
		if ((ptr->stream[i + newline]) == '\n')
			return (ptr);
		if (rd <= 0 && ptr->stream)
			return (ptr);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_file			*buff;
	static t_file	ptr[10000];
	char			*line;

	if (fd < 0)
		return (NULL);
	if (ptr[fd].stream == NULL && !ptr[fd].newline)
	{
		ptr[fd].stream = malloc(1 * sizeof(char));
		ptr[fd].stream[0] = 0;
		ptr[fd].start = 0;
	}
	buff = read_line(&ptr[fd], fd);
	if (!buff->stream[buff->start])
		return (ft_freefile(&ptr[fd]));
	if (buff->stream[buff->start + buff->newline] == '\n')
		buff->newline++;
	line = malloc((buff->newline + 1) * sizeof(char));
	ft_memcpy(line, buff->stream + buff->start, buff->newline + 1);
	line[buff->newline] = 0;
	buff->start += (buff->newline);
	buff->newline = 0;
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			line = get_next_line(fd);
			j = 0;
			while (line)// && j < 3)
			{
				printf("%s", line);
				free(line);
				line = get_next_line(fd);
				j++;
			}
			close(fd);
			i++;
		}
	}
	return (0);
}*/
