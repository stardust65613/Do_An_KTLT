#include"DoAn.h"
int main(){
    SinhVien *sv = NULL;
    char *thu_muc = TaoThuMuc();
    int so_sv;
    GetData(sv,so_sv);
    for(int i = 0; i < so_sv; i++){
        TaoFileHTML(sv[i],thu_muc);
    }
    for(int i = 0; i < so_sv; i++){
        ThuHoiBoNho(sv[i]);
    }
    TaoFileCSS(thu_muc);
    delete [] thu_muc;
    delete [] sv;
    return 0;
}