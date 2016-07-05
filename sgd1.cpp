#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <array>
#include <vector>
#include <time.h>

using namespace std;

//random numbers generator
float *create_rand_nums(int num_elements){
	float *rand_nums = (float*)malloc(sizeof(float) * num_elements);
	assert(rand_nums != NULL);
	int i;
	for (i=0;i<num_elements;i++){
		rand_nums[i] = (rand()/float(RAND_MAX));
	}

	return rand_nums;

}




int main(int argc, char**argv){
	//a,b are slope and intercept.
	//alpha is the step length of sgd.
	float a,b;
	float alpha = 0.000001;
	int num_points = 1000;

	
	//Initialize MPI
	MPI_Init(NULL,NULL);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);

	float *random_numbers = NULL;

	//Input slope and intercept.
	if (world_rank == 0){
	random_numbers = create_rand_nums(num_points);

	int num_elements_per_proc = 100;

	printf("input slope \n");
	cin>>a;
	printf("input intercept \n");
	cin>>b;
	cout<<("objective function:y=")<<a<<"x+"<<b<<endl;
	
		
	}
	

	srand(time(NULL));

	//redudant with initialization when world rank = 0
	int num_elements_per_proc = 100;
	random_numbers = create_rand_nums(num_points);

	
	//Initiallize y_array and its pointer.
	array<array<float,2>,1000> y_array = {0};
	//Pointer of y_array, which is WRONG.
	float *y = &y_array[0][0];



	//Fill in the array
	for (int i=0;i<num_points;i++){
		y_array[i][1] = a*i + b + random_numbers[i];
		y_array[i][0] = i;

	}

	random_shuffle(y_array.begin(),y_array.end());//randomly shuffle array y

	
	//Allocate memory for sub_arrays to be scattered. 
	float *sub_array = (float *)malloc(sizeof(float) * num_elements_per_proc);
	assert(sub_array != NULL);


	//MPI scatter
	MPI_Scatter(y,num_elements_per_proc,MPI_FLOAT,sub_array,num_elements_per_proc,MPI_FLOAT,0,MPI_COMM_WORLD);

	
	//Convert pointer to array
	array<float,100> sub = {0};
	for (int i=1;i<num_elements_per_proc;i++){
		sub[i-1] = sub_array[i-1];
	}
	
	
	random_shuffle(sub.begin(),sub.end());//random shuffle sub_array

	
	//sgd iteration
	float slope = 0;
	float intercept = 1;
	float delta;


	for (int i = 0; i < num_elements_per_proc; i++){
		delta = (y_array[i][1] - slope*y_array[i][0] - intercept);
		slope += alpha*y_array[i][0]*delta;
		intercept += alpha*delta;
	}

    cout<<"slope "<<slope<<endl;
	cout<<"intercept "<<intercept<<endl;
	

	//Allocate memory for sub_slopes and sub_intercepts
	float *sub_slopes = NULL;
	float *sub_intercepts = NULL;
	if (world_rank == 0){
		sub_slopes = (float *)malloc(sizeof(float) * world_size); 
		sub_intercepts = (float *)malloc(sizeof(float) * world_size);
		assert(sub_slopes != NULL); 
		assert(sub_intercepts != NULL);
	}

	
	//MPI_Gather 
	MPI_Gather(&slope,1,MPI_FLOAT,sub_slopes,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	MPI_Gather(&intercept,1,MPI_FLOAT,sub_intercepts,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	
	cout<<"world size "<<world_size<<endl;
	//Sum the result

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

	float sum_slope = 0;
	float sum_intercept = 0; 
	
	for (int i=0;i<world_size;i++){
		sum_slope += sub_slopes[i];
		sum_intercept += sub_intercepts[i];
	}
	


	//print result
	cout<<"sgd slope "<<sum_slope/world_size<<" sgd intercept "<<sum_intercept/world_size<<endl;
	cout<<"actual slope "<<a<<" actual intercept "<<b<<endl;
	return 0;
}
	