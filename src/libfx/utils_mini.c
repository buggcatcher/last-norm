/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:39:41 by mailinci          #+#    #+#             */
/*   Updated: 2025/07/24 17:39:47 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	char	*c;
	size_t	i;

	i = ft_strlen_v(s);
	c = (char *)safe_alloc(i + 1, sizeof(char), "ft_strdup");
	if (c != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			c[i] = s[i];
			i++;
		}
		c[i] = '\0';
		return ((char *)c);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*final;
	int		i;
	int		j;

	i = ft_strlen_v(s1);
	j = ft_strlen_v(s2);
	final = (char *)safe_alloc(i + j + 1, sizeof(char), "ft_strjoin");
	if (!final)
		return (NULL);
	final[i + j] = '\0';
	while (j > 0)
	{
		j--;
		final[i + j] = s2[j];
	}
	while (i > 0)
	{
		i--;
		final[i] = s1[i];
	}
	return (final);
}

char	*ft_append_char(char *s, char c)
{
	int		len;
	char	*new;
	int		i;

	if (!s)
	{
		new = safe_alloc(2, sizeof(char), "ft_append_char_empty");
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	len = ft_strlen_v(s);
	new = (char *)safe_alloc(len + 2, sizeof(char), "ft_append_char");
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(s);
	return (new);
}
