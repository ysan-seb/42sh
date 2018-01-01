/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_wdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:57:13 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/04 16:19:52 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_prt_home(char *pwd, char *tmp)
{
	char	*home;
	int		i;

	if (!pwd)
		return (NULL);
	*tmp = pwd[0];
	if (pwd && (home = sh_getvar("HOME")) && home[0])
	{
		i = 0;
		while (home[i] && home[i] == pwd[i])
			i++;
		if (i && !home[i] && home[i] != '/'
			&& (pwd[i] == '\0' || pwd[i] == '/'))
		{
			*tmp = pwd[i - 1];
			pwd[i - 1] = '~';
			return (pwd + i - 1);
		}
	}
	return (pwd);
}

static int	sh_prt_dirtrim(char *pwd, char w)
{
	int		dirtrim;
	int		i;

	dirtrim = (w == 'W' ? 1 : ft_atoi(sh_getvar("PROMPT_DIRTRIM")));
	i = 0;
	if (dirtrim)
	{
		while (pwd[i + 1])
			i += 1;
		while (i && pwd[i] == '/')
			i -= 1;
		while (i && dirtrim)
		{
			if (pwd[i] == '/' && ((dirtrim -= 1) || 1))
				while (dirtrim && i && pwd[i] == '/')
					i -= 1;
			else
				i -= 1;
		}
	}
	if (i && pwd[i] == '/' && w == 'W')
		i += 1;
	return (i);
}

static int	sh_prt_wfill(char buff[], int *b, char *src, int len)
{
	int		i;

	i = 0;
	while (src[i])
	{
		len = (src[i] == '\n' ? 0 : len + 1);
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = src[i++];
	}
	return (len);
}

int			sh_prt_wdir(char buff[], int *b, char w, int *len)
{
	char	*pwd;
	char	tmp;
	int		pos;

	if ((pwd = sh_prt_home(sh_getvar("PWD"), &tmp)))
	{
		pos = sh_prt_dirtrim(pwd, w);
		if (w == 'w' && pos)
		{
			if (pwd[0] == '~' && pos == 1)
				*len = sh_prt_wfill(buff, b, "~", *len);
			else if (pwd[0] == '~')
				*len = sh_prt_wfill(buff, b, "~/...", *len);
			else
				*len = sh_prt_wfill(buff, b, "...", *len);
		}
		*len = sh_prt_wfill(buff, b, pwd + pos, *len);
		pwd[0] = tmp;
	}
	return (*len);
}
