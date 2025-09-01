#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

int ReadTable(const char *filename, int verbose);
void FreeTable();
int l2p(int la, int verbose);

int m = 0;
int n = 0;
int *ptbr = NULL;
int ptlr = 0;
int mask = 0;

int main(int argc, char *argv[])
{
	if(argc <= 1){
		return 0;
		printf("Usage: %s <page_table>\n", argv[0]);
	}
	int ret = ReadTable(argv[1], TRUE);
	if(ret == FALSE)
		exit(-1);
	int step = 1;
	int max_la = ptlr * (1 << n);
	if(max_la > 20)
		step = max_la / 20;
	printf("max_la = 0x%x (%d)\n", max_la, max_la);
	for(int la = 0; la <= max_la; la += step){
		int pa = l2p(la, FALSE);
		printf("\t0x%x (%d)--> 0x%x (%d)\n", la, la, pa, pa);
	}
	FreeTable();
	printf("Bye!\n");
	return 0;
}

int ReadTable(const char *filename, int verbose)
{
	FILE *fp = fopen(filename, "r");
	int entry;
		
	if(fp == NULL){
		perror("Failed to open file");
		return FALSE;
	}
	fscanf(fp, "%d %d %d", &m, &n, &ptlr);
	mask = (1 << n) - 1;
	ptbr = (int *)malloc(ptlr * sizeof(int));
	if(!ptbr) {
		printf("Malloc Error!\n");
		fclose(fp);
		return FALSE;
	}
	for (int i = 0; i < ptlr; i++) {
		if(fscanf(fp, "%d", &entry) != 1) {
			printf("Error reading page table entry %d\n", i);
			fclose(fp);
			return FALSE;
		}
		ptbr[i] = entry;
	}
	if(verbose) {
		printf("page table\n");
		printf("\tm = %d, n = %d\n\tpage size = %d\n", m, n, (1 << n));
		printf("\tmaximum number of pages = %d\n", ptlr);
		printf("\tptlr = %d\n", ptlr);
		printf("\toffset mask = 0x%d\n", mask);
		for (int i = 0; i < ptlr; i++) 
			printf("\tptbr[%d] = %d\n", i, ptbr[i]);
	}
	fclose(fp);
	return TRUE;
}
void FreeTable()
{
	free(ptbr);
	ptbr = NULL;
	m = 0;
	n = 0;
	ptlr = 0;
	mask = 0;
}
int l2p(int la, int verbose)
{
	int page_number = la >> n;
	int offset = la & mask;
	if(page_number >= ptlr) {
		printf("TRAP: Page number %d is greater than ptlr %d\n", page_number, ptlr);
		return -1;
	}
	int pa = (ptbr[page_number] << n) + offset;
	if(verbose) {
		printf("Logical Address: 0x%x (%d)\n", la, la);
		printf("Page Number: %d\n", page_number);
		printf("frame number = %d\n", ptbr[page_number]);
		printf("offset = %d\n", offset);
		printf("frame_number << n = %d\n", ptbr[page_number] << n);
		printf("Physical Address: 0x%x (%d)\n", pa, pa);
	}
	return pa;
}
