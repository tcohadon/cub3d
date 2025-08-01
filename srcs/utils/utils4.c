#include "../../include/cub3d.h"

static bool	validate_single_value(const char *line, int *i)
{
	int	value;

	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == ',' || line[*i] == '\0')
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	if (!ft_isdigit(line[*i]))
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	value = ft_atoi(&line[*i]);
	if (value < 0 || value > 255)
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	return (true);
}

bool	validate_values(const char *line)
{
	int	i;
	int	value_count;

	i = 0;
	value_count = 0;
	while (line[i])
	{
		if (!validate_single_value(line, &i))
			return (false);
		value_count++;
		while (line[i] == ' ')
			i++;
		if (line[i] == ',')
			i++;
	}
	if (value_count != 3)
		return (fd_printf(2, "Error\nInvalid color format: %s\n", line), false);
	return (true);
}
