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

# define NEXT(i, cap) (((i) + 1) % (cap))
# define PREV(i, cap) (((i) - 1 + (cap)) % (cap))

enum operations{
	PA,
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
char			*normalize_input(char **argv);
int				count_spaces(char *input);
void			isolate_element(char *input_string, size_t *index, int *to_insert, size_t *sub_index);
bool			insert_values(t_int_stack *int_stack, char *input_string);
t_int_stack		*create_raw_stack(char *input_string, int num_of_elements);
unsigned int	*ranker(t_int_stack *original);
void			*parse_error(const char *error_msg, void *pointer_to_free, void **pointers_to_free, void *return_value);
bool			_check_sorted(t_int_stack *int_stack);

#endif