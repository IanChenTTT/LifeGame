#ifndef APP_H
#define APP_H
#include "Board.h"
namespace APP
{
   std::mutex g_mutex;
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
      int ATKNum;
   public:
      /// @brief FILE INPUT (DEBUG MODE)
      Manager();
      /// @brief CLI INPUT (RELEASE MODE)
      /// @param argc
      /// @param argv
      Manager(int argc, char **argv);
      ~Manager();
      void run(){
         if(this->mode == Mode::DEF){
            this->getDefender(input->NumInput);

            // int i = 10; //test iteration function
            // while(i--)
            // {
            //    std :: cout << std::endl;
            //    this->mapNeighbor();
            //    this->calcNeighbor();
            //    this->setCell();
            //    this->printPlayer();
            //    std :: cout << std::endl;
            // }
         }
         if(this->mode ==Mode::ATK){
            this->getAttacker(ATKNum,input->NumInput);
         }
      }
      /// @brief std input >> to playerBuffer
      /// @param filename 
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

      if( argc > 7 || argc < 6)
         throw std::runtime_error("No efficient parameter");
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
         this->input = new InputCLI(
            atoi(argv[1]),
            atoi(argv[2]),
            atoi(argv[3]),
            atoi(argv[4]),
            atoi(argv[5])
         );
         this->ATKNum = atoi(argv[6]);
         this->setLength(this->input->Height, this->input->Width);
         this->setPlayer();
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