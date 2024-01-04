#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include "Board.h"
#include "InputManager.h"
struct Input{
   const int mode;
   const int Height;
   const int Width;
   const int Iter;
   const int NumInput;
   Input(int mode,int Height,int Width,int Iter,int NumInput): 
   mode(mode), Height(Height), Width(Width), Iter(Iter), NumInput(NumInput){}
};
int Board::WIDTH = 9;
int Board::HEIGHT = 9;
void init(char**,Board*&);
void run(Board*&);
void ReadInFile(std::string,Board*&);
void ReadInCLI(Input,Board*&);
int main(int argc, char** argv)
{
   try
   {
      Board* board;
      init(argv,board);
      run(board);
      delete board;
   }
   catch(const std::runtime_error &e)
   {
      std::cerr << e.what() << std ::endl;
      exit(0);
   }
   catch (const std::bad_alloc &e)
   {
      std:: cerr<< "Allocation failed: " << e.what() << std ::endl;
      exit(0);
   }
   catch (const std::exception &e)
   {
      std::cerr << e.what() << std ::endl;
      exit(0);
   }
   return 0;
}
void init(char** argv,Board*& board){
   std::string fileName= "data.txt";
   ReadInFile(fileName,board);
   // ReadInCLI(input,board);
   // if(argc != 6)throw std::runtime_error("Not efficient argument was provide");
      // Input input = {
      //    atoi(argv[1]),
      //    atoi(argv[2]),
      //    atoi(argv[3]),
      //    atoi(argv[4]),
      //    atoi(argv[5]),
      // };
}
void run(Board*&board){
   int i=20;
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


