#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;
#define W 9
#define H 9
#define EMPTY 0
#define POPULATED 1
void show(int A[][W + 2])
{
   // system("cls");
   string mark[2] = {"口", "X"};
   int i, j;
   cout << "      ";
   for (i = 1; i < W + 1; i++)
      cout << "[" << setw(3) << i << "]";
   cout << endl;
   for (i = 1; i < H + 1; i++)
   {
      cout << "[" << setw(3) << i << "]";
      for (j = 1; j < W + 1; j++)
         cout << setw(5) << mark[A[i][j]];
      cout << endl;
   }
}
void read(string filename, int A[][W + 2])
{
   ifstream file;
   file.open(filename.c_str());
   int N;
   file >> N;
   int i;
   int x, y;
   for (i = 0; i < N; i++)
   {
      file >> x >> y;
      A[y][x] = POPULATED;
   }
   file.close();
}
void copy(int A[][W + 2], int B[][W + 2])
{
   int i;
   int j;
   for (i = 1; i < H + 1; i++)
      for (j = 1; j < W + 1; j++)
         A[i][j] = B[i][j];
}
void check(int A[][W + 2])
{
   int B[H + 2][W + 2] = {0};
   int i, j;
   int x, y;
   for (i = 1; i < H + 1; i++)
   {
      for (j = 1; j < W + 1; j++)
      {
         int s = 0;
         for (x = -1; x <= 1; x++)
            for (y = -1; y <= 1; y++)
               s += A[i + y][j + x];
         if (A[i][j] == POPULATED)
         {
            if (s == 3 || s == 4)
               B[i][j] = POPULATED;
            else
               B[i][j] = EMPTY;
         }
         else if (s == 3)
            B[i][j] = POPULATED;
      }
   }
   copy(A, B);
}
int main(int argc, char **argv)
{
   int A[H + 2][W + 2] = {0};
   read("lifegame.txt", A);
   int i;
   for (i = 0; i < 20; i++)
   {
      show(A);
      check(A);
      //  cin.ignore();
   }
   return 0;
}