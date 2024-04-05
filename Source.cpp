#include"DoAn.h"
int main(){
    SinhVien *sv = NULL;
    int so_sv;
    cout << "Hello world";
    GetData(sv,so_sv);
    TaoFileHTML(sv[0]);
    delete [] sv;
    return 0;
}