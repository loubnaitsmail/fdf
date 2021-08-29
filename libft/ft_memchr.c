/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:29:22 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/01 20:16:07 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (void *)(src + i);
		i++;
	}
	return (NULL);
}
