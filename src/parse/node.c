/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:53:25 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:53:30 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_token_type(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TK_S_QUOTE_6 || \
			token->type == TK_D_QUOTE_7 || \
			token->type == TK_DOLLAR_8 || \
			token->type == TK_WORD_0);
}

t_node	*ft_node(t_token *token)
{
	t_token	*start;
	t_token	*tmp;
	t_node	*new;
	t_node	*head;

	head = NULL;
	start = token;
	tmp = token;
	while (tmp)
	{
		while (tmp && tmp->type != TK_PIPE_1)
			tmp = tmp->next;
		new = ft_get_node(start);
		if (!new)
			return (ft_free_nodes(head));
		if (new->token && is_cmd_token_type(new->token))
			new->argv = ft_build_argv(start, tmp);
		if (!new->argv && new->redirs == NULL)
			return (ft_free_nodes(new));
		ft_create_node(&head, new);
		ft_advance_tokens(&start, &tmp);
	}
	head = prune_dummy_nodes(head);
	return (head);
}

static t_token	*ft_find_first_cmd_token(t_token *token)
{
	t_token	*tmp;
	t_token	*first_cmd_token;

	tmp = token;
	first_cmd_token = NULL;
	while (tmp && tmp->type != TK_PIPE_1)
	{
		if (tmp->type >= TK_REDIR_IN_2 && tmp->type <= TK_HEREDOC_5)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		else if (tmp->type == TK_WORD_0 || tmp->type == TK_S_QUOTE_6 || \
				tmp->type == TK_D_QUOTE_7 || tmp->type == TK_DOLLAR_8)
		{
			first_cmd_token = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	return (first_cmd_token);
}

static void	ft_process_redirections(t_node *node)
{
	t_token	*tmp;

	tmp = node->token;
	while (tmp && tmp->type != TK_PIPE_1)
	{
		if (tmp->type >= TK_REDIR_IN_2 && tmp->type <= TK_HEREDOC_5)
		{
			ft_add_redirection(node, tmp);
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

t_node	*ft_get_node(t_token *token)
{
	t_node	*new;
	t_token	*first_cmd_token;

	new = safe_alloc(1, sizeof(t_node), "create_node");
	if (!new)
		return (NULL);
	new->redirs = NULL;
	new->token = token;
	new->argv = NULL;
	new->dummy_on = 0;
	new->next = NULL;
	first_cmd_token = ft_find_first_cmd_token(token);
	ft_process_redirections(new);
	if (first_cmd_token)
		new->token = first_cmd_token;
	else
	{
		if (new->redirs)
			mark_node_as_dummy(new);
	}
	return (new);
}
