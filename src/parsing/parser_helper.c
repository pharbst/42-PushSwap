/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 04:29:00 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/17 04:43:55 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <push_swap.h>

// Small function to to print error, free a pointer, and/or a set of pointers, and the return value.
// set 2nd and 3rd argument to NULL if not needed.
// Usage when returning pointer value
// return (parse_error("Error\n", pointer_to_free, NULL))	// returns NULL
// Usage when returning non pointer value
// return (*parse_error("Error\n", pointer_to_free, &5))	// returns 5
void *parse_error(const char *error_msg, void *pointer_to_free, void **pointers_to_free, void *return_value) {
	unsigned int	index;

	if (error_msg)
		write(1, error_msg, strlen(error_msg));

	index = 0;
	if (pointer_to_free)
		free(pointer_to_free);
	while (pointers_to_free && pointers_to_free[index])
		free(pointers_to_free[index++]);
	return (return_value);
}

// check if stack is already sorted
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
