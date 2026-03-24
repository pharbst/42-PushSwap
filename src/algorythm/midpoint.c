
# include <push_swap.h>

t_chunk create_job(t_chunk old_job, bool lives_on) {
	t_chunk	new_job;

	if (lives_on == STACK_A) {
		new_job.lives_on = lives_on;
		new_job.min = old_job.pivot;
		new_job.max = old_job.max;
		new_job.pivot = (new_job.min + new_job.max) / 2;
	}
	else if (lives_on == STACK_B) {
		new_job.lives_on = lives_on;
		new_job.min = old_job.min;
		new_job.max = old_job.pivot;
		new_job.pivot = (new_job.min + new_job.max) / 2;
	}
	return (new_job);
}

t_stack *join_op_list(unsigned int to_join, bool just_read) {
	static t_stack	*op_list;
	t_stack			*old_list;

	if (just_read)
		return (op_list);
	if (!op_list)
		op_list = calloc(1000, sizeof(unsigned int));
	if (op_list->size == op_list->capacity) {
		old_list = op_list;
		op_list = calloc(old_list->capacity + 1000, sizeof(unsigned int));
		free(old_list);
	}
	if (to_join != 0)
		op_list->ranked_stack[op_list->size++] = to_join;
	return (NULL);
}

bool top_is_cheaper(t_chunk job, t_stack *stack_a, t_stack *stack_b) {
	if (job.lives_on == STACK_A) {
		// count non pushable at top and bot for stacka
		// return true if top is less then bottom
	}
	else if (job.lives_on == STACK_B) {
		// count non pushable at top and bot for stackb
		// return true if top is less than bottom
	}
}

void rotate_and_push(t_chunk job, t_stack *stack_a, t_stack *stack_b, void *push_fn(t_stack *stack_a, t_stack *stack_b), void *rotate_fn(t_stack *stack)) {
	size_t	to_push;

	if (rotate_fn == &ra || rotate_fn == &rra) {
		// to_push = count_elements_to_push(job, stack_a, stack_b, TOP);
		while (/*is there an element to push?*/ PART_OF(job, TOP(stack_a))) {
			if (TOP(stack_a) < job.pivot && TOP(stack_a) >= job.min)
				join_op_list(push_fn(stack_a, stack_b), false);
			join_op_list(rotate_fn(stack_a), false);
		}
	}
	else if (rotate_fn == &rra || rotate_fn == &rrb) {
		// to_push = count_elements_to_push(job, stack_a, stack_b, BOT)
		while (/*is there an element to push?*/ PART_OF(job, TOP(stack_a))) {
			join_op_list(rotate_fn(stack_a), false);
			if (TOP(stack_a) < job.pivot && TOP(stack_a) >= job.min)
				join_op_list(push_fn(stack_a, stack_b), false);
		}
	}
}

void execute_job(t_chunk job, t_stack *stack_a, t_stack *stack_b) {
	if (job.lives_on == STACK_A) {
		if (top_is_ceaper(job, stack_a, stack_b)) {
			rotate_and_push(job, stack_a, stack_b, &pb, &ra);
			rotate_and_push(job, stack_a, stack_b, &pb, &rra);
		}
		else {
			rotate_and_push(job, stack_a, stack_b, &pb, &rra);
			rotate_and_push(job, stack_a, stack_b, &pb, &ra);
		}
	}
	else if (job.lives_on == STACK_B) {
		if (top_is_cheaper(job, stack_a, stack_b)) {
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
	if (lives_on == STACK_A) {
		if (!issorted(stack_a))
			return;
		while (PART_OF(job, BOT(stack_a))) {
			join_op_list(rra(stack_a), false);
		}
	}
	else if (lives_on == STACK_B) {
		while (PART_OF(job, BOT(stack_b)))
			join_op_list(rrb(stack_b), false);
		while (PART_OF(job, TOP(stack_b)))
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
