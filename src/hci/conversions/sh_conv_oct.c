/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_conv_oct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:51:46 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:51:48 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_conv_oct(char *str)
{
	char	c;
	size_t	i;

	c = 0;
	i = 0;
	while (i < 2 && (str[i] >= '0' && str[i] < '8'))
		c = c * 8 + str[i++] - '0';
	return (c);
}
