#include "main.h"

/**
 * my_alias - handles the command if it is alias
 * @args: list of commands
 *
 * Return: 0 (success alwaus)
 */
int my_alias(char **args)
{
	int i = 1;
	alias *copy_of_list = get_alias_list();
	char *equals;

	if (args[i] == NULL)
	{
		if (copy_of_list == NULL)
			printf("NULL\n");
		else
		{
			printf("wants to enter print alias list\n");
			print_alias_list(copy_of_list);
		}
		return (0);
	}
	for (i = 1; args[i] != NULL; i++)
	{
		equals = strchr(args[i], '=');
		copy_of_list = get_alias_list();
		if (equals == NULL)
		{
			while (copy_of_list != NULL)
			{
				if (strcmp(args[i], copy_of_list->main_command) == 0)
				{
					print_alias_list(copy_of_list);
					break;
				}
				copy_of_list = copy_of_list->next;
			}
		}
		else
		{
			printf("create keyvalue_pair function args = %s \n", args[i]);
			create_keyvalue_pair(&copy_of_list, args[i], equals);
		}
	}
	return (0);
}
/**
 * get_alias - returns the alias list
 *
 * Return: alias list
 */
alias *get_alias_list(void)
{
	alias *al = NULL;

	return (al);
}
