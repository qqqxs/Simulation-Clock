#include<stdio.h>
#include<graphics.h>
#include<math.h>
#define Width 640   
#define Heigth 480
#define PI 3.14159

//定义全局变量
int center_x = Width / 2;         //圆心横坐标
int center_y = Heigth / 2;		  //圆心纵坐标
int hour_length = Width / 7;	  //时针长度
int minute_length = Width / 6;	  //分针长度
int second_length = Width / 5;    //秒针长度
int hour_endx, hour_endy;         //时针终点坐标
int minute_endx, minute_endy;     //分针终点坐标
int second_endx, second_endy;     //秒针终点坐标
double hour_angle;                //时针转过的角度
double minute_angle;              //分针转过的角度
double second_angle;              //秒针转过的角度

int JudgeYear(int year);          //判断是否为闰年
int JudgeMonth1(int month);		  //进位时判断大小月
int JudgeMonth2(int month);		  //退位时判断大小月
void PrintClock();				  //画4个整点
void DrawButton();			      //画按钮
void DrawScale();				  //画刻度
void DrawClockLine();			  //画表针
void DrawClockCircle();			  //画表盘
void RemovePast();				  //消除前一帧
void CalculateEndPosition();	  //计算终点坐标
void CalculateAngle(int a, int b, int c);//计算转过的角度

int main()
{
	initgraph(640, 480);			  //初始化图形窗口 
	int h, min;                       //存储时分的变量
	int i = 0, j = 0, k = 0;		  //计数器变量(年月日)
	int a = 0, b = 0;				  //计数器变量(时分)
	int temp_y, temp_m, temp_d;       //存储改变后的年月日
	int temp_h, temp_min, temp_s;	  //存储改变后的时分
	int _year, _month, _day;          //存储当前年月日
	int _hour, _minute;               //存储当前时分
	SYSTEMTIME ti;					  //定义时间变量存储当前时间
	GetLocalTime(&ti);                //获得当地时间
	MOUSEMSG msg;                     //定义鼠标变量保存鼠标消息
	char Y[5], M[5], D[5];            //打印按钮年月日
	char H[5], MIN[5], S[5];          //打印按钮时分秒
	int Judge = 0;                    //秒针跳出循环

	_year = ti.wYear;
	_month = ti.wMonth;
	_day = ti.wDay;
	_hour = ti.wHour;
	_minute = ti.wMinute;
	
	setbkcolor(WHITE);				  //设置背景颜色为白色
	cleardevice();					  //清屏
	BeginBatchDraw();				  //开始批量绘图

	while (1)
	{
		DrawClockCircle();
		GetLocalTime(&ti);		

		temp_h = _hour + a;
		temp_min = _minute + b;
		temp_s = ti.wSecond;
		temp_y = _year + i;
		temp_m = _month + j;
		temp_d = _day + k;

		//打印 年 月 日 时 分 秒
		settextcolor(DARKGRAY);
		outtextxy(20, 110, ("当前日期："));
		
		sprintf_s(Y, "%d", temp_y);
		outtextxy(20, 130, Y);
		outtextxy(60, 130, "年");
		
		sprintf_s(M, "%02d", temp_m);
		outtextxy(80, 130, M);
		outtextxy(100, 130, "月");
		
		sprintf_s(D, "%02d", temp_d);
		outtextxy(120, 130, D);
		outtextxy(140, 130, "日");

		if (JudgeMonth1(temp_m) == 1)
		{
			if (temp_d == 32)
			{
				_day = 1;
				k = 0;
				_month += 1;
			}
		}

		if (JudgeMonth2(temp_m) == 1)
		{ 
			if (temp_d == 0)
			{
				_day = 31;
				k = 0;
				_month -= 1;
			}
		}
		
		if (JudgeMonth1(temp_m) == 0)
		{
			if (JudgeYear(temp_y) == 1)
			{
				if (temp_d == 30)
				{
					_day = 1;
					k = 0;
					_month += 1;
				}
			}
			else if (JudgeYear(temp_y) == 0)
			{
				if (temp_d == 29)
				{
					_day = 1;
					k = 0;
					_month += 1;
				}
			}
		}
			
		if (JudgeMonth2(temp_m) == 0)
		{
			if (JudgeYear(temp_y) == 1)
			{
				if (temp_d == 0)
				{
					_day = 29;
					k = 0;
					_month -= 1;
				}
			}
			else if (JudgeYear(temp_y) == 0)
			{
				if (temp_d == 0)
				{
					_day = 28;
					k = 0;
					_month -= 1;
				}
			}			
		}
		
		if (JudgeMonth1(temp_m) == -1)
		{
			if (temp_d == 31)
			{
				_day = 1;
				k = 0;
				_month += 1;
			}
		}

		if (JudgeMonth2(temp_m) == -1)
		{ 
			if (temp_d == 0)
			{
				_day = 30;
				k = 0;
				_month -= 1;
			}
		}

		temp_d = _day + k;
		temp_m = _month + j;

		if (temp_m == 13)
		{
			_month = 1;
			j = 0;
			_year += 1;
		}
		else if (temp_m == 0)
		{
			_month = 12;
			j = 0;
			_year -= 1;
		}		

		outtextxy(20, 150, _T(("现在时刻：")));
		sprintf_s(H, "%02d", temp_h);
		outtextxy(20, 170, H);
		outtextxy(40, 170, "时");

		sprintf_s(MIN, "%02d", temp_min);
		outtextxy(60, 170, MIN);
		outtextxy(80, 170, "分");

		sprintf_s(S, "%02d", ti.wSecond);
		outtextxy(100, 170, S);
		outtextxy(120, 170, "秒");

		if (ti.wSecond == 0 && Judge == 0)
		{
			_minute += 1;
			Judge = 1;
		}
		if (ti.wSecond == 1)
		{
			Judge = 0;
		}

		if (temp_min == 60)
		{
			_minute = 0;
			b = 0;
			_hour += 1;
		}
		else if (temp_min == -1)
		{
			_minute = 59;
			b = 0;
			_hour -= 1;
		}

		if (temp_h == 24)
		{
			_hour = 0;
			a = 0;
			_day += 1;
		}
		else if (temp_h == -1)
		{
			_hour = 23;
			a = 0;
			_day -= 1;
		}		

		DrawButton();
		DrawScale();
		CalculateAngle(temp_s, temp_min, temp_h);
		CalculateEndPosition();
		DrawClockLine();
		PrintClock();
		FlushBatchDraw();    //执行未完成的绘制任务
		RemovePast();		

		if (MouseHit())
		{
			msg = GetMouseMsg();
			if (msg.x >= 520 && msg.x <= 560 && msg.y <= 120 && msg.y >= 80) //年
			{
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					i++;
				}
				else if (msg.uMsg == WM_RBUTTONDOWN)
				{
					i--;
				}
			}
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 180 && msg.y >= 140)//月
			{
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					j++;
				}
				else if (msg.uMsg == WM_RBUTTONDOWN)
				{
					j--;
				}
			}
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 240 && msg.y >= 200)//日
			{
				if (msg.uMsg == WM_LBUTTONDOWN)
				{			
					k++;
				}
				else if (msg.uMsg == WM_RBUTTONDOWN)
				{
					k--;
				}
			}
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 300 && msg.y >= 260)//时
			{
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					a++;
				}
				else if (msg.uMsg == WM_RBUTTONDOWN)
				{
					a--;
				}
			}
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 360 && msg.y >= 320)//分
			{
				if (msg.uMsg == WM_LBUTTONDOWN)
				{
					b++;
				}
				else if (msg.uMsg == WM_RBUTTONDOWN)
				{
					b--;
				}
			}						
		}	
	}
	
	EndBatchDraw();       //结束批量绘图
	system("pause");      //防止闪退
	closegraph();         //关闭图形窗口
	return 0;
}

int JudgeYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 ==0)
	{
		return 1;
	}
	else 
		return 0;
}
int JudgeMonth1(int month)    //日期增加
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return 1;
	}
	else if (month == 2)
	{
		return 0;
	}
	else
		return -1;
}
int JudgeMonth2(int month)  //日期减少
{
	if (month == 1 || month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11)
	{
		return 1;
	}
	else if (month == 3)  
	{
		return 0;
	}
	else
		return -1;
}
void PrintClock()//打印整点
{
	settextcolor(BLACK);
	outtextxy(center_x + 145, center_y - 7, "3");
	outtextxy(center_x - 4, center_y + 142, "6");
	outtextxy(center_x - 152, center_y - 7, "9");
	outtextxy(center_x - 7, center_y - 156, "12");
}
void DrawButton()
{
	//画 年 月 日 按钮
	setlinestyle(PS_SOLID, 2);
	fillrectangle(520, 240, 560, 200);
	settextcolor(DARKGRAY);
	outtextxy(530, 210, "日");

	fillrectangle(520, 180, 560, 140);
	settextcolor(DARKGRAY);
	outtextxy(530, 150, "月");

	fillrectangle(520, 120, 560, 80);
	settextcolor(DARKGRAY);
	outtextxy(530, 90, "年");

	fillrectangle(520, 300, 560, 260);
	settextcolor(DARKGRAY);
	outtextxy(530, 270, "时");

	fillrectangle(520, 360, 560, 320);
	settextcolor(DARKGRAY);
	outtextxy(530, 330, "分");
}
void DrawScale()
{
	//画刻度
	for (int i = 0; i < 60; i++)
	{
		int start_x = center_x + ((Width / 4)) * sin(PI * i / 30);
		int start_y = center_y - ((Width / 4)) * cos(PI * i / 30);
		int end_x = center_x + ((Width / 4) + 8.0) * sin(PI * i / 30);
		int end_y = center_y - ((Width / 4) + 8.0) * cos(PI * i / 30);
		if (i % 5 == 0)
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 3);
			line(start_x, start_y, end_x, end_y);
		}
		else
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			line(start_x, start_y, end_x, end_y);
		}
	}
}
void CalculateAngle(int a, int b, int c)
{
	second_angle = double(a) * 2 * PI / 60;     //秒针转过的度数
	minute_angle = double(b) * 2 * PI / 60;	 //分针转过的度数
	hour_angle = double(c) * 2 * PI / 12;		 //时针转过的度数
}
void CalculateEndPosition()
{
	second_endx = center_x + second_length * sin(second_angle);//秒针终点横坐标
	second_endy = center_y - second_length * cos(second_angle);//秒针终点纵坐标
	minute_endx = center_x + minute_length * sin(minute_angle);//分针终点横坐标
	minute_endy = center_y - minute_length * cos(minute_angle);//分针终点纵坐标
	hour_endx = center_x + hour_length * sin(hour_angle);	   //时针终点横坐标
	hour_endy = center_y - hour_length * cos(hour_angle);	   //时针终点纵坐标
}
void DrawClockLine()
{
	//画秒针
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 2);  //PS_SOLID表示画实线
	line(center_x, center_y, second_endx, second_endy);
	//画分针
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	line(center_x, center_y, minute_endx, minute_endy);
	//画时针
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);
	line(center_x, center_y, hour_endx, hour_endy);
}
void DrawClockCircle()
{
	setlinestyle(PS_SOLID, 1);    //以实线填充，宽度为2个像素
	setlinecolor(BLACK);			  //填充为蓝色
	circle(center_x, center_y, Width / 4);   //画圆
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	circle(center_x, center_y, (Width / 4) + 8);
	setlinestyle(PS_SOLID, 5);
	setlinecolor(DARKGRAY);
	circle(center_x, center_y, (Width / 4) + 15);
}
void RemovePast()
{
	//消除前一帧
	setlinecolor(WHITE);
	line(center_x, center_y, second_endx, second_endy);
	line(center_x, center_y, minute_endx, minute_endy);
	line(center_x, center_y, hour_endx, hour_endy);
}