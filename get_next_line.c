/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:55:59 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/05 20:10:03 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len);

size_t ft_strlen(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char *s1, char *s2);

t_file	*read_line(t_file *ptr, int fd)
{
	size_t	dup;
	size_t	newline;
	char	*buff;
	int	rd;

	rd = 1;
	while (rd)
	{
		newline = 0;
		dup = 0;
		buff = ptr->stream;
		while (buff[newline] != '\n' && buff[newline])
		{
			newline++;
			dup++;
		}
		ptr->newline += newline;
		ptr->line = ft_strjoin(ptr->line, buff);
		if (buff[newline] == '\n')
		{
			ptr->line = ft_substr(ptr->line, 0, ptr->newline + 2);
			ptr->stream = ft_substr(ptr->stream, dup, BUFFER_SIZE + 1);
			return (ptr);
		}
		rd = read(fd, ptr->stream, (BUFFER_SIZE));
	}
	return (ptr);
}

char	*get_next_line(int fd)
{
	int	rd;
	t_file	*buff;
	static t_file	ptr[10000];

	if (ptr[fd].stream == NULL && !ptr[fd].newline)
	{
		ptr[fd].newline = 0;
		ptr[fd].stream =  malloc((BUFFER_SIZE + 1) * sizeof(char));
		ptr[fd].line =  malloc((1) * sizeof(char));
		ptr[fd].line[0] = 0;
		rd = read(fd, ptr[fd].stream, BUFFER_SIZE);
		ptr[fd].stream[BUFFER_SIZE] = 0;
	}
	buff = read_line(&ptr[fd], fd);
	return (buff->line);
}

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
			while (line && j < 1)
			{
			//	printf("%s\n",line);
				free(line);
				line = get_next_line(fd);
				j++;
			}
			close(fd);
			i++;
		}
	}
	return (0);
}
