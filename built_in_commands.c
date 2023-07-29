#include "main.h"


/**
 * my_cd - point of entry
 * @args: args passed
 * @line_num: command count
 *
 * Return: void
 */
int my_cd(char **args, int line_num)
{
	char *dir_new, *dir_old, cwd[1024];
	char *cd_err = cd_error(args);

	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
		dir_new = _getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
		dir_new = _getenv("OLDPWD");
	else
		dir_new = args[1];
	if (dir_new == NULL)
	{
		perror("Directory not found");
		return (1);
	}
	dir_old = _getenv("PWD");
	if (my_setenv("OLDPWD", dir_old, 1) != 0)
	{
		perror("Could not set OLDPWD environment variable");
		return (1);
	}
	if (chdir(dir_new) != 0)
	{
		print_error(args[0], cd_err, line_num);
		free(cd_err);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Could not get current directory");
		free(cd_err);
		return (1);
	}
	if (my_setenv("PWD", cwd, 1) != 0)
	{
		perror("Could not set PWD environment variable");
		free(cd_err);
		return (1);
	}
	free(cd_err);
	return (0);
}

/**
 * my_env - point of entry
 *
 * Return: void
 */
int my_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}

	return (0);
}

/**
 * my_unsetenv - Entry point
 * @args: command and arguments
 * Return: Always 0 (Success)
 */
int my_unsetenv(char **args)
{
	int i, j;
	char *name = args[1];
	int len = _strlen(name);

	if (args[1] == NULL || args[2] != NULL)
	{
		perror("Invalid argument");
		return (1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}
			break;
		}
	}

	return (0);
}
/**
 * my_setenv - Entry point
 * @name: env var name
 * @value: environment value
 * @overwrite: replace variable
 *
 * Return: Always 0 (Success)
 */
int my_setenv(const char *name, const char *value, int overwrite)
{
	int i, j;
	int len;
	char *enviro;

	if (name == NULL || value == NULL)
	{
		perror("Invalid arguments");
		return (1);
	}
	len = _strlen(name) + _strlen(value) + 2;
	enviro = malloc(len);
	if (enviro == NULL)
	{
		perror("Memory allocation failed");
		return (1);
	}
	for (i = 0; name[i] != '\0'; i++)
	{
		enviro[i] = name[i];
	}
	enviro[i] = '=';

	for (j = 0; value[j] != '\0'; j++)
	{
		enviro[i + j + 1] = value[j];
	}
	enviro[i + j + 1] = '\0';
	if (overwrite == 0 && _getenv(name) != NULL)
	{
		free(enviro);
		return (0);
	}
	if (putenv(enviro) != 0)
	{
		perror("Setting environment variable failed");
		free(enviro);
		return (1);
	}
	free(enviro);
	return (0);
}


/**
 * my_exit - Entry point
 * @args: command and arguments
 * Return: Always 0 (Success)
 */
int my_exit(char **args)
{
	unsigned int exit_status = 0;
	unsigned int max = 1 << (sizeof(int) * 8 - 1);
	int i = 0, len = 10;

	if (args[1] != NULL)
	{
		if (args[1][0] == '+')
		{
			i = 1;
			len++;
		}

		if (args[1][i] != '\0')
		{
			while (args[1][i] != '\0')
			{
				if (i <= len && args[1][i] >= '0' && args[1][i] <= '9')
				{
					exit_status = (exit_status * 10) + (args[1][i] - '0');
				}
				else
				{
					printf("Invalid exit status.\n");
					return (-1);
				}
				i++;
			}

			if (exit_status > max - 1)
			{
				printf("Invalid exit status.\n");
				return (-1);
			}
		}
	}
	_freeargs(args);
	exit(exit_status);
}
