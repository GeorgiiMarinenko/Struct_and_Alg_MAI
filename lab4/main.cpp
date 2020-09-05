#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int inf = INT_MAX;
const int EdgeNum = 27;
const int NumbOfHeads = 20;

int nodes[NumbOfHeads + 1];
int LastN;


struct graph
{
    int MatrSize;//размер матрицы смежности (количество вершин)
    int** MatrSmejnosti;//указатель на матрицу смежности взвешенного графа
};

struct Edge //Ребро в неориентированном графе
{
    int First;
    int Second;
    int Weight;
};

graph* ReadGraf(const char* filename);
void PrintGraf(graph* gr);
void DynamicProgr(graph* gr, int start, int end);
void AlgKraskala();
int Component(int n);
// Функция получает цвет вершины n-й по порядку.
// если nodes[n] < 0, то вершина n имеет цвет nodes[n]
// если nodes[n] >= 0, то вершина n имеет цвет такой же,
// как и вершина с номером nodes[n]

int main()
{
    graph* A = ReadGraf("Text.txt");
//    PrintGraf(A);
    int Start, End;
    cout << " ЗАДАНИЕ 1:" << endl;
    cout << "Введите значения начальной и конечной вершин:" << endl;
    cout << "Начальная = ";
    cin >> Start;
    cout << "Конечная = ";
    cin >> End;
    cout << endl;
    DynamicProgr(A, Start,End);
    for(int i = 0; i < NumbOfHeads + 1; i++) nodes[i] = -1-i;
    AlgKraskala();
    return 0;
}

graph* ReadGraf(const char* filename) //чтение матрицы из файла
{
    ifstream FILE(filename);
    //создание структуры и матрицы
    graph* gr = new graph;
    int N;
    FILE >> N;
    gr->MatrSize = N;
    gr->MatrSmejnosti = new int*[N];
    for (int i = 0; i < N; i++)
    {
        (gr->MatrSmejnosti)[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            FILE >> (gr->MatrSmejnosti)[i][j];
            if((gr->MatrSmejnosti)[i][j] == -1)
            {
                (gr->MatrSmejnosti)[i][j] = 0;
            }
        }
    }
    return gr;
}

void PrintGraf(graph* gr)
{
    int N, i, g;
    N = gr->MatrSize;
    for (i = 0; i < N; i++)
    {
        for (g = 0; g < N; g++)
            cout<<(gr->MatrSmejnosti)[i][g]<<" ";
        cout << endl;
    }
}

void DynamicProgr(graph* gr, int start, int end)
{
    start--;
    end--;
    int i,j,k;
    int MatrSize = gr->MatrSize;
    int** MatrSmejnosti = gr->MatrSmejnosti;
    int* ShortestPath = new int[MatrSize]; //кратчайшие пути до конечной вершины
    int* LastNodes = new int[MatrSize]; //предыдущие вершины на пути от iой вершины до конечной
    for (i = 0; i < MatrSize; i++)
    {
        ShortestPath[i] = inf;
        LastNodes[i] = end;
    }
    ShortestPath[end] = 0; //путь от конечной до конечной равен нулю
    for (i = 1; i < MatrSize; i++) //поиск длин путей
    {
        for (j = 0; j < MatrSize; j++) //поиск вершин с уже известными конечными путями
        {
            if (ShortestPath[j] < inf)
            {
                for (k = 0; k < j; k++) //поиск смежных с этой вершиной вершин
                {
                    if (MatrSmejnosti[k][j] != 0)
                        if (ShortestPath[k] > ShortestPath[j] + MatrSmejnosti[k][j]) //Поиск минимального пути
                        {
                            ShortestPath[k] = ShortestPath[j] + MatrSmejnosti[k][j];
                            LastNodes[k] = j;
                        }
                }
            }
        }
    }

    j = start;
    if (ShortestPath[start] == inf)
        cout << "Искомого пути не существует.\n";
    else
    {
        cout << j+1 << "->";
        do
        {
            j = LastNodes[j];
            cout << j+1 << "->";
        } while (j != end);
        cout << "Кратчайший путь в графе\n";
    }
}

void AlgKraskala()
{
//    Edge* NonOrientedGraf = new Edge[EdgeNum]; //Массив структур Edge
    Edge NonOrientedGraf[EdgeNum] ={{1,2,8},{1,5,10},{1,3,5},{2,4,10},{2,15,25},{3,7,20},
        {3,6,8},{3,9,15},{4,8,25},{5,7,7},{6,11,4},{7,10,5},{7,14,10},{8,15,8},
        {9,13,7},{10,15,4},{11,12,7},{12,16,7},{13,16,8},{13,17,3},{14,18,15},
        {15,18,27},{16,18,5},{17,19,6},{17,20,13},{18,19,2},{19,20,9}};
    Edge BUFF = {0,0,0};
    cout << endl;
    cout << " ЗАДАНИЕ 2:";
    cout << endl << "Сортировка весов ребер по возрастанию:";
    for (int i = 0; i < EdgeNum; i++)
    {
        for (int j = 0; j < EdgeNum - 1; j++)
        {
            if (NonOrientedGraf[j].Weight > NonOrientedGraf[j+1].Weight)
            {
                BUFF = NonOrientedGraf[j];
                NonOrientedGraf[j] = NonOrientedGraf[j+1];
                NonOrientedGraf[j+1] = BUFF;
            }
        }
    }
    for (int i = 0; i < EdgeNum; i++)
    {
        cout << endl;
        cout << NonOrientedGraf[i].Weight << "\t [" << NonOrientedGraf[i].First
        << "] - [" << NonOrientedGraf[i].Second  << "]";
    }
    cout << endl;
    //КРАСКАЛ
    cout << endl;
    cout <<  endl;
    cout << "Вывод минимального оставного дерева исходного графа:" << endl;
    for(int i = 0; i < EdgeNum; i++)
    { // пока не прошли все ребра
       int c2 = Component(NonOrientedGraf[i].Second);
       if ( Component (NonOrientedGraf[i].First) != c2 )
       {

          nodes [LastN] = NonOrientedGraf[i].Second;
           cout << NonOrientedGraf[i].Weight << "\t [" <<  NonOrientedGraf[i].First << "] - [" << NonOrientedGraf[i].Second << "]" << endl;
       }
    }
}

int Component(int n)
{
   int c;
   if (nodes[n]<0)
      return nodes[LastN=n];
   c = Component(nodes[n]);
   nodes[n] = LastN;
   return c;
}
