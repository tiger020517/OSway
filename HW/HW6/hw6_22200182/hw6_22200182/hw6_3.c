#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

int ReadTable(const char *filename, int verbose);
void FreeTable();
int l2p(int sn, int offset, int verbose);

typedef struct {
	int limit, base;
} Descriptor;

Descriptor *stbr = NULL;
int stlr = 0;


int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("Usage: %s <segment_table>\n", argv[0]);
		return 0;
	}
	int ret = ReadTable(argv[1], TRUE);
	if(ret == FALSE)
		exit(-1);
	for(int sn = 0; sn < stlr; sn++)
	{
		Descriptor *d = &stbr[sn];
		int offset[] = { 0, d->limit/2, d->limit - 1, d->limit };
		for(int j = 0; j < 4; j++)
			printf("\t(%d, %d) -> %d\n", sn, offset[j], l2p(sn, offset[j], FALSE));
		putchar('\n');
	}
	printf("\t(%d, %d) -> %d\n", stlr, 0, l2p(stlr, 0, FALSE));
	FreeTable();
	return 0;
}

int ReadTable(const char *filename, int verbose)
{
	FILE *fp = fopen(filename, "r");
	int entry;

	if(fp == NULL){
		perror("File open error");
		return 0;
	}
	fscanf(fp, "%d", &stlr);
	stbr = (Descriptor *)malloc(stlr * sizeof(Descriptor));
	if(!stbr) {
		printf("Malloc Error!\n");
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < stlr; i++) {
		if (fscanf(fp, "%d", &stbr[i].limit) != 1) {
			printf("Error reading segment table entry %d\n", i);
			free(stbr);
			fclose(fp);
			return 0;
		}
	}
	for (int i = 0; i < stlr; i++) {
		if (fscanf(fp, "%d", &stbr[i].base) != 1) {
			printf("Error reading segment table base %d\n", i);
			free(stbr);
			fclose(fp);
			return 0;
		}
	}
	if (verbose) {
		printf("Segment Table\n");
		printf("\tstlr = %d\n", stlr);
		for (int i = 0; i < stlr; i++) {
			printf("\tlimit = %d, Base = %d\n", stbr[i].limit, stbr[i].base);
		}
		write(1, "\n", 1);
	}
	fclose(fp);
	return 1;
}

void FreeTable()
{
	if(stbr) {
		free(stbr);
		stbr = NULL;
	}
	stlr = 0;
}

int l2p(int sn, int offset, int verbose)
{
	if(sn < 0 || sn >= stlr) {
		printf("TRAP: Segment no %d >= stlr %d\n", sn, stlr);
		return -1;
	}
	Descriptor *d = &stbr[sn];
	if(offset >= d->limit || offset < 0) {
		printf("TRAP: Offset %d >= limit %d)\n", offset, d->limit);
		return -1;
	}
	int physical_address = d->base + offset;
	if(verbose) {
		printf("Segment %d: Base = %d, Limit = %d, Offset = %d, Physical Address = %d\n", sn, d->base, d->limit, offset, physical_address);
	}
	return physical_address;
}