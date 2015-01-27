#include "cpu_test.h"

void dummy_proc_0(){
	return;
}
void dummy_proc_1(unsigned a0){
	return;
}
void dummy_proc_2(unsigned a0, unsigned a1){
	return;
}
void dummy_proc_3(unsigned a0, unsigned a1, unsigned a2){
	return;
}
void dummy_proc_4(unsigned a0, unsigned a1, unsigned a2, unsigned a3){
	return;
}
void dummy_proc_5(unsigned a0, unsigned a1, unsigned a2, unsigned a3, unsigned a4){
	return;
}
void dummy_proc_6(unsigned a0, unsigned a1, unsigned a2, unsigned a3, unsigned a4, unsigned a5){
	return;
}
void dummy_proc_7(unsigned a0, unsigned a1, unsigned a2, unsigned a3, unsigned a4, unsigned a5, unsigned a6){
	return;
}

float* cpu_proccall_overhead(unsigned ccnt_overhead)
{
	unsigned start, end;
	static float total[PROCCALL_ARG_NUM+1];
	unsigned a0,a1,a2,a3,a4,a5,a6;
	a0 = 0;
	a1 = 1;
	a2 = 2;
	a3 = 3;
	a4 = 4;
	a5 = 5;
	a6 = 6;
	int i;

	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		total[i] = 0;
	}
	
	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_0();
		end = ccnt_read();
		total[0] += end - start - ccnt_overhead;
		
		start = ccnt_read();
		dummy_proc_1(a0);
		end = ccnt_read();
		total[1] += end - start - ccnt_overhead;

		start = ccnt_read();
		dummy_proc_2(a0,a1);
		end = ccnt_read();
		total[2] += end - start - ccnt_overhead;

		start = ccnt_read();
		dummy_proc_3(a0,a1,a2);
		end = ccnt_read();
		total[3] += end - start - ccnt_overhead;
		
		start = ccnt_read();
		dummy_proc_4(a0,a1,a2,a3);
		end = ccnt_read();
		total[4] += end - start - ccnt_overhead;
		
		start = ccnt_read();
		dummy_proc_5(a0,a1,a2,a3,a4);
		end = ccnt_read();
		total[5] += end - start - ccnt_overhead;

		start = ccnt_read();
		dummy_proc_6(a0,a1,a2,a3,a4,a5);
		end = ccnt_read();
		total[6] += end - start - ccnt_overhead;
		
		start = ccnt_read();
		dummy_proc_7(a0,a1,a2,a3,a4,a5,a6);
		end = ccnt_read();
		total[7] += end - start - ccnt_overhead;
	}

	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		total[i] /= (float)PROCCALL_TEST_NUM;
	}

	return total;
}
