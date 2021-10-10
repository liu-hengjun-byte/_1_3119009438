#include<iostream>
#include<fstream>
#include<time.h>
#include<math.h>
using namespace std;
#define SIZE 100;
#define STACKINCREMENT 10;
typedef struct
{
	char* base;
	char* top;
	int stacksize;
}SqStack;  //�����ջ
typedef struct
{
	double* base;
	double* top;
	int stacksize;
}SqStack1;   //������ջ
char operateChar[4];       //�����
double  stackNum[100];     //����������
char stackOpChar[100];    //�������ַ�����
int stackNumNo = 0;       //����������
int stackOpCharNo = 0;    //���������
int opType;              //����������
bool error = false;
int m;
struct input  //�û�����ṹ
{
	int n;            //ϰ������
	int No;           //��������Ŀ��
	int Bit;          //��������λ��
	int Fraction;          //�Ƿ�ΪС����
	int Negative;          //�Ƿ�Ϊ������
	int max;               //������ֵ����ֵ��
	int min;               //������ֵ���Сֵ
//	char yourOperateChar[4];//���Գ��ֵ��������
}in;
void InitStack(SqStack& S)//����һ����������ջS
{
	S.base = new char[100];
	S.top = S.base;
	S.stacksize = SIZE;
}
void InitStack(SqStack1& S)//����һ����������ջS
{
	S.base = new double[100];
	S.top = S.base;
	S.stacksize = SIZE;
}
char GetTop(SqStack S)
{//��ջ���գ�����e����S��ջ��Ԫ��
	char e;
	if (S.top == S.base)return -1;
	e = *(S.top - 1);
	return e;
}
double GetTop(SqStack1 S)
{//��ջ���գ�����e����S��ջ��Ԫ��
	double e;
	if (S.top == S.base)return -1;
	e = *(S.top - 1);
	return e;
}
template<class T, class T1>
int Push(T& S, T1 e)//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	*S.top++ = e;
	return 0;
}
template<class T, class T1>
int Pop(T& S, T1& e)
{    //��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������0�����򷵻�-1��
	if (S.top == S.base)return -1;
	e = *--S.top;
	return 0;
}
double Operate(double a, char theta, double b)
{
	switch (theta)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	}
	return 0;
}
char Precede(char t1, char t2)
{
	if ((t1 == '+' || t1 == '-') && (t2 == '*' || t2 == '/'))return '<';
	else return '>';
}
int createOperateNum(int bit)//�������������
{
	int i = 1, randomNumber, randomdata;
	while (bit > 0)
	{
		i = 10 * i;
		bit--;
	}
	randomNumber = rand();//���������,rand���� ���ɵ���0��32767֮���һ��������� 
	randomdata = (randomNumber % i); //��ò�����bitλ�������

	return randomdata;
}
char createOperateChar(int i)  //���������
{
	int randomNumber, randomdata;
	randomNumber = rand();
	randomdata = (randomNumber % i);

	return operateChar[randomdata];
}
//�û�����
void getInputData()
{
	cout << "����ϰ������ϰ����Ӧ����5����" << endl;
	cin >> in.n;
	while (in.n < 5)      //�����������nС��5������������
	{
		cout << "�������������������������" << endl;
		cin >> in.n;
	}
	cout << "����������ĸ���:" << endl;
	cin >> in.No;
	while (in.No < 1)      //�������NoС��1������������
	{
		cout << "����������ĸ�������������������" << endl;
		cin >> in.No;
	}
	cout << "������м����������λ��" << endl;
	cin >> in.Bit;
	while (in.Bit < 1)      //�������NoС��1������������
	{
		cout << "��������λ������������������" << endl;
		cin >> in.Bit;
	}
	cout << "�����м����Ƿ�����Ϊ������1�����ܣ�0������" << endl;
	cin >> in.Negative;
	cout << "�����м����Ƿ����С����1�����ܣ�0������" << endl;
	cin >> in.Fraction;
	if (in.Fraction == 1)
	{
		cout << "��������Ҫ������С��λ��m��m��0��m��4��:" << endl;
		cin >> m;
	}
	cout << "������������������ֵ����ֵ��" << endl;
	cin >> in.max;
	cout << "������������������ֵ���Сֵ��" << endl;
	cin >> in.min;
	cout << "����������Ҫʹ�õ�������ţ�֧�ֶ����,����'#'�ͻس���������:" << endl;
	char c[6];
	opType = 0;
	int i = 0;
	cin >> c;
	while (c[i] != '#')
	{
		if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/')
			if (opType < 4)operateChar[opType++] = c[i];
		i++;
	}
}

void createOperate()          //�������������ʽ��
{
	int i = in.No;
	srand((unsigned)time(NULL));//���ݵ�ǰʱ���������������������
	while (i > 0)
	{
		stackNum[stackNumNo++] = createOperateNum(in.Bit);
		stackOpChar[stackOpCharNo++] = createOperateChar(opType);
		i--;
	}
	stackNumNo--;
	stackOpCharNo--;//���������һ��������ɾ����   
	stackOpChar[stackOpCharNo] = '#';
	stackOpCharNo--;
}
void reset()
{
	stackNumNo = 0;
	stackOpCharNo = 0;
	error = false;
}
double EvaluateExpression(double& p)
{
	SqStack OPTR;	SqStack1 OPND;
	int i = 1, j = 1;   char c;
	double q;
	InitStack(OPTR);	InitStack(OPND);
	Push(OPND, stackNum[0]);  Push(OPTR, stackOpChar[0]);  Push(OPND, stackNum[1]);
	while (i < stackNumNo)
	{
		if (stackOpChar[i] != '#')
			switch (Precede(GetTop(OPTR), stackOpChar[i]))
			{
			case '<':
				Pop(OPND, p);
				p = Operate(p, stackOpChar[i], stackNum[j + 1]);
				if ((in.Negative == 0 && p < 0) || (in.Fraction == 0 && p != int(p)))error = true;
				Push(OPND, p);
				break;
			case '>':
				Pop(OPTR, c);
				Pop(OPND, p);   Pop(OPND, q);
				p = Operate(q, c, p);
				if ((in.Negative == 0 && p < 0) || (in.Fraction == 0 && p != int(p)))error = true;
				Push(OPND, p);
				Push(OPND, stackNum[j + 1]);
				Push(OPTR, stackOpChar[i]);
				break;
			}
		i++;
		j++;
	}
	Pop(OPTR, c);
	Pop(OPND, p);   Pop(OPND, q);
	p = Operate(q, c, p);
	if (p<in.min || p>in.max || (in.Negative == 0 && p < 0) || (in.Fraction == 0 && p != int(p))) //��p����Ϊ����ʱ��p<0
		error = true;  //p����С��ָ������Сֵ�����ܴ���ָ�������ֵ
	return 0;
}

void Savefile()      //�����ϴε�ѡ����б���
{
	ofstream outfile("1.txt");
	if (!outfile)
	{
		cout << "Open 1.txt error!" << endl;
		return;
	}
	outfile << in.Fraction << " " << in.Negative << " " << in.n << " " << in.Bit << " " <<
		in.No << " " << in.max << " " << in.min << " " << opType << " ";
	for (int i = 0; i < opType; i++)outfile << operateChar[i];
}   
int Loadfile()
{
	ifstream infile("1.txt");
	if (!infile)
	{
		cout << "Open 1.txt error!" << endl;
		return 0;
	}
	infile >> in.Fraction >> in.Negative >> in.n >> in.Bit >> in.No >> in.max >> in.min >> opType;
	for (int i = 0; i < opType; i++)infile >> operateChar[i];
	return 1;
}

int main()
{
	//	Loadfile();
		//�û���������
	double p, result;
	char t;
	int correct = 0, fail = 0, j = Loadfile();
	if (!j)getInputData();
	else
	{
		cout << "�Ƿ���Ҫ����������������(y/n)ѡ��" << endl;
		cin >> t;
		if (t == 'y')getInputData();
	}

	Savefile();
	cout << in.n << endl;


	//������Ӧ������ʽ
	while (in.n > 0)
	{
		createOperate();
		EvaluateExpression(p);
		if (!error)
		{
			int i = 0,j = 0;
			while (j <= stackOpCharNo)
			{
				if (stackOpChar[j] == '+' || stackOpChar[j] == '-' && stackOpChar[j + 1] == '*' || stackOpChar[j + 1] == '\\' || stackOpChar[j + 1] == '-') {
					cout << '(';
					cout << stackNum[i] << stackOpChar[j]<< stackNum[i+1];
					cout << ")";
					cout << stackOpChar[j+1];
					i+=2;
					j+=2;
					continue;
				}
				
					cout << stackNum[i] << stackOpChar[j];
					i++;
					j++;

			}
			cout << stackNum[i] << "=" << endl;

			cout << "��������������" << endl;
			cin >> result;
			if (in.Fraction == 1)
			{
				if ((int)(p * pow(10, m + 1)) % 10 >= 5)
					p = (int)(p * pow(10, m) + 1) / pow(10, m);
				else p = (int)(p * pow(10, m)) / pow(10, m);
			}

			if (p == result)
			{
				cout << "��ȷ" << endl;
				correct++;
			}
			else
			{
				cout << "����" << endl;
				cout << "��ȷ��ӦΪ��" << p << endl;
				fail++;
			}
			in.n--;
		}
		reset();
	}
	cout << "һ��������" << correct << "�⣬������" << fail << "��" << endl;


	return 0;
}