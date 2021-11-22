#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <stack> 
#include <queue>
using namespace std;
int rad = 1000;
int dum = 0;
void Google_search(int** a, int** dist, int size) {
	queue <int> q;
	int num;
	for (int i = 0; i < size; i++){
		int j = i;
		dist[i][j] = 0;
		q.push(i);
		while (!q.empty()) {
			num = q.front();
			q.pop();
			for (int j = 0; j < size; j++) {
				if (a[num][j] > 0 && dist[i][j] > dist[i][num] + a[num][j]) {
					q.push(j);
					dist[i][j] = dist[i][num] + a[num][j];
				}
			}
		}
	}
}

void rad_dum_wasteland( int* ext, int size, int** distG ) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (distG[i][j] > ext[i])
				ext[i] = distG[i][j];
		}

	cout << endl << "Эксцентриситеты всех вершин" << endl;
	for (int i = 0; i < size; i++) {
		if (ext[i] == 1000)
			cout << "  Вершина изолирована ";
		else
			cout << "  " << ext[i];
	}
	for (int i = 0; i < size; i++) {
		if (ext[i] > dum)
			dum = ext[i];
		if (ext[i] < rad)
			rad = ext[i];
	}
	cout << endl << endl << "Радиус графа равен  " << rad;
	cout << endl << endl << "Диаметр графа равен  " << dum;
}

void best_wateland_survivalists( int* ext, int size) {
	cout << endl << " Подмножество центральных вершин:  ";
	for (int i = 0; i < size; i++)
		if (ext[i] == rad)
			cout << "  " << i;

	cout << endl << " Подмножество переферийных вершин:  ";
	for (int i = 0; i < size; i++)
		if (ext[i] == dum)
			cout << "  " << i;
}

void step_vrshi_search_v1(int size, int** arr) {
	auto step = new int[size];
    int iznum = 0;
	for (int i = 0; i < size; i++)
		step[i] = 0;

	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++) {
			if (arr[row][col] > 0)
				step[row]++
				;
		}
	cout << endl << " Изолированные вершины:  ";
	
	for (int i = 0; i < size; i++)
		if (step[i] == 0) {
			cout << "  " << i;
			iznum++;
		}

	cout << endl << " Концевые вершины:  ";
	for (int i = 0; i < size; i++)
		if (step[i] == 1)
			cout << "  " << i;

	cout << endl << " Доминирующие вершины:  ";
	for (int i = 0; i < size; i++)
		if (step[i] == size - 1 - iznum)
			cout << "  " << i;
}

void main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int size;

	cout << "   Введите размерность матрицы: " << " ";
	cin >> size;
	cout << endl;

	int** arr = new int* [size];
	for (int count = 0; count < size; ++count)
		arr[count] = new int[size];
	for (int row = 0; row < size; row++) {
		arr[row][row] = 0;
		for (int col = row + 1; col < size; col++) {
			arr[row][col] = rand() % 100;
			if (arr[row][col] < 70) {
				arr[row][col] = 0;
				arr[col][row] = arr[row][col];
			}
			else {
				arr[row][col] = rand() % 15;
			    arr[col][row] = arr[row][col];
			}
		}
	}
	cout << "   ";
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++) {
			cout << arr[row][col] << " ";
		}
		cout << endl << "   ";
	}
	cout << endl;
	cout << endl;
	///////////////////////////////////////////////////// num 1.1
	auto distG = new int* [size];
	for (int i = 0; i < size; i++)
		distG[i] = new int[size];
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++) {
			distG[row][col] = 1000;
		}
	}

	Google_search(arr, distG, size);



	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++) {
			if(distG[row][col] == 1000)
			cout << 0 << " ";
			else
			cout << distG[row][col] << " ";
		}
		cout << endl << "   ";
	}
	cout << endl;
	cout << endl;
	auto ext = new int[size];
	for (int i = 0; i < size; i++)
		ext[i] = 0;



	rad_dum_wasteland( ext, size, distG);

	//////////////////////////////////////////////////////////////// num 1.2

	best_wateland_survivalists( ext, size);

	//////////////////////////////////////////////////////////////// num 1.3
	

	step_vrshi_search_v1(size, arr);

	system("pause");
}

/*#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <stack> 
#include <queue>
using namespace std;

int j = 0;
int r = 0;
int i = 0;
int k = 0;

void bfs(int** arr_inc, int num, int* dist, int size, int edge_count) {
	queue <int> que;
	dist[num] = 0;
	que.push(num);
	while (!que.empty()) {
		num = que.front();
		//printf("%d ", num);
		que.pop();
		for (int i = 0; i < edge_count; i++) {
			if (arr_inc[num][i] > 0) {
				for (int count = 0; count < size; count++) {
					if (arr_inc[count][i] > 0 && dist[count] > dist[num] + arr_inc[count][i]) {
						que.push(count);
						dist[count] = dist[num] + arr_inc[count][i];
					}
				}
			}
		}
	}
}

//void bfs(int current_vertex, int size, int edge_count, int** arr_inc, int* dist, int path_length) {
//
//	dist[current_vertex] = path_length;
//
//	int p;
//
//
//
//	for (i = k; i < size; i++)
//	{
//		j = r;
//		if ((arr_inc[i][j] != 0) && (dist[i] > path_length + arr_inc[i][j]))
//		{
//			dist[i] = path_length;
//			p = i;
//			//cout << i << " ";
//			for (j = 0; j < edge_count; j++)
//			{
//				i == p;
//				if (arr_inc[i][j] != 0)
//				{
//					r = j;
//					for (k = 0; k < size; k++)
//					{
//						j == r;
//						if ((arr_inc[k][j] != 0) && (dist[k] > path_length + arr_inc[i][j]))
//							bfs(i, size, edge_count, arr_inc, dist, path_length + arr_inc[i][j]);
//					}
//				}
//			}
//		}
//	}
//}


int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");

	int size;

	cout << "   Введите размерность матрицы: ";
	cin >> size;
	cout << endl;

	int** arr = new int* [size];
	for (int count = 0; count < size; ++count)
		arr[count] = new int[size];

	for (int row = 0; row < size; row++) {
		arr[row][row] = 0;
		for (int col = row + 1; col < size; col++) {
			arr[row][col] = rand() % 100;
			arr[col][row] = arr[row][col];
		}
	}
	cout << "   ";

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++) {
			cout << arr[row][col] << " ";
		}
		cout << endl << "   ";
	}
	cout << endl;
////////////////////////////////////////////////////////////////////////////////
	int edge_count=0;
	for (int row = 0; row < size; row++) {
		for (int col = row + 1; col < size; col++) {
			if (arr[row][col])
				edge_count++;
		}
	}
////////////////////////////////////////////////////////////////////////////////
	int** arr_inc = new int* [size];
	for (int count = 0; count < size; ++count) {
		arr_inc[count] = new int[edge_count];
		for (int col = 0; col < edge_count; col++)
			arr_inc[count][col] = 0;
	}

	edge_count = 0;
	for (int row = 0; row < size; row++) {
		for (int col = row + 1; col < size; col++) {
			if (arr[row][col]) {
				arr_inc[row][edge_count] = arr[row][col];
				arr_inc[col][edge_count] = arr[row][col];
				edge_count++;
			}
		}
	}
	for (int row = 0; row < size; row++)
	{
		cout << endl << "   ";
		for (int col = 0; col < edge_count; col++) {
			cout << arr_inc[row][col] << "   ";
		}
	}

	int* dist = new int[size];
	int* ext = new int[size];
	int max;

	cout << endl;
	for (int cunt = 0; cunt < size; ++cunt) {
		for (int count = 0; count < size; ++count)
			dist[count] = INT_MAX;
		bfs(arr_inc, cunt, dist, size, edge_count);

		if (dist[0] == INT_MAX)
			dist[0] = 0;
		max = dist[0];
		for (int fuck = 0; fuck < size; ++fuck) {
			if (dist[fuck] == INT_MAX)
				dist[fuck] = 0;
			//cout << " " << dist[fuck];
			if(dist[fuck] > max)
				max = dist[fuck];
		}
		ext[cunt] = max;
		cout << max << " ";
	}
	cout << endl;
}*/