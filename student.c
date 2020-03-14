#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <conio.h> 
struct record
{
	char id[10];
	char name[20];
	char phone[20];
	char adress[40];
	char postcode[10];
	char e_mail[30];
}student[500];
int num = 0;//外部变量num为文件中的纪录数 
FILE *fp;
void mainmenu();//主菜单 
void newrecord();//新添纪录 
void searchmenu();//查询菜单 
void searchbyid();//按学号查询 
void searchbyname();//按姓名查询 
void searchbyphone();//按电话查询 
void deletemenu();//删除菜单 
void deleteall();//删除所有 
void deleteone();//删除单个 
void showall();//显示所有 
void readfromfile();//读取文件 
void writetofile();//写入文件 
void deletebyid();//按学号删除 
void deletebyname();//按姓名删除 
void listbyid();//按学号排序 
void listbyname();//按姓名排序 
void listmenu();//排序菜单 
void main()
{
	readfromfile();
	while (1)
	{
		mainmenu();
	}
}
void readfromfile()//从文件导入 
{
	if ((fp = fopen(".\\student.dat", "rb")) == NULL)
	{
		printf("\n\t\t通讯录文件不存在");
		if ((fp = fopen(".\\student.dat", "wb")) == NULL)
		{
			printf("\n\t\t建立失败");
			exit(0);
		}
		else
		{
			printf("\n\t\t通讯录文件已建立");
			printf("\n\t\t按任意键进入主菜单");
			getch();
			return;
		}
		exit(0);
	}
	fseek(fp, 0, 2); /*文件位置指针移动到文件末尾*/
	if (ftell(fp) > 0) /*文件不为空*/
	{
		rewind(fp); /*文件位置指针移动到文件开始位置*/
		for (num = 0; !feof(fp) && fread(&student[num], sizeof(struct record), 1, fp); num++);
		printf("\n\t\t文件导入成功");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
	printf("\n\t\t文件导入成功");
	printf("\n\t\t通讯录文件中无任何纪录");
	printf("\n\t\t按任意键返回主菜单");
	getch();
	return;
}
void mainmenu()//主菜单 
{
	char choic;
	system("cls");
	printf("\n\t\t******************** 主菜单 ********************");
	printf("\n\t\t*********** 1-新添纪录 2-查询菜单 ************");
	printf("\n\t\t*********** 3-删除菜单 4-记录排序 ************");
	printf("\n\t\t*********** 5-保存退出 6-不保存退出***********");
	printf("\n\t\t************************************************");
	printf("\n\t\t请选择：");
	choic = getch();
	switch (choic)
	{
	case '1':newrecord(); break;
	case '2':searchmenu(); break;
	case '3':deletemenu(); break;
	case '4':listmenu(); break;
	case '5':writetofile(); break;
	case '6':exit(0);
	default:mainmenu();
	}
}
void searchmenu()//查询菜单 
{
	char choic;
	system("cls");
	printf("\n\t\t******************* 查询菜单 *******************");
	printf("\n\t\t********** 1-显示所有 2-按学号查询 ************");
	printf("\n\t\t********** 3-按姓名查询4-按电话查询 ************");
	printf("\n\t\t********** 5-返回主菜单 ************");
	printf("\n\t\t************************************************");
	printf("\n\t\t请选择：");
	choic = getch();
	switch (choic)
	{
	case '1':showall(); break;
	case '2':searchbyid(); break;
	case '3':searchbyname(); break;
	case '4':searchbyphone(); break;
	case '5':mainmenu(); break;
	}
}
void deletemenu()//删除菜单 
{
	char choic;
	if (num == 0)
	{
		printf("\n\t\t对不起，文件中无任何纪录");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
	system("cls");
	printf("\n\t\t******************* 删除菜单 *******************");
	printf("\n\t\t*********** 1-删除所有 2-删除单个 ***********");
	printf("\n\t\t*********** 3-返回主菜单 ***********");
	printf("\n\t\t************************************************");
	printf("\n\t\t请选择：");
	choic = getch();
	switch (choic)
	{
	case '1':deleteall(); break;
	case '2':deleteone(); break;
	case '3':mainmenu(); break;
	default:mainmenu(); break;
	}
}
void deleteall()//删除所有 
{
	printf("\n\t\t确认删除?(y/n)");
	if (getch() == 'y')
	{
		fclose(fp);
		if ((fp = fopen("student.bin", "wb")) == NULL)
		{
			printf("\n\t\t不能打开文件，删除失败");
			readfromfile();
		}
		num = 0;
		printf("\n\t\t纪录已删除，按任意键返回主菜单");
		getch();
		return;
	}
	else
		return;
}
void deletebyname()//按姓名删除 
{
	int a = 0;
	int findmark = 0;
	int j;
	int deletemark = 0;
	int i;
	char name[20];
	printf("\n\t\t请输入要删除学生姓名：");
	scanf("%s", name);
	for (i = a; i < num; i++)
	{
		if (strcmp(student[i].name, name) == NULL)
		{
			printf("\n\t\t以下是您要删除的学生纪录：");
			findmark++;
			printf("\n\t\t________________________________");
			printf("\n\t\t学号： %s", student[i].id);
			printf("\n\t\t姓名： %s", student[i].name);
			printf("\n\t\t电话： %s", student[i].phone);
			printf("\n\t\t地址： %s", student[i].adress);
			printf("\n\t\te-mail：%s", student[i].e_mail);
			printf("\n\t\t________________________________");
			printf("\n\t\t是否删除?(y/n)");
			if (getch() == 'y')
			{
				for (j = i; j < num - 1; j++) /*纪录移动，从stud数组中删除之*/
					student[j] = student[j + 1];
				num--;
				deletemark++;
				printf("\n\t\t删除成功");
				if ((i + 1) < num)
				{
					printf("\n\t\t是否继续删除相同姓名的同学信息?(y/n)");
					if (getch() == 'y')
					{
						a = i;
						continue;
					}
				}
				printf("\n\t\t是否继续删除?(y/n)");
				if (getch() == 'y')
					deletebyname();
				return;
			}
			if ((i + 1) < num)
			{
				printf("\n\t\t是否继续删除相同姓名的同学信息?(y/n)");
				if (getch() == 'y')
				{
					a = i;
					continue;
				}
			}
		}
		else
			continue;
	}
	if ((deletemark == 0) && (findmark == 0))
	{
		printf("\n\t\t没有该同学的纪录");
		printf("\n\t\t是否继续删除?(y/n)");
		if (getch() == 'y')
			deletebyid();
		return;
		return;
	}
	else if (findmark != 0)
	{
		printf("\n\t\t没有重名信息");
		printf("\n\t\t没有该同学的纪录");
		printf("\n\t\t是否继续删除?(y/n)");
		if (getch() == 'y')
			deletebyid();
		return;
		return;
	}
}
void deletebyid()//按学号删除 
{
	int i, j;
	int deletemark = 0;
	char id[20];
	printf("\n\t\t请输入要删除学生学号：");
	scanf("%s", id);
	if (num == 0)
	{
		printf("\n\t\t对不起，文件中无任何纪录");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
	for (i = 0; i < num; i++)
	{
		if (strcmp(student[i].id, id) == NULL)
		{
			printf("\n\t\t以下是您要删除的学生纪录：");
			printf("\n\t\t学号： %s", student[i].id);
			printf("\n\t\t姓名： %s", student[i].name);
			printf("\n\t\t电话： %s", student[i].phone);
			printf("\n\t\t地址： %s", student[i].adress);
			printf("\n\t\te-mail：%s", student[i].e_mail);
			printf("\n\t\t是否删除?(y/n)");
			if (getch() == 'y')
			{
				for (j = i; j < num - 1; j++) /*纪录移动，从stud数组中删除之*/
					student[j] = student[j + 1];
				num--;
				deletemark++;
				printf("\n\t\t删除成功");
				printf("\n\t\t是否继续删除?(y/n)");
				if (getch() == 'y')
					deletebyid();
				return;
			}
			else
				return;
		}
		continue;

	}
	if (deletemark == 0)
	{
		printf("\n\t\t没有该同学的纪录");
		printf("\n\t\t是否继续删除?(y/n)");
		if (getch() == 'y')
			deletebyid();
		return;
	}
}
void newrecord()//添加纪录 
{
	printf("\n\t\t**************** 请输入学生信息 ****************\n");
	printf("\n\t\t输入学号:");
	scanf("%s", &student[num].id);
	printf("\n\t\t输入姓名:");
	scanf("%s", &student[num].name);
	printf("\n\t\t输入电话号码:");

	scanf("%s", &student[num].phone);
	printf("\n\t\t输入地址:");
	scanf("%s", &student[num].adress);
	printf("\n\t\t输入邮编:");
	scanf("%s", &student[num].postcode);
	printf("\n\t\t输入e-mail:");
	scanf("%s", &student[num].e_mail);
	num++;
	printf("\n\t\t是否继续添加?(Y/N):");
	if (getch() == 'y')
		newrecord();
	return;
}
void showall()//显示所有 
{
	int i;
	system("cls");
	if (num != 0)
	{
		printf("\n\t\t*************** 以下为通讯录所有信息************");
		for (i = 0; i < num; i++)
		{
			printf("\n\t\t学号： %s", student[i].id);
			printf("\n\t\t姓名： %s", student[i].name);
			printf("\n\t\t电话： %s", student[i].phone);
			printf("\n\t\t地址： %s", student[i].adress);
			printf("\n\t\t邮编： %s", student[i].postcode);
			printf("\n\t\te-mail：%s", student[i].e_mail);

			printf("\t\t");
			if (i + 1 < num)
			{
				printf("\n\t\t__________________________");
				system("pause");
			}
		}
		printf("\n\t\t************************************************");
	}
	else
		printf("\n\t\t通讯录中无任何纪录");
	printf("\n\t\t按任意键返回主菜单：");
	getch();
	return;
}

//按电话查询 
void searchbyphone()
{
	int mark = 0;
	int i;
	int a = 0;
	printf("\n\t\t****************** 按电话查找 ******************");
	char phone[10];
	printf("\n\t\t请输入学号:");
	scanf("%s", phone);
	for (i = 0; i < num; i++)
	{
		if (strcmp(student[i].phone, phone) == 0)
		{
			printf("\n\t\t************** 以下是您查找的学生信息 **********");
			printf("\n\t\t学号： %s", student[i].id);
			printf("\n\t\t姓名： %s", student[i].name);
			printf("\n\t\t电话： %s", student[i].phone);
			printf("\n\t\t地址： %s", student[i].adress);
			printf("\n\t\te-mail：%s", student[i].e_mail);
			printf("\n\t\t************************************************");
			printf("\n\t\t按任意键返回主菜单：");
			mark++;
			getch();
			return;
		}
	}
	if (mark == 0)
	{
		printf("\n\t\t没有改学生的信息");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
}
void searchbyname()//按姓名查询 
{
	int mark = 0;
	int i;
	int a = 0;
	printf("\n\t\t***************** 按姓名查找 *******************");
	char name[20];
	printf("\n\t\t请输入姓名:");
	scanf("%s", name);
	for (i = a; i < num; i++)
	{
		if (strcmp(student[i].name, name) == 0)
		{
			printf("\n\t\t************* 以下是您查找的学生信息 ***********");
			printf("\n\t\t学号： %s", student[i].id);
			printf("\n\t\t姓名： %s", student[i].name);
			printf("\n\t\t电话： %s", student[i].phone);
			printf("\n\t\t地址： %s", student[i].adress);
			printf("\n\t\te-mail：%s", student[i].e_mail);
			printf("\n\t\t************************************************");
			mark++;
			if ((i + 1) < num)
			{
				printf("\n\t\t是否继续查找相同名字的学生信息：(y/n)");
				if (getch() == 'y')
				{
					a = i;
					continue;
				}
				else
					return;
			}
			else
			{
				printf("\n\t\t按任意键返回主菜单");
				getch();
				return;
			}
		}
	}
	if (mark != 0)
	{
		printf("\n\t\t没有相同姓名的学生纪录");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
	else
	{
		printf("\n\t\t没有相同姓名的学生纪录");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
}
void searchbyid()//按学号查询 
{
	int mark = 0;
	int i;
	int a = 0;
	printf("\n\t\t****************** 按学号查找 ******************\n");
	char id[10];
	printf("\n\t\t请输入学号:");
	scanf("%s", id);
	for (i = 0; i < num; i++)
	{
		if (strcmp(student[i].id, id) == 0)
		{
			printf("\n\t\t************** 以下是您查找的学生信息 **********");
			printf("\n\t\t学号： %s", student[i].id);
			printf("\n\t\t姓名： %s", student[i].name);
			printf("\n\t\t电话： %s", student[i].phone);
			printf("\n\t\t地址： %s", student[i].adress);
			printf("\n\t\te-mail：%s", student[i].e_mail);
			printf("\n\t\t************************************************");
			printf("\n\t\t按任意键返回主菜单：");
			mark++;
			getch();
			return;
		}

	}
	if (mark == 0)
	{
		printf("\n\t\t没有改学生的信息");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
}
void writetofile()//写入文件 
{
	int i;
	if ((fp = fopen(".\\student.dat", "wb")) == NULL)
	{
		printf("\n\t\t文件打开失败");
	}
	for (i = 0; i < num; i++)
	{
		if (fwrite(&student[i], sizeof(struct record), 1, fp) != 1)
		{
			printf("\n\t\t写入文件错误!\n");
		}
	}
	fclose(fp);
	printf("\n\t\t通讯录文件已保存");
	printf("\n\t\t按任意键退出程序\n\t\t");
	exit(0);

}
void deleteone()//删除单个 
{
	char choic;
	printf("\n\t\t1-按学号删除 2-按姓名删除");
	printf("\n\t\t请选择：");
	choic = getch();
	switch (choic)
	{
	case '1':deletebyid(); break;
	case '2':deletebyname(); break;
	}
}
void listbyname()//按姓名排序 
{
	int i, j;
	struct record tmp;
	for (i = 1; i < num; i++)
	{
		if (strcmp(student[i].name, student[i - 1].name) < 0)
		{
			tmp = student[i];
			j = i - 1;
			do
			{
				student[j + 1] = student[j];
				j--;
			} while ((strcmp(tmp.name, student[j].name) < 0 && j >= 0));
			student[j + 1] = tmp;
		}
	}
	printf("\n\t\t排序成功,是否显示?(y/n)");
	if (getch() == 'y')
		showall();
	return;
}
void listbyid()//按学号排序 
{
	int i, j;
	struct record tmp;
	for (i = 1; i < num; i++)
	{
		if (strcmp(student[i].id, student[i - 1].id) < 0)
		{
			tmp = student[i];
			j = i - 1;
			do
			{
				student[j + 1] = student[j];
				j--;
			} while ((strcmp(tmp.id, student[j].id) < 0) && j >= 0);
			student[j + 1] = tmp;
		}
	}
	printf("\n\t\t排序成功,是否显示?(y/n)");
	if (getch() == 'y')
		showall();
	return;
}
void listmenu()//排序菜单 
{
	char choic;
	if (num == 0)
	{
		printf("\n\t\t对不起，文件中无任何纪录");
		printf("\n\t\t按任意键返回主菜单");
		getch();
		return;
	}
	system("cls");
	printf("\n\t\t******************* 排序菜单 *******************");
	printf("\n\t\t********** 1-按学号排序 2-按姓名排序 **********");
	printf("\n\t\t********** 3-返回主菜单 **********");
	printf("\n\t\t************************************************");
	printf("\n\t\t请选择：");
	choic = getch();
	switch (choic)
	{
	case '1':listbyid(); break;
	case '2':listbyname(); break;
	case '3':mainmenu(); break;
	default:mainmenu(); break;
	}
}