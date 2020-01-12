#include "SUB_PRP.h"

void SUB_PRP::set_lenght_x(   const  double &x){
	lenght_x = x;
}
void SUB_PRP::set_lenght_y(   const double &y){
	lenght_y = y;
}
void SUB_PRP::set_dimnension( const int &d){
	dimension = d;
}
void SUB_PRP::set_voltage(  const double &U){
	voltage = U;
}

void SUB_PRP::WriteDataToFile(std::ofstream &fout){
	fout << "Substrate parameters:"       << std::endl;
	fout << "\tLenght_X = "  << lenght_x  << std::endl;
	fout << "\tLenght_Y = "  << lenght_y  << std::endl;
	fout << "\tDimension = " << dimension << std::endl;
}
