/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:58:51 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 15:58:55 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Signal handling functions */
void	handle_sigint(int sig);
void	setup_signals(void);
void	disable_signals(void);
void	ignore_signals(void);

#endif
