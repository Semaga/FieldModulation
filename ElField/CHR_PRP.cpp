#include "CHR_PRP.h"

void CHR_PRP::set_charge(         const double &charge  ){
	charge_value = charge;
}

void CHR_PRP::set_position_x(     const double &x      ){
	if ( x > lenght_x ){
		position_x = 2 * lenght_x - x;
	}else if ( x < 0 ){
		position_x = -x;
	}
		position_x = x;
}
void CHR_PRP::set_position_y(     const double& y      ){
	if ( y > lenght_y ){
		position_y = 2 * lenght_y - y;
	}else if ( y < 0 ){
		position_y = -y;
	}
	position_y = y;	
}
void CHR_PRP::set_position_z(     const double &z       ){
	position_z = z;
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
	double f_l = 0.0, f_r = 0.0;
	// f_l =  0.4 * pow( charge_value, 2 ) / pow( position_x, 2 );
	// f_r =  0.4 * pow( charge_value, 2 ) / pow( lenght_x - position_x, 2 );
	action_force_x = force_x - (f_r - f_l);
}

void CHR_PRP::set_action_force_y( const double &force_y ){
	double f_l = 0.0, f_r = 0.0, f;
	// f_l =  0.4 * pow( charge_value, 2 ) / pow( position_y, 2 );
	// f_r =  0.4 * pow( charge_value, 2 ) / pow( lenght_y - position_y, 2 );
	f = - EFS * 10'000'000 * ( position_y - lenght_y / 2.0 );
	action_force_y = force_y - (f_r - f_l)+f;
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
