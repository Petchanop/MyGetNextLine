/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:55:59 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/07 16:00:49 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len);

size_t ft_strlen(const char *str);

t_file	*ft_lstnew(char *content);

void	ft_lstadd_back(t_file **lst, t_file *new);

char	*extract_line(t_file *ptr)
{
	char	*line;
	size_t	count;
	size_t	j;
	t_file	*index;

	count = 0;
	j = 0;
	index = ptr;
	while (index)
	{
		if(index->stream && !index->newline)
			count++;
		printf("index : %s\n", index->stream);
		index = index->next;
	}
	line = malloc(((count * BUFFER_SIZE) + index->newline) * sizeof(char));
	index = ptr;
	while (index)
	{
		int i = 0;
		while (index->stream[i] && !index->newline)
			line[j] = index->stream[i++];
		while (index->stream[i] && index->newline)
		{
			line[j] = index->stream[i++];
			index->newline--;
		}
		if (index->stream[i] == '\n')
			return (line);
		index = index->next;
	}
	return (line);
}

char	*read_line(t_file *ptr, int fd)
{
	t_file	*line;	
	size_t	newline;
	int	rd;
	char	*buff;

	rd = 1;
	buff = ptr->stream;
	while (rd)
	{
		newline = 0;
		while (buff[newline] != '\n' && buff[newline])
			newline++;
		if (buff[newline] == '\n')
		{

			return (extract_line(ptr));
		}
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		rd = read(fd, buff, (BUFFER_SIZE));
		line = ft_lstnew(buff);
		ft_lstadd_back(&ptr, line);
		free(line);
	}
	line = ft_lstnew(0);
	ft_lstadd_back(&ptr, line);
	free(line);
	return (extract_line(ptr));
}

char	*get_next_line(int fd)
{
	char	*buff_read;
	static t_file	ptr[10000];
	int	rd;

	if (ptr[fd].stream == NULL && !ptr[fd].newline)
	{
		buff_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
		rd =read(fd, buff_read, BUFFER_SIZE);
		ptr[fd] = *ft_lstnew(buff_read);
	}
	buff_read = read_line(&ptr[fd], fd);
/*	if (!buff_read)
	{
		t_file	*tmp;
		while (buff)
		{
			tmp = buff;
			free(buff);
			buff = tmp->next;
		}
		buff = NULL;
		printf("deletei\n");
	}	
*/	return (buff_read);
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
			while (line && j < 4)
			{
			//	printf("result : %s",line);
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
