#include "main.h"

/**
 * check_alias - check alias functuion
 * @neww: arguments list
 * 
 * 
 * Return: success (name of alias) - error null
 */
char *check_alias(char *neww)
{
	alias *tmp = get_alias_list();

	while (tmp != NULL)
	{
		if (_strcmp(neww, tmp->new_command) == 0)
			return (tmp->new_command);

		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * execute_alias -check if alias exists
 * @args: args list
 * @main: value
 * 
 * 
 * Return: success: name of alias - error: null
 */
int execute_alias(char *main, char **args)
{
	if (execve(main, args, environ) == -1)
	{
		fprintf(stderr, "%s: No such file or directory\n", args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * create_keyvalue_pair - create alias
 * @name: arg to be initialized into name_command
 * @alias_list: pointer to alias list
 * @equals: pointer to '=' in the args
 * 
 * 
 * Return: the new node
 */
int create_keyvalue_pair(alias **alias_list, char *name, char *equals)
{
	alias *list_copy = *alias_list;
	int i, b = 0, j,  value_length;
	char *cmd_main, *cmd_new = malloc((strlen(name) + 1) * sizeof(char));

	while (name[b] != '=')
	{
		cmd_new[b] = name[b];
		b++;
	}

	*equals = '\0';
	equals = equals + 1;

	printf("now allocating memory for value_command equals = %s\n", equals);
	value_length = strlen(equals) - strspn(equals, "'\"");
	cmd_main = malloc(sizeof(char) * (value_length + 1));

	printf("now entering initialization loop\n");
	for (i = 0, j = 0; equals[i] != '\0'; i++)
	{
		if (equals[i] != '\'' && equals[i] != '"')
		{
			cmd_main[j] = equals[i];
			j++;
		}
	}
	cmd_main[j] = '\0';

	printf("before add name = %s and value = %s\n", cmd_new, cmd_main);
	*alias_list = add_alias(&list_copy, cmd_new, cmd_main);

	return (0);
}
/**
 * add_alias - add alias to the list
 * @new: name of new command
 * @main: name of main command
 * @head: pointer to list of aliases
 * 
 * 
 * Return: list head
 */
alias *add_alias(alias **head, char *new, char *main)
{
	alias *node_new = NULL;
	alias *tmp;

	node_new->main_command = malloc(sizeof(char) * 50);
	node_new->new_command = malloc(sizeof(char) * 50);

	node_new->main_command = strdup(main);
	node_new->new_command = strdup(new);
	node_new->next = NULL;

	if (*head == NULL)
	{
		*head = node_new;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
		{
			if (strcmp(new, tmp->new_command) == 0)
			{
				free(tmp->main_command);
				tmp->main_command = strdup(main);
				free(node_new->main_command);
				free(node_new->new_command);
				return (*head);
			}
			tmp = tmp->next;
		}
		tmp->next = node_new;
	}
	printf("added alias to list successfully\n");

	while (tmp != NULL)
	{
		printf("alias is %s='%s'\n", tmp->new_command, tmp->main_command);
		tmp = tmp->next;
	}
	return (*head);
}
/**
 * print_alias_list - print alias list
 * @head: pointer to a list of aliases
 * 
 * 
 * Return: none
 */
int print_alias_list(alias *head)
{
	alias *tmp = head;

	while (tmp != NULL)
	{
		printf("alias %s=\'%s\'\n", tmp->new_command, tmp->main_command);
		tmp = tmp->next;
	}
	printf("print list successfully\n");

	return (0);
}
