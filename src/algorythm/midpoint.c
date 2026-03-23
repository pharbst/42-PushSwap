
# include <push_swap.h>

// recursive logic per push/rotate phase this should help handling the chunk fragmentation
// Order to check: first check stack a as long as stack a is not sorted create subchunks or sort small threshold directly
// when creating subchunk the chunk gets split in subchunk remainder chunk
// sub chunk creation on stack a has higher prio than entire stack b

// to increase hit chance during initial push / rotate phase (from a to b)

// use "job queue" and create 2 jobs at once first job is the one with the larger chunk second is on top -> resulting in: top job push b and second top job (job with larger chunk) push b + rotate 
// this gives room for a lot of operation saves because stack a gets rotated a lot and the rotate can then be done using rr rotate both stacks at once

// void partition(t_chunk chunk, t_stack *stack_a, t_stack *stack_b) {

// }

// chunk initial state:
// chunk.min = 1
// chunk.max = num of elements (highest element)
// chunk.pivot = (chunk.min + chunk.max) \ 2

// concrete example:
// chunk.min = 0
// chunk.max = 500
// chunk.pivot = 250
// chunk.lives_on = STACK_A

// creates a subchunk from a to b with the lower 250 elements
// create a chunk struct with old pivot + (old pivot /2) = 375 lives on STACK_A
// call sort with that chunk struct
// create a chunk struct with old pivot / 2 = 125 lives on STACK_B

// at start of sort create 2nd chunk struct to increase hit rate
// put both chunk structs onto stack where 2nd chunk struct is top
// this only until stack a has less than 4 elements and only during initial push phase
// later pop them one by one and process them in "reverse order"


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

// just_read flag to true if you want to get just the pointer to the op list
// if false to_join and op_list are joined and NULL is returned
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
	// join operation to stack
	return (NULL);
}

void execute_job() {

}

void direct_sort() {

}

void sort(t_chunk job, t_stack *stack_a, t_stack *stack_b) {
	if (job.lives_on == STACK_A) {
		if (job.max - job.min > 1) { // is chunk larger than 2 elements
			execute_job(job, stack_a, stack_b);
			sort(create_job(job, STACK_A), stack_a, stack_b);
			sort(create_job(job, STACK_B), stack_a, stack_b);
		}
		else
			direct_sort(stack_a, stack_b);
			// direct sort
	}
	else if (job.lives_on == STACK_B) {
		if (job.max - job.min > 1) { // chunk is larger than 2 elements
			// push above pivot
			execute_job(job, stack_a, stack_b);
			sort(create_job(job, STACK_A), stack_a, stack_b);
			sort(create_job(job, STACK_B), stack_a, stack_b);
		}
		else {
			// push chunk to a
			execute_job(job, stack_a, stack_b);
			sort(create_job(job, STACK_A), stack_a, stack_b);
		}
	}
}
