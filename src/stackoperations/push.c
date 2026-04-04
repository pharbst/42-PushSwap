
# include <push_swap.h>

bool push(t_stack *dest, t_stack *src) {
	if (dest->size == dest->capacity || src->size == 0)
		return (true);
	dest->size++;
	memmove(&ELEMENT(dest, 1), &ELEMENT(dest, 0), (dest->size - dest->head) * sizeof(__int64_t));
	ELEMENT(dest, 0) = ELEMENT(src, 0);
	memmove(&ELEMENT(src, 0), &ELEMENT(src, 1), (src->size - src->head - 1) * sizeof(__int64_t));
	src->size--;
	src->head %= src->size;
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
