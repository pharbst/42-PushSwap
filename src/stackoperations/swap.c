
# include <push_swap.h>

bool swap(t_stack *stack) {
	unsigned int	cache;

	if (stack->size < 2)
		return (true);
	cache = stack->ranked_stack[stack->head];
	stack->ranked_stack[stack->head] = stack->ranked_stack[NEXT(stack->head, stack->capacity)];
	stack->ranked_stack[NEXT(stack->head, stack->capacity)] = cache;
	return (false);
}

int sa(t_stack *stack_a) {
	if (swap(stack_a))
		return (0);
	return (SA);
}

int sb(t_stack *stack_b) {
	if (swap(stack_b))
		return (0);
	return (SB);
}

int ss(t_stack *stack_a, t_stack *stack_b) {
	if (stack_a->size < 2 || stack_b->size < 2)
		return (0);
	return (sa(stack_a), sb(stack_b), SS);
}
