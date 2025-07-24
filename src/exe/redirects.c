/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:01:15 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:01:17 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redirection_file(t_redir *redir)
{
	int	fd;

	if (redir->type == TK_REDIR_IN_2)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == TK_REDIR_OUT_3)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TK_REDIR_APPEND_4)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	return (fd);
}

static int	get_redirection_target(int type)
{
	if (type == TK_REDIR_IN_2 || type == TK_HEREDOC_5)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int	get_redirection_fd(t_redir *redir)
{
    int fd;

    if (redir->type == TK_HEREDOC_5)
    {
        if (redir->fd == -2)
            return 0;
        fd = redir->fd;
    }
    else
    {
        fd = open_redirection_file(redir);
        if (fd < 0)
            return (printf("minishell: %s: No such file or directory\n", \
                            redir->filename), 1);
    }
    return fd;
}

static int	process_redirection(t_redir *redir)
{
    int	fd;
    int	target;

    fd = get_redirection_fd(redir);
    if (fd == 0 || fd == 1)
        return fd;
    target = get_redirection_target(redir->type);
    if (switch_fd(fd, target) != 0)
    {
        close(fd);
        redir->fd = -1;
        return (1);
    }
    close(fd);
    redir->fd = -1;
    return (0);
}

int	apply_redirects(t_redir *redirs)
{
	while (redirs)
	{
		if (process_redirection(redirs) != 0)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

