#include "System.h"

extern int userMain(int argc, char** argv);

int main(int argc, char* argv[]){
    System::startSystem();
    int ret = userMain(argc, argv);
    System::endSystem();
    return ret;    
}