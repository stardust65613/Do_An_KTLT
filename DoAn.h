//#include "unicode/utypes.h"
//#include "unicode/stringpiece.h"
//#include "utf8.h"
//#include "unicode/uchar.h"
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cstdlib>
using namespace std;
struct SinhVien{
    char MSSV[11];
    char Fullname[31];
    char Faculty[31];
    int Khoa;
    char DoB[11];
    char img[50];
    char MoTa[1001];
    char ThongTinKhac[10][100];
};
int soDong();
void xuatSinhVien(SinhVien A);
void GetData(SinhVien* &sinh_vien,int& no);