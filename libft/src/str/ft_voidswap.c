/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_voidswap.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 15:05:36 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/03 15:05:58 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_voidswap(void *s, void *d)
{
	unsigned char	c;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s;
	b = (unsigned char *)d;
	c = *a;
	*a = *b;
	*b = c;
}
