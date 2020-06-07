#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>

#define WIDTH 40  // row
#define HEIGHT 30 // col
#define MOVING_AVERAGE_AMMOUNT 9

void average(int collum);
void movingAverage(int collum, int row, float **matrix);
void initMatrix(int width, int height, float *matrix);
void initVector(int width, float *vector);

int main(int argc, char **argv)
{
  int i, j, k;
  float matrix[WIDTH][HEIGHT];
  float matrixMove[WIDTH - MOVING_AVERAGE_AMMOUNT][HEIGHT];
  float vectorAverage[HEIGHT];

  // inits
  k = 0;
  for(i = 0; i < WIDTH; i++)
  {
    for(j = 0; j < HEIGHT; j++)
    {
      //matrix = rand()*(float)1.1;
      matrix[i][j] = 1.0f + (float)k++;
    }
  }
  initVector(WIDTH, vectorAverage);
  initMatrix(WIDTH, HEIGHT, matrixMove);

  // for each colum, get a average value
  for(i = 0; i < WIDTH; i++)
  {
    vectorAverage[i] = average(i,matrix);
  }

  // for each colum for each row get the moving average
  for(i = 9; i < WIDTH; i++)
  {
    for(j = 0; j < HEIGHT; j++)
    {
      matrixMove[i][j] = movingAverage(i,j,matrix);
    }
  }
}

float average(int collum, float *matrix)
{
  int i;
  float average = 0.0f;
  for(i = 0; i < HEIGHT; i++)
  {
    average += matrix[collum][i];
  }
  average = average / HEIGHT;
  return average;
}

float movingAverage(int collum, int row, float *matrix)
{
  int i;
  float average = 0.0f;
  for(i = MOVING_AVERAGE_AMMOUNT; i < 0; i++)
  {
    average += matrix[collum-i][row];
  }
  average = average / MOVING_AVERAGE_AMMOUNT;
  return average;
}

void initMatrix(int width, int height, float *matrix)
{
  int i, j = 0;
  for(i = 0; i < width; i++)
  {
    for(j = 0; j < height; j++)
    {
      matrix[i][j] = 0.0f;
    }
  }
}

void initVector(int width, float *vector)
{
  int i = 0;
  for(i = 0; i < width; i++)
  {
    vector[i] = 0.0f;
  }
}
