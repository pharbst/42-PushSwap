/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 04:28:54 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/17 05:17:50 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <push_swap.h>

char *strjoin(char const *s1, char const *s2) {
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

// Concats a list of strings and seperates them with the seperator string, returns an allocated string
char *ft_str_concat(char **to_concat, char *seperator) {
	unsigned int	offset;
	char			*result;
	char			*cached1;
	char			*cached2;

	if (!to_concat)
		return ((char*)to_concat);
	offset = 0;
	result = strdup(to_concat[offset++]);
	cached1 = result;
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

void element_normalization_reduction(char *input, size_t *index) {
	__int64_t	i;
	__int64_t	neg;
	int		error_code;

	neg = 0;
	i = 0;
	error_code = 1;
	// count - signs to reduce
	while (strchr("+-", input[*index + i]))
		if (input[*index + i++] == '-')
			neg++;
	// when i != 0 means at least one sign was counted
	// setting the condition to i > 1 should also work since with just one sign there is nothing to reduce
	if (i > 1) {
		if (neg % 2)
			input[*index] = '-';
		else
			input[*index] = '+';
		memmove(&input[*index + 1], &input[*index + i], strlen(&input[*index + i]) + 1);
		if (!strchr("0123456789", input[((*index)++) + 1]))
			exit(*(int*)parse_error("Error\n", (void*)input, NULL, &error_code));
	}
	else if (i == 1)
		(*index)++;
}

// normalize by changing "\f\n\r\t\v" with ' '.
// reduce double spaces and "+-" before element
// check if digit sequenz is terminated by space
char *normalize_and_reduce(char *input) {
	size_t	index;

	if (!input)
		return (input);
	index = 0;

	while (strchr("\f\n\r\t\v 0123456789+-", input[index]) && index < strlen(input)) {
		// skip digits
		if (strchr("0123456789", input[index])) {
			index++;
			continue;
		}
		// switch tabs etc to white space
		if (strchr("\t\n\r\f\v", input[index]) && input[index])
			input[index] = ' ';
		// seems incorrect
		// yes it is this overwrites the actual whitespace i want to keep
		// solution: memmove dest must be +1 and src +2
		// this works cause the \0 is protecting strlen and we already checked the index + 1 is some char belonging to the str so there must be at least one more byte (index + 2)
		if (input[index] == ' ' && strchr("\f\n\r\t\v ", input[index + 1])) {
			memmove(&input[index + 1], &input[index + 2], strlen(&input[index + 2]) + 1);
			continue;
		}
		// 0 vars to count number - signs
		element_normalization_reduction(input, &index);
		if (input[index] == ' ')
			index++;
		// if (!strchr("\f\n\r\t\v ", input[index]))
		// 	return (parse_error("Error2\n", (void*)input, NULL, NULL));
	}
	if (input[index] && !strchr("\f\n\r\t\v 0123456789+-", input[index]))
		return (parse_error("Error\n", (void*)input, NULL, NULL));
	return (input);
}

char *input_parser(char **argv) {
	char	*normalized_input;

	normalized_input = normalize_and_reduce(ft_str_concat(&argv[1], " "));
	return (normalized_input);
}
