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
char* CapPhat(char* du_lieu){
    int n = strlen(du_lieu);
    char *chuoi_can_cap_phat = new char[n];
    strcpy(chuoi_can_cap_phat,du_lieu);
    cout << chuoi_can_cap_phat;
    return chuoi_can_cap_phat;
}
void ThuHoiBoNho(SinhVien sv){
    delete [] sv.Fullname;
    delete [] sv.Faculty;
    delete [] sv.MoTa;
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
    char *temp = new char[500];
    strcpy(temp,"\0");
    for(int i = 0; i < strlen(data); i++){
        flag = false;
        if(data[i] == ',' && cnt < 8){
            flag = true;
            cnt += 1;
        }
        if(cnt == 1 && flag == true){
            CatChuoi(data,sv.MSSV,1,i - 2);
            index = i + 2;
        }
        else if(cnt == 2 && flag == true){
            CatChuoi(data,temp,index,i - 2);
            sv.Fullname = CapPhat(temp);
            index = i + 2;
        }
        else if(cnt == 3 && flag == true){
            CatChuoi(data,temp,index,i - 2);
            sv.Faculty = CapPhat(temp);
            index = i + 2;
        }
        else if(cnt == 4 && flag == true){
            CatChuoi(data,temp,index,i - 2);
            sv.Khoa = stoi(temp);
            index = i + 2;
        }
        else if(cnt == 5 && flag == true){
            CatChuoi(data,sv.DoB,index,i - 2);
            index = i + 2;
        }
        else if(cnt == 6 && flag == true){
            CatChuoi(data,sv.img,index,i - 2);
            getcwd(temp,500*sizeof(char));
            strcat(temp,"\\Images\\");
            strcat(temp,sv.img);
            strcpy(sv.img,temp);
            index = i + 2;
        }
        else if(cnt == 7 && flag == true){
            CatChuoi(data,temp,index,i - 2);
            sv.MoTa = CapPhat(temp);
            index = i + 2;
        }
        else if(cnt == 6 && i == strlen(data) - 1){
            CatChuoi(data,temp,index,i - 1);
            sv.MoTa = CapPhat(temp);
            index = i + 2;
        }
        if(i == strlen(data) -  1 && cnt == 7){
            cnt = 8;
        }
    }
    if(index < strlen(data) && cnt == 8){
        CatChuoi(data,temp,index - 1,strlen(data) - 1);
        sv.ThongTinKhac = CapPhat(temp);
    }
    else{
        sv.ThongTinKhac = new char[1];
        sv.ThongTinKhac[0] = '\0';
    }
    delete [] temp;
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

int GetLine(char* &t,long &seek, char* file_name){
    FILE* p = NULL;
    int flag = -1;
    t = new char[500];
    p = fopen(file_name,"r");
    fseek(p,seek,SEEK_SET);
    fgets(t,500,p);
    seek = ftell(p);
    if(!feof(p)){
        flag = 1;
    }
    fclose(p);
    return flag;
}
void writeFile(char* &t, long &seek,char* duong_dan){
    FILE* p = NULL;
    p = fopen(duong_dan,"a");
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
    }
    else if(strcmp(name,"<title>") == 0){
        p = strstr(a,"<title>") + strlen("<title>") - 1;
    }
    else if(strcmp(name,"\"") == 0){
        p = strstr(a,name) + strlen(name);
    }
    else if(strcmp(name,"MSSV - Tên sinh viên thực hiện") == 0){
        p = strstr(a,name);
    }
    else if(strcmp(name,"Họ và tên") == 0 || strcmp(name,"MSSV") == 0 || strcmp(name,"Sinh viên khoa") || strcmp(name,"Ngày sinh") || strcmp(name,"Email"))
    {
        p = strstr(a,name) + strlen(name);
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
char *Phone(SinhVien sv){
    int cnt = 0;
    char *a = new char[30];
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
    a[cnt] = '\0';
    strcat(a,"@gmail.com");
    return a;
}
void KiemTraVaThemThongTin(SinhVien sv, char *a,bool &f){
    char *vi_tri;
    char *vi_tri2;
    bool flag = true;
    bool flag2 = f;
    char *tt = NULL;
    tt = new char[100];
    char *name = NULL;
    if(tt == a){
        cout << "error";
    }
    name = new char[50];
    char *phone = NULL;
    phone = Phone(sv);
    //Phone(sv,phone);
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
        strcpy(tt,sv.MoTa);
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
        flag2 = true;
        flag = false;
    }
    else if(strstr(a,"MSSV - Tên sinh viên thực hiện") != NULL){
        flag = false;
        char cpr[50] = "23120027 - Nguyễn Hải Đăng";
        strcpy(name,"MSSV - Tên sinh viên thực hiện");
        strcpy(tt,cpr);
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        int d1 = vi_tri - a;
        int d2 = vi_tri - a + strlen("MSSV - Tên sinh viên thực hiện");
        if(d2 - d1 > strlen("23120027 - Nguyễn Hải Đăng")){
            for(int i = d1 ; i <= d2; i++){
                a[i] = cpr[i - d1];
            }
        }else{
            int d = d2 - d1;
            int dd = strlen(a);
            for(int i = d; i >= 0; i--){
                a[dd + i - 1] = a[dd - 1];
                a[dd - 1] = ' ';
            }
            a[dd + d] = '\0';
            for(int i = d1 ; i <= d2; i++){
                a[i] = cpr[i - d1];
            }
        }
    }
    else if(strstr(a,"\"TextInList\"") != NULL && f == true){
        if(sv.ThongTinKhac[0] != '\0'){
            strcpy(tt,"\0");
            int j = 0;
            int c = 0;
            for(int i = 0; i < strlen(sv.ThongTinKhac); i++){
                if(sv.ThongTinKhac[i] == '\"'){
                    if(c % 2 == 0){
                        c++;
                        sv.ThongTinKhac[i - 1] = ' ';
                        sv.ThongTinKhac[i] = '1';
                    }
                    else{
                        c++;
                        sv.ThongTinKhac[i] = '2';
                    }
                }
                
            }
            for(int i = 0; i < strlen(sv.ThongTinKhac); i++){
                if(sv.ThongTinKhac[i] == '1'){
                    tt[j] = '\n';
                    j++;
                    tt[j] = '\0';
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
                tt[j+1] ='\0';
            }
            tt[j] = '\0';
            strcpy(name,"\"TextInList\"");
        }
        else{
            flag = false;
        }
    }
    else{
        flag = false;
    }
    if(flag == true){
        TimViTriThemThongTin(a,name,vi_tri,vi_tri2);
        ChenThongTin(tt,a,vi_tri);
    }
    f = flag2;
    delete [] tt;
    tt = NULL;
    delete [] name;
    name = NULL;
    delete [] phone;
    phone = NULL;
}
//Tao file (tam xong)
void TaoFileCSS(char *thu_muc){
    char *buffer = NULL;
    int temp = 1;
    long seek = 0;
    long seek2 = 0;
    char *duong_dan = new char[500];
    strcpy(duong_dan,thu_muc);
    strcat(duong_dan,"/personal.css");
    char file_name[13] = "personal.css";
    FILE * p = NULL;
    p = fopen(duong_dan,"w");
    if(p != NULL){
        fputs("\0",p);
    }
    while(temp > 0){
        temp = GetLine(buffer,seek,file_name);
        writeFile(buffer,seek2,duong_dan);    
    }
    delete [] duong_dan;
}
void TaoFileHTML(SinhVien sv, char *thu_muc){
    char *buffer = NULL;
    int temp = 1;
    long seek = 0;
    bool flag = false;
    long seek2 = 0;
    char *duong_dan = new char[500];
    char file_name[14] = "template.html";
    strcpy(duong_dan,thu_muc);
    strcat(duong_dan,"/");
    strcat(duong_dan,sv.MSSV);
    strcat(duong_dan,".html");
    FILE * p = NULL;
    p = fopen(duong_dan,"w");
    if(p != NULL){
        fputs("\0",p);
    }
    while(temp > 0){
        temp = GetLine(buffer,seek,file_name);
        KiemTraVaThemThongTin(sv,buffer,flag);
        writeFile(buffer,seek2,duong_dan);    
    }
    delete [] duong_dan;
}
char *TaoThuMuc(){
    char *a;
    a = new char[1000];
    int status;
    do{
        cout << "\nNhap vao duong dan:";
        cin >> a;
        status = mkdir(a);
        if(status != 0){
            if(errno != EEXIST){
                cout << "\nKhong the tao thu muc.";    
            }
            else{
                break;
            }
        }
    }while(status != 0);
    return a;
}