/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:54:38 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/17 05:10:07 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <push_swap.h>

int main(int argc, char **argv) {
	char			*normalized;
	t_int_stack		*int_stack;
	int				elements;
	int				return_value;
	unsigned int	*ranked_stack;

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
			return (*(int*)parse_error("Error stack sorted\n", NULL, NULL, (void*)&return_value));
		printf("check sorted passed\n");
		// switch the actual values with the final required index for working midpoint algo
		ranked_stack = ranker(int_stack);
		size_t index = 0;
		printf("ranked stack:\n");
		while (ranked_stack[index])
			printf("%d\n", ranked_stack[index++]);
	}
	return (0);
}
