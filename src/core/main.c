/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:47 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 16:32:54 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint = 0;

static char	*read_user_input(t_shell_state *state)
{
	char	*input;

	g_sigint = 0;
	input = readline(\
		"\033[38;2;0;175;255m🔹minishell\033[0m\033[38;2;95;215;0m❯\033[0m ");
	if (!input)
	{
		printf("exit\n");
		state->should_exit = true;
		return (NULL);
	}
	if (input[0] == '\0' && g_sigint)
	{
		free(input);
		return (NULL);
	}
	if (input[0] != '\0')
		add_history(input);
	return (input);
}

static bool	parse(char *input, t_shell_state *state, t_token **token, \
					t_node **node)
{
	*token = ft_tokenize(state, NULL, input);
	if (!*token)
		return (false);
	if (ft_check_syntax(*token) == 1)
	{
		ft_free_token(*token);
		return (false);
	}
	*node = ft_node(*token);
	if (preprocess_heredocs(*node, state) != 0)
	{
		ft_free_token(*token);
		ft_free_nodes(*node);
		return (false);
	}
	return (true);
}

static bool	process_input(char *input, t_shell_state *state)
{
	t_token	*token;
	t_node	*node;

	token = NULL;
	node = NULL;
	if (!parse(input, state, &token, &node))
		return (false);
	ignore_signals();
	executor_loop(node, state, token);
	setup_signals();
	close_all_heredoc_fds(node);
	ft_free_nodes(node);
	ft_free_token(token);
	return (true);
}

static void	shell_loop(t_shell_state *state)
{
	char	*input;

	while (!state->should_exit)
	{
		input = read_user_input(state);
		if (!input)
			continue ;
		if (!process_input(input, state))
		{
			free(input);
			continue ;
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_state	state;

	(void)argc;
	(void)argv;
	init_shell_state(&state, envp);
	setup_signals();
	shell_loop(&state);
	cleanup_shell_state(&state);
	rl_clear_history();
	return (state.exit_code);
}
