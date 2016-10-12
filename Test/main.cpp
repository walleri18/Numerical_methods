#include <stdio.h>
#define SIZE_NUMBER 20

int read_file_TO_matrix(char *name,int &str,int &stb,double **&mass)//чтение матрицы из файла
{
char buffer;
double number;
double ttt=10;
int i,j;
bool flag=false;
mass=0;
str=stb=i=j=0;
unsigned int code=0;
FILE *fo;
fo=fopen(name,"r");
if(!fo)
return 0;
while(!feof(fo))
{
	if(!fread(&buffer,sizeof(char),1,fo))
	break;
	if(buffer>='0' && buffer<='9') 
	{
			if(!(code>0 && code<=SIZE_NUMBER))
			code=1;
			else code++;
			if(ttt==10)
			number=number*ttt+(buffer-'0');
			else
			{
			number=number+(buffer-'0')*ttt;
			ttt/=10;
			}
			continue;
	}
	else if(buffer=='-')
	{
	flag=true;
	continue ;
	}
	else if(buffer=='.')
	{
		if(ttt==10)
		{
		ttt=0.1;
		continue;
		}
		else
		{
		for(int k=0;k<i;k++)
			delete []mass[k]; 
		if(mass!=0)delete []mass;
		return 0;
		}
	}
	else if(code>0 && code<=SIZE_NUMBER)
	{
		if(flag)
		number=-number;
		if(str==0)
		str=number;
		else if(stb==0)
		stb=number;
		else if(str>0 && stb>0)
		{
			if(i==0 && j==0)
			{
			mass=new double *[str];
			mass[i]=new double [stb];
			}
			else if(j>=stb)
			{
				if(++i>=str){j=-1;break ;}
				mass[i]=new double [stb];
				j=0;
			}
			if(j<stb)
			mass[i][j++]=number;
		}
	}
ttt=10;
flag=false;
number=0;
code=0;
}
if(str-1==i && stb==j)
return 1;

	for(j=i;j>=0;j--)
	delete []mass[j];
	delete []mass;

return 0;
}

void print_matrix(int str,int stb,double **mass)//вывод матрицы в консоль
{
	for(int i=0;i<str;i++)
	{
		for(int j=0;j<stb;j++)
		printf("a[%d][%d]=%f \t",i,j,mass[i][j]);
		printf("\n");
	}
	printf("\n");
}


int gaus_det(int cnt_str,double **mass,double &det)
{
int i,j,k;
det=1;
double **copy_mass=new double *[cnt_str];//создаём копию матрицы, так как элементы матрицы мы будем использовать повторно
	for(i=0;i<cnt_str;i++)
	{
	copy_mass[i]=new double [cnt_str];
	for(j=0;j<cnt_str;j++)copy_mass[i][j]=mass[i][j];
	}
//прямой ход метод Гаусса
for(i=0;i<cnt_str;i++)
{
	for(j=i+1;j<cnt_str;j++)
	{
		if(copy_mass[i][i]==0)
		{
		for(i=0;i<cnt_str;i++)
		delete []copy_mass[i];
		delete []copy_mass;
		return 0;
		}
	double b=copy_mass[j][i]/copy_mass[i][i];
	for(k=i;k<cnt_str;k++)
	copy_mass[j][k]=copy_mass[j][k]-copy_mass[i][k]*b;
	}
det*=copy_mass[i][i];//вычисление определителя
}
	for(i=0;i<cnt_str;i++)//освобождаем память
	delete []copy_mass[i];
	delete []copy_mass;
return 1;
}

int main(int args,char *argv[])
{
int str,stb;
str=stb=0;
double **mass;
int i,j;
	if(read_file_TO_matrix("./primer1",str,stb,mass)==1 && str==stb-1)//чтение матрицы из файла
	{
	double *det=new double [stb+1];//массив определителей
	double *t=new double [str];//временная переменная для хранения столбца матрицы	
		for(i=0;i<stb;i++)
		{	
	
			if(gaus_det(str,mass,det[i])!=1)//вычисление определителя используя метод Гаусса
			{
			printf("Error kramer\n");
			delete []t;
			delete []det;
			for(j=0;j<str;j++)
			delete []mass[j];
			delete []mass;
			return 0;
			}
			for(j=0;j<str;j++)//последовательная замена столбцов матрицы 
			{
			if(i>0)
			mass[j][i-1]=t[j];//восстанавливаем значение столбца
			t[j]=mass[j][i];//сохраняем значения i - столбца матрицы в переменной t
			mass[j][i]=mass[j][stb-1];//в i - столбец матрицы записываем столбец свободных членов 
			}
		}
	delete []t;
	for(i=1;i<stb;i++)
	printf("x[%d]=%f\n",i,det[i]/det[0]);//вывод результата
	delete []det;
	}
	else
	{printf("Error read matrix\n");return 0;}
return 0;
}
//скачено с http://algorithmlib.org/
