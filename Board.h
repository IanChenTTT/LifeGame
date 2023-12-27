#ifndef BOARD_H
#define BOARD_H
#define EMPTY 0
#define POPULATE 1
#define listPoint  std::list<Cell> 
enum CELLVAl{
   EMP,
   POP
};
struct Cell{
   int x;
   int y;
   CELLVAl val;
}; 
class Board{
public:
   Board(){}
   Board(int width, int height){
      HEIGHT = height;
      WIDTH = width;
   }
   static int getWidth(){return WIDTH;}
   static int getHeight(){return HEIGHT;}
   void setPlayer(){
      this->playerBuffer = new int *[this->HEIGHT];
      for (int y = 0; y < this->HEIGHT; y++)
         this->playerBuffer[y] = (int *)calloc(this->WIDTH, sizeof(int));
   }
   void setSelf(int y,int x){
      this->playerBuffer[y][x] = POPULATE;

      for(int y1 = y-1 ; y1 <= y+1 && y1 > 0 && y1 < this->HEIGHT ; y1++) // 0 and HEIGHT is boundry
      {
         for(int x1 = x-1 ; x1 <= x+1 && x1 > 0 && x1 <this->WIDTH ; x1++)
            this->tempBuffer.push_front(Cell{x1,y1,CELLVAl::POP}); 
      }

   }
   listPoint getTempBuffer(){
      return this->tempBuffer;
   }
   void CalcLifeCell(){
      int neighbor;
      for(auto it = this->tempBuffer.begin(); it!=this->tempBuffer.end();++it){
         neighbor = 0;
         for(int y1 = it->y-1 ; y1 <= it->y+1; y1++) 
         {
            for(int x1 = it->x-1 ; x1 <= it->x+1 ; x1++)
               neighbor += this->playerBuffer[y1][x1];
         }    
         neighbor >=2 && neighbor <=3?it->val = CELLVAl::POP:it->val = CELLVAl::EMP;
      }
   }
   void SetCell(){
      for(auto it = this->tempBuffer.begin(); it!=this->tempBuffer.end();++it)
         this->playerBuffer[it->y][it->x] = it->val;
   }
   void printTemp(){
      auto it = tempBuffer.begin();
      while(++it != tempBuffer.end())
         std :: cout << it->x << " " << it->y << std::endl;
   }
   void printPlayer(){
      for (int y = 0; y < this->HEIGHT; y++){
         for (int x = 0; x < this->WIDTH; x++)
            std ::cout << std::setw(2) <<this->playerBuffer[y][x];
         std ::cout << std ::endl;
      }
   }
   ~Board(){
      this->freePlayerBuf();
   }
private:
   static int WIDTH;
   static int HEIGHT;
   int** playerBuffer;
   listPoint tempBuffer;
   void freePlayerBuf(){
      for (int y = 0; y < this->HEIGHT; y++)
         delete[] playerBuffer[y];
      delete[] playerBuffer;
   }
};
#endif