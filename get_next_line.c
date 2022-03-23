/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:55:59 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/13 15:37:46 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*ft_getptr(t_file **ptr, int fd);

t_file	*ft_createptr(int fd);

void	*ft_memcpy(void *dst, const void *src, size_t len);

size_t	ft_strlen(const char *str);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_freefile(t_file *ptr, int fd)
{
	t_file	*tmp;
	t_file	*pre;

	tmp = ptr;
	pre = ptr;
	while (tmp->next)
	{
		printf("tmp->fd : %d\n", tmp->fd);
		if (tmp->fd == fd)
		{
			if (tmp->stream[0])
				free(tmp->stream);
			if (tmp == ptr)
				ptr = ptr->next;
			else
				pre->next = tmp->next;
			free(tmp);
			break ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
//	if (tmp->stream[0])
//		free(tmp->stream);
//	free(ptr);
	return (0);
}

int	ft_check_fd(int fd)
{
	char	*test;
	int		rd;
	int		valid;

	valid = 0;
	test = malloc((BUFFER_SIZE + 1) * sizeof(char));
	rd = read(fd, test, 0);
	if (rd < 0)
		valid = 1;
	free(test);
	return (valid);
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
	buff_file = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (rd)
	{
		rd = read(fd, buff_file, BUFFER_SIZE);
		buff_file[rd] = 0;
		ptr->stream = ft_strjoin(ptr->stream, buff_file);
		while (ptr->stream[i + newline] != '\n' && ptr->stream[i + newline])
			newline++;
		ptr->newline = newline;
		if ((ptr->stream[i + newline]) == '\n' || (rd <= 0 && ptr->stream))
		{
			free(buff_file);
			return (ptr);
		}
	}
	free(buff_file);
	return (NULL);
}

char	*get_next_line(int fd)
{
	t_file			*buff;
	static t_file	*ptr = NULL;
	char			*line;

	if (ft_check_fd(fd))
		return (NULL);
	buff = ft_getptr(&ptr, fd);
	buff = read_line(buff, buff->fd);
	if (!buff->stream[buff->start])
		return (ft_freefile(buff, fd));
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
		while (i <= argc)
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
