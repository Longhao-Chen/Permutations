#include<iostream>
#include<thread>
#include<omp.h>
#include<cmath>
#include<stdio.h>
using namespace std;

unsigned long int jc(int &n){
	unsigned long int res=1;
	int i;
	for (i=1;i<=n;++i){
		res*=i;
	}
	return res;
}
long int openmpF(int &max){
	std::ios::sync_with_stdio(false);
	setvbuf(stdout,NULL,_IOFBF,6553500000);
	int *v;
	unsigned int *p;
	unsigned long int *j;
	unsigned long int end;
	p=new unsigned int [max-1]; 
	j=new unsigned long int [max];
	v=new int [max];
	
	int th=std::thread::hardware_concurrency();
	#pragma omp parallel for num_threads(th)
	for(int i=1;i<=max;++i){
		j[i-1]=jc(i);
		v[i-1]=i;
	}
	end=jc(max);
	#pragma omp parellel for num_threads(th)
	for(unsigned long int s=0;s<end;++s){
		for(int i=0;i<max-1;++i){
			p[max-2-i]=(int)(s%j[i+1]/j[i]);
		}
		
		for(unsigned int i=0;i<max-1;++i){
			int py=-1;  //偏移量
			for(unsigned int in=0;in<max;++in){
				if(v[in]>0){
					++py;
					if(py==p[i]){
						printf("%d,",v[in]);
						v[in]=v[in]*-1;
						break;
					}
				}
			}
		}
		printf("\n");
		for(int i=0;i<max;++i){
			v[i]=abs(v[i]);
		}
	}
	return end;
}
int main(){
    	int max=10;   //此为数字位数
	    openmpF(max);
}
