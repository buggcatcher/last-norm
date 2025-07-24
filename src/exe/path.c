/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:01:05 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:01:07 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env *env)
{
	char	*path_var;

	path_var = get_env_value("PATH", env);
	if (!path_var)
		return (NULL);
	return (ft_split(path_var, ':'));
}

char	*search_in_paths(char **paths, char *cmd)
{
	size_t	i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	update_fds_for_next_cmd(t_node *node, int pipe_fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (node->next)
	{
		*prev_fd = pipe_fd[0];
		close(pipe_fd[1]);
	}
}
