/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:57:47 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/23 14:38:26 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static int	count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	*alloc_word(const char *s, char c, size_t current_word, size_t size)
{
	char	*word;
	size_t	i;
	size_t	start;
	size_t	end;

	end = 0;
	while (current_word--)
	{
		while (s[end] == c && s[end])
			end++;
		start = end;
		while (s[end] != c && s[end])
			end++;
	}
	if (size != 0)
		word = (char *)malloc(sizeof(char) * (size + 1));
	else
		word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**split_size(const char *s, char c, size_t size)
{
	char		**array;
	size_t		nb_word;
	size_t		current_word;

	current_word = 0;
	nb_word = count_word(s, c);
	array = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (array == NULL)
		return (NULL);
	while (++current_word <= nb_word)
	{
		array[current_word - 1] = alloc_word(s, c, current_word, size);
		if (array[current_word - 1] == NULL)
		{
			while (current_word--)
				free(array[current_word]);
			free(array);
			return (NULL);
		}
	}
	array[current_word - 1] = NULL;
	return (array);
}
