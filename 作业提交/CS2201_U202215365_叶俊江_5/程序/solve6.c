#include<stdio.h>
void f();
extern void (*myprint)();
void (*myprint)() = f;
void f(){
	printf("U202215365\n");
}
