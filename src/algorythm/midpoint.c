
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

bool element_to_push_top(t_chunk job, t_stack *stack) {
	size_t	index;

	index = 0;
	while (PART_OF(job, )) {

	}
}

bool element_to_push_bot(t_chunk job, t_stack *stack) {

}

// rewrite function
// count non pushable elements to the last element to push from both directions
// if top non pushable elements < bot pushable elements start with top
// otherwise start with bottom
void execute_job(t_chunk job, t_stack *stack_a, t_stack *stack_b) {
	if (job.lives_on == STACK_A) {
		while (/*is there an element to push?*/ PART_OF(job, TOP(stack_a))) {
			if (TOP(stack_a) < job.pivot && TOP(stack_a) >= job.min)
				join_op_list(pb(stack_a, stack_b), false);
			join_op_list(ra(stack_a), false);
		}
		while (/*is there an element to push?*/ PART_OF(job, BOT(stack_a))) {
			join_op_list(rra(stack_a), false);
			if (TOP(stack_a) < job.pivot && TOP(stack_a) >= job.min)
				join_op_list(pb(stack_a, stack_b), false);
		}
	}
	else if (job.lives_on == STACK_B) {
		while (/*is there an element to push?*/ PART_OF(job, TOP(stack_b))) {
			if (TOP(stack_b) <= job.max && TOP(stack_b) > job.pivot)
				join_op_list(pa(stack_a, stack_b), false);
			join_op_list(rb(stack_b), false);
		}
		while (/*is there an element to push?*/ PART_OF(job, BOT(stack_b))) {
			join_op_list(rrb(stack_b), false);
			if (TOP(stack_b) <= job.max && TOP(stack_b) > job.pivot)
				join_op_list(pa(stack_a, stack_b), false);
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
