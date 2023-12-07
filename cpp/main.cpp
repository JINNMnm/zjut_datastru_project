//
// Created by 31320 on 2023/9/28.
//
#include "../h/BitMap.h"
#include "../h/Console.h"
#include "../h/Node.h"
#include "../h/const.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  // init the console
  Console console(USER_FILE_PATH);

  while (1) {
    console.Run();
  }

  return 0;
}
