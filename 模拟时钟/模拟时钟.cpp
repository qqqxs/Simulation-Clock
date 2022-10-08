#include<stdio.h>
#include<graphics.h>
#include<math.h>
#define Width 640   
#define Heigth 480
#define PI 3.14159

//����ȫ�ֱ���
int center_x = Width / 2;         //Բ�ĺ�����
int center_y = Heigth / 2;		  //Բ��������
int hour_length = Width / 7;	  //ʱ�볤��
int minute_length = Width / 6;	  //���볤��
int second_length = Width / 5;    //���볤��
int hour_endx, hour_endy;         //ʱ���յ�����
int minute_endx, minute_endy;     //�����յ�����
int second_endx, second_endy;     //�����յ�����
double hour_angle;                //ʱ��ת���ĽǶ�
double minute_angle;              //����ת���ĽǶ�
double second_angle;              //����ת���ĽǶ�

int JudgeYear(int year);          //�ж��Ƿ�Ϊ����
int JudgeMonth1(int month);		  //��λʱ�жϴ�С��
int JudgeMonth2(int month);		  //��λʱ�жϴ�С��
void PrintClock();				  //��4������
void DrawButton();			      //����ť
void DrawScale();				  //���̶�
void DrawClockLine();			  //������
void DrawClockCircle();			  //������
void RemovePast();				  //����ǰһ֡
void CalculateEndPosition();	  //�����յ�����
void CalculateAngle(int a, int b, int c);//����ת���ĽǶ�

int main()
{
	initgraph(640, 480);			  //��ʼ��ͼ�δ��� 
	int h, min;                       //�洢ʱ�ֵı���
	int i = 0, j = 0, k = 0;		  //����������(������)
	int a = 0, b = 0;				  //����������(ʱ��)
	int temp_y, temp_m, temp_d;       //�洢�ı���������
	int temp_h, temp_min, temp_s;	  //�洢�ı���ʱ��
	int _year, _month, _day;          //�洢��ǰ������
	int _hour, _minute;               //�洢��ǰʱ��
	SYSTEMTIME ti;					  //����ʱ������洢��ǰʱ��
	GetLocalTime(&ti);                //��õ���ʱ��
	MOUSEMSG msg;                     //�������������������Ϣ
	char Y[5], M[5], D[5];            //��ӡ��ť������
	char H[5], MIN[5], S[5];          //��ӡ��ťʱ����
	int Judge = 0;                    //��������ѭ��

	_year = ti.wYear;
	_month = ti.wMonth;
	_day = ti.wDay;
	_hour = ti.wHour;
	_minute = ti.wMinute;
	
	setbkcolor(WHITE);				  //���ñ�����ɫΪ��ɫ
	cleardevice();					  //����
	BeginBatchDraw();				  //��ʼ������ͼ

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

		//��ӡ �� �� �� ʱ �� ��
		settextcolor(DARKGRAY);
		outtextxy(20, 110, ("��ǰ���ڣ�"));
		
		sprintf_s(Y, "%d", temp_y);
		outtextxy(20, 130, Y);
		outtextxy(60, 130, "��");
		
		sprintf_s(M, "%02d", temp_m);
		outtextxy(80, 130, M);
		outtextxy(100, 130, "��");
		
		sprintf_s(D, "%02d", temp_d);
		outtextxy(120, 130, D);
		outtextxy(140, 130, "��");

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

		outtextxy(20, 150, _T(("����ʱ�̣�")));
		sprintf_s(H, "%02d", temp_h);
		outtextxy(20, 170, H);
		outtextxy(40, 170, "ʱ");

		sprintf_s(MIN, "%02d", temp_min);
		outtextxy(60, 170, MIN);
		outtextxy(80, 170, "��");

		sprintf_s(S, "%02d", ti.wSecond);
		outtextxy(100, 170, S);
		outtextxy(120, 170, "��");

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
		FlushBatchDraw();    //ִ��δ��ɵĻ�������
		RemovePast();		

		if (MouseHit())
		{
			msg = GetMouseMsg();
			if (msg.x >= 520 && msg.x <= 560 && msg.y <= 120 && msg.y >= 80) //��
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
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 180 && msg.y >= 140)//��
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
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 240 && msg.y >= 200)//��
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
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 300 && msg.y >= 260)//ʱ
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
			else if (msg.x >= 520 && msg.x <= 560 && msg.y <= 360 && msg.y >= 320)//��
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
	
	EndBatchDraw();       //����������ͼ
	system("pause");      //��ֹ����
	closegraph();         //�ر�ͼ�δ���
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
int JudgeMonth1(int month)    //��������
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
int JudgeMonth2(int month)  //���ڼ���
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
void PrintClock()//��ӡ����
{
	settextcolor(BLACK);
	outtextxy(center_x + 145, center_y - 7, "3");
	outtextxy(center_x - 4, center_y + 142, "6");
	outtextxy(center_x - 152, center_y - 7, "9");
	outtextxy(center_x - 7, center_y - 156, "12");
}
void DrawButton()
{
	//�� �� �� �� ��ť
	setlinestyle(PS_SOLID, 2);
	fillrectangle(520, 240, 560, 200);
	settextcolor(DARKGRAY);
	outtextxy(530, 210, "��");

	fillrectangle(520, 180, 560, 140);
	settextcolor(DARKGRAY);
	outtextxy(530, 150, "��");

	fillrectangle(520, 120, 560, 80);
	settextcolor(DARKGRAY);
	outtextxy(530, 90, "��");

	fillrectangle(520, 300, 560, 260);
	settextcolor(DARKGRAY);
	outtextxy(530, 270, "ʱ");

	fillrectangle(520, 360, 560, 320);
	settextcolor(DARKGRAY);
	outtextxy(530, 330, "��");
}
void DrawScale()
{
	//���̶�
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
	second_angle = double(a) * 2 * PI / 60;     //����ת���Ķ���
	minute_angle = double(b) * 2 * PI / 60;	 //����ת���Ķ���
	hour_angle = double(c) * 2 * PI / 12;		 //ʱ��ת���Ķ���
}
void CalculateEndPosition()
{
	second_endx = center_x + second_length * sin(second_angle);//�����յ������
	second_endy = center_y - second_length * cos(second_angle);//�����յ�������
	minute_endx = center_x + minute_length * sin(minute_angle);//�����յ������
	minute_endy = center_y - minute_length * cos(minute_angle);//�����յ�������
	hour_endx = center_x + hour_length * sin(hour_angle);	   //ʱ���յ������
	hour_endy = center_y - hour_length * cos(hour_angle);	   //ʱ���յ�������
}
void DrawClockLine()
{
	//������
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 2);  //PS_SOLID��ʾ��ʵ��
	line(center_x, center_y, second_endx, second_endy);
	//������
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	line(center_x, center_y, minute_endx, minute_endy);
	//��ʱ��
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);
	line(center_x, center_y, hour_endx, hour_endy);
}
void DrawClockCircle()
{
	setlinestyle(PS_SOLID, 1);    //��ʵ����䣬���Ϊ2������
	setlinecolor(BLACK);			  //���Ϊ��ɫ
	circle(center_x, center_y, Width / 4);   //��Բ
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	circle(center_x, center_y, (Width / 4) + 8);
	setlinestyle(PS_SOLID, 5);
	setlinecolor(DARKGRAY);
	circle(center_x, center_y, (Width / 4) + 15);
}
void RemovePast()
{
	//����ǰһ֡
	setlinecolor(WHITE);
	line(center_x, center_y, second_endx, second_endy);
	line(center_x, center_y, minute_endx, minute_endy);
	line(center_x, center_y, hour_endx, hour_endy);
}