/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 17:42:52 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:30:13 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

char		*protocol_to_string(t_protocol msg)
{
	int		i;
	char	*str;

	str = ft_memalloc(BUF_SIZE);
	if (msg.prefix)
		ft_strcat(str, ":");
	ft_strcat(str, msg.prefix);
	if (msg.prefix)
		ft_strcat(str, " ");
	ft_strcat(str, msg.command);
	if (msg.params)
		ft_strcat(str, " ");
	i = 0;
	while (msg.params && msg.params[i] && msg.params[i][0])
	{
		ft_strcat(str, msg.params[i]);
		if (msg.params[i + 1])
			ft_strcat(str, " ");
		i++;
	}
	if (msg.trailer)
		ft_strcat(str, " :");
	ft_strcat(str, msg.trailer);
	ft_strcat(str, "\r\n\0");
	return (str);
}

void		print_protocol(t_protocol msg)
{
	int		i;

	i = 0;
	ft_printf("prefix: |%s|\n", msg.prefix);
	ft_printf("command: |%s|\n", msg.command);
	if (!msg.params)
		ft_printf("params: (null)\n");
	else
		ft_printf("params:\n");
	while (msg.params && (msg.params)[i])
	{
		ft_printf("\t|%s|\n", (msg.params)[i]);
		i++;
	}
	ft_printf("trailer: |%s|\n", msg.trailer);
}

void		free_protocol(t_protocol msg)
{
	int	i;

	i = 0;
	if (msg.prefix)
		free(msg.prefix);
	if (msg.command)
		free(msg.command);
	if (msg.params)
	{
		while (msg.params[i])
		{
			free(msg.params[i]);
			i++;
		}
		free(msg.params);
	}
	if (msg.trailer)
		free(msg.trailer);
}

t_protocol	fill_protocol(char *prefix, char *cmd, char **params, char *trailer)
{
	t_protocol	msg;

	msg.prefix = prefix;
	msg.command = cmd;
	msg.params = params;
	msg.trailer = trailer;
	return (msg);
}
