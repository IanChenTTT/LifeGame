#ifndef BOARD_H
#define BOARD_H
#define EMPTY 0
#define POPULATE 1
#define listPoint std::list<Cell>
#define setPoint std::set<Cell>
enum CELLVAl
{
   EMP,
   POP
};
struct Cell
{
   int x;
   int y;
   CELLVAl val;
};
class Board
{
public:
   Board() {}
   Board(int width, int height)
   {
      HEIGHT = height;
      WIDTH = width;
   }
   static int getWidth() { return WIDTH; }
   static int getHeight() { return HEIGHT; }
   void setPlayer()
   {
      this->playerBuffer = new int *[this->HEIGHT];
      for (int y = 0; y < this->HEIGHT; y++)
         this->playerBuffer[y] = (int *)calloc(this->WIDTH, sizeof(int));
   }
   void setSelf(int y, int x)
   {
      this->playerBuffer[y][x] = POPULATE;
      this->PopCell.push_back(Cell{x, y, CELLVAl::POP}); // Only Record write in
   }
   void setTempBuffer()
   {
      auto it = this->ListBuffer.begin();
      while (it != this->ListBuffer.end())
      {
      }
   }
   listPoint getTempBuffer()
   {
      return this->ListBuffer;
   }
   void CalcLifeCell()
   {
      int neighbor;
      int x;
      int y;
      int val;
      for (auto it = this->PopCell.begin(); it != this->PopCell.end(); ++it) // FOR every set Val
      {
         x = it->x;
         y = it->x;
         val = it->x;
         for (int y1 = y - 1; y1 > 0 && y1 < this->HEIGHT - 1; y1++)
         {
            for (int x1 = y - 1; x1 > 0 && x1 < this->HEIGHT - 1; x1++) // Check 9 SQUARE
            {
               neighbor = 0;
               neighbor +=
                   this->playerBuffer[y1 - 1][x1 - 1] + this->playerBuffer[y1 - 1][x1] + this->playerBuffer[y1 - 1][x1 + 1] +
                   this->playerBuffer[y1][x1 - 1] + this->playerBuffer[y1][x1 + 1] +
                   this->playerBuffer[y1 + 1][x1 - 1] + this->playerBuffer[y1 + 1][x1] + this->playerBuffer[y1 + 1][x1 + 1];
               if (neighbor == 3 && this->playerBuffer[x][y] != CELLVAl::POP)
               {
                  this->ListBuffer.push_back(Cell{x, y, CELLVAl::POP});
                  continue;
               }
               if ((neighbor == 3 || neighbor == 2) && this->playerBuffer[x][y] == CELLVAl::POP) // allive before
                  continue;
               else if (this->playerBuffer[x][y] == CELLVAl::EMP)
                  continue;
               else
                  this->ListBuffer.push_back(Cell{x, y, CELLVAl::EMP});
            } // NOTE:: only cell was POP to EMP, or EMP to POP write to ListBuffer
         }
      }
   }
   void SetCell()
   {
      auto it = this->ListBuffer.begin();
      while (it != this->ListBuffer.end())
      {
         int val = it->val; 
         this->playerBuffer[it->y][it->x] = it->val;
         if (val == CELLVAl::EMP)
            PopCell.remove(Cell{it->x, it->y, CELLVAl::POP});
         else
            setSelf(it->y, it->y);
      }
      this->ListBuffer.clear();
   }
   void printTemp()
   {
      auto it = ListBuffer.begin();
      while (++it != ListBuffer.end())
         std ::cout << it->x << " " << it->y << std::endl;
   }
   void printPlayer()
   {
      for (int y = 1; y < this->HEIGHT - 1; y++)
      {
         for (int x = 1; x < this->WIDTH - 1; x++)
            std ::cout << std::setw(2) << this->playerBuffer[y][x];
         std ::cout << std ::endl;
      }
   }
   ~Board()
   {
      this->freePlayerBuf();
   }

private:
   static int WIDTH;
   static int HEIGHT;
   int **playerBuffer;
   listPoint ListBuffer;
   listPoint PopCell;
   void freePlayerBuf()
   {
      for (int y = 0; y < this->HEIGHT; y++)
         delete[] playerBuffer[y];
      delete[] playerBuffer;
   }
};
#endif