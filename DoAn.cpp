#include"DoAn.h"
int GetBin(char c){
   int a = (int)c;
   if(a < 0){
       a = a + pow(2,8);
   }
   if(a >= 240 && a <= 247){
       return 4;
   }
   else if(a < 240 && a >= 224){
       return 3;
   }
   else if(a < 224 && a>=192){
       return 2;
   }
   else{
       return 1;
   }
}
int DoDaiChuoiUnicode(char *a){
    int n = 0;
    return n;
}
void CatChuoi(char *a, char *b, int pos1, int pos2){
    for(int i = pos1; i <= pos2; i++){
        b[i - pos1] = a[i];
    }
    b[pos2 + 1 - pos1] = '\0';
}
void LuuSinhVien(SinhVien &sv, char* data){
    bool flag;
    int cnt = 0;
    int index, index2;
    char str[10];
    for(int i = 0; i < strlen(data); i++){
        flag = false;
        if(data[i] == ','){
            flag = true;
            cnt += 1;
        }
        if(cnt == 1 && flag == true){
            CatChuoi(data,sv.MSSV,1,i - 2);
            index = i + 2;
        }
        else if(cnt == 2 && flag == true){
            CatChuoi(data,sv.Fullname,index,i - 2);
            index = i + 2;
        }
        else if(cnt == 3 && flag == true){
            CatChuoi(data,sv.Faculty,index,i - 2);
            index = i + 2;
        }
        else if(cnt == 4 && flag == true){
            CatChuoi(data,str,index,i - 2);
            sv.Khoa = stoi(str);
            index = i + 2;
        }
        else if(cnt == 5 && flag == true){
            CatChuoi(data,sv.DoB,index,i - 2);
            index = i + 2;
        }
        else if(cnt == 6 && flag == true){
            CatChuoi(data,sv.img,index,i - 2);
            index = i + 2;
        }
        else if(cnt == 7 && flag == true){
            CatChuoi(data,sv.MoTa,index,i - 2);
            index = i + 2;
        }
    }
}
int soDong(){
    int num = 0;
    char *a = new char[200];
    FILE* p = NULL;
    p = fopen("SinhVien.csv","r");
    if(p == NULL){
        cout << "\nMo file khong thanh cong.";
    }
    else{
        while(!feof(p)){
            fgets(a,500,p);
            num++;
        }
    }
    delete [] a;
    return num;
}
void GetData(SinhVien* &sinh_vien,int& no){
    int n = 0;
    //char ThongTinKhac[1000];
    char str[500];
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
            fgets(str,500,p);
            LuuSinhVien(sinh_vien[n],str);
            n++;
        }
    }
    fclose(p);
}
void xuatSinhVien(SinhVien sv){
    FILE* p;
    p = fopen("output.txt","a");
    if(p == NULL){
        cout << "\nKhong mo duoc tep.";
    }
    else{
        fputs(sv.Fullname,p);
        fputs(sv.MSSV,p);
        fputs(sv.Faculty,p);
        fputs(sv.img,p);
        fputs(sv.DoB,p);
        fputs(sv.MoTa,p);
    }
    fclose(p);
}