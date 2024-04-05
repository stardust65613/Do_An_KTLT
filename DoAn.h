//#include "unicode/utypes.h"
//#include "unicode/stringpiece.h"
//#include "utf8.h"
//#include "unicode/uchar.h"
#ifndef _DOAN_H_
#define _DOAN_H
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cstdlib>
#include<sys/stat.h>
#include<cstdio>
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
void TaoFileHTML(SinhVien sv);
int GetLine(char* &t,long &seek);
void writeHTML(SinhVien sv,char* &t,long &seek,int flag);
void xuatSinhVien(SinhVien A);
void GetData(SinhVien* &sinh_vien,int& no);
#endif