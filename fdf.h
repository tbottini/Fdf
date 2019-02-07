
#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include "mlx.h"
#include <math.h>
#include "/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"

# define SCREEN_X 800
# define SCREEN_Y 800

# define PI 3.1415926535

# define KEY_W 		13
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
# define KEY_CTRL 	256
# define KEY_SHIFT 	257
# define KEY_ESC	53
# define WHEEL_UP 	5
# define WHEEL_DOWN 6
# define RM_BUTTON	1
# define LM_BUTTON	2

# define WHITE		color(255, 255, 255)
# define BLUE		color(0, 0, 255)
# define RED		color(255, 0, 0)
# define GREEN		color(0, 255, 0)
# define YELLOW		color(255, 255, 0)
# define PURPLE		color(255, 0, 255)
# define CYAN		color(0, 255, 255)
# define BLACK		color(0, 0, 0)
# define BEIGE		color(245, 245, 210)
# define PCHARRIE 	color(125, 0, 50)
# define FRATARDI 	color(75, 0, 15)

typedef struct 		s_vector2
{
	int x;
	int y;
}					t_vector2;

typedef struct		s_vector3
{
	float x;
	float y;
	float z;
}					t_vector3;

typedef struct 		s_rmesh
{
	char 			**wires;
	int 			size_x;
	int 			size_y;
	float			scale;
}					t_rmesh;

typedef	struct 		s_world_obj
{
	t_vector3		*position;
	t_vector3		*rotation;
}					t_world_obj;

typedef struct 		s_camera
{
	t_vector3 		*position;
	t_vector3		*rotation;
	int 			size_x;
	int 			size_y;
	int 			fov;
	char			proj;
}					t_camera;

typedef struct 		s_mlx_data
{
	void 			*mlx;
	void 			*win;
	void 			*img;
	unsigned int 	*screen;
	t_camera		*cam;
	t_rmesh			*wires;
	t_vector2 		*mouse_pos;
}					t_mlx_data;

int 			draw_wires(t_mlx_data *fdf);
unsigned int 	color(unsigned char r, unsigned char g, unsigned char b);
void			pixel_img(t_mlx_data *fdf, t_vector2 vct, unsigned int color);
void			trait(t_mlx_data *fdf, t_vector2 vct1, t_vector2 vct2, unsigned int col);

t_vector2		*vct2_new(int x, int y);
t_vector2		*vct2_value(t_vector2 *vct, int x, int y);
void			vct2_print(t_vector2 vct);

t_vector3		*vct3_new(int x, int y, int z);
t_vector3		*vct3_value(t_vector3 *vct, int x, int y, int z);
void			vct3_print(char *info, t_vector3 vct);
t_vector3		*vct3_add(t_vector3 *vct1, t_vector3 *vct2);
t_vector3		*vct3_mul(t_vector3 *vct1, int mul);
t_vector3		*vct3_cpy(t_vector3 *vct1, t_vector3 *vct2);
t_vector3		*vct3_negate(t_vector3 *vct);
t_vector3		*vct3_rotation(t_vector3 *pos, t_vector3 rot);
t_vector3		*vct3_calc(t_vector3 *vct1, t_vector3 *vct2, int(*f)(int,int));

int				sub(int a, int b);
int				add(int a, int b);
int				divi(int a, int b);
int				mul(int a, int b);

t_vector3		*model_to_world(t_vector3 local_pos, t_vector3 trans, t_vector3 rot, int sca);
t_vector2		*world_to_view(t_vector2 *cursor, t_camera cam, t_vector3 w_pos, float scale);

t_rmesh			*fdf_parseur(int ac, char **av);
void			rmesh_del(t_rmesh *rmesh);

int				mouse_motion(int x, int y, t_mlx_data *fdf);
void			ajust_cam(t_mlx_data *fdf);
int				input_fdf(int key, t_mlx_data *fdf);
void			print_input(t_mlx_data *fdf);
#endif

