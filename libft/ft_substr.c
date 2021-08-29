/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 17:22:39 by litsmail          #+#    #+#             */
/*   Updated: 2021/01/11 16:18:44 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;

	if (!s)
		return (NULL);
	len = ft_strlen(s) < len ? ft_strlen(s) : len;
	while (start-- && *s)
		s++;
	if (!(copy = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}
