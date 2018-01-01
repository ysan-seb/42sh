/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prompt_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:46:32 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/12/04 16:40:33 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_prt_bslash(char buff[], int *b)
{
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[(*b)++] = '\\';
	return (1);
}

static int	sh_norminette(char *ps, char buff[], int *b, int *len)
{
	if (ps[0] == 'a' || ps[0] == 'n' || ps[0] == 'r')
		sh_prt_chr(buff, b, ps[0], len);
	else if (CASE(ps[0]) == 'h')
		sh_prt_host(buff, b, ps[0], len);
	else if (ps[0] == 'l')
		sh_prt_term(buff, b, len);
	else if (ps[0] == 's')
		*len += sh_prt_shell(buff, b);
	else if (ps[0] == 't' || ps[0] == 'T' || ps[0] == '@' || ps[0] == 'A')
		sh_prt_time(buff, b, ps[0], len);
	else if (ps[0] == 'u')
		*len += sh_prt_user(buff, b);
	else if (CASE(ps[0]) == 'v')
		*len += sh_prt_vers(buff, b, ps[0]);
	else if (CASE(ps[0]) == 'w')
		sh_prt_wdir(buff, b, ps[0], len);
	else if (ps[0] == '$')
		*len += sh_prt_uid(buff, b);
	else
		return (0);
	return (1);
}

int			sh_prompt_conv(char *ps, char buff[], int *b, int *len)
{
	if (CASE(ps[0]) == 'd')
		return (sh_prt_date(buff, b, ps, len));
	else if (ps[0] == 'e')
		return (sh_prt_esc(buff, b, ps));
	else if (sh_norminette(ps, buff, b, len))
		return (1);
	*len += sh_prt_bslash(buff, b);
	return (0);
}
