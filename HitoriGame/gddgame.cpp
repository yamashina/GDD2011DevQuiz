#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int data[100][10] = {0};
static int numData[100] = {0};

int getTestCaseNum(FILE *fp);
void setTestData(FILE *fp, int numTestCase);
bool isMultipleOf5(int *line);
void devide(int *line);
int getNumMultipleOf5(int *line, int row);
void clearMultipleOf5(int *line);

int countByProc1(int row);
int countByProc2(int row);
int countByProc3(int row);
int countByProc4(int row);

int main() {
	FILE *fp = fopen("testdata.txt", "r");
	
	if (fp == NULL) {
		printf("failed to open file.\n");
	}
	else {
		
		// test02:Put array testdata and print
		int numTestCase = getTestCaseNum(fp);
		
		setTestData(fp, numTestCase);

		int i, j;
		for (i=0; i<numTestCase; i++) {
			// test03:Exec proc.1:devide half until line data become multiple of 5.
			int counter_proc1 = countByProc1(i);
			
			// test04:Exec proc.2:if NumOfMultiple5 > numData/2, clear NumOfMultiple5.
			//                    otherwise devide half.
			int counter_proc2 = countByProc2(i);
			
			// test05:Exec proc.3:if NumOfMultiple5 >= numData/2, clear NumOfMultiple5.
			//                    otherwise devide half.
			int counter_proc3 = countByProc3(i);
			
			// test06:Exec proc.4:if there is multiple of 5, clear NumOfMultiple5.
			//                    otherwise devide half.
			int counter_proc4 = countByProc4(i);
			
			// which procedure is minimum
			int counter = counter_proc1;
			if (counter > counter_proc2) {
				counter = counter_proc2;
			}
			if (counter > counter_proc3) {
				counter = counter_proc3;
			}
			if (counter > counter_proc4) {
				counter = counter_proc4;
			}
			printf("%d\n", counter);
		}
	}
	
	fclose(fp);
	
	return 0;
}

int getTestCaseNum(FILE *fp)
{
	int result = 0;
	
	fscanf(fp, "%d\n", &result);
	
	return result;
}

void setTestData(FILE *fp, int numTestCase)
{
	int i;
	for (i=0; i<numTestCase; i++) {
		// get data num
		fscanf(fp, "%d\n", &numData[i]);
//		printf("%d\n", numData[i]);
		
		// set testdata
		char str[256] = {0};
		fgets(str, 256, fp);
//		printf("%s\n", str);
			
		char *pToken = strtok(str, " \n");
		int j = 0;
		data[i][j] = atoi(pToken);
		j++;
		while (pToken != NULL) {
			pToken = strtok(NULL, " \n");
			if (pToken != NULL) {
				data[i][j] = atoi(pToken);
				j++;
			}
			else {
				break;
			}
		}
	}
}

bool isMultipleOf5(int *line)
{
	bool result = true;
	
	int i;
	for (i=0; i<10; i++) {
		if (line[i] % 5 != 0) {
			result = false;
			break;
		}
	}
	
	return result;
}

void devide(int *line)
{
	int i;
	for (i=0; i<10; i++) {
		line[i] /= 2;
	}
}

// Return multiple of 5 number without 0
int getNumMultipleOf5(int *line, int num)
{
	int numMultipleOf5 = 0;
	int i;
	
	for (i=0; i<num; i++) {
		if (line[i] % 5 == 0) {	// whether multiple of 5
			if (line[i] != 0) {	// exclude 0
				numMultipleOf5++;
			}
		}
	}
	
	return numMultipleOf5;
}

void clearMultipleOf5(int *line)
{
	int i;
	for (i=0; i<10; i++) {
		if (line[i] % 5 == 0) {
			line[i] = 0;
		}
	}
}

int countByProc1(int row)
{
	int counter = 0;
	int line[10] = {0};
	int i;
	for (i=0; i<10; i++) {
		line[i] = data[row][i];
	}
			
	// test03:Exec proc.1:devide half until line data become multiple of 5.
	while (isMultipleOf5(line) == false) {
		devide(line);
		counter++;
	}
	counter++;
	
	return counter;
}

int countByProc2(int row)
{
	int counter = 0;
	int line[10] = {0};
	int i;
	for (i=0; i<10; i++) {
		line[i] = data[row][i];
	}
			
	// test04:Exec proc.2:if NumOfMultiple5 > numData/2, clear NumOfMultiple5.
	//                    otherwise devide half.
	while (isMultipleOf5(line) == false) {
		int numMultipleOf5 = 0;
		numMultipleOf5 = getNumMultipleOf5(line, numData[row]);
		
		if (numMultipleOf5 != 0) {
			if (numMultipleOf5 > (numData[row]/2)) {
				clearMultipleOf5(line);
			}
			else {
				devide(line);
			}
		}
		else {
			devide(line);
		}
		
		counter++;
	}
	counter++;
	
	return counter;
}

int countByProc3(int row)
{
	int counter = 0;
	int line[10] = {0};
	int i;
	for (i=0; i<10; i++) {
		line[i] = data[row][i];
	}
			
	// test05:Exec proc.3:if NumOfMultiple5 >= numData/2, clear NumOfMultiple5.
	//                    otherwise devide half.
	while (isMultipleOf5(line) == false) {
		int numMultipleOf5 = 0;
		numMultipleOf5 = getNumMultipleOf5(line, numData[row]);
		
		if (numMultipleOf5 != 0) {
			if (numMultipleOf5 >= (numData[row]/2)) {
				clearMultipleOf5(line);
			}
			else {
				devide(line);
			}
		}
		else {
			devide(line);
		}
		
		counter++;
	}
	counter++;
	
	return counter;
}

int countByProc4(int row)
{
	int counter = 0;
	int line[10] = {0};
	int i;
	for (i=0; i<10; i++) {
		line[i] = data[row][i];
	}
			
	// test06:Exec proc.4:if there is multiple of 5, clear NumOfMultiple5.
	//                    otherwise devide half.
	while (isMultipleOf5(line) == false) {
		int numMultipleOf5 = 0;
		numMultipleOf5 = getNumMultipleOf5(line, numData[row]);
		
		if (numMultipleOf5 != 0) {
			clearMultipleOf5(line);
		}
		else {
			devide(line);
		}
		
		counter++;
	}
	counter++;
	
	return counter;
}
