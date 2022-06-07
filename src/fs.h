#ifndef SRC_ALKAID_FS_H_
#define SRC_ALKAID_FS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace alkaid {

using namespace std;

class fs {
  public:
    static char* readFile(const char* filepath, unsigned int* file_len_out);
};

}


#endif