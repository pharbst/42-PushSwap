/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:33:50 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/14 16:27:30 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int main(int argc, char **argv) {
	char			*normalized;
	t_int_stack		*int_stack;
	int				elements;
	int				elements_cpy;
	int				return_value;
	unsigned int	*ranked_stack;
	int				ret_val;
	t_chunk			init_job;
	t_stack			*stack_a;
	t_stack			*stack_b;

	ret_val = 1;
	if (argc > 2) {
		// normalize and reduce input
		normalized = input_parser(argv);
		// printf("result:|%s|\n", normalized);
		// int_stack creation
		elements = count_spaces(normalized) + 1;
		elements_cpy = elements;
		int_stack = create_raw_stack(normalized, elements);
		if (!int_stack)
			return (*(int*)parse_error("Error dublicate element\n", NULL, NULL, &ret_val));
		// while (elements--)
		// 	printf("%d\n", int_stack->raw_stack[int_stack->len - elements - 1]);
		elements = elements_cpy;
		// validity check
		return_value = 1;
		if (_check_sorted(int_stack))
			return (*(int*)parse_error("Error stack sorted\n", NULL, NULL, (void*)&return_value));
		// printf("check sorted passed\n");
		// switch the actual values with the final required index for working midpoint algo
		ranked_stack = ranker(int_stack);
		size_t index = 0;
		// printf("ranked stack:\n");
		// while (elements--)
		// 	printf("%d\n", ranked_stack[index++]);
		// printf("starting to sort...\n");
		init_job.lives_on = STACK_A;
		init_job.max = elements_cpy -1;
		init_job.min = 0;
		init_job.pivot = (init_job.max + init_job.min) / 2;
		stack_a = calloc(1, sizeof(t_stack));
		stack_b = calloc(1, sizeof(t_stack));
		stack_a->capacity = elements_cpy;
		stack_a->size = elements_cpy;
		stack_a->ranked_stack = ranked_stack;
		stack_b->capacity = elements_cpy;
		stack_b->ranked_stack = calloc(elements_cpy + 1, sizeof(unsigned int));
		sort(init_job, stack_a, stack_b);
		t_stack *operations = join_op_list(0, true);
		index = 0;
		while (index < operations->size)
		{
			unsigned int op = operations->ranked_stack[index];

			if (op == PA)
				printf("pa\n");
			else if (op == PB)
				printf("pb\n");
			else if (op == SA)
				printf("sa\n");
			else if (op == SB)
				printf("sb\n");
			else if (op == SS)
				printf("ss\n");
			else if (op == RA)
				printf("ra\n");
			else if (op == RB)
				printf("rb\n");
			else if (op == RR)
				printf("rr\n");
			else if (op == RRA)
				printf("rra\n");
			else if (op == RRB)
				printf("rrb\n");
			else if (op == RRR)
				printf("rrr\n");

			index++;
		}
	}
	return (0);
}
