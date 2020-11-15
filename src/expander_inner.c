/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_inner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:25:43 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 17:42:14 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/executor.h"

void	resolve_environ_value(struct s_resolution_context *ctx)
{
	char	letter;
	char	*tmp;
	t_hash	*node;
	int		i;

	i = ctx->i;
	node = ctx->ex->shell->environ;
	if (ctx->t->context->cat[i] == '$')
		i++;
	while (ctx->t->context->cat[i] == '#')
	{
		letter = ctx->t->context->str[i++];
		if (!has_child(node, letter))
			return ;
		node = node->next[letter % 16][letter / 16];
	}
	if (!node->value)
		return ;
	tmp = ft_strdup(node->value);
	assert(tmp != NULL, "resolve_environ_value",
			": Error allocating temporary memory", 1);
	push_to_list(ctx->list_sec, tmp);
}
