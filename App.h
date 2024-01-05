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
   public:
      /// @brief FILE INPUT
      Manager();
      /// @brief CLI INPUT 
      /// @param argc
      /// @param argv
      Manager(int argc, char **argv);
      ~Manager();
      void run()
      {
         int i = 20;
         std::cout << (this->input == NULL) << std::endl; //if NULL DEBUG MODE ON
         this->printPlayer();
         while (i--)
         {
            // board->printTemp();
            // board->CalcLifeCell();
            this->mapNeighbor();
            this->calcNeighbor();
            this->setCell();
            this->printPlayer();
            std::cout << i << std::endl;
            // usleep(1000000);
            // system("clear");
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
   }
   Manager ::Manager(int argc, char **argv)
   {
      if (argc != 6)
         throw std::runtime_error("No efficient parameter");
      this->input = new InputCLI(
         atoi(argv[1]),
          atoi(argv[2]),
          atoi(argv[3]),
          atoi(argv[4]),
          atoi(argv[5])
      );
      this->setLength(this->input->Height, this->input->Width);
   }
   Manager ::~Manager()
   {
      delete this->input;
   }
}

#endif