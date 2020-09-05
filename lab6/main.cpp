#include <iostream>
#include <ctime>
using namespace std;


int Arr1[20] = {7,16,18,99,23,1,53,251,27,13,67,120,134,62,2,72,90,84,47,14};
int Arr2[20] = {7,16,18,99,23,1,53,251,27,13,67,120,134,62,2,72,90,84,47,14};

void PrintArr(int *Arr)
{
    for( int i = 0; i < 20; i++)
    {
        cout << Arr[i] << " ";
    }
    cout << endl;
}

double StraightChoice(int *Arr1)
{
    int size = 20;
    int Cmp = 0;
    int Max, Temp; // для поиска минимального элемента и для обмена
    clock_t start = clock();
    for (int i = 0; i < size - 1; i++)
    {
        Cmp++;
        Max = i; // запоминаем индекс текущего элемента
        // ищем минимальный элемент чтобы поместить на место i-ого
        for (int j = i + 1; j < size; j++)  // для остальных элементов после i-ого
        {
            Cmp++;
            if (Arr1[j] > Arr1[Max]) // если элемент меньше минимального,
            {
                Cmp++;
                Max = j;// запоминаем его индекс в min
                
            }
        }
        Temp = Arr1[i];// меняем местами i-ый и минимальный элементы
        Arr1[i] = Arr1[Max];
        Arr1[Max] = Temp;
        cout << "i = " << i << "\t ";
        PrintArr(Arr1);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "\nЧисло сравнений = " << Cmp << "\nTime = " << seconds <<  endl;
    return seconds;
}

double Shell(int *Arr)
{
    int i, j, Temp;
    int Cmp = 0;
    int d = 20;
    int Step = 0;
    clock_t start = clock();
    d = d/2;
    while(d > 0)
    {
        Cmp++;
        for(i = 0; i < 20 - d; i++)
        {
            Cmp++;
            j = i;
            while(j >= 0 && Arr[j] < Arr[j+d])
            {
                Cmp +=2;
                Temp = Arr[j];
                Arr[j] = Arr[j+d];
                Arr[j+d] = Temp;
                j--;
            }
        }
        d = d/2;
        cout << "i = " << Step << "\t ";
        Step++;
        PrintArr(Arr2);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "\nЧисло сравнений = " << Cmp << "\nTime = " << seconds <<  endl;
    return seconds;
}
int main()
{
    double StraightChoice_Time = 0, Shell_Time = 0;
    
    cout << "ЗАДАНИЕ 1. Алгоритм прямого включения:" << endl;
    cout << "Печать исходного массива:" << endl;
    PrintArr(Arr1);
    cout << endl;
    StraightChoice_Time = StraightChoice(Arr1);
    cout << "\nВывод полученного результата: " << endl;
    PrintArr(Arr1);
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
    
    cout << "ЗАДАНИЕ 2.  Метод Шелла:" << endl;
    cout << "Печать исходного массива:" << endl;
    PrintArr(Arr2);
    cout << endl;
    Shell_Time = Shell(Arr2);
    cout << "Вывод полученного результата: " << endl;
    PrintArr(Arr2);
    cout << "------------------------------------------------------------" << endl;
    
    if(StraightChoice_Time < Shell_Time)
    {
        cout << "Алгоритм прямого выбора  работает быстрее алгоритма Шелла за время: " << StraightChoice_Time << endl;
    }
    else
    {
        cout << "Алгоритм Шелла работает быстрее алгоритма прямого выбора за время: " << Shell_Time << endl;
    }
    
    return 0;
}
