/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:57:55 by pharbst           #+#    #+#             */
/*   Updated: 2026/03/17 15:26:35 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// 0 in input can lead to incorrect duplicate error

// Library includes
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

// Data Structs
typedef struct s_int_stack {
	__int64_t	len;
	__int64_t	*raw_stack;
}	t_int_stack;

typedef struct s_stack {
	__int64_t	*ranked_stack;
	__int64_t	size;
	__int64_t	capacity;
	__int64_t	head;
}	t_stack;

typedef struct s_chunk {
	__int64_t	min;
	__int64_t	max;
	__int64_t	pivot;
	bool		lives_on;
}	t_chunk;

// for lives_on parameter
# define STACK_A true
# define STACK_B false

// second index
# define NEXT(stack) (((stack)->head + 1) % (stack)->size)
// last index
# define PREV(stack) ((((stack)->head - 1) + (stack)->size) % (stack)->size)
// top element
# define TOP(stack) ELEMENT(stack, 0)
// bottom element
# define BOT(stack) ELEMENT(stack, -1)
// true if element is part of job
# define PART_OF(job, element) ((element) >= (job).min && (element) <= (job).max)
// true if element is below pivot
# define BELOW_PIVOT(job, element) ((element) >= (job).min && (element) <= (job).pivot)
// true if element above pivot
# define ABOVE_PIVOT(job, element) ((element) > (job).pivot && (element) <= (job).max)
// element at index from head circular protection
# define ELEMENT(stack, index) (stack)->ranked_stack[(((stack)->head + ((index) % (stack)->size)) + (stack)->size) % (stack)->size]
// true if element is part of pushable for the job
# define PUSHABLE(job, element) ((job.lives_on == STACK_A && BELOW_PIVOT(job, element)) || (job.lives_on == STACK_B && ABOVE_PIVOT(job, element)))
// number of elements for the job
# define JOB_SIZE(job) ((job).max - (job).min + 1)

enum operations{
	PA = 1,
	PB,
	SA,
	SB,
	SS,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

t_stack *join_op_list(__int64_t to_join, bool just_read);

// Parsing
char			*strjoin(char const *s1, char const *s2);
char			*ft_str_concat(char **to_concat, char *seperator);
char			*normalize_and_reduce(char *input);
char			*input_parser(char **argv);
__int64_t		count_spaces(char *input);
void			isolate_element(char *input_string, __int64_t *index, int *to_insert, __int64_t *sub_index);
bool			insert_values(t_int_stack *int_stack, char *input_string);
t_int_stack		*create_raw_stack(char *input_string, int num_of_elements);
__int64_t		*ranker(t_int_stack *original);
void			*parse_error(const char *error_msg, void *pointer_to_free, void **pointers_to_free, void *return_value);
bool			_check_sorted(t_int_stack *int_stack);

// Stackoperations
int				sa(t_stack *stack_a);
int				sb(t_stack *stack_b);
int				ss(t_stack *stack_a, t_stack *stack_b);
int				pa(t_stack *stack_a, t_stack *stack_b);
int				pb(t_stack *stack_a, t_stack *stack_b);
int				ra(t_stack *stack_a);
int				rb(t_stack *stack_b);
int				rr(t_stack *stack_a, t_stack *stack_b);
int				rra(t_stack *stack_a);
int				rrb(t_stack *stack_b);
int				rrr(t_stack *stack_a, t_stack *stack_b);

// Algorythm
void			sort(t_chunk job, t_stack *stack_a, t_stack *stack_b);

#endif
