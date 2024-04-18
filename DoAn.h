//#include "unicode/utypes.h"
//#include "unicode/stringpiece.h"
//#include "utf8.h"
//#include "unicode/uchar.h"
#ifndef _DOAN_H_
#define _DOAN_H_
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/stat.h>
//#include<direct.h>
#include<errno.h>
using namespace std;
struct SinhVien{
    char MSSV[11];
    char *Fullname;
    char *Faculty;
    int Khoa;
    char DoB[11];
    char img[51];
    char *MoTa;
    char *ThongTinKhac;
};
void ThuHoiBoNho(SinhVien sv);
int soDong();
void printsv(SinhVien a);
void TaoFileHTML(SinhVien sv, char* thu_muc);
int GetLine(char* &t,long &seek, char* file_name);
void writeHTML(char* &t,long &seek,int flag, char* duong_dan);
void xuatSinhVien(SinhVien A);
int GetData(SinhVien* &sinh_vien,int& no);
char *TaoThuMuc();
void TaoFileCSS(char *thu_muc);
#endif