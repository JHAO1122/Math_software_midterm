# include "conway.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ncurses.h>
# include <ctype.h>
# include <unistd.h>
# include <time.h>

#pragma pack(push, 1)
struct BMPfileheader
{
    unsigned short bftype;
    unsigned int bfsize;
    unsigned short bfreserved1;
    unsigned short bfreserved2;
    unsigned int bfoffbits;
};
struct BMPinfoheader
{
    unsigned int bisize;
    int biwidth;
    int biheight;
    unsigned short bipplanes;
    unsigned short bitcount;
    unsigned int bicompression;
    unsigned int bisizeimage;
    int bixpelspermeter;
    int biypelspermeter;
    unsigned int bicolor_used;
    unsigned int bicolor_important;
};
#pragma pack(pop)

world w;
int boundary = 1;

void init_world(world *w, int rows, int cols){
    w->rows = rows;
    w->cols = cols;
    w->cells = (int **)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++){
        w->cells[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++){
            w->cells[i][j] = 0;
        }
    }
}

void randomize_world(world *w){
    for(int i = 0; i < w->rows; i++){
        for(int j = 0; j < w->cols; j++){
            w->cells[i][j] = rand() % 2;
        }
    }
}
void load_world(const char *filename, world *w, int x_0, int y_0)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File not found.\n");
        exit(1);
    }
    char temp[500];
    int t = 0;
    if(fp != NULL)
    {
        char line[500];
        while(fgets(line,sizeof(line),fp))
        {
            if(line[0] == '#') continue;
            else if(line[0] == 'x')
            {
                sscanf(line, "x = %d, y = %d", &w->rows, &w->cols);
            }
            else if(isdigit(line[0]) || line[0] == 'b' || line[0] == 'o' || line[0] == '!' || line[0] == '$')
            {
                for(size_t i = 0; i < strlen(line); i++)
                {
                    temp[t++] = line[i];        
                }
            }
        }
    }
    temp[t] = '\0';
    int x = x_0;
    int y = y_0;
    for(size_t i = 0; i < strlen(temp); i++)
    {
        int count = 0;
        if(isdigit(temp[i]))
        {
            while(isdigit(temp[i]))
            {
                count = count * 10 + temp[i] - '0';
                i++;
            }
        } 
        if(temp[i] == 'b')
        {
            if(count == 0) count++;
            else
            {
                for(int j = 0; j < count; j++)
                {
                    w->cells[x][y] = 0;
                    x++;
                }
            }    
        }
        if(temp[i] == 'o')
        {
            if(count == 0) count++;
            else
            {
                for(int j = 0; j < count; j++)
                {
                    w->cells[x][y] = 1;
                    x++;
                }
            }
        }
        if(temp[i] == '!')
        {
            break;
        }   
        if(temp[i] == '$')
        {
            y++;
            x = x_0;
        }
    }
}
void print_world(const world *w){
    for(int i = 0; i < w->rows; i++){
        for(int j = 0; j < w->cols; j++){
            if(w->cells[i][j] == 1) mvaddch(i,j,'*');
            else mvaddch(i,j,' ');
        }
    }
}

int count_neighbours(const world *w, int row, int col){
    int count_num = 0;
    for(int i = -1; i <= 1; i++)
    {
        for(int j =-1; j <= 1; j++)
        {
            if(i == 0 && j == 0) continue;
            if(boundary == 0)
            {
                if(row + i < 0 || row + i >= w->rows || col + j < 0 || col + j >= w->cols) continue; 
                if(w->cells[row + i][col + j] == 1) count_num++;
            }
            else if(boundary == 1)
            {        
                int _row = (row + i + w->rows) % w->rows;
                int _col = (col + j + w->cols) % w->cols;
                if(w->cells[_row][_col] == 1) count_num++;
            }    
        }
    }
    return count_num;
}

void next_world(world *w, world *next_w)
{
    next_w->rows = w->rows;
    next_w->cols = w->cols;
    next_w->cells = (int **)malloc(w->rows * sizeof(int *));
    for(int i = 0; i < w->rows; i++){
        next_w->cells[i] = (int *)malloc(w->cols * sizeof(int *));
        for(int j = 0; j < w->cols; j++)
        {
            int num_neighbours = count_neighbours(w,i,j);
            if(w->cells[i][j] == 0 && num_neighbours == 3) next_w->cells[i][j] = 1;
            else if(w->cells[i][j] == 1 && num_neighbours < 2) next_w->cells[i][j] = 0;
            else if(w->cells[i][j] == 1 && num_neighbours > 3) next_w->cells[i][j] = 0;
            else next_w->cells[i][j] = w->cells[i][j];
        }
    }
    for(int i = 0; i < w->rows; i++){
        for(int j = 0; j < w->cols; j++){
            w->cells[i][j] = next_w->cells[i][j];
        }
    }
    for(int i = 0; i < w->rows; i++){
        free(next_w->cells[i]);
    }
    free(next_w->cells);
}

void save_worldimage(const world *w,const char *filename)
{
    FILE *fp = fopen(filename,"wb");
    if(fp == NULL) return;  
    int row_size = w->cols * 3;
    int filler = (4 - (row_size % 4)) % 4;
    row_size += filler;
    #pragma pack(push, 1)
    struct BMPfileheader fileheader;
    struct BMPinfoheader infoheader;
    fileheader.bftype = 0x4d42;
    fileheader.bfsize = 54 + row_size * w->rows; 
    fileheader.bfreserved1 = 0;
    fileheader.bfreserved2 = 0;
    fileheader.bfoffbits = 54;
    infoheader.bisize = 40;
    infoheader.biwidth = w->cols;
    infoheader.biheight = w->rows;
    infoheader.bipplanes = 1;
    infoheader.bitcount = 24;
    infoheader.bicompression = 0;
    infoheader.bisizeimage = row_size * w->rows;
    infoheader.bixpelspermeter = 0;
    infoheader.biypelspermeter = 0;
    infoheader.bicolor_used = 0;
    infoheader.bicolor_important = 0;
    #pragma pack(pop)
    fwrite(&fileheader, sizeof(fileheader), 1, fp);
    fwrite(&infoheader, sizeof(infoheader), 1, fp);
    for(int i = w->rows - 1; i >= 0; i--)
    {
        for(int j = 0; j < w->cols; j++)
        {
            if(w->cells[i][j] == 1)
            {
                unsigned char color[3] = {255, 255, 255};
                fwrite(color, 3, 1, fp);
            }
            else
            {
                unsigned char color[3] = {0, 0, 0};
                fwrite(color, 3, 1, fp);
            }
        } 
        for(int k = 0; k < filler; k++) fputc(0, fp);     
    }
    fclose(fp);
}
void free_world(world *w){
    for(int i = 0;i < w->rows; i++){
        free(w->cells[i]);
    }
    free(w->cells);
}