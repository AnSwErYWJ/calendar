#include <stdio.h>
#include <string.h>
#include<stdlib.h>

void view_day(int day,int month_day,int week)
{
    char WEEK[9];
    if (day<=0||day>month_day)
    {
        fprintf(stderr,"Error:the entered DAY is invalid\n");
        exit(6);
    }
    switch (week)
    {
    case 0:
        strcpy (WEEK,"SUNDAY");
        break;
    case 1:
        strcpy (WEEK,"MONDAY");
        break;
    case 2:
        strcpy (WEEK,"TUESDAY");
        break;
    case 3:
        strcpy (WEEK,"WEDNESDAY");
        break;
    case 4:
        strcpy (WEEK,"THURSDAY");
        break;
    case 5:
        strcpy (WEEK,"FRIDAY");
        break;
    case 6:
        strcpy (WEEK,"SATURDAY");
        break;
    default:
        printf("Error:wrong value of week!");
        exit(7);
    }
    printf ("This day is %s!",WEEK);
}
void view_month(int week,int month_day)
{
    int i=0;
    week=(week+1)%7;
    printf ("\n the calender of this month as following\n");
    printf ("\n *********************************\n");
    printf (" SUN  MON  TUE  WEN  THU  FRI  STA\n");
    for (i=0; i<week; i++)
        printf ("     ");
    for (i=1; i<=month_day; i++)
    {
        printf (" %2d  ",i);
        week++;
        if (week%7==0&&i!=month_day)
            printf ("\n");
    }
    printf ("\n *********************************\n");
}
int main(int argc,const char *argv[])
{
    int year=0,month=0,day=0,week;
    int month_day=0;//每个月的天数
    int m_day=0;//该月前月引起的星期差
    int y_day=0;//闰年比平年多出的一天
    int leap_year;//闰年标识
    int i,flag;
    if (argc!=2)
    {
        fprintf (stderr,"Usage: ./bin ****/** or ****/**/**");
        exit(1);
    }

    i=0;
    flag=-1;
    //-1:year;0:month;1:day
    //遍历传入的参数日期，计算出year，month，day
    while (argv[1][i])
    {
        if ((argv[1][i]=='/'||argv[1][i]=='.')&&flag==-1)
        {
            flag=0;
            i++;
            continue;
        }
        if ((argv[1][i]=='/'||argv[1][i]=='.')&&flag==0)
        {
            flag=1;
            i++;
            continue;
        }
        switch(flag)
        {
        case -1:
            year=year*10+(argv[1][i]-'0');
            break;
        case 0:
            month=month*10+(argv[1][i]-'0');
            break;
        case 1:
            day=day*10+(argv[1][i]-'0');
            break;
        default:
            fprintf(stderr,"error:calc the year month and day\n");
            exit(2);
        }
        i++;
    }

    if(year>2030||year<1929)//控制年份不过大或过小
    {
        fprintf(stderr,"Warning:the enterer YEAR is out of the range!\n");
        exit(3);
    }

    if (month<1||month>12)//若月份传入错误数字
    {
        fprintf (stderr,"Error:the entered MONTH is invalid\n");
        exit (4);
    }

    if (year>2000)//该年1月1号到2000年1月1号的"星期差"
        y_day=(year-1-2000)/4-(year-1-2000)/100+(year-1-2000)/400+1+(year-2000);//闰年多2天，平年多1天
    else
        y_day=(year-2000)/4-(year-2000)/100+(year-2000)/400+(year-2000);

    //该年是否为润年
    if((year%4==0&&year%100!=0)||(year%400==0))
        leap_year=1;
    else
        leap_year=0;
    //该月以前的月所引起的星期差
    switch (month)
    {
    case 1:
        m_day=0;
        month_day=31;
        break;
    case 2:
        m_day=3;
        month_day=((leap_year==1)? 29:28);
        break;
    case 3:
        m_day=3+leap_year;
        month_day=31;
        break;
    case 4:
        m_day=6+leap_year;
        month_day=30;
        break;
    case 5:
        m_day=1+leap_year;
        month_day=31;
        break;
    case 6:
        m_day=4+leap_year;
        month_day=30;
        break;
    case 7:
        m_day=6+leap_year;
        month_day=31;
        break;
    case 8:
        m_day=2+leap_year;
        month_day=31;
        break;
    case 9:
        m_day=5+leap_year;
        month_day=30;
        break;
    case 10:
        m_day=leap_year;
        month_day=31;
        break;
    case 11:
        m_day=3+leap_year;
        month_day=30;
        break;
    case 12:
        m_day=5+leap_year;
        month_day=31;
        break;
    default:
        printf("Error:wrong value of month!");
        exit(5);
    }

    week=(y_day+m_day+(day-1)+6)%7;//以2000/01/01为基准，此日为周六
    while(week<0)
        week+=7;

    if (day) //判定查看日期或是月份
        view_day(day,month_day,week);
    else
        view_month(week,month_day);
    printf ("\nBye!\n");
    exit(0);
}
