#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Board.h"
void init(Board*&);
void run(Board*&);
void read(std::string,Board*&);

int Board::WIDTH = 9;
int Board::HEIGHT = 9;
int main()
{
   try
   {
      Board* board;
      init(board);
      run(board);
      delete board;
   }
   catch(const std::runtime_error &e)
   {
      std::cout << e.what() << std ::endl;
      exit(0);
   }
   catch (const std::bad_alloc &e)
   {
      std::cout << "Allocation failed: " << e.what() << std ::endl;
      exit(0);
   }
   catch (const std::exception &e)
   {
      std::cerr << e.what() << std ::endl;
      exit(0);
   }
   return 0;
}
void init(Board*& board){
   std::string fileName= "data.txt";
   read(fileName,board);
}
void run(Board*&board){
   board->printPlayer();
   // board->printTemp();
   board->CalcLifeCell();
   board->SetCell();
   std::cout << std::endl;
   board->printPlayer();
}
/**
 * Read player input file
 * 
 * @param string filename
 * @throw runtime_error e
*/
void read(std::string filename, Board*& board){
   std::fstream file(filename,std::ios::in);
   int num = 0;
   int y = 0;
   int x = 0;
   if(file.is_open()&&file.good())
   {
      file>>num;
      board =new Board();
      board->setPlayer();
      while(file >> y >> x)
         board->setSelf(y,x);
      file.clear();
      file.close();
   }
   else
   {
      file.clear();
      file.close();
      throw std::runtime_error("Could not open the file");
   }
}


