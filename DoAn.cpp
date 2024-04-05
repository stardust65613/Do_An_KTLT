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
void writeHTML(SinhVien sv,char* &t, long &seek,int flag){
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
    t = NULL;
}

//void XuLyTT(SinhVien sv,char * data){

//}
//Them thong tin(đang làm)
bool IsBlockInLine(char *a, char* block_name){
    char b[20] = "\"";
    strcat(b,block_name);
    strcat(b,"\"");
    char c[20] = "\"\\";
    strcat(c,block_name);
    strcat(c,"\"");
    if(strstr(a,b) != NULL && strstr(a,c)!= NULL){
        return true;
    }
    else{
        return false;
    }
}
void TimViTriThemThongTin(char* a,char *name,char* &p,char* &p2){
    if(strcmp(name,"<img") == 0){
        p = strstr(a,"src=\"") + strlen("src=\"") - 1;
        p2 = strchr(p,'\"');
    }
    else if(strcmp(name,"<title>") == 0){
        p = strstr(a,"<title>") + strlen("<title>") - 1;
        p2 = strstr(a,"<\\title>"); 
    }
    else if(strcmp(name,"<") != 0){
        p = strstr(a,name) + strlen(name) + 1;
        p2 = NULL;
    }
}
int DoDai(char *a){
    char b = '\0';
    int cnt = 0;
    while(a[cnt] != b){
        cnt++;
    }
    return cnt;
}
void ChenThongTin(char *thong_tin_them,char *a,char *vi_tri){
    int b = vi_tri - a;
    char *temp = new char[1000];
    
    for(int i = 0; i < strlen(thong_tin_them) + strlen(a); i++){
        if(i <= b){
            temp[i] = a[i];
        } 
        else{
            temp[i +  strlen(thong_tin_them)] = a[i];
        }
    }
    temp[strlen(thong_tin_them) + strlen(a)]= '\0';
    for(int i = 0; i < strlen(thong_tin_them); i++){
        temp[b + i + 1] = thong_tin_them[i];  
    }
    
    strcpy(a,temp);
    delete [] temp;
}
void KiemTraVaThemThongTin(SinhVien sv, char *a){
    char *vi_tri;
    char *vi_tri2;
    char *tt = new char[1000];
    char *name = new char[20];
    if(strstr(a,"title") != NULL){
        strcpy(name,"title");
        strcpy(name,"<title>");
        strcpy(tt,"HCMUS - ");
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        strcat(tt,sv.Fullname);
        ChenThongTin(tt,a,vi_tri);
    }
    else if(strstr(a,"<img") != NULL){
        strcpy(name,"<img");
        strcpy(tt,sv.img);
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    else if(strstr(a,"Personal_FullName") != NULL){
        strcpy(name,"Personal_FullName");
        strcpy(tt,sv.Fullname);
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    else if(strstr(a,"Personal_Department") != NULL){
        strcpy(name,"Personal_Department");
        strcpy(tt,sv.Faculty);
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    else if(strstr(a,"Personal_Phone") != NULL){
        strcpy(name,"Personal_Phone");
        strcpy(tt,"Email :");
        strcat(tt,getPhone(sv.Fullname));
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    else if(strstr(a,"Description") != NULL){
        strcpy(name,"Description");
        strcpy(tt,sv.MoTa);
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    delete [] tt;
    delete [] name;
}
//Tao file (tam xong)
void TaoFileHTML(SinhVien sv){
    char *buffer;
    int temp = 1;
    long seek = 0;
    long seek2 = 0;
    while(temp > 0){
        temp = GetLine(buffer,seek);
        if(temp < 0){
            break;
        }
        KiemTraVaThemThongTin(sv,buffer);
        writeHTML(sv,buffer,seek2,temp);    
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