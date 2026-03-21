
#include <push_swap.h>

bool rotate(t_stack *stack) {
	if (stack->size < 2)
		return (true);
	stack->head = NEXT(stack->head, stack->capacity);
	return (false);
}

bool ra(t_stack *stack_a) {
	return (rotate(stack_a));
}

bool rb(t_stack *stack_b) {
	return (rotate(stack_b));
}

bool rr(t_stack *stack_a, t_stack *stack_b) {
	if (stack_a->size < 2 || stack_b->size < 2)
		return (true);
	return (rotate(stack_a), rotate(stack_b), false);
}

