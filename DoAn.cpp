#include"DoAn.h"

void GetData(SinhVien* &sinh_vien,int& no){
    int n = 0;
    wchar_t ThongTinKhac[1000];
    wchar_t str[500];
    FILE* p;
    p = fopen("SinhVien.csv","r");
    no = soDong();
    SinhVien *ptr = NULL;
    ptr = new SinhVien[no];
    sinh_vien = ptr;
    if(p == NULL){
        cout << "\nKhong mo duoc tep.";
    }
    else{
        while(!feof(p)){
            fgetws(str,500,p);
            n++;
            //test
            cout << "NNNNN:"<< n;
        }
    }
    sinh_vien[0].Fullname[0] = L'A';
    fclose(p);
}