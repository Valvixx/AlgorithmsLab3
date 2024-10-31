#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>

struct node {
    char inf[256];  // полезная информация
    int priority;
    struct node* next; // ссылка на следующий элемент
};

struct node* head = NULL, * last = NULL; // указатели на первый и последний элементы списка

struct node* get_struct() {
    struct node* p = (struct node*)malloc(sizeof(struct node));  // выделяем память под новый элемент списка
    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    char s[256];
    int priority;
    printf("Введите название объекта: \n");
    scanf("%255s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);

    printf("Введите приоритет объекта: \n");
    scanf("%d", &priority);
    p->priority = priority;
    p->next = NULL;

    return p;
}

/* Последовательное добавление в список элемента (в конец) */
void spstore() {
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head == NULL || p->priority > head->priority) {  // если списка нет или приоритет больше, чем у головы
        p->next = head;
        head = p;
        if (last == NULL) last = p; // если список был пуст
    }
    else {
        struct node* current = head;
        while (current->next != NULL && current->next->priority >= p->priority) {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
        if (current == last) last = p;  // обновляем last, если вставка в конец
    }
}

/* Просмотр содержимого списка */
void review_list() {
    struct node* struc = head;
    if (head == NULL) {
        printf("Список пуст\n");
    }
    while (struc) {
        printf("Имя - %s, Приоритет - %d\n", struc->inf, struc->priority);
        struc = struc->next;
    }
}

/* Удаление элемента по содержимому */
void del(char* name) {
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }

    // Удаление первого элемента, если он совпадает
    if (strcmp(name, struc->inf) == 0) {
        flag = 1;
        head = struc->next;
        free(struc);
        if (head == NULL) last = NULL; // Обновляем last, если удален единственный элемент
        return;
    }

    prev = struc;
    struc = struc->next;

    // Поиск и удаление других элементов
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            flag = 1;
            prev->next = struc->next;
            if (struc == last) {
                last = prev; // Обновляем last, если удаляем последний элемент
            }
            free(struc);
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (!flag) {
        printf("Элемент не найден\n");
    }
}


//--- Очередь ---
struct QueueNode {
    char inf[256];
    struct QueueNode* next;
};

struct QueueNode* Qhead = NULL, * Qlast = NULL;

struct QueueNode* getQueue() {
    struct QueueNode* p = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    char s[256];
    printf("Введите название объекта: \n");
    scanf("%255s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p;
}

void enqueue() {
    struct QueueNode* p = getQueue();
    if (p == NULL) return;

    if (Qhead == NULL) {
        Qhead = p;
        Qlast = p;
    }
    else {
        Qlast->next = p;
        Qlast = p;
    }
}

void dequeue() {
    if (Qhead == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    struct QueueNode* temp = Qhead;
    printf("Удаление элемента: %s\n", temp->inf);

    Qhead = Qhead->next;
    if (Qhead == NULL) Qlast = NULL;

    free(temp);
}

void review_queue() {
    struct QueueNode* struc = Qhead;
    if (Qhead == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    while (struc) {
        printf("Элемент: %s\n", struc->inf);
        struc = struc->next;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    spstore();
    spstore();
    spstore();
    review_list();
    char nameToDelete[256];
    printf("Введите имя элемента для удаления из списка: ");
    scanf("%255s", nameToDelete);
    del(nameToDelete);
    review_list();

    enqueue();
    enqueue();
    review_queue();
    dequeue();
    review_queue();

    return 0;
}
