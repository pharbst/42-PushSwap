/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42.heilbronn.de>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:54:38 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/14 15:26:47 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void *parse_error(const char *error_msg, void **pointer_to_free, void *return_value) {
	unsigned int	index;

	write(1, error_msg, str_len(error_msg));

	index = 0;
	while (pointer_to_free && pointer_to_free[index])
		free(pointer_to_free[index++]);
	return (return_value);
}

char *ft_str_concat(char **to_concat, char *seperator) {
	unsigned int	offset;
	char			*result;
	char			*cached1;
	char			*cached2;

	if (!to_concat)
		return (to_concat);
	offset = 0;
	cached1, result = strdup(to_concat[offset++]);
	while (to_concat[offset]) {
		cached2 = strdup(to_concat[offset++]);
		result = strjoin(cached1, seperator);
		free(cached1);
		cached1 = result;
		result = strjoin(cached1, cached2);
		free(cached1);
		free(cached2);
		cached1 = result;
	}
	return (result);
}

char *remove_double_space_tabs(char *input) {
	size_t	i;
	size_t	len;
	char	*result;

	if (!input)
		return (input);
	len = strlen(input);
	i = 0;
	while (input[i]) {
		if (strchr("\t\n\r\f\v", input[i]))
			input[i] = ' ';
		if (input[i] == ' ' && input[i + 1] == ' ')
			memmove(&input[i + 1], &input[i + 2], (len--) - i - 1);
		else
			i++;
	}
	result = strdup(input);
	free(input);
	return (result);
}

bool inputcheck(char *format) {
	if (!format)
		return (1);
	while (*format) {
		if (!ft_strchr(" -+0123456789", *format))
			return (true);
		format++;
	}
	return (false);
}

char *normalize_input(char **argv) {
	char	*normalized_input;

	normalized_input = remove_double_space_tabs(ft_str_concat(&argv[1], " "));
	if (inputcheck(normalized_input))
		return (parse_error("Error\n", normalized_input, NULL));
	return (normalized_input);
}

t_stack *arg_parser(char **argv) {
	char	*output_string;

}
