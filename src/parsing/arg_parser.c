/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:54:38 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/17 02:30:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

// Small function to to print error, free a pointer, and/or a set of pointers, and the return value.
// set 2nd and 3rd argument to NULL if not needed.
// Usage when returning pointer value
// return (parse_error("Error\n", pointer_to_free, NULL))	// returns NULL
// Usage when returning non pointer value
// return (*parse_error("Error\n", pointer_to_free, &5))	// returns 5
void *parse_error(const char *error_msg, void *pointer_to_free, void **pointers_to_free, void *return_value) {
	unsigned int	index;

	write(1, error_msg, strlen(error_msg));

	index = 0;
	if (pointer_to_free)
		free(pointer_to_free);
	while (pointers_to_free && pointers_to_free[index])
		free(pointers_to_free[index++]);
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
	printf("input: %s\n", input);
	// exit(0);

	while (strchr("\f\n\r\t\v 0123456789+-", input[index]) && index <= strlen(input)) {
		printf("%zu\n", index);
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
		neg = 0;
		i = 0;
		// count - signs to reduce
		while (strchr("+-", input[index + i]))
			if (input[index + i++] == '-')
				neg++;
		// when i != 0 means at least one sign was counted
		// setting the condition to i > 1 should also work since with just one sign there is nothing to reduce
		if (i > 1) {
			if (neg % 2)
				input[index] = '-';
			else
				input[index] = '+';
			memmove(&input[index + 1], &input[index + i], strlen(&input[index + i]) + 1);
			if (!strchr("0123456789", input[(index++) + 1]))
				return (parse_error("Error1\n", (void*)input, NULL, NULL));
		}
		if (input[index] == ' ')
			index++;
		// if (!strchr("\f\n\r\t\v ", input[index]))
		// 	return (parse_error("Error2\n", (void*)input, NULL, NULL));
	}
	if (input[index] && !strchr("\f\n\r\t\v 0123456789+-", input[index]))
		return (parse_error("Error\n", (void*)input, NULL, NULL));
	result = strdup(input);
	free(input);
	return (result);
}

// Wrapper function creates a normalized string from argv
char *normalize_input(char **argv) {
	char	*normalized_input;

	normalized_input = normalize_and_reduce(ft_str_concat(&argv[1], " "));
	return (normalized_input);
}

// Counts spaces in a string
int count_spaces(char *input) {
	int	index;
	int	counter;

	if (!input)
		return (-1);
	index = 0;
	counter = 0;
	while (input[index])
		if (input[index++] == ' ')
			counter++;
	return (counter);
}

typedef struct s_int_stack {
	size_t	len;
	int		*raw_stack;
}	t_int_stack;

bool insert_values(t_int_stack *int_stack, char *input_string) {
	size_t	index;
	size_t	sub_index;
	int		to_insert;
	size_t	element;
	size_t	element_dub;

	index = 0;
	element = int_stack->len;
	while (element--) {
		if (input_string[index] == ' ')
			index++;
		sub_index = 0;
		while (strchr("+-0123456789", input_string[index + sub_index]))
			sub_index++;
		if (input_string[index + sub_index]) {
			input_string[index + sub_index] = '\0';
			to_insert = atoi(&input_string[index]);
			input_string[index + sub_index] = ' ';
		}
		else
			to_insert = atoi(&input_string[index]);
		element_dub = 0;
		while (element + element_dub < int_stack->len) {
			if (int_stack->raw_stack[element_dub] == to_insert)
				return (true);
			element_dub++;
		}
		int_stack->raw_stack[int_stack->len - element - 1] = to_insert;
		index += sub_index;
	}
	return (false);
}

// creates an integer array of the normalized string
t_int_stack *create_raw_stack(char *input_string, int num_of_elements) {
	t_int_stack	*int_stack;

	// allocate
	int_stack = calloc(1, sizeof(t_int_stack));
	if (!int_stack)
		return (NULL);
	int_stack->raw_stack = calloc(num_of_elements, sizeof(int));
	if (!int_stack->raw_stack)
		return (free(int_stack), NULL);
	int_stack->len = num_of_elements;

	// loop over string and extract one element convert it to int and put it into int_stack->raw_stack
	// make it a function
	insert_values(int_stack, input_string);
	return (int_stack);
}

bool _check_sorted(t_int_stack *int_stack) {
	size_t	index;

	if (int_stack->len < 2)
		return (true);
	index = 1;
	while (index < int_stack->len)
		if (int_stack->raw_stack[index] < int_stack->raw_stack[(index++) - 1])
			return (false);
	return (true);
}

#include <stdio.h>

int main(int argc, char **argv) {
	char		*normalized;
	t_int_stack	*int_stack;
	int			elements;
	int			return_value;

	if (argc > 2) {
		// normalize and reduce input
		normalized = normalize_input(argv);
		printf("result:|%s|\n", normalized);
		// int_stack creation
		elements = count_spaces(normalized) + 1;
		int_stack = create_raw_stack(normalized, elements);
		while (elements--)
			printf("%d\n", int_stack->raw_stack[int_stack->len - elements - 1]);
		// validity check
		return_value = 1;
		if (_check_sorted(int_stack))
			return (parse_error("Error stack sorted\n", NULL, NULL, (void*)&return_value));
		printf("check sorted passed\n");
	}
	return (0);
}

// argument parser creates the stack a from argv
// t_stack *arg_parser(char **argv) {
// 	char	*normalized_input;
// 	int		number_of_values;
// 	int		*raw_stack;

// 	normalized_input = normalize_input(&argv[1]);	//&argv[1] == argv + 1
// 	number_of_values = count_spaces(normalized_input) + 1;
// 	raw_stack = create_raw_stack(normalized_input, number_of_values);
// }
