#include<bits/stdc++.h>
#include<graphics.h>
#include<conio.h>

#define lt(a) (int(a+0.5))
#define width 40
#define height 40

using namespace std;

double x[101][101];
double result[101][101]={};
int space=20;
int Ox=300;

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void Khoitao(){
	fstream  f;
	f.open("data.txt", ios::out | ios::in );
	for(int i=1; i<=height; i++){
		for(int j=1; j<=width; j++){
			x[i][j]=GetRandom(1,100);
			f << x[i][j] << " ";	
		}
		f << endl;
	}
	f.close();
}

void Ghikq(){
	fstream  f;
	f.open("ketqua.txt", ios::out | ios::in );
	for(int i=1; i<=height; i++){
		for(int j=1; j<=width; j++){
			f << result[i][j] << " ";	
		}
		f << endl;
	}
	f.close();
}

void Locthong(){
//	double[] signal = (some 1d signal);
	double filter[][3] = {{0, 0.125, 0}, {0.125, 0.25, 0.125}, {0, 0.125, 0}}; // Ma tran loc thong thap
//	double filter[][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}; // Ma tran loc thong cao
//	double filter[][3] = {{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}}; // Ma tran loc thong cao
//	double filter[][3] = {{1, -2, 1}, {-2, 5, -2}, {1, -2, 1}}; // Ma tran loc thong cao
	
	// thuc hien loc
	for (int i=1; i <=height; i++) {
		for(int j=1; j<=width; j++){
			result[i][j] += x[i][j] * filter[1][1];
			if(i-1 > 0){
				result[i][j] += x[i-1][j] * filter[0][1];
			}
			if(j-1 > 0){
				result[i][j] += x[i][j-1] * filter[1][0];
			}
			if(i+1 <= height){
				result[i][j] += x[i+1][j] * filter[2][1];
			}
			if(j+1 <= width){
				result[i][j] += x[i][j+1] * filter[1][2];
			}
			if(i-1 > 0 && j-1 > 0){
				result[i][j] += x[i-1][j-1] * filter[0][0];
			}
			if(i-1 > 0 && j+1 <= width){
				result[i][j] += x[i-1][j+1] * filter[0][2];
			}
			if(i+1 <= height && j-1 > 0){
				result[i][j] += x[i+1][j-1] * filter[2][0];
			}
			if(i+1 <= height && j+1 <= width){
				result[i][j] += x[i+1][j+1] * filter[2][2];
			}
		}
	}
}

void Ve(int viewX, int viewY){
	int dem=20;
	for(int i=viewX; i<height; i++){
		for(int j=viewY; j<width; j++){
			if(dem==1500)
				return;
			dem+=space;
			setcolor(LIGHTBLUE);
			line(dem, x[i][j]+Ox, dem+space, x[i][j+1]+Ox);
		}
		viewY=1;
		dem+=space;
		line(dem, x[i][width]+Ox, dem+space, x[i+1][1]+Ox);
	}
}

void Ve1(int viewX, int viewY){
	int dem=20;
	for(int i=viewX; i<height; i++){
		for(int j=viewY; j<width; j++){
			if(dem==1500)
				return;
			dem+=space;
			setcolor(14);
			line(dem, result[i][j]+Ox, dem+space, result[i][j+1]+Ox);
		}
		viewY=1;
		dem+=space;
		line(dem, result[i][width]+Ox, dem+space, result[i+1][1]+Ox);
	}
}

int main()
{
	Khoitao();
	Locthong();
	Ghikq();
	initwindow(1800,800);
	
	for(int i=1; i<=width; i++){
		for(int j=1; j<=height; j++){
			cleardevice();
			outtextxy(400,50,"LOC THONG THAP");
//			outtextxy(400,50,"LOC THONG CAO");
			line(0,0+Ox,1800,0+Ox);
			line(40,0,40,800);
			Ve(i,j);
			Ve1(i,j);
			Sleep(100);
		}
	}
	getch();
}
