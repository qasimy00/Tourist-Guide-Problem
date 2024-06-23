#include <iostream>
#include <fstream>
using namespace std;


void displayarray(int **arr,int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << "";
			if (arr[i][j] > 0) {
				cout << "   ";
			}
			else {
				cout << "    ";
			}
		}
		cout << endl;
	}
}

void pathfinder(int **arr,int *paths,int*visited,int start,int destination, int size,int count,string &abc){
	visited[start] = 1;
	paths[count] = start;
	count++;
	if (start == destination) {
		for (int i = 0;i < size;i++) {
			//cout << paths[i]+1 << "  ";
			abc = abc + char(paths[i] + 49);
			if (paths[i] == destination) {
				i = size+1;
			}
		}
		//cout << endl;
		abc = abc + '-';
		//cout << abc << endl;
		return;
	}
	else {
		for (int i = 0;i < size;i++) {
			if (arr[start][i] != 0 && i != start && visited[i] != 1) {
				int a = count;
				//weight = arr[start][i];
				//cout << "city1  " << start+1 << "  city2  " << i+1 <<"  weight  "<<weight<< endl;
				pathfinder(arr, paths, visited, i, destination, size, count, abc);	
				 
				for (int i = a;i < size;i++) {
					if (paths[i] != -1) {
						visited[paths[i]] = 0;
					}
				}
				count = a;
			}
		}
	}
	
	
}

int main() {
	ifstream file;
	int size, links=0;
	int** arr;
	int cone, ctwo, weight;
	int start, destination, passengers;
	file.open("inputs.txt");
	if (!file) {
		cout << "File not opened" << endl;
	}
	else {
		file >> size;
		file >> links;
		arr = new int* [size];
		for (int i = 0; i < size; i++) {
			arr[i] = new int[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				arr[i][j] = 0;
			}
		}

		for (int k = 0; k < links;k++) {
			file >> cone;
			file >> ctwo;
			file >> weight;


			cone--;
			ctwo--;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (i == cone && j == ctwo) {
						arr[i][j] = weight;
						arr[j][i] = weight;
					}
				}
			}
		}
		

		//getting last line 
		file >> start;
		file >> destination;
		file >> passengers;
		

		int* visited = new int[size];
		for (int i = 0; i < size; i++) {
			visited[i] = 0;
		}
		int* paths = new int [size];
		for (int i = 0; i < size; i++) {
				paths[i] = -1;
		}

		string abc="";
		pathfinder(arr,paths,visited,start-1,destination-1,size,0,abc);
		//cout << abc;
		int counter = 0;
		for (int i = 0;i < abc.size();i++) {
			if (abc[i] == '-') {
				counter++;
			}
		}
		//cout <<endl<< counter << endl;
		int* minweights = new int[counter];
		for (int i = 0;i < counter;i++) {
			minweights[i] = 10000000;
		}
		int tempweight = 0;
		int p = 0,q=0,counter2=0,counter3=0;
		for (int i = 0;i < abc.size();i++) {
			if (abc[i] != '-' && abc[i + 1] != '-') {
				p = abc[i] - 48;
				q = abc[i + 1] - 48;
				tempweight = arr[p - 1][q - 1];
				//cout << p << " " << q << " " << tempweight << endl;
				if (minweights[counter2]>tempweight) {
					minweights[counter2] = tempweight;
							
				}
			}
			else {
				counter3++;
				if (counter3 % 2 == 0) {
					counter2++;
					//cout << counter2 << endl;
				}
			}
		}
				
		/*for (int i = 0;i < counter;i++) {
			cout<<weght[i]<<" ";
		}*/
		//cout << endl;
		int max = minweights[0];
		for (int i = 0;i < counter;i++) {
			if (max < minweights[i]) {
				max = minweights[i];
			}
		}
		//cout << max << endl;

		int trips = 0;
		trips = passengers / max;
		trips++;
		cout <<trips <<" Trips"<< endl<<endl;
		
		//Display graph
		displayarray(arr, size);
	}

	
	
	return 0;
}

