/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:48:56 by litsmail          #+#    #+#             */
/*   Updated: 2020/12/12 17:31:01 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		last;
	char	*copy;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	last = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (last && ft_strchr(set, s1[last]))
		last--;
	if (last - start + 1 > 0)
		copy = ft_substr(s1, start, last - start + 1);
	else
		copy = ft_calloc(1, 1);
	return (copy);
}
