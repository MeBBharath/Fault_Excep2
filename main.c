#include <stdint.h>
#include <stdio.h>
int f1(int a, int b);

int main(void)
{
    /* Loop forever */
	uint32_t *pSHSCR=(uint32_t *)0xE000ED24;
	*pSHSCR |=(7<<16);

	uint32_t *pCCR=(uint32_t *)0xE000ED14;
	*pCCR |= (1<<4);

	f1(10,0);

	for(;;);
}
int f1(int a, int b)
{
	return a/b;
}
void HardFault_Handler(void)
{
	printf("Hardf");
	while(1);
}
void MemManage_Handler(void)
{
	printf("MemManf");
	while(1);
}
void BusFault_Handler(void)
{
	printf("Busf");
	while(1);
}
__attribute__ ((naked))void UsageFault_Handler(void)
{
	__asm ("MRS r0,MSP");
	__asm ("B UsageFault_Handler_c");
}
void  UsageFault_Handler_c(uint32_t *pBaseStack)
{

	uint32_t *pUFSR=(uint32_t *)0xE000ED2A;
	printf("UFSR=%lx",(*pUFSR)&0xFFFF);
	printf("pBaseStack=%p",pBaseStack);
	printf("Usagef");
	while(1);
}
