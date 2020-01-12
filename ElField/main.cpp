//Try to calculate electric field of some electric charges

//Import stadardt header files
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <time.h>

//Import own header files
#include "CHR_PRP.h"
#include "SUB_PRP.h"
#include "FUNC.h"


int main(int argc, char const *argv[]){
	SUB_PRP substrate;
	//Set paramaters of cell wildth and lenght, fragmentation
	int NumberOfParticle, NumberOfItteration;
	std::string OutputFile_EFS;
	std::string OutputFile_EFP;
	std::string OutputFile_be = "POS_be.txt";
	std::string OutputFile_af = "POS_af.txt";
	ReadInputFile("InputFile.txt", substrate, NumberOfParticle, NumberOfItteration, OutputFile_EFS, OutputFile_EFP);

	//Put data of substrate to variables
	int dimension = substrate.get_dimension();
	double lenght_x = substrate.get_lenght_x();
	double lenght_y = substrate.get_lenght_y();
	

	//make vector with Charges properties
	CHR_PRP cha(substrate);
	std::vector<CHR_PRP> Charges;
	for (int i = 0; i < NumberOfParticle; i++){
		Charges.push_back(cha);
	}
	WriteMessage("Start to write particles's position", "main");
	srand (time(NULL));
	for (int i = 0; i != Charges.size(); i++){
		Charges[i].set_charge(-1);                                                           //set unit charge

		Charges[i].set_position_x( lenght_x / RAND_MAX * rand() );                                                    //set position in centimeters
		Charges[i].set_position_y( lenght_y / RAND_MAX * rand() );  
		Charges[i].set_position_z( 0.00'000'005 + 0.00'000'060 / RAND_MAX * rand() );                          //set position in centimeters 		
	}	
	WriteMessage("Particles's position was write", "main");

	// CalculateEFP(EFP, Charges, delta_x, delta_y);
	WriteChargesDataToFile(OutputFile_be, Charges, substrate);
	
	//Calcaulate forces action to particles
	CalculateForce(Charges);

	//Calculate Total energy of system
	double TotalEnergy = CalculateTotalEnergy(Charges);

	ToLocalMinimum(Charges, NumberOfItteration);
	TotalEnergy = CalculateTotalEnergy(Charges);

	WriteChargesDataToFile(OutputFile_af, Charges, substrate);

	return 0;
}