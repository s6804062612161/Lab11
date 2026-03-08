#include <stdio.h>
#include <string.h>

#define NO_SCORE 5
#define NO_STUDENT 10

typedef struct {
    char name[16];
    char surname[20];
    int score[NO_SCORE];
    float total;
} Student;

void readStudentData(Student *);
void findTotalScore(Student *);
float findAverage(Student);
void findLessThanTen(Student);

void main() {
    Student std[NO_STUDENT];
    Student temp; 
    float avg;
    int i;
    FILE *fptr;

    for(i = 0; i < NO_STUDENT; i++) {
        printf("\nStudent No.%d\n", i + 1);
        readStudentData(&std[i]);
    }
    
    fptr = fopen(".\\lab11\\no2\\std10.dat", "wb");
    if (fptr == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }
    fwrite(std, sizeof(Student), NO_STUDENT, fptr);
    fclose(fptr);

    printf("\n--- Data saved to file successfully ---\n");
    fptr = fopen(".\\lab11\\no2\\std10.dat", "rb"); 
    if (fptr == NULL) {
        printf("Error: Cannot open file for reading!\n");
        return;
    }

    printf("\n--- Reading data and processing ---\n");
    for(i = 0; i < NO_STUDENT; i++) {
        fread(&temp, sizeof(Student), 1, fptr);
        findTotalScore(&temp);
        avg = findAverage(temp);
        printf("\n\tAverage score is %.2f", avg);
        findLessThanTen(temp);
        printf("\n------------------------------\n");
    }
    
    fclose(fptr);
}

void readStudentData(Student *pStd) {
    int i;
    printf("Enter student data\n");
    printf("\tName : ");
    scanf("%s", pStd->name); 
    printf("\tSurname : ");
    scanf("%s", pStd->surname);
    for (i = 0; i < NO_SCORE; i++) {
        printf("\tScore %d : ", i + 1);
        scanf("%d", &pStd->score[i]);
    }
}

void findTotalScore(Student *pStd) {
    int i;
    printf("\nPrint student data");
    printf("\n\t%s %s got score: ", pStd->name, pStd->surname);
    pStd->total = 0.0;
    for (i = 0; i < NO_SCORE; i++) {
        printf("%6d", pStd->score[i]);
        pStd->total += pStd->score[i];
    }
    printf("\n\tTotal score is %.2f", pStd->total);
}

float findAverage(Student s) {
    return (s.total / NO_SCORE);
}

void findLessThanTen(Student s) {
    int i, count = 0;
    printf("\n\tScore less than 10:");
    for (i = 0; i < NO_SCORE; i++) {
        if (s.score[i] < 10) {
            printf("\n\t  - Test no.%d: %d", i + 1, s.score[i]);
            count++;
        }
    }
    if (count == 0)
        printf(" None");
}
