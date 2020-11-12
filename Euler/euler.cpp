#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using std::endl;
using std::ofstream;
using std::cerr;

// My function, which I like to integrate
float diffeq(double a,double b,double x){
	double c = a*pow(x,5)+b;
	return c;
}

// Single Euler step
float euler(double dt,double f0,double a,double b,double x){
	double fd = diffeq(a,b,x);
	double fn = f0 + dt*fd;
	return fn;
}

// Routine to solve 'diffeq' using 'euler'
void integrate(double dt, double a, double b, double xstart, double xend){
	double num = abs ((xend-xstart)/dt);
	int inum = (int)num;
	double flist[inum]; // num is converted to int
	flist[0] = diffeq(a,b,xstart);
	double xlist[inum];
	xlist[0] = xstart;

	ofstream datfile; // create file pointer variable
	datfile.open("INT_data.dat"); // initialize 'datfile' to open 'INT_data.dat' for writing
	if( !datfile ) { // file couldn't be opened
    		cerr << "Error: file could not be opened" << endl;
      		exit(1);
   	}

	for (int i = 1; i < inum; i++){
		flist[i] = euler(dt,flist[i-1],a,b,xlist[i-1]);
		xlist[i] = xlist[i-1] + dt;
		if (i % 10 == 0){
			datfile << xlist[i] << " " << flist[i] << endl;
		}
	}
	datfile.close(); // close file pointer and flush all pending IO operations to it
}

int main(){
	double a = 1.0;
	double b = 0.2;
	double dt = 0.001;
	double xstart = -1.0;
	double xend = 1.0;
	integrate(dt,a,b,xstart,xend);
	return 0;
}
