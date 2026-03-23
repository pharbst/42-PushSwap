/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 04:28:58 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/17 05:18:23 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <push_swap.h>

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

void isolate_element(char *input_string, size_t *index, int *to_insert, size_t *sub_index) {
	*sub_index = 0;
	while (strchr("+-0123456789", input_string[*index + *sub_index]))
		(*sub_index)++;
	if (input_string[*index + *sub_index]) {
		input_string[*index + *sub_index] = '\0';
		*to_insert = atoi(&input_string[*index]);
		input_string[*index + *sub_index] = ' ';
	}
	else
		*to_insert = atoi(&input_string[*index]);
}

bool insert_values(t_int_stack *int_stack, char *input_string) {
	size_t	index;
	size_t	sub_index;
	size_t	element;
	size_t	element_dub;
	int		to_insert;

	index = 0;
	element = int_stack->len;
	while (element--) {
		if (input_string[index] == ' ')
			index++;
		isolate_element(input_string, &index, &to_insert, &sub_index);
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
	if (insert_values(int_stack, input_string))
		return (NULL);
	return (int_stack);
}


// produces a new stack with the final required indexes for working midpoint algo
// original stack: [9, 6, 5, 4, 8] -> copy: [5, 3, 2, 1, 4, 0] (0 is treated like '\0' terminater to get rid of a size value)
unsigned int *ranker(t_int_stack *original) {
	unsigned int	*copy;
	size_t			lowest;
	size_t			index;

	copy = calloc(original->len + 1, sizeof(unsigned int));
	if (!copy)
		return (NULL);
	index = 0;
	while (index < original->len) {
		lowest = 0;
		while (lowest < original->len)
			if (original->raw_stack[lowest++] < original->raw_stack[index])
				copy[index]++;
		index++;
	}
	return (free(original->raw_stack), free(original), copy);
}
