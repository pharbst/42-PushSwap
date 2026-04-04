
# include <push_swap.h>

void print_stack(t_stack *stack) {
	__int64_t	index;

	index = 0;
	printf("printing stack:\n");
	while (index < stack->size)
		printf("%ld\n", ELEMENT(stack, index++));
}

static inline bool issorted(t_stack *stack) {
	__int64_t	index;

	index = 0;
	while (index < stack->size - 1) {
		if (ELEMENT(stack, index) > ELEMENT(stack, index + 1))
			return (true);
		index++;
	}
	return (false);
}

static inline t_chunk create_job(t_chunk old_job, bool lives_on) {
	t_chunk	new_job;

	if (lives_on == STACK_A) {
		new_job.lives_on = lives_on;
		new_job.min = old_job.pivot + 1;
		new_job.max = old_job.max;
		new_job.pivot = (new_job.min + new_job.max) / 2;
	}
	else {
		new_job.lives_on = lives_on;
		new_job.min = old_job.min;
		new_job.max = old_job.pivot;
		new_job.pivot = (new_job.min + new_job.max) / 2;
	}
	return (new_job);
}

t_stack *join_op_list(__int64_t to_join, bool just_read) {
	static t_stack	op_list;
	t_stack			old_list;

	if (just_read)
		return (&op_list);
	if (!op_list.ranked_stack) {
		op_list.ranked_stack = calloc(1000, sizeof(__int64_t));
		op_list.capacity = 1000;
	}
	if (op_list.size == op_list.capacity) {
		old_list.ranked_stack = op_list.ranked_stack;
		op_list.ranked_stack = calloc(op_list.capacity + 1000, sizeof(__int64_t));
		op_list.capacity += 1000;
		free(old_list.ranked_stack);
	}
	if (to_join != 0)
		op_list.ranked_stack[op_list.size++] = to_join;
	return (NULL);
}

// static inline bool	PUSHABLE(t_chunk job, unsigned int element)
// {
// 	if (job.lives_on == STACK_A)
// 		return (element >= job.min && element <= job.pivot);
// 	else
// 		return (element > job.pivot && element <= job.max);
// }

// here is some logic error
// top is cheaper must find the last pushable from top
// then count the elements that are not pushable on the way back to the top
// then the same from the bottom
bool top_is_cheaper(t_chunk job, t_stack *stack) {
	__int64_t	index;
	__int64_t	not_pushable_top;
	__int64_t	not_pushable_bot;

	not_pushable_top = 0;
	not_pushable_bot = 0;

	index = 0;
	while (PART_OF(job, ELEMENT(stack, index)) && index < stack->size)
		index++;
	while (--index >= 0 && !PUSHABLE(job, ELEMENT(stack, index)))
		continue;
	while (index-- > 0)
		if (!PUSHABLE(job, ELEMENT(stack, index)))
			not_pushable_top++;

	index = 1;
	// printf("-index: %d")
	while (PART_OF(job, ELEMENT(stack, -index)) && index <= stack->size)
		index++;
	while (--index >= 0 && !PUSHABLE(job, ELEMENT(stack, -index)))
		continue;
	while (--index > 0)
		if (!PUSHABLE(job, ELEMENT(stack, -index)))
			not_pushable_bot++;

	if (not_pushable_top <= not_pushable_bot)
		return (true);
	return (false);
}

__int64_t count_elements_to_push(t_chunk job, t_stack *stack, bool top) {
	__int64_t	index;
	__int64_t	pushable_elements;

	print_stack(stack);
	index = 0;
	pushable_elements = 0;
	if (top) {
		while (PART_OF(job, ELEMENT(stack, index)) && index < stack->size) {
			if (PUSHABLE(job, ELEMENT(stack, index)))
				pushable_elements++;
			index++;
		}
	}
	else {
		// index is wrong cause -index is resolving before - 1. so the question is what index do i need here?
		while (PART_OF(job, ELEMENT(stack, index - 1)) && -index - 1 < stack->size) {
			printf("index: %ld\n", -index - 1);
			// printf("ELEMENT: %ld\n", ELEMENT(stack, index - 1));
			if (PUSHABLE(job, ELEMENT(stack, index - 1)))
				pushable_elements++;
			index--;
		}
	}
	return (pushable_elements);
}

void rotate_and_push(t_chunk job, t_stack *stack_a, t_stack *stack_b, int push_fn(t_stack *stack_a, t_stack *stack_b), int rotate_fn(t_stack *stack)) {
	__int64_t	to_push;
	t_stack	*primary;

	if (job.lives_on == STACK_A)
		primary = stack_a;
	else
		primary = stack_b;

	if (rotate_fn == &ra || rotate_fn == &rb) {
		to_push = count_elements_to_push(job, primary, true);
		while (to_push) {
			if (PUSHABLE(job, TOP(primary))) {
				join_op_list(push_fn(stack_a, stack_b), false);
				to_push--;
			}
			else
				join_op_list(rotate_fn(primary), false);
		}
	}
	else if (rotate_fn == &rra || rotate_fn == &rrb) {
		to_push = count_elements_to_push(job, primary, false);
		while (to_push) {
			join_op_list(rotate_fn(primary), false);
			if (PUSHABLE(job, TOP(primary))) {
				join_op_list(push_fn(stack_a, stack_b), false);
				to_push--;
			}
		}
	}
	printf("after rotate and push:\n");
	printf("stack a:\n");
	print_stack(stack_a);
	printf("stack b:\n");
	print_stack(stack_b);
}

void execute_job(t_chunk job, t_stack *stack_a, t_stack *stack_b) {
	if (job.lives_on == STACK_A) {
		if (top_is_cheaper(job, stack_a)) {
			rotate_and_push(job, stack_a, stack_b, &pb, &ra);
			rotate_and_push(job, stack_a, stack_b, &pb, &rra);
		}
		else {
			rotate_and_push(job, stack_a, stack_b, &pb, &rra);
			rotate_and_push(job, stack_a, stack_b, &pb, &ra);
		}
	}
	else if (job.lives_on == STACK_B) {
		if (top_is_cheaper(job, stack_b)) {
			rotate_and_push(job, stack_a, stack_b, &pa, &rb);
			rotate_and_push(job, stack_a, stack_b, &pa, &rrb);
		}
		else {
			rotate_and_push(job, stack_a, stack_b, &pa, &rrb);
			rotate_and_push(job, stack_a, stack_b, &pa, &rb);
		}
	}
}

void direct_sort(t_chunk job, t_stack *stack_a, t_stack *stack_b, bool lives_on) {
	int	index;

	print_stack(stack_a);
	if (lives_on == STACK_A) {
		if (!issorted(stack_a))
			return;
		index = 0;
		while (PART_OF(job, BOT(stack_a)) && index++ < (int)stack_a->size) {
			join_op_list(rra(stack_a), false);
		}
	}
	else if (lives_on == STACK_B) {
		index = 0;
		while (PART_OF(job, BOT(stack_b)) && index++ < (int)stack_b->size)
			join_op_list(rrb(stack_b), false);
		index = 0;
		while (PART_OF(job, TOP(stack_b)) && index++ < (int)stack_b->size)
			join_op_list(pa(stack_a, stack_b), false);
	}
	if (issorted(stack_a))
		join_op_list(sa(stack_a), false);
}

void sort(t_chunk job, t_stack *stack_a, t_stack *stack_b) {
	if (job.lives_on == STACK_A) {
		if (JOB_SIZE(job) > 2) { // chunk is larger than 2 elements
			execute_job(job, stack_a, stack_b);
			sort(create_job(job, STACK_A), stack_a, stack_b);
			sort(create_job(job, STACK_B), stack_a, stack_b);
		}
		else
			direct_sort(job, stack_a, stack_b, STACK_A);
	}
	else if (job.lives_on == STACK_B) {
		if (JOB_SIZE(job) > 2) { // chunk is larger than 2 elements
			execute_job(job, stack_a, stack_b);
			sort(create_job(job, STACK_A), stack_a, stack_b);
			sort(create_job(job, STACK_B), stack_a, stack_b);
		}
		else
			direct_sort(job, stack_a, stack_b, STACK_B);
	}
}
