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
    char *a = new char[500];
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




//test xóa
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



//
int GetLine(char* &t,long &seek){
    FILE* p = NULL;
    int flag = -1;
    t = new char[500];
    p = fopen("template.html","r");
    fseek(p,seek,SEEK_SET);
    fgets(t,500,p);
    seek = ftell(p);
    if(!feof(p)){
        flag = 1;
    }
    fclose(p);
    return flag;
}
void writeHTML(SinhVien sv,char *t, long &seek,int flag){
    FILE* p = NULL;
    p = fopen("D:\\Test2\\23120027.html","a");
    if(p == NULL){
        cout << "\nerror";
    }
    fseek(p,seek,SEEK_SET);
    fputs(t,p);
    seek = ftell(p);
    fclose(p);
    delete [] t;
}

//void XuLyTT(SinhVien sv,char * data){

//}
//Them thong tin(đang làm)
bool IsBlockInLine(char *a, char* block_name){
    char b[20] = "\"";
    strcat(a,block_name);
    strcat(a,"\"");
    char c[20] = "\"\\";
    strcat(a,block_name);
    strcat(a,"\"");
    if(strstr(a,b) != NULL && strstr(a,c)!= NULL){
        return true;
    }
    else{
        return false;
    }
}
void TimViTriThemThongTin(char *a,char *tag_name,char* &p,char* &p2){
    char *p;
    if(strcmp(tag_name,"<img") == 0){
        p = strstr(a,"src=\"") + 4;
        p2 = strchr(p,'\"');
    }
}

void ChenThongTin(char *thong_tin_them,char *a,char *vi_tri, bool flag){
    int b = vi_tri - a;
    int n;
    cout << b;
    if(flag == true){
        for(int i = strlen(a) - 1; i > b + strlen(thong_tin_them) ; i--){
            a[i] = a[i - strlen(thong_tin_them)];  
        }
        for(int i = 0; i < strlen(thong_tin_them); i++){
            a[b + i + 1] = thong_tin_them[i];  
        }
    }
    else{
        for(int i = 0; i < strlen(thong_tin_them); i++){
            a[strlen(a) + i] = thong_tin_them[i]; 
        }
        a[strlen(a) + strlen(thong_tin_them)] = '\n';
    }  
    cout << a;
}
void KiemTraVaThemThongTin(SinhVien sv, char *a){
    bool flag;
    char *vi_tri;
    char *vi_tri2;
    char *tt = new char[1000];
    char *tag_name = new char[20];
    if(strstr(a,"title") != NULL){
        return;
        flag = IsBlockInLine(a,"title");
        tt = "HCMUS - ";
        TimViTriThemThongTin(a,"title",vi_tri,vi_tri2);
        strcat(tt,sv.Fullname);
        ChenThongTin(tt,a,vi_tri,flag);
    }
    else if(strstr(a,"<img") != NULL){
        strcpy(tag_name,"<img");
        strcpy(tt,sv.img);
        TimViTriThemThongTin(a,tag_name,vi_tri,vi_tri2);

        ChenThongTin(tt,a,vi_tri,true);
    }
    delete [] tt;
    delete [] tag_name;
}
//Tao file (tam xong)
void TaoFileHTML(SinhVien sv){
    char *buffer;
    int temp = 1;
    long seek = 0;
    long seek2 = 0;
    FILE *p = NULL;
    p = fopen("template.html","r");
    fclose(p);
    if(p == NULL){
        cout << "\nKhong mo duoc file HTML";
    }
    else{
        while(temp > 0){
            cout << temp << endl;
            temp = GetLine(buffer,seek);
            if(temp < 0){
                break;
            }
            KiemTraVaThemThongTin(sv,buffer);
            writeHTML(sv,buffer,seek2,temp);
        }
    }
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