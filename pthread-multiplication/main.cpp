#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <string>

using namespace std;

#define NUM_THREADS 5

#define MAX_SIZE = 10000;

struct thread_data{
	int thread_id;
	char *message;
};

class matrix{
	private:
		int *m;
		int row, column;
	public:
		matrix(int r, int c) : row(r), column(c), m(new int[r*c]){
			for(int i = 0; i < r; i++){
				for(int j = 0; j < c; j++){
					m[i][j] = 0;
				};
			};
		};	
		~matrix(){delete[] m; };

		int getRow(){return row;};
		int setRow(int r){row = r;};
		int getColumn(){return column;};
		int setColumn(int c){column = c;};

		int printMatrix(){
			for(int k = 0; k < this->row; k++){
				for(int j = 0; j < this->column; j++){
					int s = s + this->m[k][j];
					cout << s << " ";
					// cout << "k: " << k << endl;
					// cout << "j: " << j << endl;
					// cout << "row: " << this->row << endl;
					// cout << "column: " << this->column << endl;
				}
			cout << endl;
			};
		};
};


void *PrintHello(void *threadarg) {
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
    
	cout << "Thread ID : " << my_data->thread_id;
	cout << " Message : " << my_data->message << endl;

	pthread_exit(NULL);
}




int main () {
	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	int rc;
	int i;

	matrix m(10,3);

	m.printMatrix();

	for( i = 0; i < NUM_THREADS; i++){
		cout << "main() : creating thread, " << i << endl;
		td[i].thread_id = i;
		td[i].message = (char *)"This is message";
		rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
		if (rc) {
			cout << "Error: unable to create thread, " << rc << endl;
			exit(-1);
		}
	
	}
	pthread_exit(NULL);
}
