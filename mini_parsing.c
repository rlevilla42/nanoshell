#include <stdio.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_env 
{
	char 		*name;
	char 		*value;
	struct s_env *next;
} t_env;

int	size_dollar(char **cmd, int i, int j)
{
	int		size;
	char	*temp;

	temp = cmd[i];
	size = 0;
	while (temp[j] != 0 && (temp[j] < 9 || temp[j] > 12)
			&& temp[j] != 32) // la a partir du $ dans char **cmd il check jusque la fin du mot tout simplement (faut donc que ce soit differemt de NULL ET whitespace 
	{
		j++;
		size++;
	}
	return (size);
}

int	replace_dollar_by_find_value(char *value, char **cmd, int i, int size)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (cmd[i][j] != '$')
		j++;
	while (value[k] != '\0')
	{
		cmd[i][j] = value[k];
		j++;
		k++;
	}
	return (0);
}

int	find_name_cmd_env(char *temp, t_env *cmd_env, int i, int size)
{
	int		check_exist_flag;
	t_env	*cmd_temp;

	check_exist_flag = 0;
	cmd_temp = cmd_env;
	while (cmd_temp != NULL)
	{
		if (strncmp(temp, cmd_temp.name, size) == 0) // temp exist dans cmd_env.name !
		{
			check_exist_flag = 1;
			replace_dollar_by_find_value(cmd_temp.value, cmd, i, size);
		}
		else
			cmd_temp = cmd_temp->next;
	}
	return (0);
}

int	ft_dollars_parse(char **cmd)
{
	int			i;
	int			j;
	int			size;
	char	*temp;
	t_env	*cmd_env;

	i = 0;
	size = 0;
	k = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '$')
			{
				size = size_dollar(cmd, i, j);
				if (size == 0)
					return (0);
				temp = ft_strndup(&cmd[i][j + 1], size); // dans strndup faire condition ou if size == 0 alors strndup = NULL
													   // la je copie apres le $jusque la fin du mot
				find_name_cmd_env(temp, cmd_env, i, size);
				if (!temp)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i = 0;
	int	j = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
