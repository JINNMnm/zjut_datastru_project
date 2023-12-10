//
// Created by 31320 on 2023/9/28.
//
#include "../h/Console.h"
#include "../h/Node.h"
#include "../h/const.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  // init the console
  Console::CleanWindow();
  cout << "start" << endl;
  Console console;
  console.init();

  while (1) {
    console.Run();
  }

  return 0;
}
