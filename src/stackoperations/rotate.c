
#include <push_swap.h>

bool rotate(t_stack *stack) {
	if (stack->size < 2)
		return (true);
	stack->head = NEXT(stack->head, stack->capacity);
	return (false);
}

int ra(t_stack *stack_a) {
	if (rotate(stack_a))
		return (0);
	return (RA);
}

int rb(t_stack *stack_b) {
	if (rotate(stack_b))
		return (0);
	return (RB);
}

int rr(t_stack *stack_a, t_stack *stack_b) {
	if (stack_a->size < 2 || stack_b->size < 2)
		return (0);
	return (rotate(stack_a), rotate(stack_b), RR);
}

