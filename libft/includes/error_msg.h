/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:02:41 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 21:02:41 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# define E_2FWARG "Too few arguments"
# define E_2MNARG "Too many arguments"
# define E_ALNUM "String must contain alphanumeric characters"
# define E_ARGREQ "Option requires an argument"
# define E_BADFD "Bad file descriptor"
# define E_EQMISS "Missing equal (`=')"
# define E_ILLOPT "Illegal option"
# define E_NOCMD "Command not found"
# define E_NOENT "No such file or directory"
# define E_NODIR "Not a directory"
# define E_NOENV "Variable not found"
# define E_NOGNL "Cannot get input"
# define E_NOMEM "Not enought space"
# define E_NOOLDPWD "No previous directory"
# define E_NOOPEN "Cannot open file"
# define E_NORGHT "Permission denied"
# define E_NOTERM "Terminal type not defined"
# define E_NOTSET "Varibale not set"
# define E_RAW "Could not switch to non-canonical mode"
# define E_REDIR "Unable to set redirection"
# define E_SEVER "Severe error occured"
# define E_SYNERR "Syntax error near unexpected token"
# define E_TCBASE "Could not access the termcap data base"
# define E_TERMIOS "Could not restore previous structure"
# define E_NOVAR(var) var" not set"

#endif
