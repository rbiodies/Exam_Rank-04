/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:23:18 by rbiodies          #+#    #+#             */
/*   Updated: 2022/03/03 17:28:37 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h>	// EXIT_FAILURE, NULL, malloc, free
# include <unistd.h>	// write
# include <string.h>	// strcmp

# define STDIN		0
# define STDOUT		1
# define STDERR		2

# define TYPE_END	3
# define TYPE_PIPE	4
# define TYPE_BREAK	5

typedef struct s_list
{
	int				size;
	char			**tokens;
	struct s_list	*prev;
	struct s_list	*next;
	int				type;
	int				fd[2];
}	t_list;

int		ft_parser(t_list **list, char **argv);
void	ft_error_fatal(void);
int		ft_strlen(char *str);
int		ft_executor(t_list *list, char **envp);
int		ft_putstr_error(char *str);

#endif