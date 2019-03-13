/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:28:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/03/13 21:23:37 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include "/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"

# define SCREEN_X 800
# define SCREEN_Y 800
# define PI 3.1415926535
# define KEY_W 		13
# define KEY_Y		16
# define KEY_U 		32
# define KEY_I 		34
# define KEY_H 		4
# define KEY_J		38
# define KEY_K		40
# define KEY_A 		0
# define KEY_S 		1
# define KEY_D 		2
# define KEY_Q 		12
# define KEY_E 		14
# define KEY_R 		15
# define KEY_F 		3
# define KEY_P		35
# define KEY_O		31
# define KEY_U		32
# define KEY_I		34
# define KEY_T 		17
# define KEY_G		5
# define KEY_CTRL 	256
# define KEY_SHIFT 	257
# define KEY_ESC	53
# define WHEEL_UP 	5
# define WHEEL_DOWN 6
# define RM_BUTTON	1
# define LM_BUTTON	2
# define WHITE		rgb_color(255, 255, 255)
# define BLUE		rgb_color(0, 0, 255)
# define RED		rgb_color(255, 0, 0)
# define GREEN		rgb_color(0, 255, 0)
# define YELLOW		rgb_color(255, 255, 0)
# define PURPLE		rgb_color(255, 0, 255)
# define CYAN		rgb_color(0, 255, 255)
# define BLACK		rgb_color(0, 0, 0)
# define BEIGE		rgb_color(245, 245, 210)
# define PCHARRIE 	rgb_color(125, 0, 50)
# define FRATARDI 	rgb_color(75, 0, 15)

typedef struct		s_col
{
	unsigned int	c;
}					t_col;

typedef struct		s_vct2
{
	int				x;
	int				y;
}					t_vct2;

typedef struct		s_vct3
{
	float			x;
	float			y;
	float			z;
}					t_vct3;

typedef struct		s_rmesh
{
	char			**wires;
	int				x;
	int				y;
	float			scale;
}					t_rmesh;

typedef	struct		s_world_obj
{
	t_vct3			*position;
	t_vct3			*rotation;
}					t_world_obj;

typedef struct		s_camera
{
	t_vct3			*position;
	t_vct3			*rotation;
	int				x;
	int				y;
	int				fov;
	char			proj;
}					t_camera;

typedef struct		s_color_stock
{
	t_col			color1;
	t_col			color2;
	int				color_s1;
	int				color_s2;
	t_col			color_stock[11];
}					t_color_stock;

typedef struct		s_mlx_data
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned		*screen;
	t_camera		*cam;
	t_rmesh			*wires;
	t_vct2			*mouse_pos;
	int				scale_z;
	t_color_stock	cs;
}					t_mlx_data;

t_vct2				*vct2_new(int x, int y);
t_vct2				*vct2_value(t_vct2 *vct, int x, int y);
void				vct2_print(t_vct2 vct);
t_vct3				*vct3_new(int x, int y, int z);
t_vct3				*vct3_value(t_vct3 *vct, int x, int y, int z);
void				vct3_print(char *info, t_vct3 vct);
t_vct3				*vct3_add(t_vct3 *vct1, t_vct3 *vct2);
t_vct3				*vct3_mul(t_vct3 *vct1, int mul);
t_vct3				*vct3_cpy(t_vct3 *vct1, t_vct3 *vct2);
t_vct3				*vct3_negate(t_vct3 *vct);
t_vct3				*vct3_rotation(t_vct3 *pos, t_vct3 rot);
t_vct3				*vct3_calc(t_vct3 *vct1, t_vct3 *vct2,
							int(*f)(int, int));
int					rmesh_draw(t_mlx_data *fdf);
void				rmesh_del(t_rmesh *rmesh);
t_camera			*camera_new(int fov, int size_x, int size_y);
void				camera_ajust(t_mlx_data *fdf);
void				camera_del(t_camera *cam);
int					sub(int a, int b);
int					add(int a, int b);
int					divi(int a, int b);
int					mul(int a, int b);
void				color_stock_set(t_color_stock *cs);
int					input_color(t_color_stock *cs, int key);
t_col				cs_color(t_color_stock cs, char color);
t_mlx_data			*mlx_data_get(char *screen_name, int fov, int ac,
							char **av);
void				mlx_data_close(t_mlx_data *fdf);
void				fdf_refresh(t_mlx_data *fdf);
unsigned int		rgb_color(unsigned char r, unsigned char g,
							unsigned char b);
void				pixel_img(t_mlx_data *fdf, t_vct2 vct,
							t_col color);
void				trait(t_mlx_data *fdf, t_vct2 vct1, t_vct2 vct2,
							t_col col);
t_vct3				*model_to_world(t_vct3 local_pos, t_vct3 trans, t_vct3 rot,
							int sca);
t_vct2				*world_to_view(t_vct2 *cursor, t_camera cam,
							t_vct3 w_pos, float scale);
t_rmesh				*fdf_parseur(int ac, char **av);
int					mouse_motion(int x, int y, t_mlx_data *fdf);
void				ajust_cam(t_mlx_data *fdf);
int					input_fdf(int key, t_mlx_data *fdf);
void				print_input(t_mlx_data *fdf);
int					wall_nb(int nb, int min, int max);

#endif
