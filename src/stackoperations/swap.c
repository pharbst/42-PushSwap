
# include <push_swap.h>

bool swap(t_stack *stack) {
	unsigned int	cache;

	if (stack->size < 2)
		return (true);
	cache = stack->ranked_stack[stack->head];
	stack->ranked_stack[stack->head] = stack->ranked_stack[NEXT(stack->head, stack->capacity)];
	stack->ranked_stack[NEXT(stack->head, stack->capacity)] = cache;
}

bool sa(t_stack *stack_a) {
	return (swap(stack_a));
}

bool sb(t_stack *stack_b) {
	return (swap(stack_b));
}

bool ss(t_stack *stack_a, t_stack *stack_b) {
	if (stack_a->size < 2 || stack_b->size < 2)
		return (true);
	return (sa(stack_a), sb(stack_b), false);
}
