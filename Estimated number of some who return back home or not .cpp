#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <math.h>


using namespace std;

struct MOBILE{
double data[6];
double dis;
int mesyus_n,lives_n;
};

struct AREA {
double data[3];
double return_p,nreturn_p;
};



class Returnp {
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

Returnp::Returnp (int time,char *ac)
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

void Returnp::mesyufile (char *ac)
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


void Returnp::livefile (char *ac)
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
		if (mobiles.at(a).data[3] == mesyus.at(b).data[0])
		{
			lat1=mesyus.at(b).data[1];
			lng1=mesyus.at(b).data[2];
			mobiles.at(a).mesyus_n=b;

		}
		 
		
	}
	mobiles.at(a).lives_n=99999;

	for (int b=0;b<lives.size();b++)
	{
	if (mobiles.at(a).data[4] == lives.at(b).data[0])
	{
	lat2=lives.at(b).data[1];
	lng2=lives.at(b).data[2];
	mobiles.at(a).lives_n=b;
	}
	
	
	}
	mobiles.at(a).dis = distance(lat1,lng1,lat2,lng2);

}

}

double Returnp::distance(double lat1, double lng1, double lat2, double lng2){
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

	return distance;
}

void Returnp::calculate_return()
{
	for (int a=0;a<mesyus.size();a++) //帰宅困難者数（and可能者）の初期化
{
	mesyus.at(a).return_p=0;
	mesyus.at(a).nreturn_p=0;
}

for (int a=0;a<lives.size();a++)
{
	lives.at(a).return_p=0;
	lives.at(a).nreturn_p=0;
}

for (int a=0;a<mobiles.size();a++) //帰宅困難者数（and可能者）の推定
{


	if(mobiles.at(a).lives_n == 99999 ||mobiles.at(a).mesyus_n ==99999)
	continue;

	else if(mobiles.at(a).dis>=20000)
	{mesyus.at(mobiles.at(a).mesyus_n).return_p=mesyus.at(mobiles.at(a).mesyus_n).return_p+mobiles.at(a).data[5];
	lives.at(mobiles.at(a).lives_n).return_p=lives.at(mobiles.at(a).lives_n).return_p+mobiles.at(a).data[5];
	}

	else if (10000<mobiles.at(a).dis && 20000<mobiles.at(a).dis)
	{
	mesyus.at(mobiles.at(a).mesyus_n).return_p=mesyus.at(mobiles.at(a).mesyus_n).return_p+mobiles.at(a).data[5]/2;
	mesyus.at(mobiles.at(a).mesyus_n).nreturn_p=mesyus.at(mobiles.at(a).mesyus_n).nreturn_p+mobiles.at(a).data[5]/2;
	lives.at(mobiles.at(a).lives_n).return_p=lives.at(mobiles.at(a).lives_n).return_p+mobiles.at(a).data[5]/2;
	lives.at(mobiles.at(a).lives_n).nreturn_p=lives.at(mobiles.at(a).lives_n).nreturn_p+mobiles.at(a).data[5]/2;
	}
	else if (mobiles.at(a).dis<=10000)
	{mesyus.at(mobiles.at(a).mesyus_n).nreturn_p=mesyus.at(mobiles.at(a).mesyus_n).nreturn_p+mobiles.at(a).data[5];
	lives.at(mobiles.at(a).lives_n).nreturn_p=lives.at(mobiles.at(a).lives_n).nreturn_p+mobiles.at(a).data[5];
	}
}
};

void Returnp::output(int which,string output_file){
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
	cout << "ファイルの書き込みが終わりました"<<endl;

}

int main (int argc, char *argv[])
{

string a;
int filetype,time;
cout << "推定したい時間帯は？:";
cin >> time;
Returnp file(time,argv[3]);
file.mesyufile(argv[1]);
file.livefile(argv[2]);
file.calculate_distance();
file.calculate_return();

cout <<"ファイル形式は？ 1:メッシュ,2:市区町村:"<<endl;
cin >> filetype;
cout <<"ファイル名は？(txt付き):"<<endl;
cin >>a; 
file.output(filetype,a);

cout << file.mobiles.size();
	
return 0;
}





