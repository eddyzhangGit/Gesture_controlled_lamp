#ifndef Start_Measurment_Loop /* Include guard */
#define Start_Measurment_Loop 

void Start_Measurment(float CLKHS_fre_corr_fact);
void timeval_print(struct timeval *tv);
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1);








#endif
