/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_category.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:56:47 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/03 11:30:45 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_cat_op(char *str, int status[3])
{
	if (ft_strnequ(str, "||", 2) || ft_strnequ(str, "&&", 2))
		return (ANDOR);
	if (ft_strnequ(str, ";", 1))
		return (ESPERCOLON);
	if (ft_strnequ(str, "|", 1))
		return (PIPE);
	if (ft_strnequ(str, "\n", 1))
	{
		status[2] = 1;
		return (NEWLINE);
	}
	return (0);
}

static int	sh_cat_rdir(char *str)
{
	if (!sh_rdir_op(str) || str[0] == '&')
		return (0);
	return (1);
}

static int	sh_cat_coa(char *str, int i[2], int status[3])
{
	status[1] = 0;
	if (status[0] == CMD)
		return (status[0]--);
	if (status[0] == OPT)
	{
		if (ft_strnequ(str + i[0], "--", i[1] > 2 ? i[1] : 2))
			return (status[0]--);
		if (str[i[0]] == '-')
			return (status[0]);
		else
			status[0] = ARG;
	}
	return (status[0]);
}

int			sh_category(char *str, int i[2], int status[3])
{
	if (ft_strnequ(str + i[0], "(", 1))
		return (SUB_SHELL);
	if (sh_cat_op(str + i[0], status))
	{
		status[0] = CMD;
		return (sh_cat_op(str + i[0], status));
	}
	if (sh_rdir_op(str + i[0]))
	{
		status[1] = (i[1] == 2 && ft_strnequ(str + i[0], "<<", i[1])) ? 2 : 1;
		return (REDIRECTION);
	}
	status[2] = 0;
	if ((i[1] == 1 && str[i[0]] >= '0' && str[i[0]] <= '9'
				&& sh_cat_rdir(str + i[0] + i[1]))
			|| status[1])
		return ((status[1] == 2 ? HEREDOC : FILDES) + (status[1] = 0));
	return (sh_cat_coa(str, i, status));
}
