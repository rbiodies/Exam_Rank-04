/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:35:27 by rbiodies          #+#    #+#             */
/*   Updated: 2022/03/03 17:28:07 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_putstr_error(char *str)
{
	if (str != NULL)
		write(STDERR, str, ft_strlen(str));
	return (1);
}

void	ft_error_fatal(void)
{
	ft_putstr_error("error: fatal\n");
	exit(EXIT_FAILURE);
}

static void	ft_lstclear(t_list *list)
{
	t_list	*temp;
	int		i;

	while (list != NULL)
	{
		temp = list->next;
		i = 0;
		while (list->tokens[i] != NULL)
		{
			free(list->tokens[i]);
			i++;
		}
		free(list->tokens);
		free(list);
		list = temp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_list	*list;
	int		ret;

	ret = 0;
	i = 1;
	list = NULL;
	if (argc > 1)
	{
		while (i < argc)
		{
			if (strcmp(argv[i], ";") == 0)
			{
				i++;
				continue ;
			}
			i += ft_parser(&list, &argv[i]);
			i++;
		}
		if (list != NULL)
			ret = ft_executor(list, envp);
		ft_lstclear(list);
	}
	return (ret);
}
