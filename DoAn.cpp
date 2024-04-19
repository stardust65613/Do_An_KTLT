#include"DoAn.h"
int GetNum(char c){
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
    int length = 0;
    int temp =  0;
    while(n < strlen(a)){
        temp = GetNum(a[n]);
        n += temp;
        length++;
    }
    return length;
}
void GetChar(int len,int pos,char * a,char *b){
    for(int i = 0; i < len; i++){
        a[i] = b[pos + i];
    }
    a[len] = '\0';
}
char XoaDauTiengViet(char *a){
    char c;
    if(strstr(a,"Ư") != NULL || strstr(a,"Ứ") != NULL || strstr(a,"Ừ") != NULL || strstr(a,"Ử") != NULL || strstr(a,"Ữ") != NULL || strstr(a,"Ự") != NULL){
        c = 'u';
    }
    else if(strstr(a,"Ô") != NULL || strstr(a,"Ơ") != NULL || strstr(a,"Ố") != NULL || strstr(a,"Ớ") != NULL || strstr(a,"Ồ") != NULL || strstr(a,"Ờ") != NULL || strstr(a,"Ỗ") != NULL || strstr(a,"Ỡ") != NULL || strstr(a,"Ổ") != NULL || strstr(a,"Ở") != NULL || strstr(a,"Ộ") != NULL || strstr(a,"Ợ") != NULL){
        c = 'o';
    }
    else if(strstr(a,"Đ") != NULL){
        c = 'd';
    }
    else if(strstr(a,"Ă") != NULL || strstr(a,"Â") != NULL || strstr(a,"Ắ") != NULL || strstr(a,"Ấ") != NULL || strstr(a,"Ẳ") != NULL || strstr(a,"Ẩ") != NULL || strstr(a,"Ẵ") != NULL || strstr(a,"Ẫ") != NULL || strstr(a,"Ặ") != NULL || strstr(a,"Ậ") != NULL || strstr(a,"Á") != NULL || strstr(a,"À") != NULL || strstr(a,"Ả") != NULL || strstr(a,"Ã") != NULL || strstr(a,"Ạ") != NULL){
        c = 'a';
    }
    else if(strstr(a,"Ê") != NULL || strstr(a,"Ế") != NULL || strstr(a,"Ề") != NULL || strstr(a,"Ễ") != NULL || strstr(a,"Ể") != NULL || strstr(a,"Ệ") != NULL){
        c = 'e';
    }
    else if(strstr(a,"Í") != NULL || strstr(a,"Í") != NULL || strstr(a,"Ì") != NULL || strstr(a,"Ĩ") != NULL || strstr(a,"Ỉ") != NULL || strstr(a,"Ị") != NULL){
        c = 'i';
    }
    else{
        c = 'y';
    }
    return c;
}
char* CapPhat(char* du_lieu){
    int n = strlen(du_lieu);
    char *chuoi_can_cap_phat = new char[n + 1];
    strcpy(chuoi_can_cap_phat,du_lieu);
    return chuoi_can_cap_phat;
}
void ThuHoiBoNho(SinhVien sv){
    delete [] sv.Fullname;
    delete [] sv.Faculty;
    delete [] sv.MoTa;
    delete [] sv.ThongTinKhac;
}
void CatChuoi(char *a, char *b, int pos1, int pos2){
    for(int i = pos1; i <= pos2; i++){
        b[i - pos1] = a[i];
    }
    b[pos2 + 1 - pos1] = '\0';
}
bool KiemTraDuLieu(char *a,int limit){
    if(DoDaiChuoiUnicode(a) <= limit){
        return true;
    }
    else{
        cout << "\nSo ki tu cua du lieu " << a << " la " << strlen(a) << " vuot qua so ki tu cho phep.\nSo ki tu cho phep:"<< limit;
        return false;
    }
}
int LuuSinhVien(SinhVien &sv, char* data){
    bool flag;
    int k = 0;
    int cnt = 0;
    int cnt2 = 0;
    int index;
    int limit;
    char *temp = new char[500];
    strcpy(temp,"\0");
    for(int i = 0; i < strlen(data); i++){
        flag = false;
        if(data[i] == '\"' && cnt < 8){
            cnt2 += 1;
            if(cnt2 % 2 == 0 && cnt2 != 0){
                cnt++;
                flag = true;
            }
        }
        if(cnt == 1 && flag == true){
            CatChuoi(data,temp,1,i - 1);
            index = i + 3;
            limit = 10;
            CatChuoi(data,sv.MSSV,1,i - 1);
        }
        else if(cnt == 2 && flag == true){
            CatChuoi(data,temp,index,i - 1);
            limit = 30;
            sv.Fullname = CapPhat(temp);
            index = i + 3;
        }
        else if(cnt == 3 && flag == true){
            CatChuoi(data,temp,index,i - 1);
            limit = 30;
            sv.Faculty = CapPhat(temp);
            index = i + 3;
        }
        else if(cnt == 4 && flag == true){
            CatChuoi(data,temp,index,i - 1);
            sv.Khoa = stoi(temp);
            index = i + 3;
        }
        else if(cnt == 5 && flag == true){
            CatChuoi(data,temp,index,i - 1);
            limit = 10;
            CatChuoi(data,sv.DoB,index,i - 1);
            index = i + 3;
        }
        else if(cnt == 6 && flag == true){
            CatChuoi(data,sv.img,index,i - 1);
            getcwd(temp,500*sizeof(char));
            strcat(temp,"\\Images\\");
            strcat(temp,sv.img);
            limit = 50;
            strcpy(sv.img,temp);
            
            index = i + 3;
        }
        else if(cnt == 7 && flag == true){
            CatChuoi(data,temp,index,i - 1);
            limit = 1000;
            sv.MoTa = CapPhat(temp);
            
            index = i + 3;
        }
        else if(cnt == 6 && i == strlen(data) - 1){
            CatChuoi(data,temp,index,i);
            limit = 1000;
            sv.MoTa = CapPhat(temp);
            index = i + 3;
        }
        else if(i == strlen(data) -  1 && cnt == 7){
            cnt = 8;
            index = i + 3;
        }
        if(flag == true && KiemTraDuLieu(temp,limit) == false){
            k = -1;
        }
    }
    if(index < strlen(data) && cnt == 8){
        CatChuoi(data,temp,index - 1,strlen(data) + 1);
        limit = 1000;
        if(KiemTraDuLieu(temp,limit) == false){
            k = -1;
        }
        sv.ThongTinKhac = CapPhat(temp);
    }
    else{
        sv.ThongTinKhac = new char[2];
        sv.ThongTinKhac[0] = '\0';
    }
    
    delete [] temp;
    return k;
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
int GetData(SinhVien* &sinh_vien,int& no){
    int n = 0;
    int flag = 0;
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
            flag = LuuSinhVien(sinh_vien[n],str);
            n++;
            if(flag != 0){
                return n;
            }
        }
    }
    fclose(p);
    return 0;
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
    if(p != NULL){
        fseek(p,seek,SEEK_SET);
        fputs(t,p);
        seek = ftell(p);
        fclose(p);
    }
    else{
        cout << "khong the ghi file";
    }
    delete [] t;
    t = NULL;
}
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
    int cnt = 1;
    int len = 0;
    char c[5];
    char *a = new char[30];
    len = GetNum(sv.Fullname[0]);
    char l[4];
    if(len == 1){
        a[0] = sv.Fullname[0] + 32;
    }
    else{
        GetChar(len,0,c,sv.Fullname);
        a[0] = XoaDauTiengViet(c);
    }
    for(int i = 1;i < strlen(sv.Fullname); i++){
        if(sv.Fullname[i-1] == ' '){
            len = GetNum(sv.Fullname[i]);
        }
        else{
            len = 0;
        }
        if(len != 0){
            if(len != 1){
                GetChar(len,i,c,sv.Fullname);
                a[cnt] = XoaDauTiengViet(c);
                cnt++; 
            }
            else{
                a[cnt] = sv.Fullname[i] + 32;
                cnt++;
            }
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
    char *temp = NULL;
    char *name = NULL;
    if(tt == a){
        cout << "error";
    }
    temp = new char[500];
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
                        temp[i - 1] = ' ';
                        temp[i] = '1';
                    }
                    else{
                        c++;
                        temp[i] = '2';
                    }
                }
                else{
                    temp[i] = sv.ThongTinKhac[i];
                }
            }
            temp[strlen(sv.ThongTinKhac)] = '\0';
            for(int i = 0; i < strlen(temp); i++){
                if(temp[i] == '1'){
                    tt[j] = '\n';
                    j++;
                    tt[j] = '\0';
                    strcat(tt,"<li>");
                    j += strlen("<li>");
                }
                else if(temp[i] == '2'){
                    strcat(tt,"</li>");
                    j += strlen("</li>");
                }
                else{
                    tt[j] = temp[i];
                    j++;
                }
                tt[j+1] ='\0';
            }
            tt[j] = '\0';
            temp = NULL;
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
    delete [] temp;
    temp = NULL;
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
    fclose(p);
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