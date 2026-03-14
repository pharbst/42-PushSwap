/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:54:38 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/14 19:45:06 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

// Small function to to print error, free a set of pointers, and the return value.
// Usage when returning pointer value
// return (parse_error("Error\n", pointer_to_free, NULL))	// returns NULL
// Usage when returning non pointer value
// return (*parse_error("Error\n", pointer_to_free, &5))	// returns 5
void *parse_error(const char *error_msg, void **pointer_to_free, void *return_value) {
	unsigned int	index;

	write(1, error_msg, strlen(error_msg));

	index = 0;
	while (pointer_to_free && pointer_to_free[index])
		free(pointer_to_free[index++]);
	return (return_value);
}

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

// normalize by changing "\f\n\r\t\v" with ' '.
// reduce double spaces and "+-" before element
// check if digit sequenz is terminated by space
char *normalize_and_reduce(char *input) {
	size_t	index;
	size_t	i;
	char	*result;
	int		neg;

	if (!input)
		return (input);
	index = 0;

	while (input[index]) {
		if (strchr("\t\n\r\f\v", input[index]))
			input[index] = ' ';
		// seems incorrect
		if (input[index] == ' ' && strchr("\f\n\r\t\v ", input[index + 1])) {
			memmove(&input[index], &input[index + 1], strlen(&input[index + 1]) + 1);
			continue;
		}
		neg = 0;
		i = 0;
		while (strchr("+-", input[index + i]))
			if (input[index + i++] == '-')
				neg++;
		if (i) {
			if (neg % 2)
				input[index] = '-';
			else
				input[index] = '+';
			memmove(&input[index + 1], &input[index + i], strlen(&input[index + i]) + 1);
			if (!strchr("0123456789", input[(index++) + 1]))
				return (parse_error("Error\n", (void**)&input, NULL));
		}
		while (strchr("0123456789", input[index]))
			index++;
		if (!strchr("\f\n\r\t\v ", input[index]))
			return (parse_error("Error\n", (void**)&input, NULL));
	}
	result = strdup(input);
	free(input);
	return (result);
}

// char *input_checker_reducer(char *normalized_input) {
	
// }

// Wrapper function creates a normalized string from argv
char *normalize_input(char **argv) {
	char	*normalized_input;

	normalized_input = normalize_and_reduce(ft_str_concat(argv, " "));
	return (normalized_input);
}

// Counts spaces in a string
int count_spaces(char *input) {
	int	index;
	int	counter;

	if (!input)
		return (-1);
	index = 0;
	while (input[index])
		if (input[index++] == ' ')
			counter++;
	return (counter);
}

// creates an integer array of the normalized string
int *create_raw_stack(char *input_string, int num_of_elements) {
	int		*raw_stack;

	raw_stack = calloc(num_of_elements, sizeof(int));
	if (!raw_stack)
		return (raw_stack);
	
}

#include <stdio.h>

int main(int argc, char **argv) {
	char	*normalized;
	int		*array;

	printf("result:|%s|\n", normalize_input(argv));
	return (0);
}

// argument parser creates the stack a from argv
// t_stack *arg_parser(char **argv) {
// 	char	*normal_input;
// 	int		number_of_values;
// 	int		*raw_stack;

// 	normal_input = normalize_input(&argv[1]);	//&argv[1] == argv + 1
// 	number_of_values = count_spaces(normal_input) + 1;
// 	raw_stack = create_raw_stack(normal_input, number_of_values);
// }
