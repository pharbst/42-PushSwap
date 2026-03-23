
# include <push_swap.h>

bool rev_rotate(t_stack *stack) {
	if (stack->size < 2)
		return (true);
	stack->head = PREV(stack->head, stack->capacity);
	return (false);
}

int rra(t_stack *stack_a) {
	if (rev_rotate(stack_a))
		return (0);
	return (RRA);
}

int rrb(t_stack *stack_b) {
	if (rev_rotate(stack_b))
		return (0);
	return (RRB);
}

int rrr(t_stack *stack_a, t_stack *stack_b) {
	if (stack_a->size < 2 || stack_b->size < 2)
		return (0);
	return (rev_rotate(stack_a), rev_rotate(stack_b), RRR);
}

