
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <cstdio>
#include <fstream>

using namespace std;

#ifdef WIN32
#define GNUPLUT_NAME "C:\\Games\\gnuplot\\bin\\gnuplot -persist"
#endif 


int main()
{
#ifdef WIN32
	FILE* pipe = _popen(GNUPLUT_NAME, "w");
#endif 
	double victims, killers,time, n;
	double	a1, b1, a2, b2;
	cin >> victims >> killers >> a1 >> b1 >> a2 >> b2 >> time >> n;
	double time_int = time /n;
	vector<double> t_pts;
	for (double i = 0.0; i <= time; i += time_int) {
		t_pts.push_back(i);
	}
	/*
	cout << "t:" << "\n";
	for (double i : t_pts)
		if (i != t_pts[t_pts.size() - 1])
			cout << setprecision(2) << fixed << i << " ";
		else
			cout << setprecision(2) << fixed << i;
	cout << "\n";
	*/
	vector<double> victim;
	vector<double> killer;
	double aOb = a1 / b1;

	
	victims = victims - a2/b2;
	killers = killers - a1/b1;
	for (double t : t_pts) {
		double vi = victims * cos(sqrt(a1 * a2) * t) -
			killers * sqrt(a2) * b1 / (b2 * sqrt(a1)) *
			sin(sqrt(a1 * a2) * t) + a2 / b2;

		double ki = victims * sqrt(a1) * b2 / (b1 * sqrt(a2)) *
			sin(sqrt(a1 * a2) * t) +
			killers * cos(sqrt(a1 * a2) * t) + a1 / b1;
		victim.push_back(vi);
		killer.push_back(ki);
	}
	
	ofstream myfile;
	ofstream myfile2;
	myfile.open("points.txt");
	myfile2.open("points2.txt");

	for (int i = 0; i < t_pts.size(); i++) {
		// victims/killers relations output
		myfile << setprecision(2) << fixed << victim.at(i) << " ";
		myfile << setprecision(2) << fixed << killer.at(i) << "\n";
		// time victims/killers correspondance output
		/*
		myfile << setprecision(2) << fixed << t_pts.at(i) << " ";
		myfile << setprecision(2) << fixed << victim.at(i) << "\n";
		myfile2 << setprecision(2) << fixed << t_pts.at(i) << " ";
		myfile2 << setprecision(2) << fixed << killer.at(i) << "\n";
		*/
	}
	myfile.close();
	myfile2.close();


	/*
	cout << "v:" << "\n";
	for (double v : victim)
		if (v != victim[victim.size() - 1])
			cout << setprecision(2) << fixed << v << " ";
		else
			cout << setprecision(2) << fixed << v;
	cout << "\n";
	cout << "k:" << "\n";
	for (double k : killer)
		if (k != killer[killer.size() - 1])
			cout << setprecision(2) << fixed << k << " ";
		else
			cout << setprecision(2) << fixed << k;
			*/
	if (pipe != NULL) {
		fprintf(pipe, "set style line 1 \
    linecolor rgb '#0060ad' \n ");
		fprintf(pipe, "set style line 2 \
    linecolor rgb '#FF0000' \n ");
		// time - victims/ predators correspondance plot
		//fprintf(pipe, "set multiplot\n");
		//fprintf(pipe, "plot 'points.txt' using 1:2 title 'victims' with line linestyle 1,  'points2.txt' using 1:2 title 'killers' with line linestyle 2 \n");
		// relations plot
		fprintf(pipe, "plot 'points.txt' using 1:2 title 'relations' with line linestyle 1 \n");
	}
}

