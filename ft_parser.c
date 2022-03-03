/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:22:29 by rbiodies          #+#    #+#             */
/*   Updated: 2022/03/03 17:08:46 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

static int	ft_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL \
	&& strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		i++;
	return (i);
}

static char	*ft_strdup(char *str)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
		ft_error_fatal();
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static int	ft_type(char *arg)
{
	if (arg == NULL)
		return (TYPE_END);
	if (strcmp(arg, "|") == 0)
		return (TYPE_PIPE);
	if (strcmp(arg, ";") == 0)
		return (TYPE_BREAK);
	return (0);
}

static void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*temp;

	temp = *list;
	if (*list == NULL)
		*list = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

int	ft_parser(t_list **list, char **argv)
{
	t_list	*new;
	int		i;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		ft_error_fatal();
	new->size = ft_size(argv);
	new->tokens = (char **)malloc(sizeof(char *) * (new->size + 1));
	if (new->tokens == NULL)
		ft_error_fatal();
	i = 0;
	while (i < new->size)
	{
		new->tokens[i] = ft_strdup(argv[i]);
		i++;
	}
	new->tokens[i] = NULL;
	new->prev = NULL;
	new->next = NULL;
	new->type = ft_type(argv[i]);
	ft_lstadd_back(list, new);
	return (i);
}
