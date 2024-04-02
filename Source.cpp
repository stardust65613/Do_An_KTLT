#include"DoAn.h"
int main(){
    SinhVien *sv = NULL;
    int so_sv;
    GetData(sv,so_sv);
    xuatSinhVien(sv[0]);
    delete [] sv;
    return 0;
}