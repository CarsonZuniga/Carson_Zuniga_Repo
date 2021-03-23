#include "excel.h"

int main(int argc, char *argv[]){
    std::string cmd_file = argv[1];
    excel my_sheet(cmd_file);
    //my_sheet.printData();
    
    my_sheet.sort("Sample");
    my_sheet.printData();
    
    return 0;
}