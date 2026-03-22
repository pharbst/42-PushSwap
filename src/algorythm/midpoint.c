
# include <push_swap.h>

// recursive logic per push/rotate phase this should help handling the chunk fragmentation
// Order to check: first check stack a as long as stack a is not sorted create subchunks or sort small threshold directly
// when creating subchunk the chunk gets split in subchunk remainder chunk
// sub chunk creation on stack a has higher prio than entire stack b

// to increase hit chance during initial push / rotate phase (from a to b)

// use "job queue" and create 2 jobs at once first job is the one with the larger chunk second is on top -> resulting in: top job push b and second top job (job with larger chunk) push b + rotate 
// this gives room for a lot of operation saves because stack a gets rotated a lot and the rotate can then be done using rr rotate both stacks at once

void partition(t_chunk chunk, t_stack *stack_a, t_stack *stack_b) {

}

// chunk initial state:
// chunk.min = 1
// chunk.max = num of elements (highest element)
// chunk.pivot = (chunk.min + chunk.max) \ 2

// concrete example:
// chunk.min = 1
// chunk.max = 500
// chunk.pivot = 250.5 // 250 is enough
// chunk.lives_on = STACK_A

// creates a subchunk from a to b with the lower 250 elements
// create a chunk struct with old pivot + (old pivot /2) = 375 lives on STACK_A
// call sort with that chunk struct
// create a chunk struct with old pivot / 2 = 125 lives on STACK_B
// 

t_int_stack *sort(t_chunk chunk, t_stack *stack_a, t_stack *stack_b) {
	if (issorted(stack_a)) {
		// if stack_a threshold or stack_a chunk threshold
		if (stack_a->size < 4 /*|| stack_a top chunk element count < 3*/)
			sort_a(stack_a);
			// sort directly
		// else
		else
			// partition(chunk data struct, stack_a, stack_b)
			// create subchunk
		sort(stack_a, stack_b);
		// sort()
	}
	else if (stack_b->size) {
		// check top "chunk" threshold
			// push / sort directly
		// else
			// create subchunk
		// sort()
	}
}
