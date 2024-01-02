#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include "Board.h"
void init(Board*&);
void run(Board*&);
void ReadInFile(std::string,Board*&);
struct Input{
   int mode;
   int Height;
   int Width;
   int Iter;
   int NumInput;
};
int Board::WIDTH = 9;
int Board::HEIGHT = 9;
int main(int argc, char** args)
{
   try
   {
      // Input in;
      // in.mode = atoi(args[1]);
      // in.Height = atoi(args[2]);
      // in.Width = atoi(args[3]);
      // in.Iter = atoi(args[4]);
      // in.NumInput = atoi(args[5]);
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
   ReadInFile(fileName,board);
}
void run(Board*&board){
   int i=5;
   board->printPlayer();
   while(i--){
      // board->printTemp();
      // board->CalcLifeCell();
      board->mapNeighbor();
      board->calcNeighbor();
      board->setCell();
      std::cout << std::endl;
      board->printPlayer();
      // usleep(1000000);
      std :: cout << std::endl;
      // system("clear");
   }
}
void ReadInCLI(Input in,Board*& board){
   board = new Board(in.Width,in.Height);
   board->setPlayer();
}
/**
 * Read player input file
 * 
 * @param string filename
 * @throw runtime_error e
*/
void WriteInFile(std::string filename, Board*& board){
   std::fstream file(filename,std::ios::out);
   int num = 0;
   int y = 0;
   int x = 0;
   if(file.is_open()&&file.good())
   {
      file<<num;
      board =new Board();
      board->setPlayer();
      while(file >> y >> x)
         board->setSelf(y,x,CELLVAl::POP);
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
/**
 * Read player input file
 * 
 * @param string filename
 * @throw runtime_error e
*/
void ReadInFile(std::string filename, Board*& board){
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
         board->setSelf(y,x,CELLVAl::POP);
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


