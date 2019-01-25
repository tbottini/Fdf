
#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include "mlx.h"
#include <math.h>
# define SCREEN_X 800
# define SCREEN_Y 1200

# define PI 3.1415926535
//key value
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_R 15
# define KEY_F 3

//mouse key value
# define WHEEL_UP 5
# define WHEEL_DOWN 6
# define RIGHT_MOUSE_BUTTON 1
# define LEFT_MOUSE_BUTTON 2

//color
# define	WHITE	color(255, 255, 255)
# define	BLUE	color(0, 0, 255)
# define	RED		color(255, 0, 0)
# define	GREEN	color(0, 255, 0)
# define	YELLOW	color(255, 255, 0)
# define	PURPLE	color(255, 0, 255)
# define	CYAN	color(0, 255, 255)
# define	BLACK	color(0, 0, 0)

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
	unsigned char	size_x;
	unsigned char	size_y;
}					t_rmesh;

typedef	struct 		s_world_obj
{
	t_vector3		*position;
	t_vector3		*rotation;
}					t_world_obj;

typedef struct s_mlx_data
{
	void 			*mlx;
	void 			*win;
	void 			*img;
	unsigned int 	*screen;
	t_world_obj		*cam;
	t_rmesh			*wires;
	int 			fov;
}					t_mlx_data;
//structure maillage ? vector2 pos screen 4 t_maillage
//strucutre maillageObject ? tab vector3 localPointPosition
//sturcutre worldObject ? maillageObject || Object + 3vct3 posrotsca
//pour l'edition

int				input_fdf(int key, t_mlx_data *fdf);
int 			start_point(t_rmesh *wires, t_world_obj *cam, unsigned int *screen, int fov);
unsigned int 	color(unsigned char r, unsigned char g, unsigned char b);
void			pixel_img(unsigned int *screen, t_vector2 vct, unsigned int color);
void			trait(unsigned int *screen, t_vector2 vct1, t_vector2 vct2, unsigned int col);
t_vector2		*vct2_new(int x, int y);
t_vector2		*vct2_value(t_vector2 *vct, int x, int y);
void			pixel_img2(unsigned int *screen, int x, int y, unsigned int color);
void			trait2(unsigned int *screen, int x1, int y1, int x2, int y2, unsigned int col);
void			vct2_print(t_vector2 vct);
t_vector3		*vct3_new(int x, int y, int z);
t_vector3		*vct3_value(t_vector3 *vct, int x, int y, int z);
void			vct3_print(t_vector3 vct);
t_vector3		*vct3_add(t_vector3 *vct1, t_vector3 *vct2);
t_vector3		*model_to_world(t_vector3 local_pos, t_vector3 trans, t_vector3 rot, int sca);
t_vector2		*world_to_view(t_vector2 *cursor, t_vector3 rot_cam, t_vector3 pos_cam, t_vector3 w_pos, float fov);
t_vector3		*vct3_mul(t_vector3 *vct1, int mul);
t_vector3		*vct3_cpy(t_vector3 *vct1, t_vector3 *vct2);
t_vector3		*vct3_negate(t_vector3 *vct);
t_vector3		*vct3_rotation(t_vector3 *pos, t_vector3 rot);
t_rmesh			*fdf_parseur(int ac, char **av);
int  sub(int a, int b);
int add(int a, int b);
int divi(int a, int b);
int mul(int a, int b);
t_vector3		*vct3_calc(t_vector3 *vct1, t_vector3 *vct2, int(*f)(int,int));
#endif

