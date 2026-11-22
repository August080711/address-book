#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char phone[20];
    int age;
} Contact;

Contact contacts[100];
int count = 0;

void addContact() {
    if (count >= 100) { printf("通讯录满啦~\n"); return; }
    printf("姓名："); scanf("%19s", contacts[count].name);
    printf("电话："); scanf("%19s", contacts[count].phone);
    printf("年龄："); scanf("%d", &contacts[count].age);
    count++;
    printf("添加成功咯~\n");
}

void showAll() {
    int i;
	if (count == 0) { 
	printf("通讯录还是空的呢~\n"); 
	return;
	 }
    for (i = 0; i < count; i++)
        printf("%d. %s %s %d岁\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].age);
}

int main() {
    int choice;
    do {
        printf("\n--- 通讯录 ---\n1. 添加  2. 显示全部  0. 退出\n请选择：");
        scanf("%d", &choice);
        if (choice == 1) addContact();
        else if (choice == 2) showAll();
        else if (choice != 0) printf("没有这个选项呀，再选一次呢~\n");
    } while (choice != 0);
    printf("下次见咯~\n");
    return 0;
}

