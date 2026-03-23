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

// Library includes
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

// Data Structs
typedef struct s_int_stack {
	size_t	len;
	int		*raw_stack;
}	t_int_stack;

typedef struct s_stack {
	unsigned int	*ranked_stack;
	size_t			size;
	size_t			capacity;
	size_t			head;
}	t_stack;

typedef struct s_chunk {
	unsigned int	min;
	unsigned int	max;
	unsigned int	pivot;
	bool			lives_on;
}	t_chunk;

# define STACK_A true
# define STACK_B false

# define NEXT(i, cap) (((i) + 1) % (cap))
# define PREV(i, cap) (((i) - 1 + (cap)) % (cap))

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

// Function definitions
char			*strjoin(char const *s1, char const *s2);
char			*ft_str_concat(char **to_concat, char *seperator);
char			*normalize_and_reduce(char *input);
char			*input_parser(char **argv);
int				count_spaces(char *input);
void			isolate_element(char *input_string, size_t *index, int *to_insert, size_t *sub_index);
bool			insert_values(t_int_stack *int_stack, char *input_string);
t_int_stack		*create_raw_stack(char *input_string, int num_of_elements);
unsigned int	*ranker(t_int_stack *original);
void			*parse_error(const char *error_msg, void *pointer_to_free, void **pointers_to_free, void *return_value);
bool			_check_sorted(t_int_stack *int_stack);

// Stackoperations
// change return type to return operation enum (int)
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

void			sort(t_chunk job, t_stack *stack_a, t_stack *stack_b);

#endif