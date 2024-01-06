#ifndef APP_H
#define APP_H
#include "Board.h"
namespace APP
{
   /// @brief READONLY struct from user CLI input
   struct InputCLI
   {
      const int mode;
      const int Height;
      const int Width;
      const int Iter;
      const int NumInput;
      InputCLI(int mode, int Height, int Width, int Iter, int NumInput) : mode(mode), Height(Height), Width(Width), Iter(Iter), NumInput(NumInput) {}
      InputCLI &operator=(const InputCLI &other)
      {
         // Guard self assignment
         if (this == &other)return *this;
         return *this;
      }
   }; // CONST INITIALIZER

   class Manager : public Board // Namespace::class = App Manager
   {
   private:
      InputCLI* input;
      enum  Mode{
         ATK,
         DEF,
         DEBUG
      } mode;
   public:
      /// @brief FILE INPUT (DEBUG MODE)
      Manager();
      /// @brief CLI INPUT (RELEASE MODE)
      /// @param argc
      /// @param argv
      Manager(int argc, char **argv);
      ~Manager();
      void run()
      {

         // std::cout << (this->input == NULL) << std::endl; //if NULL DEBUG MODE ON
         // int i = 20;
         // this->printPlayer();
         // while (i--)
         // {
         //    // board->printTemp();
         //    // board->CalcLifeCell();
         //    this->mapNeighbor();
         //    this->calcNeighbor();
         //    this->setCell();
         //    this->printPlayer();
         //    std::cout << i << std::endl;
            // usleep(1000000);
            // system("clear");

         // }
         if(this->mode == Mode::DEF)
         {
            std :: cout << std::endl;
            this->printPlayer();
            std :: cout << std::endl;
            this->getDefender(input->NumInput);
            this->printPlayer();
         }
      }
      /**
       * Read player input file
       *
       * @param string filename
       * @throw runtime_error e
       */
      void ReadInFile(std::string filename)
      {
         std::fstream file(filename, std::ios::in);
         int num = 0;
         int y = 0;
         int x = 0;
         if (file.is_open() && file.good())
         {
            file >> num;
            this->setPlayer();
            while (file >> y >> x)
               this->setSelf(y, x, CELLVAl::POP);
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
   };

   Manager ::Manager()
   {
      std::string fileName = "data.txt";
      ReadInFile(fileName);
      this->mode = Mode::DEBUG;
   }
   Manager ::Manager(int argc, char **argv)
   {
      switch (atoi(argv[1]))
      {
      case 1:
         this->mode = Mode::DEF;

         this->input = new InputCLI(
         atoi(argv[1]),
          atoi(argv[2]),
          atoi(argv[3]),
          atoi(argv[4]),
          atoi(argv[5])
         );
         this->setLength(this->input->Height, this->input->Width);
         this->setPlayer();
         break;
      case 2:
         this->mode = Mode::ATK;
         break;
      default:
         throw std::runtime_error("No efficient parameter");
         break;
      }
   }
   Manager ::~Manager()
   {
      if(this->input != nullptr)delete this->input;
   }
}

#endif