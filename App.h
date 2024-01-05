#ifndef APP_H
#define APP_H
#include "Board.h"
namespace APP
{
   /// @brief READONLY struct from user CLI input
   struct InputCLI{
   const int mode;
   const int Height;
   const int Width;
   const int Iter;
   const int NumInput;
   InputCLI(int mode,int Height,int Width,int Iter,int NumInput): 
   mode(mode), Height(Height), Width(Width), Iter(Iter), NumInput(NumInput){}
   }; //CONST INITIALIZER

   class Manager : public Board // Namespace::class = App Manager
   {
   private:
      Board *board;
   public:
      Manager();
      ~Manager();
      /**
       * run the program
       * 
       * @param int argc
       * @param char** argv
      */
      void run(int argc, char** argv)
      {
         init(argv, board);
         run(board);
      }
      void init(char **argv, Board *&board)
      {
         std::string fileName = "data.txt";
         ReadInFile(fileName, board);
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
      void run(Board *&board)
      {
         int i = 20;
         board->printPlayer();
         while (i--)
         {
            // board->printTemp();
            // board->CalcLifeCell();
            board->mapNeighbor();
            board->calcNeighbor();
            board->setCell();
            board->printPlayer();
            std::cout << i<< std:: endl;
            std:: cout << "it end here 2" << i << std :: endl;;
            // usleep(1000000);
            // system("clear");
         }
         std:: cout << "it end here 1";
      }
      /**
       * Read player input file
       *
       * @param string filename
       * @throw runtime_error e
       */
      void ReadInFile(std::string filename, Board *&board)
      {
         std::fstream file(filename, std::ios::in);
         int num = 0;
         int y = 0;
         int x = 0;
         if (file.is_open() && file.good())
         {
            file >> num;
            board = new Board();
            board->setPlayer();
            while (file >> y >> x)
               board->setSelf(y, x, CELLVAl::POP);
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
      void ReadInCLI(InputCLI in,Board*& board){
         board = new Board(in.Width,in.Height);
         board->setPlayer();
      }
   };

   Manager ::Manager()
   {
   }

   Manager ::~Manager()
   {
      Board::~Board();
      delete board;
   }
}

#endif