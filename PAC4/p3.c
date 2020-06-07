#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>

#define WIDTH 40  // row
#define HEIGHT 30 // col
#define MOVING_AVERAGE_AMMOUNT 9

float average(int collum, float matrix[][HEIGHT]);
float movingAverage(int collum, int row, float *matrix);
void initMatrix(int width, int height, float matrix[width][height]);
void initVector(int width, float *vector);

int main(int argc, char **argv)
{
  int i, j, k;
  float matrix[WIDTH][HEIGHT];
  float matrixMove[WIDTH - MOVING_AVERAGE_AMMOUNT][HEIGHT];
  float vectorAverage[HEIGHT];

  // inits
  printf("Initialize the main matrix array\n");
  k = 0;
  for(i = 0; i < WIDTH; i++)
  {
    for(j = 0; j < HEIGHT; j++)
    {
      //matrix = rand()*(float)1.1;
      matrix[i][j] = 1.0f + (float)k++;
    }
  }

  printf("Initialize the average vector\n");
  initVector(WIDTH, vectorAverage);
  
  printf("Initialize the moving average vector\n");
  initMatrix(WIDTH - MOVING_AVERAGE_AMMOUNT, HEIGHT, matrixMove);

  // for each colum, get a average value
  printf("Get averages of a row for each column\n");
  for(i = 0; i < WIDTH; i++)
  {
    vectorAverage[i] = average(i, matrix);
    printf("Average of vector %d is %f\n",i,vectorAverage[i]);
  }

  // for each colum for each row get the moving average
  printf("Get moving averages for each row for each column\n");
  for(i = 9; i < WIDTH; i++)
  {
    for(j = 0; j < HEIGHT; j++)
    {
      // https://www.tutorialspoint.com/cprogramming/c_pointer_to_an_array.htm
      // https://www.studytonight.com/c/pointers-with-array.php
      matrixMove[i][j] = movingAverage(i,j, &matrix[0][0]);
      printf("Moving average from point %d, %d is %f\n",i,j,matrixMove[i][j]);
    }
  }

}

float average(int collum, float matrix[][HEIGHT])
{
  int i;
  float average_ = 0.0f;
  for(i = 0; i < HEIGHT; i++)
  {
    average_ += matrix[collum][i];
  }
  average_ = average_ / HEIGHT;
  return average_;
}

float movingAverage(int collum, int row, float *matrix)
{
  int i;
  float average = 0.0f;
  // It is legal to use array names as constant pointers, and vice versa. Therefore, *(balance + 4) is a legitimate way of accessing the data at balance[4].
  // a[i][j] is the same as *(*(a + i) + j)
  // *((arr+i*n) + j)

  for(i = MOVING_AVERAGE_AMMOUNT; i > 0; i--)
  {
    //average += matrix[collum-i][row];
    average += *((matrix+collum*WIDTH) + i);
    //printf("MovingAverage adding value to now %f\n", average);
  }
  average = average / MOVING_AVERAGE_AMMOUNT;
  return average;
}

void initMatrix(int width, int height, float matrix[width][height])
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
