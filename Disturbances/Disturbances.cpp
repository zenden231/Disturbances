// Disturbances.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ПИВ

#include "pch.h"
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

#include <vector>
#include "math.h"

using namespace std;

class Disturbances
{
private:
    double ampl = 3.5;
	vector<double> R; //position 
	vector<double> L; //size of disturbance
	double Ntid;
public: 
	Disturbances(int n)
	{
		cout << "Constructor" << endl;
		for (int i = 0; i < n; i++)
		{
			R.push_back(100);
			L.push_back(1000);
		}
	}

	double getValue(vector<double> r, double Ne = 1)
	{
		for (unsigned int i = 0; i < r.size(); i++)
		{
			Ntid *= exp(-pow((r[i]-R[i]),2)/L[i]);
		}
		Ntid = Ne*(ampl*Ntid + 1);
		return (Ntid);
	}

	void showParameters()
	{
		cout << "Amplitude = " << ampl << "\n";
		cout << "R: ";
		for (unsigned int i = 0; i < R.size(); i++)
		{
			cout << R[i] << " ";
		}
		cout << endl;
		cout << "L: ";
		for (unsigned int i = 0; i < L.size(); i++)
		{
			cout << L[i] << " ";
		}
		cout << endl;
		//cout << "Ntid = " << Ntid;
	}
};

int main()
{
	cout << fixed;
	cout.precision(2);
	int DIM = 2; //dimension
	if (DIM == 2)
		vector<vector<double>> GRID;
	else if (DIM == 3)
		vector<vector<vector<double>>> GRID;
	double Xmin = 0;
	double Xmax = 200;
	double Ymin = 0;
	double Ymax = 200;
	int s = 10; //number of step
	double Xstep = (Xmax - Xmin) / s;
	double Ystep = (Ymax - Ymin) / s;
	double X = 0;
	double Y = 0;
	Disturbances TID(DIM);
	vector<double> m(DIM);

	FILE *file = fopen("output.txt", "w");

	for (int i = 0; i <= s; i++)
	{
		for (int j = 0; j <= s; j++)
		{
			m[0] = X;
			m[1] = Y;
			cout << m[0] << " " << m[1] << " " << TID.getValue(m, 1) << "\n";
			fprintf(file, " %10.4f %10.4f %10.4f \n", m[0], m[1], TID.getValue(m, 1));
			Y = Y + Ystep;
		}
		fprintf(file, "\n");
		Y = Ymin;
		X = X + Xstep;
	}

	fclose(file);

	cout << "Ntid = " << TID.getValue(m, 1) << "\n";
	cout << "TID: \n"; TID.showParameters();
	cout << endl;

	return 0;
}