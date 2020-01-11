#ifndef SUB_PRP_H
#define SUB_PRP_H

#include <fstream>

class SUB_PRP{

private:
	double lenght_x;
	double lenght_y;
	int    dimension;

	double potential;
public:
	void set_lenght_x(   const double &x);
	void set_lenght_y(   const double &y);
	void set_dimnension( const int    &d);
	void set_potential(  const double &p);

	double get_lenght_x(){  return lenght_x;  }
	double get_lenght_y(){  return lenght_y;  }
	int    get_dimension(){ return dimension; }
	double get_potential(){ return potential; }

	void WriteDataToFile(std::ofstream &fout);

};

#endif