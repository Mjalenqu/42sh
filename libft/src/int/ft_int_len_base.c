/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_int_len_base.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 11:00:05 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/03 16:53:04 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_intlen_base(int n, int base)
{
	if (n < 0)
	{
		if (n / base)
			return (2 + ft_intlen_base(-(n / base), base));
		else
			return (1 + ft_intlen_base((n / base), base));
	}
	else if (n < base)
		return (1);
	return (1 + ft_intlen_base(n / base, base));
}
