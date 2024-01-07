#ifndef BOARD_H
#define BOARD_H
#define listCell std::list<Cell>
#define unMapCell std::unordered_map<Cell, int, KeyHasher> //(Cell,Cell Value,Keyhasher)
namespace APP
{
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
      bool operator==(const Cell &other) const
      {
         return (other.x == this->x && other.y == this->y && other.val == this->val);
      }
   };
   struct KeyHasher
   {
      std::size_t operator()(const Cell &key) const
      {
         using std::hash;
         using std::size_t;
         using std::string;
         return ((hash<int>()(key.x) ^ (hash<int>()(key.y << 1)) >> 1));
      }
   };
   class Board
   {
   public:
   protected:
      const int SPACING = 2; // SPACING NEED TO BE EVEN, LIKE 1-9 NEED 0 and 10
      const Cell InitCELL = {
          1,
          1,
      };
      Board() {}
      Board(int width, int height)
      {
         HEIGHT = height;
         WIDTH = width;
      }
      void setLength(int height, int width)
      {
         this->HEIGHT = height;
         this->WIDTH = width;
      }
      static int getWidth() { return WIDTH; }
      static int getHeight() { return HEIGHT; }
      void setPlayer()
      {
         this->playerBuffer = new int *[this->HEIGHT + SPACING];
         for (int y = 0; y < this->HEIGHT + SPACING; y++)
            this->playerBuffer[y] = (int *)calloc(this->WIDTH + SPACING, sizeof(int));
      }
      /// @brief set player buffer
      /// @param int y
      /// @param int x
      /// @param CELLVAL val
      void setSelf(int y, int x, CELLVAl val)
      {
         this->playerBuffer[y][x] = val;
         this->popCell.emplace_back(Cell{x, y, val}); // Only Record write in
      }
      void mapNeighbor()
      {
         auto it = popCell.begin();
         int x;
         int y;
         while (it != popCell.end())
         {
            x = it->x;
            y = it->y;
            for (int y1 = y - 1; y1 <= y + 1; y1++) // 0 and HEIGHT is boundry
            {
               for (int x1 = x - 1; x1 <= x + 1; x1++)
               {
                  if (y1 <= 0 || y1 >= HEIGHT + SPACING / 2 || x1 <= 0 || x1 >= WIDTH + SPACING / 2)
                     continue;
                  this->mapCell.emplace(Cell{x1, y1, (CELLVAl)this->playerBuffer[y1][x1]}, CELLVAl::EMP);
               }
            }
            it++;
         }
      }
      void calcNeighbor()
      {
         int neighbor;
         int x;
         int y;
         int val;
         for (auto it = this->mapCell.begin(); it != this->mapCell.end(); ++it)
         {
            x = it->first.x;
            y = it->first.y;
            val = it->first.val;
            neighbor = 0;
            for (int y1 = y - 1; y1 <= y + 1; y1++)
            {
               for (int x1 = x - 1; x1 <= x + 1; x1++)
                  neighbor += this->playerBuffer[y1][x1];
            }
            if (this->playerBuffer[y][x] == CELLVAl::POP)
            {
               if (neighbor == 3 || neighbor == 4)
                  continue;
               else
                  this->listBuffer.push_back(Cell{x, y, CELLVAl::EMP});
            }
            else if (neighbor == 3)
               this->listBuffer.push_back(Cell{x, y, CELLVAl::POP});
         }
      }
      void setCell()
      {
         auto it = this->listBuffer.begin();
         while (it != this->listBuffer.end())
         {
            int val = it->val;
            this->playerBuffer[it->y][it->x] = it->val;
            setSelf(it->y, it->x, it->val);
            if (val == CELLVAl::EMP)
               popCell.remove(Cell{it->x, it->y, CELLVAl::POP});
            it++;
         }
         this->listBuffer.clear();
         this->mapCell.clear();
      }
      void printPlayer()
      {
         for (int y = 1; y < HEIGHT + SPACING / 2; y++)
         {
            for (int x = 1; x < WIDTH + SPACING / 2; x++)
               std ::cout << "  " << this->playerBuffer[y][x];
            std ::cout << std ::endl;
         }
      }
      void getDefender(const int NumInput)
      {
         int num = 0;
         int x;
         int y;
         int MH = HEIGHT/2;
         std :: vector<Cell> Block; // Fit L to 田
         for (y = InitCELL.y; (y <= MH) && num + 3 < NumInput; y += 3)
         {
            for (x = InitCELL.x ; (x < WIDTH) && num + 3 <  NumInput; x += 3)
            {
               if(y % 2)
               {
                  if (x % 2) // FOUR TYPE OF L
                  {
                     this->setSelf(y, x, CELLVAl::POP);
                     this->setSelf(y, x + 1, CELLVAl::POP);
                     this->setSelf(y + 1, x, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x+1,y+1,CELLVAl::POP});
                  }
                  else{
                     this->setSelf(y, x, CELLVAl::POP);
                     this->setSelf(y, x + 1, CELLVAl::POP);
                     this->setSelf(y + 1, x + 1, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x,y+1,CELLVAl::POP});
                  }
               }
               else{
                  if (x % 2) // FOUR TYPE OF L
                  {
                     this->setSelf(y+ 1, x + 1, CELLVAl::POP);
                     this->setSelf(y, x + 1, CELLVAl::POP);
                     this->setSelf(y + 1, x, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x,y,CELLVAl::POP});
                  }
                  else{
                     this->setSelf(y, x, CELLVAl::POP);
                     this->setSelf(y + 1, x , CELLVAl::POP);
                     this->setSelf(y + 1, x + 1, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x+1,y,CELLVAl::POP});
                  }
               }
            }
         }
        for (y = HEIGHT; (y > MH + 2) && num + 3 < NumInput; y -= 3)
         {
            for (x = WIDTH ; (x > InitCELL.x) && num + 3 <  NumInput; x -= 3)
            {
               if(y%2){
                  if (x % 2) // FOUR TYPE OF L
                  {
                     this->setSelf(y - 1, x - 1, CELLVAl::POP);
                     this->setSelf(y , x - 1, CELLVAl::POP);
                     this->setSelf(y -1 , x , CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x,y,CELLVAl::POP});
                  }
                  else{
                     this->setSelf(y, x, CELLVAl::POP);
                     this->setSelf(y - 1, x - 1, CELLVAl::POP);
                     this->setSelf(y - 1, x, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x-1,y,CELLVAl::POP});
                  }
               }
               else{
                  if ( x % 2) // FOUR TYPE OF L
                  {
                     this->setSelf(y, x, CELLVAl::POP);
                     this->setSelf(y, x - 1, CELLVAl::POP);
                     this->setSelf(y - 1, x - 1, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x,y-1,CELLVAl::POP});
                  }
                  else{
                     this->setSelf(y, x, CELLVAl::POP);
                     this->setSelf(y, x - 1, CELLVAl::POP);
                     this->setSelf(y - 1, x, CELLVAl::POP);
                     num += 3;
                     Block.push_back(Cell{x-1,y-1,CELLVAl::POP});
                  }
               }
            }
         }
         if(NumInput > (WIDTH*HEIGHT/2))
         {
            for (auto cell : Block ){
               this->setSelf(cell.y,cell.x,cell.val);
               num++;
            }
            
         }
         for(y = InitCELL.y ; y <= HEIGHT && num < NumInput ; y++){
               for(x = InitCELL.x ; x <= WIDTH && num < NumInput ; x++){
                  if(this->playerBuffer[y][x] == 0){
                     setSelf(y,x,CELLVAl::POP);
                     num++;
                  } 
                 
               }
         }
       for (auto i : this->popCell)
       {
          std :: cout << i.x << " " << i.y << std::endl; 
       }
       
      }
      void getAttacker(int ATKNum)
      {
         this->setAttacker(ATKNum);
      }
      ~Board()
      {
         if(this->playerBuffer != NULL)this->freePlayerBuf();
      }

   private:
      static int WIDTH;
      static int HEIGHT;
      int **playerBuffer;
      listCell listBuffer;
      listCell popCell;
      unMapCell mapCell;
      void freePlayerBuf()
      {
         for (int y = 0; y < this->HEIGHT + SPACING; y++)
            delete[] playerBuffer[y];
         delete[] playerBuffer;
      }
      void setAttacker(int ATKNum){
           int i; 
            int x;
            int y;
            while(ATKNum--)
            {
               int i = 10;
               std :: cin >> x >> y;
               std :: cout << x << " " << y << std::endl;
               this->setSelf(y,x,CELLVAl::POP);
               std :: cout << this->popCell.size() << std :: endl;
            }
      }
      void Task(){
      }
   };
} // namespace APP
#endif