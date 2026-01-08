/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_.bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 09:30:15 by jait-chd          #+#    #+#             */
/*   Updated: 2026/01/08 11:26:43 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zero_protocol.h"

static int	headers_complete(t_data *d)
{
    return (d->tex_no && d->tex_so && d->tex_we && d->tex_ea
        && d->floor[0] != -1 && d->ceiling[0] != -1);
}

static int	parse_headers(t_data *d, char **lines, int *idx)
{
    while (lines[*idx] && !is_map_line(lines[*idx]))
    {
        if (parse_header_line(d, lines[*idx]))
            return (1);
        (*idx)++;
    }
    if (!headers_complete(d))
        return (err("Missing identifiers"), 1);
    if (!lines[*idx])
        return (err("Map missing"), 1);
    return (0);
}

static void	free_content_and_lines(char *content, char **lines)
{
    ft_free(content);
    free_lines(lines);
}

static void	parse_exit(t_data *data, char *content, char **lines)
{
    free_content_and_lines(content, lines);
    free_data(data);
    exit(1);
}

void	parse_bar_file(t_data *data, char *file)
{
    char	*content;
    char	**lines;
    int		idx;

    content = read_file_content(file);
    if (!content)
        exit(err("Read failed") && 1);
    lines = split_lines(content);
    if (!lines)
        exit(err("Split failed") && 1);
    idx = 0;
    if (parse_headers(data, lines, &idx))
        parse_exit(data, content, lines);
    if (build_map(data, lines, idx))
        parse_exit(data, content, lines);
    if (validate_map(data))
        parse_exit(data, content, lines);
    free_content_and_lines(content, lines);
}