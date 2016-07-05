//#include <iostream>
//#include <mpi.h>
//#include <stdio.h>
//#include <assert.h>
//#include <algorithm>
//#include <array>
//#include <vector>
//#include <time.h>
//
//using namespace std;
//
//float *create_rand_nums(int num_elements){
//	float *rand_nums = (float*)malloc(sizeof(float) * num_elements);
//	assert(rand_nums != NULL);
//	int i;
//	for (i=0;i<num_elements;i++){
//		rand_nums[i] = (rand()/float(RAND_MAX));
//	}
//
//	return rand_nums;
//
//}
//
//
//
//int main(int argc, char**argv){
//	float a,b;
//	float alpha = 0.00001;
//
//	int num_points = 1000;
//
//	printf("input slope \n");
//	cin>>a;
//	printf("input intercept \n");
//	cin>>b;
//	cout<<("objective function:y=")<<a<<"x+"<<b<<endl;
//	
//	
//
//	
//	float *random_numbers = NULL;
//
//	//Initialize (x,y), theta
//	
//
//	srand(time(NULL));
//	random_numbers = create_rand_nums(num_points);
//	
//	
//
//	array<array<float,2>,1000> y_array = {0};
//
//	//Initialize array
//	for (int i=0;i<num_points;i++){
//		y_array[i][1] = a*i + b; //+ random_numbers[i];
//		y_array[i][0] = i;
//	}
//
//	//Array permutation
//	random_shuffle(y_array.begin(),y_array.end());
//
//	float theta[2] = {0,1};
//	float delta;
//
//	for (int i = 1; i < 100; i++){
//		delta = (y_array[i][1] - theta[0]*y_array[i][0] - theta[1]);
//		theta[0] += 2*alpha*y_array[i][0]*delta;
//		theta[1] += 2*alpha*delta;
//	}
//    
//	
//	//print result
//	cout<<"sgd slope "<<theta[0]<<" sgd intercept "<<theta[1]<<endl;
//	cout<<"actual slope "<<a<<" actual intercept "<<b<<endl;
//	return 0;
//}
//	
