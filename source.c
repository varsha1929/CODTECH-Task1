//It is a program to add,delete,modify and show student info whose data is being recorded in
// a file. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of student details
struct Student{
    int roll;
    char name[50];
    float cgpa;
};

//function to check if a roll no. is unique or not
int isNotUnique(int r)
{
    FILE *ptr;
    ptr = fopen("student.txt","r");
    if(ptr == NULL) return 0;
    char name[50];
    int roll;
    float cgpa;
    while(fscanf(ptr,"%[^,],%d,%f\n",name,&roll,&cgpa)==3)
    {
        if(r == roll)
        {
            fclose(ptr);
             return 1;
        } 
    }
    fclose(ptr);
    return 0;
}

//function to add new student
void add_student()
{
    struct Student detail;
    printf("Enter Name : ");
    fflush(stdin);
    fgets(detail.name,50,stdin);
    detail.name[strcspn(detail.name, "\n")] = '\0';
    get_roll:
    printf("Enter Roll No. : ");
    scanf("%d",&detail.roll);
    if(isNotUnique(detail.roll) || detail.roll <= 0 || detail.roll > 1000){
        printf("Roll No. Must be between 1-1000 and should be unique.\n");
        goto get_roll;
    }
    get_cgpa:
    printf("Enter CGPA : ");
    scanf("%f",&detail.cgpa);   
    if(!(detail.cgpa >= 0 && detail.cgpa <= 10)) 
    {
        printf("CGPA should be between 0 and 10.\n");
        goto get_cgpa;
    }
     FILE *fileptr;
    fileptr = fopen("student.txt","a");
    if(fileptr != NULL)
    {
        fprintf(fileptr,"%s,%d,%.2f\n",detail.name,detail.roll,detail.cgpa);
        printf("Student Added Successfully\n\n");
    }
    else{
        printf("Error Opening File!\n");
        return;
    }
    
    fclose(fileptr);
    system("pause");
}

//function to search for a student by using roll no.
void search()
{
    int r;
    char name[50];
    int roll;
    float cgpa;
    int found = 0;
    printf("Enter Roll No. : ");
    scanf("%d",&r);
    FILE *fptr;
    fptr = fopen("student.txt","r");

    while(fscanf(fptr,"%[^,],%d,%f\n",name,&roll,&cgpa)==3)
    {
        if(roll == r)
        {
            found = 1;
            printf("%s\t%d\t%.2f\n",name,roll,cgpa);
        }
    }
    fclose(fptr);
    if(!found) printf("Student with roll np %d not found.\n",r);
    system("pause");
}

//function to display all roll student record
void display_all()
{
    FILE *fptr;
    int flag = 1;
    char name[50];
    int roll;
    float cgpa;
    fptr = fopen("student.txt","r");
    printf("%-20s%-10s%-10s\n","Name","Roll No","CGPA");
    printf("------------------------------------------\n");
    if(fptr != NULL)
    {
        while(fscanf(fptr,"%[^,],%d,%f\n",name,&roll,&cgpa)==3)
        {
            printf("%-20s%-10d%-10.2f\n",name,roll,cgpa);
            flag = 0;
        }
    }
    else printf("Error Opening File!\n");

    printf("\n");
    if(flag) printf("\t****No Record Found*****\n\n");
    fclose(fptr);
    system("pause");
}

// function to modify an existing student data
void modify()
{
  int r;
  char name[50];
  int roll;
  float cgpa;
  int found = 0;
  printf("Enter Roll No. to modify : ");
  scanf("%d",&r);
  
  FILE *fptr;
  FILE *temp;
  fptr = fopen("student.txt","r");
  temp = fopen("temp.txt","a");

  while(fscanf(fptr,"%[^,],%d,%f\n",name,&roll,&cgpa)==3)
  {
    if(r == roll)
    {
        found = 1;
        printf("\nRecord Found : \n");
        printf("Name : %s\nRoll No : %d\nCGPA : %.2f",name,roll,cgpa);
        printf("\n\nEnter New Details : ");
        struct Student new_detail;
        getchar();
        printf("\nEnter New Name : ");
        fgets(new_detail.name,sizeof(new_detail.name),stdin);
        new_detail.name[strcspn(new_detail.name,"\n")] = '\0';
        printf("Enter New Roll No. : ");
        scanf("%d",&new_detail.roll);
        printf("Enter New CGPA : ");
        scanf("%f",&new_detail.cgpa);

        fprintf(temp,"%s,%d,%.2f\n",new_detail.name,new_detail.roll,new_detail.cgpa);
    }
    else{
        fprintf(temp,"%s,%d,%f",name,roll,cgpa);
    }
  }
  fclose(fptr);
  fclose(temp);

  if(found)
  {
    remove("student.txt");
    rename("temp.txt","student.txt");
    printf("\nStudent Record Updated Successfully.\n");
  }
  else{
    remove("temp.txt");
    printf("\nStudent with Roll No %d Not Found.\n",r);
  }
  system("pause");
}

//function to delete any student's record by their roll no.
void del()
{
    int r;
    int roll;
    char name[50];
    float cgpa;
    int found = 0;
    printf("Enter Roll No to be Deleted : ");
    scanf("%d",&r);
    FILE *fptr;
    FILE *temp;
    fptr = fopen("student.txt","r");
    temp = fopen("temp.txt","a");
    if(fptr != NULL)
    {
        while(fscanf(fptr,"%[^,],%d,%f\n",name,&roll,&cgpa)==3)
        {
            if(r != roll)
            {
                fprintf(temp,"%s,%d,%f\n",name,roll,cgpa);
            }
            else found = 1;
        }
    }
    else{
        printf("Error Opening file.\n");
    }
    fclose(fptr);
    fclose(temp);

    if(found)
    {
        remove("student.txt");
        rename("temp.txt","student.txt");
        printf("\nStudent Deletet Successfully.\n");
    }
    else{
        remove("temp.txt");
        printf("\nStudent with roll no %d not found.\n",r);
    }
    system("pause");
}

//welcome screen
void display_screen()
{
    int choice = 0;
    int ex = 0;
    while(!ex)
    {
    system("cls");
    printf("\n\t\tStudent Info System\n");
    printf("#######################################################\n\n");
    printf("[1]Add Student.\n");
    printf("[2]Search Student.\n");
    printf("[3]Modify Student.\n");
    printf("[4]Display All.\n");
    printf("[5]Delete Student.\n");
    printf("[0]Exit.\n");
    printf("\nEnter Your Choice : ");
    scanf("%d",&choice);
    getchar();
     switch (choice)
    {
    case 1 :
    system("cls");
    printf("\n==========Add Student===========\n\n");
    add_student();
    break;
    case 2: 
    system("cls");
    printf("\n==========Search Student===========\n\n");
    search();
    break;
    case 3: 
    system("cls");
    printf("\n==========Modify Student===========\n\n");
    modify();
    break;
    case 4:
    system("cls");
    printf("\n==========Display All Student===========\n\n");
    display_all();
    break;
    case 5:
    system("cls");
    printf("\n==========Delete Student===========\n\n");
    del();
    break;    
    case 0:
    ex = 1;
    printf("\nExiting...\n");
    break;    
    default:
        break;
    }
  }
}
    
//main function
int main()
{
    display_screen();
    return 0;
}