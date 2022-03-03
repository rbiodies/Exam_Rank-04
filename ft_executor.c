/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbiodies <rbiodies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:27:34 by rbiodies          #+#    #+#             */
/*   Updated: 2022/03/03 14:28:34 by rbiodies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

static void	ft_child(t_list *temp, char **envp)
{
	if (temp->type == TYPE_PIPE && dup2(temp->fd[STDOUT], STDOUT) < 0)
		ft_error_fatal();
	if (temp->prev && temp->prev->type == TYPE_PIPE \
	&& dup2(temp->prev->fd[STDIN], STDIN) < 0)
		ft_error_fatal();
	if (execve(temp->tokens[0], temp->tokens, envp) < 0)
	{
		ft_putstr_error("error: cannot execute ");
		ft_putstr_error(temp->tokens[0]);
		ft_putstr_error("\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static int	ft_parent(t_list *temp, pid_t pid, int pipe_open)
{
	int	status;
	int	ret;

	waitpid(pid, &status, 0);
	if (pipe_open == 1)
	{
		close(temp->fd[STDOUT]);
		if (temp->type == TYPE_END || temp->type == TYPE_BREAK)
			close(temp->fd[STDIN]);
	}
	if (temp->prev && temp->prev->type == TYPE_PIPE)
		close(temp->prev->fd[STDIN]);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}

static int	ft_run_cmd(t_list *temp, char **envp)
{
	int		pipe_open;
	pid_t	pid;
	int		ret;

	ret = 1;
	pipe_open = 0;
	if (temp->type == TYPE_PIPE \
	|| (temp->prev && temp->prev->type == TYPE_PIPE))
	{
		if (pipe(temp->fd))
			ft_error_fatal();
		pipe_open = 1;
	}
	pid = fork();
	if (pid < 0)
		ft_error_fatal();
	else if (pid == 0)
		ft_child(temp, envp);
	else
		ret = ft_parent(temp, pid, pipe_open);
	return (ret);
}

int	ft_executor(t_list *list, char **envp)
{
	t_list	*temp;
	int		ret;

	ret = 0;
	temp = list;
	while (temp != NULL)
	{
		if (strcmp(temp->tokens[0], "cd") == 0)
		{
			if (temp->tokens[1] == NULL)
				return (ft_putstr_error("error: cd: bad arguments\n"));
			else if (chdir(temp->tokens[1]))
			{
				ft_putstr_error("error: cd: cannot change directory to ");
				ft_putstr_error(temp->tokens[1]);
				return (ft_putstr_error("\n"));
			}
		}
		else
			ret = ft_run_cmd(temp, envp);
		temp = temp->next;
	}
	return (ret);
}
