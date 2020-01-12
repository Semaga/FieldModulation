#include "CHR_PRP.h"

void CHR_PRP::set_charge(         const double &charge  ){
	charge_value = charge;
}

void CHR_PRP::set_position_x(     const double &x      ){
	if( ( x < lenght_x ) && (x > 0) ){
		position_x = x;
	}
}
void CHR_PRP::set_position_y(     const double& y      ){
	if( ( y < lenght_y ) && (y > 0)){
		position_y = y;
	}
}
void CHR_PRP::set_position_z(     const double &z       ){
	if ( ( z < 0.00'000'065) && (z > 0.00'000'005)){
		position_z = z;
	}
}

void CHR_PRP::set_velosity_x(     const double &Vx      ){
	velosity_x = Vx;
}
void CHR_PRP::set_velosity_y(     const double &Vy      ){
	velosity_y = Vy;
}
void CHR_PRP::set_velosity_z(     const double &Vz      ){
	velosity_z = Vz;
}


void CHR_PRP::set_action_force_x( const double &force_x ){
	double f = 0.0;
	f = - 1500'000'000 * (position_x - lenght_x/2.0);
	action_force_x = force_x + f;
}

void CHR_PRP::set_action_force_y( const double &force_y ){
	double f = 0.0;
	// f = - 1500'000'000 * (position_y - lenght_y/2.0);
	action_force_y = force_y + f;
}

void CHR_PRP::set_action_force_z( const double &force_z){
	double epsilon = 1.054, f = 0.0;
	f  = - ( epsilon - 1 ) * charge_value*charge_value / (( epsilon + 1 ) * position_z*position_z);
	f += charge_value * EFS; //clamping potential
	f += force_z;
	action_force_z = f; 
}

void CHR_PRP::set_energy(         const double &E       ){
	energy = E;
}

void CHR_PRP::WriteDataToFile(    std::ofstream &fout){
	fout << "Particle parameters:"              << std::endl;
	fout << "\tPosition_X = "   << position_x   << std::endl;
	fout << "\tPosition_Y = "   << position_y   << std::endl;
	fout << "\tPosition_Z = "   << position_z   << std::endl;
	fout << "\tCharge_value = " << charge_value << std::endl;
}
