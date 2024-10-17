#include <iostream>
#include <cstring>
#include <locale.h>
#include <windows.h>
struct node
{
	char inf[256];  // полезная информация
	int priority;
	struct node* next; // ссылка на следующий элемент
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка

// Функции добавления элемента, просмотра списка
void spstore(), review(), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(); // функция создания элемента

struct node* get_struct()
{
	struct node* p = NULL;
	char s[256];
	int priority;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	printf("Введите приоритет объекта: \n");
	scanf("%d", &priority);
	p->priority = priority;

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/

/* Добавление элемента в список с учетом приоритета */
void spstore()
{
	struct node* p = get_struct();
	if (p == NULL) return;

	if (head == NULL || p->priority > head->priority)  // если списка нет или приоритет больше, чем у головы
	{
		p->next = head;
		head = p;
		if (last == NULL) last = p; // если список был пуст
	}
	else
	{
		struct node* current = head;
		while (current->next != NULL && current->next->priority >= p->priority)
		{
			current = current->next;
		}
		p->next = current->next;
		current->next = p;
		if (current == last) last = p;  // обновляем last, если вставка в конец
	}
}

/* Просмотр содержимого списка. */
void review()
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, Приоритет - %d\n", struc->inf, struc->priority);
		struc = struc->next;
	}
}

/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // устанавливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	spstore();
	spstore();
	spstore();
	review();

	return 0;
}