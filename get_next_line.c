/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:55:59 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/03 15:02:42 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len);

size_t ft_strlen(const char *str);

t_file	*read_line(t_file *ptr)
{
	size_t	dup;
	size_t	newline;
	char	*buff;

	dup = 1;
	newline = 0;
	if (!ft_strlen(ptr->stream))
	{
		ptr->stream = NULL;
		return (ptr);
	}
	if (ptr->newline)
	{
		ptr->start = ptr->newline;
		ptr->stream += ptr->start;
	}
	buff = ptr->stream;
	while ((*buff) != '\n' && (*buff))
	{
		newline++;
		buff++;
		dup++;
	}
	ptr->newline = newline + 1;
	return (ptr);
}

char	*get_next_line(int fd)
{
	int	rd;
	t_file	*buff;
	char	*buff_file;
	char	*line;
	static t_file	ptr[10000];

	if (ptr[fd].stream == NULL && !ptr[fd].newline)
	{
		ptr[fd].start = 0;
		ptr[fd].newline = 0;
		buff_file = malloc((4096 + 1) * sizeof(char));
		rd = read(fd, buff_file, (4097));
		if (rd)
			ptr[fd].stream = buff_file;
		else
			return (0);
	}
	buff = read_line(&ptr[fd]);
	line = malloc((buff->newline) * sizeof(char));
	if (!ft_strlen(buff->stream))
		line = NULL;
	else
	{
		ft_memcpy(line, buff->stream, buff->newline);
		line[(buff->newline) - 1] = 0;
	}
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int	fd;
	int	i;
	int	j;
	char	*line;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			line = get_next_line(fd);
			j = 0;
			while (line) //&& j < 15)
			{
				printf("%s\n",line);
				free(line);
				line = get_next_line(fd);
				j++;
			}
			i++;
		}
	}
	return (0);
}*/
