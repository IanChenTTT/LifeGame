#include <iostream>
#include <list>
#include <fstream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <vector>
#include "App.h"
int APP::Board::WIDTH = 9;
int APP::Board::HEIGHT = 9;
/// @brief Program entry point
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char** argv)
{
   try
   {
      APP::Manager* manager = new APP::Manager(argc,argv);
      manager->run();
      delete manager;
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



