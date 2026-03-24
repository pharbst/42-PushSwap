
# include <push_swap.h>

bool push(t_stack *dest, t_stack *src) {
	if (dest->size == dest->capacity || src->size == 0)
		return (true);
	dest->head = NEXT(dest);
	dest->ranked_stack[dest->head] = src->ranked_stack[src->head];
	dest->size++;
	src->head = PREV(src);
	src->size--;
	return (false);
}

int pa(t_stack *stack_a, t_stack *stack_b) {
	if (push(stack_a, stack_b))
		return (0);
	return (PA);
}

int pb(t_stack *stack_a, t_stack *stack_b) {
	if (push(stack_b, stack_a))
		return (0);
	return (PB);
}
