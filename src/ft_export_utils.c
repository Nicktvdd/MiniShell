/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:23:16 by rrask             #+#    #+#             */
/*   Updated: 2023/08/30 11:30:48 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**envdupyo(char **env) //Create a func that frees and reallocates env
{
	char	**env_copy;
	int		len;
	int		i;

	len = 0;
	while (env[len] != NULL)
		len++;
	env_copy = malloc(sizeof(char *) * (len + 2));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	env_copy[i] = NULL;
	env_copy[i + 1] = NULL;
	return (env_copy);
}

/*Matches the key in the environment, and returns the position.
If it does not exist, it creates it and locates it.*/
int	match_env_key(char *arg, char **env, int index, int len)
{
	int	i;
	char **dupstuff;

	dupstuff = NULL;
	if (!arg || !*env)
		return (-1);
	i = index;
	while ((env[i]) && ft_strncmp(arg, env[i], len) != 0)
		i++;
	if (env[i] == '\0')
	{
		//Needs to fix the segfault
		dupstuff = envdupyo(env);
		dupstuff[i] = ft_strdup(arg);
		dupstuff[i+1] = NULL;
		// env[i] = ft_strdup(arg);
		// env[i + 1] = NULL;
		
		// match_env_key(arg, env, 0, ft_keylen(arg));
	}
		print_export_env(dupstuff);	
	return (i);
}

char	*get_string(char *arg)
{
	char	*str;
	int		start;
	int		end;
	int		len;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	if (!arg)
		return (NULL);
	while (arg[start] && arg[start] != '=')
		start++;
	start++;
	while (arg[end])
		end++;
	len = end - start;
	str = malloc(sizeof(char) * len + 1);
	while (start < end)
	{
		str[i] = arg[start];
		i++;
		start++;
	}
	return (str);
}

char	*get_key(char *arg)
{
	char	*str;
	int		end;
	int		i;

	end = 0;
	i = 0;
	while (arg[end] && arg[end] != '=')
		end++;
	end++;
	str = malloc(sizeof(char) * end + 1);
	if (!str)
		return (NULL);
	while (i < end)
	{
		str[i] = arg[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*combine_str(const char *str, const char *key)
{
	const int	len1 = ft_strlen(key);
	const int	len2 = ft_strlen(str);
	const int	final_size = len1 + len2 + 3;
	char *const	new = ft_calloc(sizeof(char), final_size);

	ft_strlcat(new, key, final_size);
	ft_strlcat(new, str, final_size);
	return (new);
}
