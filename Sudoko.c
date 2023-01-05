#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int board[9][9]; 
int valid[11]; 
int subgridCt = 2; 



typedef struct{
    
    int row;
    int column;
    
}parameters;


pthread_t col_thread, row_thread, first_thread, second_thread, third_thread, fourth_thread, fifth_thread, sixth_thread, seventh_thread, eighth_thread, ninth_thread;


void *column_worker(void *param); 	
void *row_worker(void *param);
void *square_worker(void *param);


int main(int argc, char *argv[])
{
   	int j = 0; 
	int i = 0; 
        int k = 0; 
	
        
        
	if (argc == 1) {
            fprintf(stderr,"Usage: ./hw2 <sudoku grid>\n");

            return -1;
    	}
        
        
	FILE *sudoku; 
	sudoku = fopen(argv[1], "r");

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			fscanf(sudoku, "%d ", &board[i][j]);
		}
	}		
		    
   
        
        parameters *checkRows = (parameters *) malloc(sizeof(parameters));
        checkRows->row = 0;
        checkRows->column = 0;
       
        parameters *checkCols = (parameters *) malloc(sizeof(parameters));
        checkCols->row = 0;
        checkCols->column = 0;
       
        parameters *first3by3 = (parameters *) malloc(sizeof(parameters));
        first3by3->row = 0;
        first3by3->column = 0;
        
        parameters *second3by3 = (parameters *) malloc(sizeof(parameters));
        second3by3->row = 0;
        second3by3->column = 3;
     
        parameters *third3by3 = (parameters *) malloc(sizeof(parameters));
        third3by3->row = 0;
        third3by3->column = 6;
      
        parameters *fourth3by3 = (parameters *) malloc(sizeof(parameters));
        fourth3by3->row = 3;
        fourth3by3->column = 0;
       
        parameters *fifth3by3 = (parameters *) malloc(sizeof(parameters));
        fifth3by3->row = 3;
        fifth3by3->column = 3;
       
        parameters *sixth3by3 = (parameters *) malloc(sizeof(parameters));
        sixth3by3->row = 3;
        sixth3by3->column = 6;
       
        parameters *seventh3by3 = (parameters *) malloc(sizeof(parameters));
        seventh3by3->row = 6;
        seventh3by3->column = 0;
    
        parameters *eighth3by3 = (parameters *) malloc(sizeof(parameters));
        eighth3by3->row = 6;
        eighth3by3->column = 3;
      
        parameters *ninth3by3 = (parameters *) malloc(sizeof(parameters));
        ninth3by3->row = 6;
        ninth3by3->column = 6;
        
        
        
        void * rows;
        void * cols;
        void * first_square;
        void * second_square;
        void * third_square;
        void * fourth_square;
        void * fifth_square;
        void * sixth_square;
        void * seventh_square;
        void * eighth_square;
        void * ninth_square;
        
        
        
        pthread_create(&col_thread, NULL, column_worker, (void *) checkCols);
        pthread_create(&row_thread, NULL, row_worker, (void *) checkRows);
        pthread_create(&first_thread, NULL, square_worker, (void *) first3by3);
        pthread_create(&second_thread, NULL, square_worker, (void *) second3by3);
        pthread_create(&third_thread, NULL, square_worker, (void *) third3by3);
        pthread_create(&fourth_thread, NULL, square_worker, (void *) fourth3by3);
        pthread_create(&fifth_thread, NULL, square_worker, (void *) fifth3by3);
        pthread_create(&sixth_thread, NULL, square_worker, (void *) sixth3by3);
        pthread_create(&seventh_thread, NULL, square_worker, (void *) seventh3by3);
        pthread_create(&eighth_thread, NULL, square_worker, (void *) eighth3by3);
        pthread_create(&ninth_thread, NULL, square_worker, (void *) ninth3by3);
     
        

	
	pthread_join(col_thread, &cols);
        pthread_join(row_thread, &rows);
        pthread_join(first_thread, &first_square);
        pthread_join(second_thread, &second_square);
        pthread_join(third_thread, &third_square);
        pthread_join(fourth_thread, &fourth_square);
        pthread_join(fifth_thread, &fifth_square);
        pthread_join(sixth_thread, &sixth_square);
        pthread_join(seventh_thread, &seventh_square);
        pthread_join(eighth_thread, &eighth_square);
        pthread_join(ninth_thread, &ninth_square);
        
	
        
	while(k < 11){
	
            
            if(valid[k] == 1){               
		k++;
            }
            else{
                printf("The Sudoku Puzzle is NOT solved. \n");
                exit(0);
            }
            
        }
        printf("The Sudoku Puzzle is solved. \n");
	

	return 0;
}


void *column_worker(void *params)
{
    int i, j; 
    
    parameters * c_worker = (parameters *) params;
    int beginCol = c_worker->column;
    int beginRow = c_worker->row;

    
    for(i = beginCol; i < 9; i++){
     
	int col[9]= {0}; 
        
        for(j = beginRow; j < 9; j++){
            
            int val = board[i][j]; 
            
            
            
	    if(col[val-1] == 0 && val > 0){
               col[val-1] = val;
		
            }
		
            else{
		valid[0] = 0;
                pthread_exit(0);
            }
        }
    }   
    valid[0] = 1;
    pthread_exit(0);	       
}


void *row_worker(void *params){

    int i, j; 
    
    parameters * r_worker = (parameters *) params;
    int beginCol = r_worker->column;
    int beginRow = r_worker->row;
    
    
    
    for(i = beginCol; i < 9; i++){
        
        int row[9]= {0};        
        for(j = beginRow; j < 9; j++){
            
            int val = board[i][j];
            
           
            
            if(row[val-1] == 0 && val > 0){
                row[val-1] = val;
            }
            
            
            
            else{
                valid[1] = 0;
		pthread_exit(0);
            }
        }
    }        
    valid[1] = 1;
    pthread_exit(0);
}



void *square_worker(void *params){
	
    int i, j;

    parameters * worker = (parameters *) params;
    int beginRow = worker->row;
    int beginCol = worker->column;
    
   
	
    int square[9] = {0}; 

    for (i = beginRow; i < beginRow + 3; ++i) {
        for (j = beginCol; j < beginCol + 3; ++j) {
            
            int val = board[i][j];
            
            
	   
            if (square[val-1] == 0 && val > 0) {
                square[val-1] = val;
            }
            
            
            
            else{
                valid[subgridCt] = 0;
		subgridCt++;
		pthread_exit(0);
            }
        }
    }	
    valid[subgridCt] = 1;
    subgridCt++;
    pthread_exit(0);
}
