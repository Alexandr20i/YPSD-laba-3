// laba_3_YAPSD.cpp : 14 варик [Модуль значения элементов] + [Дерево поиска] + [Симметричный]

#include <iostream>
#include <fstream>

using namespace std;

struct tree
{
    int value;     // поле данных
    tree* left;    // указатель на левую ветку дерева
    tree* right;   // указатель на правую ветку дерева
};

void Add(tree*& head, int c) //функция добавляющая в дерево n элементов из fin
{
    if (head == NULL) // когда дерева ещё нет:
    {
        head = new tree; // выделяем память
        head->value = c; // записываем данные в звено
        head->left = head->right = NULL; // подзвенья инизиализируем пустотой
    }

    else {
        if (c < head->value) // если новый элемент меньше value, то двигаемся влево
        {
            if (head->left != NULL) 
                Add(head->left, c);  // в свободный участок записываем 'c'
            else {
                head->left = new tree; // выделяем память левому подзвену
                head->left->left = head->left->right = NULL; // инициализируем лево и право в подзвене
                head->left->value = c; // записываем в левое подзвено 'c'
            }
        }

        else  // в других случаях (c >= head->value) 
        {
            if (head->right != NULL)
                Add(head->right, c);
            else {
                head->right = new tree;
                head->right->left = head->right->right = NULL;
                head->right->value = c;
            }
        }
    }
}

void preorderPrint(tree *&head) //функция симметричного обхода дерева до обработки
{
    if (head != NULL)   
    {
        preorderPrint(head->left);  // доходим до левого конца
        cout << head->value << ' '; // начинаем выводить элементы
        preorderPrint(head->right); // двигаемся вправо
    }
}

void Procedure(tree* head) //функция обращающая дерево
{
    if (head == NULL)
        return;
    Procedure(head->left);
    if (head->value < 0)    // находим отрицательное значение элемента
        head->value = abs(head->value); // меняем на положительное 
    Procedure(head->right);
}

void Result(tree* head,ofstream& ofs) //функция обратного обхода дерева после обработки
{
    if (head == NULL)
        return;
    Result(head->left,ofs);
    cout << head->value << ' ';
    ofs << head->value << ' ';
    Result(head->right,ofs);
}

void Clear(tree* head)  //функция очищающая память
{
    if (head != NULL) {
        Clear(head->left);
        Clear(head->right);
        delete head; // убираем конечный элемент дерева
        //head = NULL;
    }
}

int main()
{
    tree* head = NULL; //создание дерева

    ifstream ifs;
    ofstream ofs;

    ifs.open("input.txt");
    ofs.open("output.txt");
    
    int c;
    while (ifs >> c)
        Add(head, c);   // добавление в дерево 

    preorderPrint(head);// вывод в консоль дерева

    cout << endl;

    Procedure(head);   // обращение дерева
    Result(head,ofs);  // вывод в консоль и файл дерева

    ifs.close();
    ofs.close();

    Clear(head);      // обищаем память

    return 0;
}


