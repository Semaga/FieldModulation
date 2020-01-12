#ifndef CHR_PRP_H
#define CHR_PRP_H

#include <fstream>
#include "SUB_PRP.h"

class CHR_PRP{

private:
	double charge_value;
	double position_x;
	double position_y;
	double position_z;

	double lenght_x;
	double lenght_y;

	double action_force_x;
	double action_force_y;
	double action_force_z;

	double energy;

	double EFS;


public:
	CHR_PRP(SUB_PRP & substrate){
		lenght_x = substrate.get_lenght_x();
		lenght_y = substrate.get_lenght_y();
		EFS      = substrate.get_voltage();
	}
	void set_position_x(      const double &x        );
	void set_position_y(      const double &y        );
	void set_position_z(      const double &z        );
	void set_charge(          const double &charge   );

	void set_action_force_x(  const double &force_x  );
	void set_action_force_y(  const double &force_y  );
	void set_action_force_z(  const double &force_y  );

	void set_energy(          const double &E     );

  void WriteDataToFile(     std::ofstream &fout);

	double get_position_x(){         return position_x;}
	double get_position_y(){         return position_y;}
	double get_position_z(){         return position_z;}

	double get_charge(){             return charge_value;}
	
	double get_action_force_x(){     return action_force_x;}
	double get_action_force_y(){     return action_force_y;}
	double get_action_force_z(){     return action_force_z;}

	double get_energy(){             return energy;}

	double get_lenght_x(){           return lenght_x;}
	double get_lenght_y(){           return lenght_y;}

  double get_substrate_lenght_x(){ return lenght_x;}
  double get_substrate_lenght_y(){ return lenght_y;}

};

#endif