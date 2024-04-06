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
        if(i == strlen(data) -  1){
            cnt = 8;
        }
    }
    if(index < strlen(data) && cnt != 7){
        CatChuoi(data,sv.ThongTinKhac,index - 1,strlen(data) - 1);
        cout << sv.ThongTinKhac;
    }
}
void printsv(SinhVien a){
    FILE *p = fopen("output.txt","w");
    fputs(a.ThongTinKhac,p);
    fclose(p);
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
    else if(strcmp(name,"\"") == 0){
        p = strstr(a,name) + strlen(name);
        p2 = NULL;
    }
    else if(strcmp(name,"Họ và tên") == 0 || strcmp(name,"MSSV") == 0 || strcmp(name,"Sinh viên khoa") || strcmp(name,"Ngày sinh") || strcmp(name,"Email"))
    {
        p = strstr(a,name) + strlen(name);
        p2 = NULL;
    }
    
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
void Phone(SinhVien sv,char *a){
    int cnt = 0;
    for(int i = 1;i < strlen(sv.Fullname); i++){
        if(sv.Fullname[i-1] == ' '){
            a[cnt] = sv.Fullname[i] + 32;
            cnt++;
            
        }
        else if(i == 1){
            a[cnt] = sv.Fullname[0] + 32;
            cnt++;
        }
    }
    strcat(a,"@gmail.com");
}
void KiemTraVaThemThongTin(SinhVien sv, char *a){
    char *vi_tri;
    char *vi_tri2;
    bool flag = true;
    bool flag2 = false;
    char *tt = new char[1000];
    char *name = new char[50];
    char *phone = new char[30];
    Phone(sv,phone);
    if(strstr(a,"title") != NULL){
        strcpy(name,"title");
        strcpy(name,"<title>");
        strcpy(tt,"HCMUS - ");
        strcat(tt,sv.Fullname);
    }
    else if(strstr(a,"<img") != NULL){
        strcpy(name,"<img");
        strcpy(tt,sv.img);
    }
    else if(strstr(a,"Email:") != NULL){
        strcpy(name,"Email:");
        strcpy(tt,phone);
    }
    else if(strstr(a,"\"Personal_FullName\"") != NULL){
        strcpy(name,"\"Personal_FullName\"");
        strcpy(tt,sv.Fullname);
    }
    else if(strstr(a,"\"Personal_Department\"") != NULL){
        strcpy(name,"\"Personal_Department\"");
        strcpy(tt,sv.Faculty);
    }
    else if(strstr(a,"Personal_Phone") != NULL){
        strcpy(name,"\"Personal_Phone\"");
        strcpy(tt,"\nEmail :");
        strcat(tt,phone);
    }
    else if(strstr(a,"Description") != NULL){
        strcpy(name,"\"Description\"");
        strcpy(tt,sv.ThongTinKhac);
    }
    else if(strstr(a,"Họ và tên:") != NULL){
        strcpy(name,"Họ và tên:");
        strcpy(tt,sv.Fullname);
    }
    else if(strstr(a,"MSSV:") != NULL){
        strcpy(name,"MSSV:");
        strcpy(tt,sv.MSSV);
    }
    else if(strstr(a,"Sinh viên khoa") != NULL){
        strcpy(name,"Sinh viên khoa");
        strcpy(tt,sv.Faculty);
    }
    else if(strstr(a,"Ngày sinh:") != NULL){
        strcpy(name,"Ngày sinh:");
        strcpy(tt,sv.DoB);
    }
    else if(strstr(a,"Sở thích") != NULL){
        flag = true;
        strcpy(tt,"<li>");
        int j = strlen(tt);
        int c = 0;
        for(int i = 0; i < strlen(sv.ThongTinKhac); i++){
            if(sv.ThongTinKhac[i] == '\"'){
                if(c % 2 == 0){
                    c++;
                    sv.ThongTinKhac[i] = '1';
                }
                else{
                    c++;
                    sv.ThongTinKhac[i] = '2';
                }
            }
            else if(sv.ThongTinKhac[i] == ','){
                sv.ThongTinKhac[i] = '\n';
            }

        }
        for(int i = 0; i < strlen(sv.ThongTinKhac); i++){
            if(sv.ThongTinKhac[i] == '1'){
                strcat(tt,"<li>");
                j += strlen("<li>");
            }
            else if(sv.ThongTinKhac[i] == '2'){
                strcat(tt,"</li>");
                j += strlen("</li>");
            }
            else{
                tt[j] = sv.ThongTinKhac[i];
                j++;
            }
        }
        tt[j] = '\0';
    }
    else{
        flag = false;
    }
    if(flag == true){
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    delete [] tt;
    delete [] name;
    delete [] phone;
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