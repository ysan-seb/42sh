/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_termcaps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:57:33 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:57:33 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_init_tc(t_tc *s, char **stc, char *tc)
{
	if (!(*stc = tgetstr(tc, (char**)&(s->buff))))
		return (ft_error(tc, "termcap not provided by terminal", NULL));
	return (0);
}

int			sh_init_termcaps(t_tc *init)
{
	char	*termtype;
	int		success;

	if (!(termtype = sh_getvar("TERM")))
		return (ft_error("`TERM' environment variable not found", NULL, NULL));
	success = tgetent(init->data, termtype);
	if (success < 0)
		return (ft_error("Could not access the termcap data base", NULL, NULL));
	else if (success == 0)
		return (ft_error(termtype, "Terminal type not defined", NULL));
	ft_bzero(init->buff, 2048);
	if (sh_init_tc(init, &init->cd, "cd")
			|| sh_init_tc(init, &init->ce, "ce")
			|| sh_init_tc(init, &init->dn, "do")
			|| sh_init_tc(init, &init->le, "le")
			|| sh_init_tc(init, &init->nd, "nd")
			|| sh_init_tc(init, &init->up, "up"))
		return (1);
	init->vi = tgetstr("vi", (char**)&(init->buff));
	init->ve = tgetstr("ve", (char**)&(init->buff));
	init->coord = NULL;
	init->clipboard = NULL;
	init->cut = 0;
	return (0);
}
