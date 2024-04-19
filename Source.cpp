#include"DoAn.h"
int main(){
    SinhVien *sv = NULL;
    char *thu_muc = TaoThuMuc();
    int so_sv;
    int flag = GetData(sv,so_sv);
    if(flag == 0){
        for(int i = 0; i < so_sv; i++){
            TaoFileHTML(sv[i],thu_muc);
        }
        TaoFileCSS(thu_muc);
    }
    else{
        so_sv = flag;
    }
    for(int i = 0; i < so_sv; i++){
       ThuHoiBoNho(sv[i]);
    }
    delete [] thu_muc;
    delete [] sv;
    return 0;
}