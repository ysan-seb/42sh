/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrapp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 17:46:58 by pguillie          #+#    #+#             */
/*   Updated: 2017/06/21 12:03:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrapp(const char *str, const char c)
{
	char	*new;
	int		i;

	if (!str || !(new = ft_strnew(ft_strlen(str) + 1)))
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	return (new);
}
