
# include <push_swap.h>

bool swap(t_stack *stack) {
	unsigned int	cache;

	if (stack->size < 2)
		return (true);
	cache = stack->ranked_stack[stack->head];
	stack->ranked_stack[stack->head] = 
}