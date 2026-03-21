
# include <push_swap.h>

bool push(t_stack *dest, t_stack *src) {
	if (dest->size == dest->capacity || src->size == 0)
		return (true);
	dest->head = NEXT(dest->head, dest->capacity);
	dest->ranked_stack[dest->head] = src->ranked_stack[src->head];
	dest->size++;
	src->head = PREV(src->head, src->capacity);
	src->size--;
	return (false);
}

bool pa(t_stack *stack_a, t_stack *stack_b) {
	if (push(stack_a, stack_b))
		return (true);
	return (false);
}

bool pb(t_stack *stack_a, t_stack *stack_b) {
	if (push(stack_b, stack_a))
		return (true);
	return (false);
}
