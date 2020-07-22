#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
int roll_no,roll_no2,td,tm,ty,cm,cd,cy,sd,sm,sy;
struct personal
{
  int std_roll;
 char std_name[200],std_add[200],p_name[200],m_name[200],ph_no[10];
}st;
struct off
{
    int s_roll,s_att,s_exp;
    char overall_grade[3];
    float t_mark,ca_mark,s_mark;
}of;
COORD coord = {0,0};
void gotoxy(int x, int y)
{
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void add_studentPPdata()
{
    system("CLS");
    gotoxy(15,15);
    printf("**********************************************");
    gotoxy(15,16);
    printf("     ADDITION OF STUDENT'S PERSONAL DATA\n");
    gotoxy(15,17);
    printf("**********************************************");

    FILE *f;
    f=fopen("data.bin","ab+");
    struct personal s;
    int r=0;
    printf("\n\n Enter the Roll number : ");
    scanf("%d",&s.std_roll);
    FILE *c;
    c=fopen("data.bin","rb");
    while(fread(&st,sizeof(st),1,c))
    {
        if(s.std_roll==st.std_roll)
        {
            r=1;
            break;
        }
    }
    fclose(c);
    if (r==1)
    {
        gotoxy(15,19);
        printf("\n\n Roll Number Already Exists");
        getch();
        s_pdata();
    }
    gotoxy(15,21);printf("\nData of Student Roll Number %d",s.std_roll);
    gotoxy(15,23);printf("\n\nEnter the Student's Name:");
    scanf("%s",s.std_name);
    gotoxy(15,25);printf("\n\nEnter the Student's Father's name : ");
    scanf("%s",&s.p_name);
    gotoxy(15,27);printf("\n\nEnter the Student's Mother's name : ");
    scanf("%s",&s.m_name);
    gotoxy(15,29);printf("\n\nEnter the Student's Address : ");
    scanf("%s",&s.std_add);
    gotoxy(15,31);printf("\n\nEnter the Student's Phone Number : ");
    scanf("%s",&s.ph_no);
    fwrite(&s,sizeof(s),1,f);
    fclose(f);
    gotoxy(15,33);printf("\n\n\n The Student Data has been added");
    getch();
    s_pdata();
}

void add_studentOdata()
{
    system("CLS");
    gotoxy(15,15);printf("**********************************************");
    gotoxy(15,16);printf("     ADDITION OF STUDENT'S OFFICIAL DATA");
    gotoxy(15,17);printf("**********************************************");
    FILE*o2;
    o2=fopen("offci.bin","ab+");
    if(o2==NULL)
    {
        gotoxy(15,18);printf("Error");
        getch();
        s_odata();
    }
    int s1=0;
    struct off o3;
    gotoxy(15,20);printf("\n\n Enter the Student's Roll Number :");
    scanf("%d",&o3.s_roll);
    FILE*o4;
    o4=fopen("offci.bin","rb");
    {
        if(o4==NULL)
        exit(1);
    }
    while(fread(&of,sizeof(of),1,o4)==1)
    {
        if(o3.s_roll==of.s_roll)
       {
           gotoxy(15,22);printf("\n\n Roll Number exists");
           s1=1;
           break;
       }

    }
    if(s1==1)
    {
        getch();
        s_odata();
    }
    else
    {
       of.s_roll=o3.s_roll;
       gotoxy(15,22);printf("\n\n Student Data for the Roll Number %d",of.s_roll);
       gotoxy(15,24);printf("\n\n Enter the total Tutorial Mark : ");
       scanf("%f",&of.t_mark);
       gotoxy(15,26);printf("\n\n Enter the Average CA Mark : ");
       scanf("%f",&of.ca_mark);
       gotoxy(15,28);printf("\n\n Enter the Semester Mark : ");
       scanf("%f",&of.s_mark);
       gotoxy(15,30);printf("\n\n Enter the Overall Grade : ");
       scanf("%s",of.overall_grade);
       gotoxy(15,32);printf("\n\n Enter the Student Attendance Percentage : ");
       scanf("%d",&of.s_att);
       gotoxy(15,34);printf("\n\n Enter the Student Exemption Details : ");
       scanf("%d",&of.s_exp);
       fwrite(&of,sizeof(of),1,o2);
       gotoxy(15,36);printf("\n\n The Data has been added");
    }
    fclose(o4);
    fclose(o2);
    getch();
    s_odata();

}

void modify_studentPPdata()
{
    system("CLS");
    gotoxy(15,15);
    printf("*********************************************");
    gotoxy(15,16);
    printf("     MODIFICATION OF STUDENT'S PERSONAL DATA");
    gotoxy(15,17);
    printf("*********************************************");
    FILE *f,*t;
    f=fopen("data.bin","rb");
    t=fopen("temp.bin","wb");
    int flag=0;
    struct personal s;
    gotoxy(15,19);printf("\n\n Enter Roll Number to be modified : ");
    scanf("%d",&s.std_roll);
    while(fread(&st,sizeof(st),1,f)==1)
    {
        if(st.std_roll==s.std_roll)
        {
            flag=1;
            gotoxy(15,21);printf("\n\n Enter the Student's Name : ");
            scanf("%s",&s.std_name);
            gotoxy(15,23);printf("\n\n Enter the Student's Father Name : ");
            scanf("%s",&s.p_name);
            gotoxy(15,25);printf("\n\n Enter the Student's Mother Name : ");
            scanf("%s",&s.m_name);
            gotoxy(15,27);printf("\n\n Enter the Student's Address : ");
            scanf("%s",&s.std_add);
            gotoxy(15,29);printf("\n\n Enter the Student Phone Number : ");
            scanf("%s",&s.ph_no);
            fwrite(&s,sizeof(s),1,t);
        }
        else
        {
            fwrite(&st,sizeof(st),1,t);
        }
    }
    fclose(f);
    fclose(t);
    remove("data.bin");
    rename("temp.bin","data.bin");
    if(flag==1)
    {
       gotoxy(15,31); printf("\n\n Data Modified");
    }
    else
    {
        gotoxy(15,31);printf("\n\n Data Not Found");
    }
    getch();
    s_pdata();
}

void modify_studentOdata()
{
    system("CLS");
    gotoxy(15,15);printf("*********************************************");
    gotoxy(15,16);printf("     MODIFICATION OF STUDENT'S OFFICIAL DATA");
    gotoxy(15,17);printf("*********************************************");
    FILE *o2,*t2;
    o2=fopen("offci.bin","rb");
    if(o2==NULL)
    {
        gotoxy(15,19);printf("\n\n File Does Not Exist ");
        getch();
        s_odata();
    }
    if(t2==NULL)
    {
        gotoxy(15,21);printf("\n\n File Does Not Exist ");
        getch();
        s_odata();
    }
    t2=fopen("oftem.bin","wb");
    int flag=0,s2=0;
    gotoxy(15,23);printf("\n\n Enter the Student's Roll Number whose data has to be modified : ");
    scanf("%d",&s2);
    while(fread(&of,sizeof(of),1,o2)==1)
    {
        if(s2==of.s_roll)
        {
            flag=1;
            gotoxy(15,25);printf("\n\n Enter the total Tutorial Mark : ");
            scanf("%f",&of.t_mark);
            gotoxy(15,27);printf("\n\n Enter the average CA Mark : ");
            scanf("%f",&of.ca_mark);
            gotoxy(15,29);printf("\n\n Enter the Semester Mark : ");
            scanf("%f",&of.s_mark);
            gotoxy(15,31);printf("\n\n Enter the Overall Grade : ");
            scanf("%s",of.overall_grade);
            gotoxy(15,33);printf("\n\n Enter the Student's Attendance Percentage : ");
            scanf("%d",&of.s_att);
            gotoxy(15,35);printf("\n\n Enter the Student's Exemption Details : ");
            scanf("%d",&of.s_exp);
            fwrite(&of,sizeof(of),1,t2);
        }
        else
        {
            fwrite(&of,sizeof(of),1,t2);
        }
    }
    fclose(o2);
    fclose(t2);
    remove("Offci.bin");
    rename("oftem.bin","Offci.bin");
    if(flag==1)
    {
        gotoxy(15,37);printf("\n\n Data Modified");
    }
    else
    {
        gotoxy(15,39);printf("\n\n Data Not Found");
    }
    getch();
    s_odata();
}

void view_studentPPdata()
{
    system("CLS");
    gotoxy(15,15);
    printf("*********************************************");
    gotoxy(15,16);
    printf("     VIEW THE STUDENT'S PERSONAL DATA");
    gotoxy(15,17);
    printf("**********************************************");
    int flag=0;
    int r;
    gotoxy(15,20);printf("\n\n Enter the Student's Roll Number whose data is to be viewed : ");
    scanf("%d",&r);
    FILE *f;
    f=fopen("data.bin","rb");
    while(fread(&st,sizeof(st),1,f))
    {
        if (st.std_roll==r)
        {
            flag=1;
            gotoxy(15,22);printf("\n\n Student's Roll Number : %d",st.std_roll);
            gotoxy(15,24);printf("\n\n Student's Name : %s",st.std_name);
            gotoxy(15,26);printf("\n\n Student's Father Name : %s",st.p_name);
            gotoxy(15,28);printf("\n\n Student's Mother Name : %s",st.m_name);
            gotoxy(15,30);printf("\n\n Student's Address : %s",st.std_add);
            gotoxy(15,32);printf("\n\n Student's Phone Number : %s",st.ph_no);
            gotoxy(15,34);printf("\n\n Back");
            break;
        }
    }
    fclose(f);
    if (flag==0)
    {
        gotoxy(15,36);printf("\n\n Data Not Found");
    }
    getch();
    s_pdata();
}
void view_studentPPsdata()
{
    system("CLS");
    gotoxy(15,15);
    printf("*********************************************");
    gotoxy(15,16);
    printf("     VIEW THE STUDENT'S PERSONAL DATA");
    gotoxy(15,17);
    printf("**********************************************");
    int flag=0;
    int r;
    gotoxy(15,20);printf("\n\n Enter the Student's Roll Number whose data is to be viewed : ");
    scanf("%d",&r);
    FILE *f;
    f=fopen("data.bin","rb");
    while(fread(&st,sizeof(st),1,f))
    {
        if (st.std_roll==r)
        {
            flag=1;
            gotoxy(15,22);printf("\n\n Student Roll Number : %d",st.std_roll);
            gotoxy(15,24);printf("\n\n Student Name : %s",st.std_name);
            gotoxy(15,26);printf("\n\n Student Father Name : %s",st.p_name);
            gotoxy(15,28);printf("\n\n Student Mother Name : %s",st.m_name);
            gotoxy(15,30);printf("\n\n Student Address : %s",st.std_add);
            gotoxy(15,32);printf("\n\n Student Phone Number : %s",st.ph_no);
            gotoxy(15,34);printf("\n\n Back");
            break;
        }
    }
    fclose(f);
    if (flag==0)
    {
        gotoxy(15,36);printf("\n\n Data Not Found");
    }
    getch();
    student_portal();
}

void view_studentOdata()
{
    system("CLS");
    gotoxy(15,15);printf("*********************************************");
    gotoxy(15,16);printf("     VIEW THE STUDENT'S OFFICIAL DATA");
    gotoxy(15,17);printf("**********************************************");
    FILE*o2;
    o2=fopen("offci.bin","rb");
    if(o2==NULL)
    {
        gotoxy(15,19); printf("Error");
        getch();
        s_odata();
    }
    int flag=0,i=0;
    gotoxy(15,21);printf("\n\n Enter the Student's Roll Number whose data is to be viewed : ");
    scanf("%d",&i);
    while(fread(&of,sizeof(of),1,o2)==1)
    {
        if(i==of.s_roll)
        {
            flag=1;
            gotoxy(15,23);printf("\n\n Student Roll Number : %d",of.s_roll);
            gotoxy(15,25);printf("\n\n Student Tutorial Mark : %f",of.t_mark);
            gotoxy(15,27);printf("\n\n Student CA Mark : %f",of.ca_mark);
            gotoxy(15,29);printf("\n\n Student Semester Mark : %f",of.s_mark);
            gotoxy(15,31);printf("\n\n Student Overall Grade : %s",of.overall_grade);
            gotoxy(15,33);printf("\n\n Student Attendance Report : %d",of.s_att);
            gotoxy(15,35);printf("\n\n Student Exemption Report : %d",of.s_exp);
            gotoxy(15,37);printf("\n\n Back");
            break;
        }
    }
    if (flag==0)
    {
        gotoxy(15,23);printf("\n\n Data Not Found");
    }
    fclose(o2);
    getch();
    s_odata();
}

void view_studentOsdata()
{
    system("CLS");
    gotoxy(15,15);printf("*********************************************");
    gotoxy(15,16);printf("     VIEW THE STUDENT'S OFFICIAL DATA");
    gotoxy(15,17);printf("**********************************************");
    FILE*o2;
    o2=fopen("offci.bin","rb");
    if(o2==NULL)
    {
        gotoxy(15,19); printf("\n\n Error");
        getch();
        student_portal();
    }
    int flag=0,i=0;
    gotoxy(15,21);printf("\n\n Enter the Student's Roll Number whose data is to be viewed : ");
    scanf("%d",&i);
    while(fread(&of,sizeof(of),1,o2)==1)
    {
        if(i==(of.s_roll))
        {
            flag=1;
            gotoxy(15,23);printf("\n\n Student Roll Number : %d",of.s_roll);
            gotoxy(15,25);printf("\n\n Student Tutorial Mark : %f",of.t_mark);
            gotoxy(15,27);printf("\n\n Student CA Mark : %f",of.ca_mark);
            gotoxy(15,29);printf("\n\n Student Semester Mark : %f",of.s_mark);
            gotoxy(15,31);printf("\n\n Student Overall Grade : %s",of.overall_grade);
            gotoxy(15,33);printf("\n\n Student Attendance Report : %d",of.s_att);
            gotoxy(15,35);printf("\n\n Student Exemption Report : %d",of.s_exp);
            gotoxy(15,37);printf("\n\n Back");
            break;
        }
    }
    if (flag==0)
    {
        gotoxy(15,23);printf("\n\n Data Not Found");
    }
    fclose(o2);
    getch();
    student_portal();
}
void del_PPdata()
{
    system("CLS");
    gotoxy(15,15);
    printf("*********************************************");
    gotoxy(15,16);
    printf("     DELETE THE STUDENT'S PERSONAL DATA");
    gotoxy(15,17);
    printf("**********************************************");
    int r,flag=0;
    gotoxy(15,19);printf("\n\n Enter the Student's Roll Number whose data is to be deleted : ");
    scanf("%d",&r);
    FILE *f,*t;
    f=fopen("data.bin","rb");
    t=fopen("temp.bin","wb");
    while(fread(&st,sizeof(st),1,f)==1)
    {
        if(st.std_roll!=r)
        {
            fwrite(&st,sizeof(st),1,t);
        }
        else
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        gotoxy(15,21);printf("\n\n Data Deleted");
    }
    else
    {
        gotoxy(15,21);printf("\n\n Data Not Found");
    }
    fclose(f);
    fclose(t);
    remove("data.bin");
    rename("temp.bin","data.bin");
    getch();
    s_pdata();
}
void del_Odata()
{
    system("CLS");
    gotoxy(15,15);printf("*********************************************");
    gotoxy(15,16);printf("     DELETE THE STUDENT'S OFFICIAL DATA");
    gotoxy(15,17);printf("**********************************************");
    int r2,flag=0;
    gotoxy(15,19);printf("\n\n Enter the Student's Roll Number whose data is to be deleted : ");
    scanf("%d",&r2);
    FILE *o2,*t2;
    o2=fopen("offci.bin","rb");
    t2=fopen("otem.bin","wb");
    while(fread(&of,sizeof(of),1,o2)==1)
    {
        if(of.s_roll!=r2)
        {
            fwrite(&of,sizeof(of),1,t2);
        }
        else
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        gotoxy(15,21);printf("\n\n Data Deleted");
    }
    else
    {
        gotoxy(15,21);printf("\n\n Data Not Found");
    }
    fclose(o2);
    fclose(t2);
    remove("offci.bin");
    rename("otem.bin","offci.bin");
    getch();
    s_odata();
}
void add_exam()
{
    system("cls");
    gotoxy(15,15);
    printf("*********************************************");
    gotoxy(15,16);
    printf("     ADD EXAMINATION SCHEDULE");
    gotoxy(15,17);
    printf("**********************************************");
    FILE *p;
    p=fopen("exam.txt","a");
    if(p==NULL)
    {
        printf("\n\n File Not Found ");
        exit(1);
    }
    gotoxy(15,19);printf("\n\n Enter Tutorial Day : ");scanf("%d",&td);gotoxy(15,21);printf("\n\n\tEnter Month: ");scanf("%d",&tm);gotoxy(15,23);printf("\n\n\tEnter Year : ");scanf("%d",&ty);
    gotoxy(15,25);printf("\n\n Enter CA Day : ");scanf("%d",&cd);gotoxy(15,27);printf("\n\n\tEnter Month : ");scanf("%d",&cm);gotoxy(15,29);printf("\n\n\tEnter Year : ");scanf("%d",&cy);
    gotoxy(15,31);printf("\n\n Enter Semester Day : ");scanf("%d",&sd);gotoxy(15,33);printf("\n\n\tEnter Month : ");scanf("%d",&sm);gotoxy(15,35);printf("\n\n\tEnter Year : ");scanf("%d",&sy);

    gotoxy(15,37);printf("\n\n\n Enter the Tutorial Date: %d-%d-%d",td,tm,ty);
    gotoxy(15,39);printf("\n\n\n Enter the CA Date: %d-%d-%d",cd,cm,cy);
    gotoxy(15,41);printf("\n\n\n Enter the Semester Date: %d-%d-%d",sd,sm,sy);
    fprintf(p,"\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",td,tm,ty,cd,cm,cy,sd,sm,sy);
    gotoxy(15,43);printf("\n Exam schedule added");
    fclose(p);
    getch();
    s_odata();

}
void view_exam()
{
    system("cls");
    gotoxy(15,15);
    printf("*********************************************");
    gotoxy(15,16);
    printf("     VIEW THE EXAMINATION SCHEDULE");
    gotoxy(15,17);
    printf("**********************************************");
    FILE *p;
    p=fopen("exam.txt","r");
    {
        if(p==NULL)
        {
            printf("\n\n File Not Found ");
            exit(1);
        }
    }
    while(fscanf(p,"\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",&td,&tm,&ty,&cd,&cm,&cy,&sd,&sm,&sy)!=EOF)
    {
        gotoxy(15,19);printf("\n\n Tutorial Date : %d-%d-%d",td,tm,ty);
        gotoxy(15,21);printf("\n\n CA Date : %d-%d-%d",cd,cm,cy);
        gotoxy(15,23);printf("\n\n Semester Date : %d-%d-%d",sd,sm,sy);
        gotoxy(15,25);printf("\n\n All The Best ! ");

    }
    fclose(p);
    getch();
    student_portal();
}
void teacher_login()
{
    system("cls");
    int id,a,USER_ID=123;
    char pass[20],PASSWORD[20]="TEACHER";
    gotoxy(15,15);
    printf("***************************************");
    gotoxy(15,16);printf("        WELCOME TO TEACHER'S LOGIN");
    gotoxy(15,17);
    printf("***************************************");
    gotoxy(15,19);printf("\n Enter the User Credentials ");
    gotoxy(15,21);printf("\n UserID : ");
    scanf("%d",&id);gotoxy(15,23);
    printf("\n Password : ");scanf("%s",pass);
    if((id==USER_ID)&&(strcmp(pass,PASSWORD)==0))
       {
           teacher_portal();
           getch();
       }
       else{
            printf("\n\n Incorrect Password");
            getch();
            main();
       }
}
void teacher_portal()
{
    int c;
    system("cls");
    gotoxy(15,15);
    printf("*******************************************");
    gotoxy(15,16);printf("           HOME");
    gotoxy(15,17);
    printf("*******************************************");
    gotoxy(15,19);printf("\n\n       1. Student's Personal Information");
    gotoxy(15,21);printf("\n\n       2. Student's Official Information");
    gotoxy(15,23);printf("\n\n       3. Back");
    gotoxy(15,25);printf("\n\n\n\n   Enter Your Choice : ");scanf("%d",&c);
    switch(c)
    {
        case 1:s_pdata();break;
        case 2:s_odata();break;
        case 3:main();break;
        default:break;
    }
    getch();
    teacher_login();
}
void s_pdata()
{
    system("cls");
    int b;
    gotoxy(15,15);
    printf("\n***************************************************************");
    gotoxy(15,16);
    printf("\n WELCOME TO THE STUDENT'S PERSONAL PAGE");
    gotoxy(15,17);
    printf("\n***************************************************************");
    gotoxy(15,19);printf("\n\n     1. Add a Student Data");
    gotoxy(15,21);printf("\n\n     2. Modify the Personal Data of a Student");
    gotoxy(15,23);printf("\n\n     3. View a Student's Personal Data");
    gotoxy(15,25);printf("\n\n     4. Delete a Student's Data");
    gotoxy(15,27);printf("\n\n     5. Back");
    gotoxy(15,29);printf("\n\n\n\n Enter your choice : ");scanf("%d",&b);
    switch(b)
    {
        case 1:add_studentPPdata();break;
        case 2:modify_studentPPdata();break;
        case 3:view_studentPPdata();break;
        case 4:del_PPdata();break;
        case 5:teacher_portal();break;
        default:break;
    }
    getch();
    teacher_portal();
}
void s_odata()
{
    system("cls");
    int b;
    gotoxy(15,15);
    printf("***************************************************************");
    gotoxy(15,16);printf("     WELCOME TO THE STUDENT OFFICIAL PAGE");
    gotoxy(15,17);
    printf("***************************************************************");
    gotoxy(15,19);printf("\n\n       1. Evaluate Student Official Data");
    gotoxy(15,21);printf("\n\n       2. View Student Official Data");
    gotoxy(15,23);printf("\n\n       3. Modify the Official Data of Student");
    gotoxy(15,25);printf("\n\n       4. Delete the Official Data of Student");
    gotoxy(15,27);printf("\n\n       5. Schedule the Examination Time Table");
    gotoxy(15,29);printf("\n\n       6. Back ");
    gotoxy(15,31);printf("\n\n\n\n   Enter your choice : ");scanf("%d",&b);
    switch(b)
    {
        case 1:add_studentOdata();break;
        case 2:view_studentOdata();break;
        case 3:modify_studentOdata();break;
        case 4:del_Odata();break;
        case 5:add_exam();break;
        case 6:teacher_portal();break;
        default: break;;
    }
    getch();
    teacher_portal();
}

void student_login()
{
    system("cls");
    int id1,USER_ID1=456;
    char pass1[20],PASSWORD1[20]="STUDENT";
    gotoxy(15,15);
    printf("***************************************");
    gotoxy(15,16);printf("      WELCOME TO STUDENT'S LOGIN ");
    gotoxy(15,19);
    printf("****************************************");
    gotoxy(15,21);printf("\n\n Enter the User Credentials : ");
    gotoxy(15,23);printf("\n\n UserID : ");scanf("%d",&id1);
    gotoxy(15,25);printf("\n\n Password : ");scanf("%s",pass1);
    if((id1==USER_ID1)&&(strcmp(pass1,PASSWORD1)==0))
       {
           student_portal();
           getch();
       }
       else{
            gotoxy(15,27); printf("INCORRECT PASSWORD");
            getch();
            main();
       }
}
void student_portal()
{
    system("cls");
    int d;
    gotoxy(15,15);
    printf("***************************************************");
    gotoxy(15,16);printf("      MAIN MENU");
    gotoxy(15,17);
    printf("****************************************************");
    gotoxy(15,19);printf("\n\n     1. View Student Personal Data");
    gotoxy(15,21);printf("\n\n     2. View Student Official Data");
    gotoxy(15,23);printf("\n\n     3. View Examinations Scheduled");
    gotoxy(15,25);printf("\n\n     4. Back");
    gotoxy(15,27);printf("\n\n\n\n Enter your choice : ");scanf("%d",&d);
    switch(d)
    {
        case 1:view_studentPPsdata();break;
        case 2:view_studentOsdata();break;
        case 3:view_exam();break;
        case 4:main();break;
        default:break;
    }
    getch();
    student_login();
}
int main()
{
    system("cls");
    int ch;
    gotoxy(15,15);
    printf("************************************************");
    gotoxy(15,16);printf("            XYZ COLLEGE OF TECHNOLOGY\n");
    gotoxy(15,17);
    printf("************************************************");
    gotoxy(15,18);
    printf("************************************************");
    gotoxy(15,19);printf("            COLLEGE PORTAL\n");
    gotoxy(15,20);
    printf("*************************************************");
    gotoxy(15,22);printf("\n\n       1. Teacher Login");
    gotoxy(15,24);printf("\n\n       2. Student Login");
    gotoxy(15,26);printf("\n\n       3. Exit");
    gotoxy(15,28);printf("\n\n\n\n   Enter Your Choice : ");scanf("%d",&ch);
    switch(ch)
    {
        case 1:teacher_login();break;
        case 2:student_login();break;
        case 3:exit(1); break;
        default:break;
    }
    getch();
    return 0;

}
