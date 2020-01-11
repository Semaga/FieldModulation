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
	std::string OutputFile_EFS_af = "POS_af.txt";
	std::string OutputFile_EFP_af = "EFP_af.txt";
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
		Charges[i].set_charge(1);                                                           //set unit charge

		Charges[i].set_position_x( lenght_y / RAND_MAX * rand());                                                    //set position in centimeters
		Charges[i].set_position_y( lenght_y / RAND_MAX * rand());                            //set position in centimeters 		
	}	
	WriteMessage("Particles's position was write", "main");
	// std::vector <std::vector <double> > EFS(dimension, std::vector<double> (dimension));
	// WriteMessage("Make vector for writing data of EFS", "main");

	// std::vector <std::vector <double> > EFP(dimension, std::vector<double> (dimension));
	// WriteMessage("Make vector for writing data of EFS", "main");

	//2D Vector for result of calculation
	//In this vector will put data's modulation of Electric Field Strenght
	 
	double delta_x = lenght_x/dimension;                                                  //fragmentation along x-axes
	double delta_y = lenght_y/dimension;                                                  //fragmentation along y-axes

	//zero the vector
	VectorToZero(EFS);
	WriteMessage("Calculate EFS and write data in vector", "main");

	// CalculateEFS(EFS, Charges, delta_x, delta_y);

	WriteMessage("Data of EFF was write in vector", "main");
	WriteVectorToFile(OutputFile_EFS, EFS, Charges, substrate);

	VectorToZero(EFP);
	WriteMessage("Calculate Potantial of EF and write data in vector", "main");
	
	// CalculateEFP(EFP, Charges, delta_x, delta_y);
	
	WriteVectorToFile(OutputFile_EFP, EFP, Charges, substrate);
	
	//Calcaulate forces action to particles
	CalculateForce(Charges);

	//Calculate Total energy of system
	double TotalEnergy = CalculateTotalEnergy(Charges);

	double eps;
	ToLocalMinimum(Charges, NumberOfItteration);
	TotalEnergy = CalculateTotalEnergy(Charges);
	WriteMessage("@@@@@@@@@@@@@@@@@@@@@@"," ");
	WriteMessage("**********************"," ");

	VectorToZero(EFS);
	// WriteMessage("Calculate EFS and write data in vector", "main");

	// CalculateEFS(EFS, Charges, delta_x, delta_y);

	WriteMessage("Data of EFF was write in vector", "main");
	WriteVectorToFile(OutputFile_EFS_af, EFS, Charges, substrate);

	VectorToZero(EFP);
	WriteMessage("Calculate Potantial of EF and write data in vector", "main");
	
	// CalculateEFP(EFP, Charges, delta_x, delta_y);
	
	// WriteVectorToFile(OutputFile_EFP_af, EFP, Charges, substrate);
	
	//Calcaulate forces action to particles
	CalculateForce(Charges);


	return 0;
}