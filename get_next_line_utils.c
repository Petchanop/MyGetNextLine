/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:44:18 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/10 06:12:05 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*psrc;
	unsigned char	*pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (!dst)
		return (NULL);
	while (len-- && psrc)
		*pdst++ = *psrc++;
	return (dst);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*str;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	str[i + ft_strlen(s1)] = '\0';
	free(s1);
	return (str);
}

t_file	*ft_createptr(int fd)
{
	t_file	*ptr;

	ptr = malloc(sizeof(t_file));
	ptr->fd = fd;
	ptr->stream = malloc(1 * sizeof(char));
	ptr->stream[0] = 0;
	ptr->start = 0;
	return (ptr);
}

t_file	*ft_getptr(t_file *ptr, int fd)
{
	t_file	*new;
	t_file	*data;

	data = ptr;
	while (data)
	{
		if (data->fd == fd)
			return (data);
		data = data->next;
	}
	new = ft_createptr(fd);
	data = new;
	return (new);
}
