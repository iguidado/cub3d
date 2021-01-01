/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:59:28 by iguidado          #+#    #+#             */
/*   Updated: 2020/12/31 10:59:37 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void		ft_write_pixmap(t_img *img, int fd)
{
	int i;

	img->img_height--;
	while (img->img_height >= 0)
	{
		i = 0;
		while (i < img->img_width)
		{
			write(fd, &(img->img_data[(img->img_height * img->img_width * 4) + (i * 4)]), 4);
			i++;
		}
		img->img_height--;
	}
}

void		ft_init_bmp_hdr(t_img *img, t_bmp_header *hdr)
{
	hdr->type = 0x4d42;
	hdr->offset = 54;
	hdr->image_size_bytes = (img->img_width * img->img_height * 4);
	hdr->file_size = hdr->offset + hdr->image_size_bytes;
	hdr->dib_header_size = 40;
	hdr->res1 = 0;
	hdr->res2 = 0;
	hdr->width_px = img->img_width;
	hdr->height_px = img->img_height;
	hdr->bpp = 16;
	hdr->compression = 0;
	hdr->num_planes = 1;
	hdr->num_colors = 0;
	hdr->important_colors = 0;
	hdr->x_resolution_ppm = 0;
	hdr->y_resolution_ppm = 0;
	hdr->num_colors = 0;
	hdr->important_colors = 0;
}

void		ft_write_bmp_hdr(int fd, t_bmp_header *hdr)
{
	write(fd, ((char *)&hdr->type), sizeof(hdr->type));
	write(fd, ((char *)&hdr->file_size), sizeof(hdr->file_size));
	write(fd, ((char *)&hdr->res1), sizeof(hdr->res1));
	write(fd, ((char *)&hdr->res2), sizeof(hdr->res2));
	write(fd, ((char *)&hdr->offset), sizeof(hdr->offset));
	write(fd, ((char *)&hdr->dib_header_size), sizeof(hdr->dib_header_size));
	write(fd, ((char *)&hdr->width_px), sizeof(hdr->width_px));
	write(fd, ((char *)&hdr->height_px), sizeof(hdr->height_px));
	write(fd, ((char *)&hdr->num_planes), sizeof(hdr->num_planes));
	write(fd, ((char *)&hdr->bpp), sizeof(hdr->bpp));
	write(fd, ((char *)&hdr->compression), sizeof(hdr->compression));
	write(fd, ((char *)&hdr->image_size_bytes), sizeof(hdr->image_size_bytes));
	write(fd, ((char *)&hdr->x_resolution_ppm), sizeof(hdr->x_resolution_ppm));
	write(fd, ((char *)&hdr->y_resolution_ppm), sizeof(hdr->y_resolution_ppm));
	write(fd, ((char *)&hdr->num_colors), sizeof(hdr->num_colors));
	write(fd, ((char *)&hdr->important_colors), sizeof(hdr->important_colors));
}

void		ft_export_bmp(t_img *img)
{
	int				fd;
	t_bmp_header	hdr;
	unsigned char	*data;

	fd = open("firstimage.bmp", O_CREAT|O_TRUNC|O_RDWR, S_IRWXU);
	ft_init_bmp_hdr(img, &hdr);
	ft_write_bmp_hdr(fd, &hdr);
	ft_write_pixmap(img, fd);
	close(fd);
}
