/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:44:18 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/07 13:47:24 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    *ft_memcpy(void *dst, const void *src, size_t len)
{
        unsigned char   *psrc;
        unsigned char   *pdst;

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

t_file	*ft_lstnew(char *content)
{
	t_file	*tmp;

	tmp = malloc(sizeof(t_file));
	if (!tmp)
		return (NULL);
	if (tmp)
	{
		tmp->stream = content;
		tmp->newline = 0;
		tmp->next = NULL;
	}
	return (tmp);
}

void	ft_lstadd_back(t_file **lst, t_file *new)
{
	t_file	*temp;

	if (*lst)
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		lst = &temp;
	}
	else
		*lst = new;
}

static size_t	ft_size(char const *s, unsigned int start, size_t len)
{
	if ((start + len) < ft_strlen(s))
		return (len + 1);
	return (ft_strlen(s) - start + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start < ft_strlen(s))
	{
		sub = malloc((ft_size(s, start, len)) * sizeof(char));
		if (!sub)
			return (NULL);
		while (i < len && s[i + start])
		{
			sub[i] = s[i + start];
			i++;
		}
	}
	else
		sub = malloc(sizeof(char));
	if (!sub)
		return (NULL);
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
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
	return (str);
}

char	*ft_strchr(char const *p, int ch)
{
	char	c;
	int		i;

	c = ch;
	i = 0;
	while (p[i])
	{
		if (p[i] == c)
			return ((char *)(p + i));
		i++;
	}
	if (p[i] == c)
		return ((char *)(p + i));
	return (NULL);
}
