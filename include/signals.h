/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 13:03:30 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/30 16:02:19 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	init_signals_before_rl(struct sigaction *sa);
void	init_signals_after_rl(struct sigaction *sa);

#endif