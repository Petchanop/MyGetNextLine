/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:44:18 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/03 14:25:40 by npiya-is         ###   ########.fr       */
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

