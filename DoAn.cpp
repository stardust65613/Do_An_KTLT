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
    int index;
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
    FILE* p = NULL;
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
int GetLine(char *t,int seek,int& flag){
    FILE* p = NULL;
    char str[100];
    p = fopen("template.html","r");
    fseek(p,seek,SEEK_SET);
    fgets(str,200,p);
    int a = ftell(p);
    if(feof(p)){
        flag = -1;
    }
    fclose(p);
    return a;
}
int writeHTML(SinhVien sv,char *t, int seek){
    FILE* p = NULL;
    p = fopen("D:\\Test2\\23120027.html","w");
    if(p == NULL){
        cout << "\nerror";
    }
    else{
        cout << "\nTao file thanh cong.";
    }
    fseek(p,seek,SEEK_SET);
    fputs(t,p);
    int a = ftell(p);
    fclose(p);
    return a;
}

//void XuLyTT(SinhVien sv,char * data){

//}
void TaoFileHTML(SinhVien sv){
    char *buffer = new char[300];
    int temp = 1;
    int seek = 0;
    int seek2 = 0;
    FILE *p = NULL;
    p = fopen("template.html","r");
    if(p == NULL){
        cout << "\nKhong mo duoc file HTML";
    }
    else{
        while(temp > 0){
            seek = GetLine(buffer,seek,temp);
            seek2 = writeHTML(sv,buffer,seek2);
        }
    }
    delete [] buffer;
}
//void TaoFileHTML(char* dir_name){

  //  fopen
//}
void TaoThuMuc(){
    char *a;
    a = new char[1000];
    cout << "\nNhap vao duong dan:";
    cin >> a;
    int status = 0;// mkdir(a);
    if(status != 0){
        cout << "\nKhong the tao thu muc.";
    }
    else{

    }
    delete [] a;
}