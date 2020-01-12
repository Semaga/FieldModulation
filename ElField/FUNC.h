#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "CHR_PRP.h"
#include "SUB_PRP.h"

void VectorToZero(              std::vector <std::vector <double> >&v);


void WriteVectorToFile(          const std::string &OutputFile, 
	                               std::vector <std::vector <double> > &v, 
	                               std::vector <CHR_PRP> &Charge, 
	                               SUB_PRP &Substrate);

void WriteChargesDataToFile (    const std::string &OutputFile,
	                               std::vector <CHR_PRP> &Charge,
	                               SUB_PRP &Substrate);


void ReadInputFile(              const std::string &InputeFile, 
	                               SUB_PRP &Substrate, 
	                               int &NumberOfParticle, 
	                               int &NumberIfItteration, 
	                               std::string &OutputFile_EFS, 
	                               std::string &OutputFile_EFP);


void WriteMessage(               const std::string &s, 
	                               const std:: string &PositionFile);


std::vector <std::string> split( std::string &s, char delimeter = ' ');


void CalculateForce(             std::vector <CHR_PRP> &Charhe);


void CalculateEFS(               std::vector <std::vector <double> > &EFS, 
	                               std::vector <CHR_PRP> &Charges, 
	                               const double &delta_x, 
	                               const double &delta_y);


void CalculateEFP(               std::vector <std::vector <double> > &EFS, 
	                               std::vector <CHR_PRP> &Charges, 
	                               const double &delta_x, 
	                               const double &delta_y);


void ToLocalMinimum(             std::vector <CHR_PRP> &Charges, 
	                               const int &NumberIfItteration);

double CalculateTotalEnergy(     std::vector<CHR_PRP> &Charge);


#endif