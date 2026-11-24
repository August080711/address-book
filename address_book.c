#include <stdio.h>
#include <string.h>

#define FILENAME "contacts.txt"

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

/* 按姓名找联系人：找到返回下标，找不到返回 -1。
   查找、删除、修改都要先找人，所以抽成一个公共函数。*/
int findByName(const char *name) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0)
            return i;
    }
    return -1;
}

void searchContact() {
    char name[20];
    int idx;
    printf("要找谁呀："); scanf("%19s", name);
    idx = findByName(name);
    if (idx == -1) { printf("没有找到 %s 呢~\n", name); return; }
    printf("找到了：%s %s %d岁\n", contacts[idx].name, contacts[idx].phone, contacts[idx].age);
}

void deleteContact() {
    char name[20];
    int idx, i;
    printf("要删掉谁呀："); scanf("%19s", name);
    idx = findByName(name);
    if (idx == -1) { printf("没有找到 %s 呢~\n", name); return; }
    /* 把后面的人逐个往前挪一位，盖掉要删的那一个 */
    for (i = idx; i < count - 1; i++)
        contacts[i] = contacts[i + 1];
    count--;
    printf("已经删掉 %s 啦~\n", name);
}

void modifyContact() {
    char name[20];
    int idx;
    printf("要改谁的信息呀："); scanf("%19s", name);
    idx = findByName(name);
    if (idx == -1) { printf("没有找到 %s 呢~\n", name); return; }
    printf("现在是：%s %s %d岁\n", contacts[idx].name, contacts[idx].phone, contacts[idx].age);
    printf("新电话："); scanf("%19s", contacts[idx].phone);
    printf("新年龄："); scanf("%d", &contacts[idx].age);
    printf("修改好啦~\n");
}

/* 第三步新增：启动时从文件读回联系人。
   文件不存在就是第一次运行，不是错误，静悄悄地从空通讯录开始。*/
void loadContacts() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) return;
    while (count < 100 &&
           fscanf(fp, "%19s %19s %d",
                  contacts[count].name,
                  contacts[count].phone,
                  &contacts[count].age) == 3) {
        count++;
    }
    fclose(fp);
    if (count > 0)
        printf("从文件读回了 %d 位联系人~\n", count);
}

/* 第三步新增：退出时把联系人存进文件，一行存一个人。*/
void saveContacts() {
    FILE *fp = fopen(FILENAME, "w");
    int i;
    if (fp == NULL) { printf("保存失败啦，文件打不开呢~\n"); return; }
    for (i = 0; i < count; i++)
        fprintf(fp, "%s %s %d\n", contacts[i].name, contacts[i].phone, contacts[i].age);
    fclose(fp);
    printf("已经存进 %s 啦，下次打开还在~\n", FILENAME);
}

int main() {
    int choice;
    loadContacts();
    do {
        printf("\n--- 通讯录 ---\n1. 添加  2. 显示全部  3. 查找  4. 删除  5. 修改  0. 退出\n请选择：");
        scanf("%d", &choice);
        if (choice == 1) addContact();
        else if (choice == 2) showAll();
        else if (choice == 3) searchContact();
        else if (choice == 4) deleteContact();
        else if (choice == 5) modifyContact();
        else if (choice != 0) printf("没有这个选项呀，再选一次呢~\n");
    } while (choice != 0);
    saveContacts();
    printf("下次见咯~\n");
    return 0;
}
