#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <math.h>


using namespace std;

struct MOBILE{ //for Mobile spatial statistics data 
double data[6]; 
//data[1]	Date(20170400)
//data[2]	Weekdays or Holidays
//data[3]	Time (24-hour unit)
//data[4]	Location (mesh ID(12 x 12 250 mesh units))
//data[5]	Hometown (city code) 
//data[6]	Total population

double dis; //Distance from Location mesh to Hometown code
int mesyus_n,lives_n; //The link mesh ID of mesh data and city code of city data
};

struct AREA { //for mesh data and city data
double data[3]; 
//1	Mesh ID (12 x 12 250 mesh units) or City code
//2	Latitude of the center point in mesh or city 
//3	Longitude of the center point in mesh(Calculated from GIS) or city

double return_p,nreturn_p; // people who are unable or enable to return home after disasters
};



class Returnp { //for Estimate people who are unable or enable to return home after disasters
private:
MOBILE mobile;
AREA area;
double lat1,lat2,lng1,lng2;
double pi;
double earth_radius;
int data,Time;

FILE *fp;

public:
vector<MOBILE> mobiles; 
vector<AREA> mesyus,lives;
Returnp (int time,char *ac);
void calculate_distance(); 
void calculate_return();
double distance (double lat1, double lng1, double lat2, double lng2);
void mesyufile (char *ac);
void livefile (char *ac);
void output(int which,string output_file);

};

Returnp::Returnp (int time,char *ac) //Import, read and put mobile spatial statistics file in mobile.data[] of this Returnp class.
{
	
	if ((this->fp = fopen(ac,"r")) == NULL)
		{
		cout << "ファイルを出力できません！" << endl;
		}

		do{
		fscanf(fp, "%lf,%lf,%lf,%lf,%lf,%lf",&this->mobile.data[0],&this->mobile.data[1],&this->mobile.data[2],&this->mobile.data[3],&this->mobile.data[4],&this->mobile.data[5]);
		if (this->mobile.data[2]==time)
		this->mobiles.push_back(this->mobile);
		}while(this->mobile.data[2]<=time);
		
	fclose(this->fp);
	Time =time;
	cout << Time <<"時のモバイル空間統計の読み込み完了" <<endl;
	
}

void Returnp::mesyufile (char *ac) //Import,read and put the mesh file in mesyu.data of this Returnp class.
{
		if ((this->fp = fopen(ac,"r")) == NULL)
		{
		cout << "ファイルを出力できません！" << endl;
		}

		while(fscanf(fp, "%lf %lf %lf",&this->area.data[0],&this->area.data[1],&this->area.data[2])!=EOF)
		{this->mesyus.push_back(this->area);
		};

			fclose(this->fp);
}


void Returnp::livefile (char *ac) //Import,read and put the city file in live.data of this Returnp class.
{
	
		if ((this->fp = fopen(ac,"r")) == NULL)
		{
		cout << "ファイルを出力できません！" << endl;
		}

		while(fscanf(fp, "%d,%lf,%lf",&this->data,&this->area.data[1],&this->area.data[2])!=EOF)
		{
			this->area.data[0]= this->data;
			this->lives.push_back(this->area);
		};
fclose(this->fp);
}



void Returnp::calculate_distance(){

for (int a=0;a<mobiles.size();a++)
{	
	mobiles.at(a).mesyus_n=99999;
	for (int b=0;b<mesyus.size();b++)
	{
		if (mobiles.at(a).data[3] == mesyus.at(b).data[0]) //1.	Matching mesh code of mobile.data and the longitude/latitude data of mesyu.data.
		{
			lat1=mesyus.at(b).data[1];
			lng1=mesyus.at(b).data[2];
			mobiles.at(a).mesyus_n=b;

		}
		 
		
	}
	mobiles.at(a).lives_n=99999;

	for (int b=0;b<lives.size();b++)
	{
	if (mobiles.at(a).data[4] == lives.at(b).data[0]) //2.	Matching city code of mobile.data and the longitude/latitude data of live.data.
	{
	lat2=lives.at(b).data[1];
	lng2=lives.at(b).data[2];
	mobiles.at(a).lives_n=b;
	}
	
	
	}
	mobiles.at(a).dis = distance(lat1,lng1,lat2,lng2); //3.	double distance (double lat1, double lng1, double lat2, double lng2);

}

}

double Returnp::distance(double lat1, double lng1, double lat2, double lng2) //①	import longitude/latitude data of 2 point(mesh and city).
 { 
	pi = 3.14159265359 ;
	earth_radius = 6378140;

	double rlat1 = lat1 * pi / 180;
	double rlng1 = lng1 * pi / 180;
	double rlat2 = lat2 * pi / 180;
	double rlng2 = lng2 * pi / 180;

	double a =
		sin(rlat1) * sin(rlat2) +
		cos(rlat1) * cos(rlat2) *
		cos(rlng1 - rlng2);
	double rr = acos(a);


	double distance = earth_radius * rr;

	return distance; //②	Transform the 2data to radian and calculate the distance.
 }

void Returnp::calculate_return()
{
	for (int a=0;a<mesyus.size();a++) //1.	Initialization of return_p and nreturn_p in both mesh and live
{
	mesyus.at(a).return_p=0;
	mesyus.at(a).nreturn_p=0;
}

for (int a=0;a<lives.size();a++)
{
	lives.at(a).return_p=0;
	lives.at(a).nreturn_p=0;
}

for (int a=0;a<mobiles.size();a++) //2.	Calculate the people who are unable or enable to return home after disasters in the 3case.
{


	if(mobiles.at(a).lives_n == 99999 ||mobiles.at(a).mesyus_n ==99999)
	continue;

	else if(mobiles.at(a).dis>=20000) //1.	20000 <= Distance between mesh and residential area 
	{mesyus.at(mobiles.at(a).mesyus_n).return_p=mesyus.at(mobiles.at(a).mesyus_n).return_p+mobiles.at(a).data[5]; //→100% of people are unable to return home 
	lives.at(mobiles.at(a).lives_n).return_p=lives.at(mobiles.at(a).lives_n).return_p+mobiles.at(a).data[5];//→100% of people are unable to return home 
	}

	else if (10000<mobiles.at(a).dis && 20000<mobiles.at(a).dis) //2.	10000<= Distance between mesh and residential area <=20000
	{
	mesyus.at(mobiles.at(a).mesyus_n).return_p=mesyus.at(mobiles.at(a).mesyus_n).return_p+mobiles.at(a).data[5]/2; //→50% of people are enable to return home 
	mesyus.at(mobiles.at(a).mesyus_n).nreturn_p=mesyus.at(mobiles.at(a).mesyus_n).nreturn_p+mobiles.at(a).data[5]/2; //→50% of people are unable to return home 
	lives.at(mobiles.at(a).lives_n).return_p=lives.at(mobiles.at(a).lives_n).return_p+mobiles.at(a).data[5]/2; //→50% of people are enable to return home 
	lives.at(mobiles.at(a).lives_n).nreturn_p=lives.at(mobiles.at(a).lives_n).nreturn_p+mobiles.at(a).data[5]/2; //→50% of people are unable to return home 
	}
	else if (mobiles.at(a).dis<=10000) //3.	Distance between mesh and residential area <=10000
	{mesyus.at(mobiles.at(a).mesyus_n).nreturn_p=mesyus.at(mobiles.at(a).mesyus_n).nreturn_p+mobiles.at(a).data[5]; //100% of people are enable to return home 
	lives.at(mobiles.at(a).lives_n).nreturn_p=lives.at(mobiles.at(a).lives_n).nreturn_p+mobiles.at(a).data[5]; //100% of people are enable to return home 
	}
}
};

void Returnp::output(int which,string output_file){ //1.	output data file either people who are unable or enable to return home via mesh or city code.
	ofstream fout(output_file);
	if (!fout.is_open())
	{
		cout << "ファイルは出力できません";
	}
	fout << Time<< "時" <<endl;
	switch (which)
	{
	case 1:
	fout << "メッシュ別の統計" <<endl;
	for(int a=0;a<mesyus.size();a++)
	fout <<mesyus.at(a).data[0]<<","<<mesyus.at(a).nreturn_p <<","<<mesyus.at(a).return_p<< endl;
	break;

	case 2:
	fout << "市区町村別の統計" <<endl;
	for(int a=0;a<lives.size();a++)
	fout <<lives.at(a).data[0]<<","<<lives.at(a).nreturn_p <<","<<lives.at(a).return_p<<endl;

	default:
		break;
	}
	fout.close();
	cout << "Finish the wrtting file"<<endl;

}

int main (int argc, char *argv[])
{

string a;
int filetype,time;
cout << "What time data you want？:";  
cin >> time; //input time when you want to get data
Returnp file(time,argv[3]); //input Mobile spatial statistics file
file.mesyufile(argv[1]); //input mesh file
file.livefile(argv[2]); //input city file
file.calculate_distance(); //calculate distance mesh and citu 
file.calculate_return(); //calculate the people who are unable or enable to return home after disasters 

cout <<"calculate people via mesh or city？ 1:mesh,2:city:"<<endl;
cin >> filetype; //calculate people via mesh or city??
cout <<"what is file name？(should add .txt ):"<<endl;
cin >>a; //what file name??
file.output(filetype,a); //output file 
	
return 0;
}





