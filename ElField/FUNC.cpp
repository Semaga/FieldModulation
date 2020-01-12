#include "FUNC.h"

//Get 2d vector and nullifies them
void VectorToZero(std::vector <std::vector <double> >&v){
	for(int i = 0; i != v.size(); i++){
		for(int j = 0; j != v[i].size(); j++){
			v[i][j] = 0;
		}
	}
}

//Write data from 2d vector to file
void WriteVectorToFile(const std::string &OutputFile, 
	                     std::vector <std::vector <double> > &v, 
	                     std::vector <CHR_PRP> &Charge, 
	                     SUB_PRP &Substrate)
{
	//Get vectors of result of calculation, ChargeParameters and Substrate parameters 
	std::string s = "Start write the " + OutputFile;
	WriteMessage(s,"WriteVectorToFile");
	std::ofstream fout(OutputFile);
	//Make stream to write-file
	if(fout){
		WriteMessage("Output file "+OutputFile+ " is open ...","FUNC");
		Substrate.WriteDataToFile(fout);
		//Write information about wubstrate
		fout << "NumberOfParticle: " << Charge.size() << std::endl;
		for(auto &i:Charge){
		//Write information about charge particles using vector
			i.WriteDataToFile(fout);
		} 
		//Write result of calculation to file
		WriteMessage("Write date to file","FUNC");
		fout << "Data:" << std::endl;
		for(int i = 0; i != v.size(); i++){
			for(int j = 0; j != v[i].size(); j++){
				fout << v[i][j] << ' ';
			}
		}
		fout << std::endl;
		fout.close();
		WriteMessage("File "+OutputFile+" was closed.","FUNC");
	}else
		WriteMessage("Error file "+OutputFile+" not found","FUNC");
}

void WriteChargesDataToFile (    const std::string &OutputFile,
	                               std::vector <CHR_PRP> &Charge,
	                               SUB_PRP &Substrate)
{
	//Get vectors of result of calculation, ChargeParameters and Substrate parameters 
	std::string s = "Start write the " + OutputFile;
	WriteMessage(s,"WriteVectorToFile");
	std::ofstream fout(OutputFile);
	//Make stream to write-file
	if(fout){
		WriteMessage("Output file "+OutputFile+ " is open ...","FUNC");
		Substrate.WriteDataToFile(fout);
		//Write information about wubstrate
		fout << "NumberOfParticle: " << Charge.size() << std::endl;
		for(auto &i:Charge){
		//Write information about charge particles using vector
			i.WriteDataToFile(fout);
		} 
		//Write result of calculation to file
		WriteMessage("Write date to file","FUNC");
		fout.close();
		WriteMessage("File "+OutputFile+" was closed.","FUNC");
	}else
		WriteMessage("Error file "+OutputFile+" not found","FUNC");
}


//Read input data from InputFile
void ReadInputFile(    const std::string &InputeFile, 
	                     SUB_PRP &Substrate, 
	                     int &NumberOfParticle, 
	                     int &NumberIfItteration,
	                     std::string &OutputFile_EFS, 
	                     std::string &OutputFile_EFP)
{
	WriteMessage("Try to open inpute file",
		           "ReadInputFile");	
	std::cout << "" << std::endl;
	std::ifstream fin(InputeFile);
	std::vector <std::string> s;
	if(fin){
		WriteMessage("Input file is open",
			           "ReadInputFile");
		std::string line;
		double param;
		int chec;
		getline(fin, line);
		getline(fin, line);
		s = split(line);
		param = stod(s[2]);
		Substrate.set_lenght_x(param);
		
		getline(fin, line);
		s = split(line);
		param = stod(s[2]);	
		Substrate.set_lenght_y(param);
		WriteMessage("\t\tLenght and wildth of substrate was read ...",
			               "ReadInputFile");

		getline(fin, line);
		getline(fin, line);
		s = split(line);
		chec = stoi(s[2]);	
		Substrate.set_dimnension(chec);
		WriteMessage("\t\tDimenstion of calculation was read ...",
			               "ReadInputFile");
		getline(fin, line);
		s = split(line);
		NumberIfItteration = stoi(s[2]);
		WriteMessage("\t\tNumber of itteration was read ...",
			               "ReadInputFile");


		getline(fin, line);
		getline(fin, line);
		s = split(line);
		chec = stoi(s[4]);	
		WriteMessage("\t\tNumber of particles is equal ", 
			                "ReadInputFile");
		NumberOfParticle = chec;
		WriteMessage("\t\tNumber of particles was read ...", 
			               "ReadInputFile");

		getline(fin, line);
		getline(fin, line);
		s = split(line);
		OutputFile_EFS = s[2];
		WriteMessage("\t\tRead name of output file with EFS-data: "+OutputFile_EFS, 
			               "ReadInputFile");

		getline(fin, line);
		s = split(line);
		OutputFile_EFP = s[2];
		WriteMessage("\t\tRead name of output file with EFP-data: "+OutputFile_EFP, 
			               "ReadInputFile");
		

	}
}

std::vector <std::string> split(std::string & s, char delimeter){
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delimeter)){
		tokens.push_back(item);
	}
	return tokens;
}

void WriteMessage(const std::string &s, const std::string &PositionFile){
	std::cout << "\t####" << std::endl;
	std::cout << '\t' << "Message from " << PositionFile <<" function :\t" << s << std::endl;
}

double CalculateTotalEnergy(std::vector<CHR_PRP> &Charge){
	double TotalEnergy = 0.0;
	double MultCharge, Rx2, Ry2, Rz2;
	for(int i = 0; i != Charge.size(); i++){
		for(int j = 0; j != Charge.size(); j++){
			if (j !=i ){
				MultCharge   = Charge[i].get_charge() * Charge[j].get_charge();
				Rx2          = pow(Charge[j].get_position_x() - Charge[i].get_position_x(),2);
				Ry2          = pow(Charge[j].get_position_y() - Charge[i].get_position_y(),2);
				Rz2          = pow(Charge[j].get_position_z() - Charge[i].get_position_z(),2);
				TotalEnergy += MultCharge / sqrt(Rx2 + Ry2 + Rz2);
			}
		}
	}
	WriteMessage("TotalEnergy of charge particales system is equal "+ std::to_string(TotalEnergy/2), "CalculateTotalEnergy");

	return TotalEnergy /= 2;	
}

void CalculateForce( std::vector <CHR_PRP> &Charges){
	for(int i = 0; i != Charges.size(); i++){
		//Zeroing components of strenghts action to particle
		double force_x = 0.0, 
		       force_y = 0.0, 
		       force_z = 0.0,
 		       R2 = 0.0, 
 		       delta_z = 0.0,
		       delta_y = 0.0, 
		       delta_x = 0.0;
		for(int j = 0; j != Charges.size(); j++){
			if (j != i){
				// WriteMessage("Ups, ","CalculateForce");
				delta_x = Charges[i].get_position_x() - Charges[j].get_position_x();
				delta_y = Charges[i].get_position_y() - Charges[j].get_position_y();
				delta_z = Charges[i].get_position_z() - Charges[j].get_position_z();
				R2 = pow(delta_y, 2) + pow(delta_x, 2) + pow(delta_z, 2) ;
				force_x += Charges[i].get_charge() * Charges[j].get_charge() * delta_x/ pow(R2, 1.5);
				force_y += Charges[i].get_charge() * Charges[j].get_charge() * delta_y/ pow(R2, 1.5);
				force_z += Charges[i].get_charge() * Charges[j].get_charge() * delta_z/ pow(R2, 1.5);
			}
		}
		Charges[i].set_action_force_x(force_x);
		Charges[i].set_action_force_y(force_y);
		Charges[i].set_action_force_z(force_z);
		WriteMessage("Force was Calculate for "+std::to_string(i)+ " particle","CalculateForce");
	}
}

void CalculateEFS( std::vector <std::vector <double> > &EFS, 
	                 std::vector <CHR_PRP> &Charges, 
	                 const double &delta_x, 
	                 const double &delta_y)
{
	double x = delta_x, y = delta_y;
	for(int k = 0; k != Charges.size(); k++){
		double position_x = 0.0, position_y = 0.0, R=0; 
		for(int i = 0; i != EFS.size(); i++){
			for(int j = 0; j != EFS[i].size(); j++){
				position_x = Charges[k].get_position_x() - i*x;
				position_y = Charges[k].get_position_y() - j*y;
				R = (pow(position_x, 2) + pow(position_y,2));
				EFS[i][j] += Charges[k].get_charge()/R;
			}
		}
	}
}

void CalculateEFP( std::vector <std::vector <double> > &EFP, 
	                 std::vector <CHR_PRP> &Charges, 
	                 const double &delta_x, 
	                 const double &delta_y)
{
	double x = delta_x, y = delta_y;
	for(int k = 0; k != Charges.size(); k++){
		double position_x = 0.0, position_y = 0.0, R=0; 
		for(int i = 0; i != EFP.size(); i++){
			for(int j = 0; j != EFP[i].size(); j++){
				position_x = Charges[k].get_position_x() - i*x;
				position_y = Charges[k].get_position_y() - j*y;
				R = sqrt(pow(position_x, 2) + pow(position_y,2));
				EFP[i][j] += Charges[k].get_charge()/R;
			}
		}
	}	
}

void ToLocalMinimum(std::vector <CHR_PRP> &Charges, 
	                  const int &NumberIfItteration)
{
	//Shift all particles after that calculate enegy
	WriteMessage("\t\t@@@@@@","ToLocalMinimum");
	WriteMessage("\n\t\t\t@@@Start optimize@@@","ToLocalMinimum");
	double dY = 0.00001, dX = 0.00001, dZ = 0.00'000'005, x, y, z;
	for(int n = 0; n != NumberIfItteration; n++){
		WriteMessage("@@@Start " + std::to_string(n) +" itteration", "ToLocalMinimum");
		WriteMessage("@@@Start to shift particales","ToLocalMinimum");
		for (auto &i:Charges){
			x  =  i.get_position_x();
			y  =  i.get_position_y();	
			z  =  i.get_position_z();  
			if ( ( i.get_action_force_x() > 0 ) && ( ( x + dX ) < i.get_substrate_lenght_x() ) ){
				i.set_position_x(x + dX);
			}else if( ( i.get_action_force_x() < 0 ) && ((x - dX) > 0) ) {
				i.set_position_x( x - dX);
			}
			if ( ( i.get_action_force_y() > 0 ) && ( ( y + dY ) < i.get_substrate_lenght_y() ) ){
				i.set_position_y( y + dY);
			}else if( ( i.get_action_force_y() < 0 ) && ((y - dY) > 0 ) ){
				i.set_position_y( y - dY);
			}
			if ( ( i.get_action_force_z() > 0 ) && ((z + dZ) < 0.00'000'065 ) ){
				i.set_position_z( z + dZ );
			}else if ( ( i.get_action_force_z() < 0 ) && ((z - dZ) > 0.00'000'005 ) ){
				i.set_position_z( z - dZ);
			}
		}
		WriteMessage("@@@Finish to shift particales","ToLocalMinimum");
		WriteMessage("@@@Calculate forces is start","ToLocalMinimum");	
		CalculateForce(Charges);
		WriteMessage("@@@Calculate forces is OVER","ToLocalMinimum");	
		WriteMessage("@@@Finish " + std::to_string(n) + " itteration", "ToLocalMinimum");
	}
}