#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<cstdlib>
using namespace std;
struct SinhVien{
    char MSSV[11];
    wchar_t Fullname[31];
    wchar_t Faculty[31];
    int Khoa;
    char DoB[11];
    char img[50];
    wchar_t MoTa[1001];
    wchar_t ThongTinKhac[10][100];
};
int soDong();
void xuatSinhVien(SinhVien A);
void GetData(SinhVien* &sinh_vien,int& no);