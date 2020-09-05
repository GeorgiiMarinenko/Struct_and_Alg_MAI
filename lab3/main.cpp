/*Однонаправленный целочисленный стек на 20 элементов
- создание стека
- вывод на экран значения элементов с их индексами
- включение нового элемента в список
- удаление элемента в списке
- очищение стека
- после операции включения или выборки выводить содержимое списка*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Element
{
    Element()
    {
        cout << sizeof(this) << " bytes of memory allocated\tto address: " << this << endl;
    }
    ~Element()
    {
        cout << sizeof(this) << " bytes of memory cleared\tfrom address: " << this << endl;
    }
    int Data;
    int index;
    Element* PreviousElem;
};


 struct Stack
{
    Element* Head = nullptr;

    void CreateStackFromFile(string path)
    {
        ifstream fin(path);
        int CounterStr = 0;
        string Str;

        while (!fin.eof())
        {
            getline(fin, Str);
            if (Str.length() > 0)
            {
                CounterStr++;
            }
        }
        if (CounterStr == 0)
        {
            cout << "Файл пустой!" << endl;
            return;
        }
        fin.seekg(0);

        
        for (int i = 0; i < CounterStr; i++) //Чтение файла
        {
            Element* NextElem = new Element();
            fin >> NextElem->Data; //чтение значения элемента в стеке

            if (Head == nullptr)
            {
                Head = NextElem;
                Head->PreviousElem = nullptr;
            }
            else
            {
                NextElem->PreviousElem = Head;
                Head = NextElem;
            }
        

        }
        ReIndex();
        cout << "Дескриптор: " << Head << endl;
        fin.close();
    }

    void PrintStack()
    {
        if (Head != nullptr)
        {
            Element* PreviousElement = Head;
            while (PreviousElement != nullptr)
            {
                cout << PreviousElement->index << ". " << PreviousElement->Data << endl;
                PreviousElement = PreviousElement->PreviousElem;  //Движение к первозаписанному элементу
            }
        }
        else
        {
            cout << "Стек пуст" << endl;
        }
    }
    
    void PushElement(Element* NewElement)
    {
        NewElement->PreviousElem = nullptr;
        if (Head != nullptr)
        {
            NewElement->PreviousElem = Head;
            Head = NewElement;
        }
        else
        {
            Head = NewElement;
        }
        ReIndex();
    }
    
    void DeleteElement()
    {
        if (Head != nullptr)
        {
            if (Head->PreviousElem == nullptr) // 1 элемент
            {
                delete Head;
                Head = nullptr;
            }
            else
            {
               
                Head = Head->PreviousElem;
                Element* OldHead = Head;
                delete OldHead;
            }
            ReIndex();
        }
        else
        {
            cout << "Стек пуст" << endl;
        }
    }
    
    void DeleteStack()
    {
        if (Head != nullptr)
        {
            Element* CurrentElement = Head;
            Element* PreviousElem;
            
            while (CurrentElement != nullptr)
            {
                PreviousElem = CurrentElement->PreviousElem;
                delete CurrentElement;
                CurrentElement = PreviousElem;
            }
            Head = nullptr;
            cout << "Стек очищен" << endl;
        }
        else
        {
            cout << "Стек пустой" << endl;
        }
    }

    void ReIndex()
    {
        if (Head != nullptr)
        {
            Element* CurrentElement = Head;
            int index = 0;
            while (CurrentElement != nullptr)
            {
                CurrentElement->index = index;
                index++;
                CurrentElement = CurrentElement->PreviousElem;
            }
        }
    }

};

int main()
{
    int userChoice;
    int value;
    Element* NewElement;
    string path = "Text.txt";
    Stack* stack = new Stack();

    userChoice = 1;
    while (userChoice < 7)
    {

        cout << endl;
        cout << "Меню" << endl;
        cout << "1. создание стека" << endl;
        cout << "2. вывод на экран значения элементов с их индексами" << endl;
        cout << "3. включение нового элемента в список" << endl;
        cout << "4. удаление элемента в списке" << endl;
        cout << "5. очищение стека" << endl;
        cout << "6. завершение работы\n" << endl;
        cout << "Выберете действие: ";
        cin >> userChoice;
        
        switch (userChoice)
        {
            case 1:
                stack->CreateStackFromFile(path);
                cout << "-----------------------------------------------------\n\n";
                break;
                
            case 2:
                stack->PrintStack();
                cout << "-----------------------------------------------------\n\n";
                break;
                        
            case 3:
                cout << "Введите значение типа int: ";
                cin >> value;
                NewElement = new Element();
                NewElement->Data = value;
                stack->PushElement(NewElement);
                cout << "-----------------------------------------------------\n\n";
                break;
                
            case 4:
                stack->DeleteElement();
                cout << "-----------------------------------------------------\n\n";
                break;
                        
            case 5:
                stack->DeleteStack();
                cout << "-----------------------------------------------------\n\n";
                break;
                
            case 6:
                cout << "Работа завершена! " << endl;
                return 0;
                break;
                
                default:
                break;
        }
    }
    return 0;
}
