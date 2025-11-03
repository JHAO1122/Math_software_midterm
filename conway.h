/** 
* @file conway.h
* @brief Conway game of life header file
* @author TIANJIAHAO
* @date 2025-3-13
*/
/**
 * @brief conway game of life world structure
*/
typedef struct{
    int rows; //The rows of the world
    int cols; //The columns of the world
    int **cells; //life status of every cells in the world, 0 for dead, 1 for alive
} world; 

extern world w; // An extern world structure , with the name "w"

extern int boundary;//An extern variable to control the boundary condition, 1 for periodic boundary condition, 0 for no boundary condition

/**
 * @brief Initialize the world structure with the given rows and columns
 * @param w is the pointer to the world structure
 * @param rows is the number of rows in the world matrix
 * @param cols is the number of columns in the world matrix
 */
void init_world(world *w, int rows, int cols);
/**
 * @brief randomize the world with random values
 */
void randomize_world(world *w);
/**
 * @brief load the world from a file
 * @param filename is the name of the file to load the world from
 * @param w is the pointer to the world structure
 * @param x_0 is the x coordinate of the left-top corner of the world in the file
 * @param y_0 is the y coordinate of the left-top corner of the world in the file
 */
void load_world(const char *filename, world *w, int x_0, int y_0);
/**
 * @brief The function to print the world to the console
 */
void print_world(const world *w);
/**
 * @brief Count the number of neighbours of a cell in the world
 * @param w is the pointer to the world structure
 * @param row is the row index of the cell
 * @param col is the column index of the cell
 * @return returns the number of neighbours of the cell
 */
int count_neighbours(const world *w, int row, int col);
/**
 * @brief compute the next generation of the world
 * @param w is the pointer to the current world structure
 * @param next_w is the pointer to the next world structure to be computed
 */
void next_world(world *w, world *next_w);
/**
 * @brief save the world image to a file
 * @param w is the pointer to the world structure
 * @param filename is the name of the file to save the world image to
 */
void save_worldimage(const world *w,const char *filename);
/**
 * @brief free the memory allocated for the world structure
 */
void free_world(world *w);





