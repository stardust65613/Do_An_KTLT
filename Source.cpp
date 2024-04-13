#include"DoAn.h"
int main(){
    SinhVien *sv = NULL;
    char *thu_muc = TaoThuMuc();
    int so_sv = soDong();
    cout << so_sv;
    for(int i = 0; i < so_sv; i++){
        GetData(sv);
        TaoFileHTML(*sv,thu_muc);
        ThuHoiBoNho(*sv);
        delete sv;
    }
    TaoFileCSS(thu_muc);
    delete [] thu_muc;
    return 0;
}