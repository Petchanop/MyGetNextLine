/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:41:13 by npiya-is          #+#    #+#             */
/*   Updated: 2022/03/10 06:23:26 by npiya-is         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_file
{
	struct s_file	*next;
	char			*stream;
	size_t			start;
	size_t			newline;
	int				fd;
}	t_file;

char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *str);
#endif
