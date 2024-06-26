/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:52:33 by rrask             #+#    #+#             */
/*   Updated: 2023/08/30 14:44:10 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_var(char *arg, char **env, int index, int len)
{
	int	i;

	if (!arg || !*env)
		return (-1);
	i = index;
	while (env[i] && ft_strncmp(arg, env[i], len))
		i++;
	return (i);
}

static	void	remove_env_var(char **e_cpy, int index)
{
	free(e_cpy[index]);
	while (e_cpy[index + 1])
	{
		e_cpy[index] = e_cpy[index + 1];
		index++;
	}
	e_cpy[index] = NULL;
}

char	**ft_unset(char *cmd, char**env)
{
	int		index;
	int		len;

	if (!cmd)
		return (env);
	index = 0;
	len = ft_strlen(cmd);
	index = get_env_var(cmd, env, index, len);
	while (env[index] && env[index][len] != '=')
		index = get_env_var(cmd, env, index + 1, len);
	remove_env_var(env, index);
	return (env);
}
