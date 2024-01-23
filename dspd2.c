#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    char name[20];
    char dept[3];
    int sem;
    char roll_no[10];
    int classes_conducted[5];
    int classes_attended[5];
    struct student *left;
    struct student *right;
    int height;
};

struct fee_status
{
    char roll_no[11];
    char fee_status[7];
    struct fee_status *left;
    struct fee_status *right;
    int height;
};

struct applicant_list
{
    char Name[20];
    char roll_no[11];
    char applicant_status[2];
    struct applicant_list *left;
    struct applicant_list *right;
    int height;
};

struct attendance_record
{
    char roll_no[11];
    char dept[3];
    int sem;
    int class_attended;
    int class_conducted;
    float attendance_percent;
    struct attendance_record *left;
    struct attendance_record *right;
    int height;
};

//////////////////////////////////////////////////////

int height(struct student *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

struct student* rightRotate(struct student *y)
{
    struct student *x = y->left;
    struct student *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    return x;
}
 
struct student* leftRotate(struct student *x)
{
    struct student *y = x->right;
    struct student *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left),  
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    return y;
}
 
int getBalance(struct student *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
struct student* newstudent(char n[],char d[],int s,char r[],int cc[],int ca[])
{
    int i;
    struct student *newstudent=(struct student*)malloc(sizeof(struct student));
    strcpy(newstudent->name,n);
    strcpy(newstudent->dept,d);
    newstudent->sem=s;
    strcpy(newstudent->roll_no,r);
    for(i==0;i<5;i++)
    {
        newstudent->classes_conducted[i]=cc[i];
    }
    for(i==0;i<5;i++)
    {
        newstudent->classes_attended[i]=ca[i];
    }
    newstudent->left=NULL;
    newstudent->right=NULL;
    newstudent->height=1;
    return newstudent;
}

struct student* insertStudent(struct student* student, char n[],char d[],int s,char r[],int cc[],int ca[])
{
    if (student == NULL)
        return(newstudent(n,d,s,r,cc,ca));
 
    if (s < student->sem)
        student->left  = insertStudent(student->left, n,d,s,r,cc,ca);
    else if (s > student->sem)
        student->right = insertStudent(student->right,n,d,s,r,cc,ca);
    else 
    {
        if(strcmp(d,student->dept)<0)
        {
            student->left  = insertStudent(student->left, n,d,s,r,cc,ca);
        }
        else if(strcmp(d,student->dept)>0)
        {
            student->right = insertStudent(student->right,n,d,s,r,cc,ca);
        }
        else
        {
            if(strcmp(r,student->roll_no)<0)
            {
               student->left = insertStudent(student->left, n,d,s,r,cc,ca);
            }
           else if(strcmp(r,student->roll_no)>0)
           {
               student->right = insertStudent(student->right,n,d,s,r,cc,ca);
           }
        }
    }
 
    student->height = 1 + max(height(student->left),
                        height(student->right));
 
    int balance = getBalance(student);
 
    if (balance > 1 && strcmp(r , student->left->roll_no)<0)
        return rightRotate(student);

    if (balance < -1 && strcmp(r , student->left->roll_no)>0)
        return leftRotate(student);
 
    if (balance > 1 && strcmp(r , student->left->roll_no)>0)
    {
        student->left =  leftRotate(student->left);
        return rightRotate(student);
    }
 
    if (balance < -1 && strcmp(r , student->left->roll_no)<0)
    {
        student->right = rightRotate(student->right);
        return leftRotate(student);
    }
 
    return student;
}

void Inorder(struct student *root)
{
    if(root!=NULL)
    {
        Inorder(root->left);
        printf("Name:%s\nDepartmenr:%s\nSemester:%d\nRoll no:%s\n",root->name,root->dept,root->sem,root->roll_no);
        Inorder(root->right);
    }
}

//////////////////////////////////////////////////////

int height1(struct fee_status* N)
{
    if(N==NULL)
     return 0;
    return N->height;
}

int max1(int a,int b)
{
    return (a>b)?a:b;
}

struct fee_status* newFeeStatus(char r[],char status[])
{
    struct fee_status* newNode=(struct fee_status*)malloc(sizeof(struct fee_status));
    strcpy(newNode->roll_no,r);
    strcpy(newNode->fee_status,status);
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->height=1;
    return newNode;
}

struct fee_status* rightRotate1(struct fee_status *y)
{
    struct fee_status *x = y->left;
    struct fee_status *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max1(height1(y->left),
                    height1(y->right)) + 1;
    x->height = max1(height1(x->left),
                    height1(x->right)) + 1;

    return x;
}
 
struct fee_status* leftRotate1(struct fee_status *x)
{
    struct fee_status *y = x->right;
    struct fee_status *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max1(height1(x->left),  
                    height1(x->right)) + 1;
    y->height = max1(height1(y->left),
                    height1(y->right)) + 1;
 
    return y;
}

int getBalance1(struct fee_status* N)
{
    if (N == NULL)
        return 0;
    return height1(N->left) - height1(N->right);
}

struct fee_status* insertFeeStatus(struct fee_status* fee,char r[],char status[])
{
    if (fee == NULL)
        return(newFeeStatus(r,status));

    if (strcmp(r,fee->roll_no)<0)
        fee->left  = insertFeeStatus(fee->left, r,status);
    else if (strcmp(r,fee->roll_no)>0)
        fee->right = insertFeeStatus(fee->right, r,status);
    else 
        return fee;
    
    fee->height = 1 + max1(height1(fee->left),
                           height1(fee->right));

    int balance = getBalance1(fee);

    if (balance > 1 && strcmp(r,fee->left->roll_no)<0)
        return rightRotate1(fee);

    if (balance < -1 && strcmp(r,fee->right->roll_no)>0)
        return leftRotate1(fee);

    if (balance > 1 && strcmp(r,fee->left->roll_no)>0)
    {
        fee->left =  leftRotate1(fee->left);
        return rightRotate1(fee);
    }

    if (balance < -1 && strcmp(r,fee->right->roll_no)<0)
    {
        fee->right = rightRotate1(fee->right);
        return leftRotate1(fee);
    }

    return fee;
}

void Inorder1(struct fee_status* root)
{
    if(root!=NULL)
    {
        Inorder1(root->left);
        printf("Roll no:%s\nFee_Status:%s\n",root->roll_no,root->fee_status);
        Inorder1(root->right);
    }
}

//////////////////////////////////////////////////////

int height2(struct applicant_list* N)
{
    if(N==NULL)
     return 0;
    return N->height;
}

int max2(int a,int b)
{
    return (a>b)?a:b;
}

struct applicant_list* newApplicant(char n[],char r[],char status[])
{
    struct applicant_list* newApplicant=(struct applicant_list*)malloc(sizeof(struct applicant_list));
    strcpy(newApplicant->Name,n);
    strcpy(newApplicant->roll_no,r);
    strcpy(newApplicant->applicant_status,status);
    newApplicant->left=NULL;
    newApplicant->right=NULL;
    newApplicant->height=1;
    return newApplicant;
}

struct applicant_list* rightRotate2(struct applicant_list *y)
{
    struct applicant_list *x = y->left;
    struct applicant_list *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max2(height2(y->left),
                    height2(y->right)) + 1;
    x->height = max2(height2(x->left),
                    height2(x->right)) + 1;

    return x;
}
 
struct applicant_list* leftRotate2(struct applicant_list *x)
{
    struct applicant_list *y = x->right;
    struct applicant_list *T2 = y->left;
 
    y->left= x;
    x->right = T2;
 
    x->height = max1(height2(x->left),  
                    height2(x->right)) + 1;
    y->height = max2(height2(y->left),
                    height2(y->right)) + 1;
 
    return y;
}

int getBalance2(struct applicant_list* N)
{
    if (N == NULL)
        return 0;
    return height2(N->left) - height2(N->right);
}

struct applicant_list* insertApplicant(struct applicant_list* appl,char n[],char r[],char status[])
{
    if (appl == NULL)
        return(newApplicant(n,r,status));
 
    if(strcmp(r,appl->roll_no)<0)
    {
        appl->left = insertApplicant(appl->left,n,r,status);
    }
    else if(strcmp(r,appl->roll_no)>0)
    {
        appl->right = insertApplicant(appl->right,n,r,status);
    }
    else 
        return appl;
 
    appl->height = 1 + max2(height2(appl->left),
                        height2(appl->right));
 
    int balance = getBalance2(appl);
 
    if (balance > 1 && strcmp(r , appl->left->roll_no)<0)
        return rightRotate2(appl);
 
    if (balance < -1 && strcmp(r , appl->left->roll_no)>0)
        return leftRotate2(appl);
 
    if (balance > 1 && strcmp(r , appl->left->roll_no)>0)
    {
        appl->left =  leftRotate2(appl->left);
        return rightRotate2(appl);
    }
 
    if (balance < -1 && strcmp(r , appl->left->roll_no)<0)
    {
        appl->right = rightRotate2(appl->right);
        return leftRotate2(appl);
    }
 
    return appl;
}

void Inorder2(struct applicant_list* root)
{
    if(root!=NULL)
    {
        Inorder2(root->left);
        printf("Name:%s\nRoll no:%s\nApplicant_Status:%s\n",root->Name,root->roll_no,root->applicant_status);
        Inorder2(root->right);
    }
}

//////////////////////////////////////////////////////

int height3(struct attendance_record* N)
{
    if(N==NULL)
     return 0;
    return N->height;
}

int max3(int a,int b)
{
    return (a>b)?a:b;
}

float attendance_percent(int ca[], int cc[])
{
    int max_conduct = 0; 
    int max_attend = 0;
    int i;
    for (i = 0; i < 5; i++)
    {
        if (cc[i] > max_conduct)
        {
            max_conduct = cc[i];
            max_attend = ca[i];
        }
        else if (cc[i] == max_conduct && ca[i] > max_attend) 
        {
            max_attend = ca[i];
        }
    }

    return ((float)max_attend / (float)max_conduct) * 100;
}

struct attendance_record* newAttend(char r[],int sem,char dept[],int ca[],int cc[])
{
    int i;
    struct attendance_record* newNode=(struct attendance_record*)malloc(sizeof(struct attendance_record));
    strcpy(newNode->roll_no,r);
    strcpy(newNode->dept,dept);
    newNode->sem=sem;
    int class_attended=0;
    int class_conducted=0;
    for(i=0;i<5;i++)
    {
        class_attended+=ca[i];
    }
    for(i=0;i<5;i++)
    {
        class_conducted+=cc[i];
    }
    newNode->class_attended=class_attended;
    newNode->class_conducted=class_conducted;
    newNode->attendance_percent=attendance_percent(ca,cc);
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->height=1;
    return newNode;
}

struct attendance_record* rightRotate3(struct attendance_record *y)
{
    struct attendance_record *x = y->left;
    struct attendance_record *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max3(height3(y->left),
                    height3(y->right)) + 1;
    x->height = max3(height3(x->left),
                    height3(x->right)) + 1;

    return x;
}
 
struct attendance_record* leftRotate3(struct attendance_record *x)
{
    struct attendance_record *y = x->right;
    struct attendance_record *T2 = y->left;
 
    y->left= x;
    x->right = T2;
 
    x->height = max3(height3(x->left),  
                    height3(x->right)) + 1;
    y->height = max3(height3(y->left),
                    height3(y->right)) + 1;
 
    return y;
}

int getBalance3(struct attendance_record* N)
{
    if (N == NULL)
        return 0;
    return height3(N->left) - height3(N->right);
}

struct attendance_record* insertAttend(struct attendance_record* root,char r[],char dept[],int sem,int ca[],int cc[])
{
    if (root == NULL)
        return(newAttend(r,sem,dept,ca,cc));
 
    if (sem < root->sem)
        root->left  = insertAttend(root->left,r,dept,sem,ca,cc);
    else if (sem > root->sem)
        root->right = insertAttend(root->right,r,dept,sem,ca,cc);
    else 
    {
        if(strcmp(dept,root->dept)<0)
        {
            root->left  = insertAttend(root->left,r,dept,sem,ca,cc );
        }
        else if(strcmp(dept,root->dept)>0)
        {
            root->right = insertAttend(root->right,r,dept,sem,ca,cc);
        }
        else
        {
            if(strcmp(r,root->roll_no)<0)
            {
               root->left = insertAttend(root->left, r,dept,sem,ca,cc);
            }
           else if(strcmp(r,root->roll_no)>0)
           {
               root->right = insertAttend(root->right,r,dept,sem,ca,cc);
           }
        }
    }
 
    root->height = 1 + max3(height3(root->left),
                        height3(root->right));
 
    int balance = getBalance3(root);
 
    if (balance > 1 && strcmp(r , root->left->roll_no)<0)
        return rightRotate3(root);
 
    if (balance < -1 && strcmp(r , root->left->roll_no)>0)
        return leftRotate3(root);
 
    if (balance > 1 && strcmp(r , root->left->roll_no)>0)
    {
        root->left =  leftRotate3(root->left);
        return rightRotate3(root);
    }
 
    if (balance < -1 && strcmp(r , root->left->roll_no)<0)
    {
        root->right = rightRotate3(root->right);
        return leftRotate3(root);
    }
 
    return root;
}

void Inorder3(struct attendance_record* root)
{
    if(root!=NULL)
    {
        Inorder3(root->left);
        printf("Roll no:%s\nDepartment:%s\nSem:%d\nAttendance_Percent:%f\n",root->roll_no,root->dept,root->sem,root->attendance_percent);
        Inorder3(root->right);
    }
}

///////////////////////////////////////////////////////

void SearchRollNo(struct student* root, char rollno[])
{
    if(root != NULL)
    {
        if(strcmp(rollno,root->roll_no) > 0)
            SearchRollNo(root->right, rollno);
        else if(strcmp(rollno,root->roll_no) < 0)
            SearchRollNo(root->left, rollno);
        else if(strcmp(rollno,root->roll_no) == 0)
        {
            printf("Roll No.: %s\nName: %s\nDepartment: %s\nSemester: %d\n", root->roll_no, root->name, root->dept, root->sem);
        }
    }
    else
        printf("\nRecord not found\n");
}

int SearchApplList(struct applicant_list* root,char rollno[])
{
    if(root != NULL)
    {
        if(strcmp(rollno,root->roll_no) > 0)
            SearchApplList(root->right, rollno);
        else if(strcmp(rollno,root->roll_no) < 0)
            SearchApplList(root->left, rollno);
        else if(strcmp(rollno,root->roll_no) == 0)
        {
            if(strcmp(root->applicant_status,"A")==0)
            {
                return 1;
            }
            else 
                 return 0;
        }
    }
}

int SearchFeeStatus(struct fee_status* root,char rollno[])
{
    if(root != NULL)
    {
        if(strcmp(rollno,root->roll_no) > 0)
            SearchFeeStatus(root->right, rollno);
        else if(strcmp(rollno,root->roll_no) < 0)
            SearchFeeStatus(root->left, rollno);
        else if(strcmp(rollno,root->roll_no) == 0)
        {
            if(strcmp(root->fee_status,"clear")==0)
            {
                return 1;
            }
            else 
                 return 0;
        }
    }
}

int SearchAttendanceList(struct attendance_record* root,char rollno[])
{
    if(root != NULL)
    {
        if(strcmp(rollno,root->roll_no) > 0)
            SearchAttendanceList(root->right, rollno);
        else if(strcmp(rollno,root->roll_no) < 0)
            SearchAttendanceList(root->left, rollno);
        else if(strcmp(rollno,root->roll_no) == 0)
        {
            if(root->attendance_percent>=75)
            {
                return 1;
            }
            else 
                 return 0;
        }
    }
}

///////////////////////////////////////////////////////

void NonApplicant(struct applicant_list* root,struct student* stu)
{
    if(stu!=NULL)
    {    
         NonApplicant(root,stu->left);
         if(SearchApplList(root,stu->roll_no)==0)
         {
             printf("Name:%s\nDepartmenr:%s\nSemester:%d\nRoll no:%s\n",stu->name,stu->dept,stu->sem,stu->roll_no);
         }
         NonApplicant(root,stu->right);
    }
}

///////////////////////////////////////////////////////

void Eligible(struct fee_status* fee,struct applicant_list* root,struct attendance_record* attend,struct student* stu)
{
    if(stu!=NULL)
    {    
        Eligible(fee,root,attend,stu->left);
        if(SearchApplList(root,stu->roll_no)==1 && SearchFeeStatus(fee,stu->roll_no)==1 && SearchAttendanceList(attend,stu->roll_no)==1)
        {
            printf("Name:%s\nDepartmenr:%s\nSemester:%d\nRoll no:%s\n",stu->name,stu->dept,stu->sem,stu->roll_no);
        }
        Eligible(fee,root,attend,stu->right);
    }
}

///////////////////////////////////////////////////////

void lowAttendance(struct attendance_record* root,struct student* stu)
{
    if(stu!=NULL)
    {
        lowAttendance(root,stu->left);
        if(SearchAttendanceList(root,stu->roll_no)==0)
        {
            printf("Name:%s\nDepartmenr:%s\nSemester:%d\nRoll no:%s\n",stu->name,stu->dept,stu->sem,stu->roll_no);
        }
        lowAttendance(root,stu->right);
    }
}

//////////////////////////////////////////////////////

struct student* minValueNode(struct student* node)
{
    struct student* current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

struct student* deleteNode(struct student* root, char roll_no[])
{
    if (root == NULL)
        return root;
 
    if (strcmp(roll_no, root->roll_no) < 0)
        root->left = deleteNode(root->left, roll_no);
 
    else if(strcmp(roll_no, root->roll_no) > 0)
        root->right = deleteNode(root->right, roll_no);
 
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct student *temp = root->left ? root->left : root->right;
 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
             *root = *temp;
            free(temp);
        }
        else
        {
            struct student* temp = minValueNode(root->right);
 
            strcpy(root->roll_no, temp->roll_no);
            strcpy(root->name, temp->name);
            strcpy(root->dept, temp->dept);
            root->sem = temp->sem;
            for(int i = 0; i < 5; i++)
            {
                root->classes_conducted[i] = temp->classes_conducted[i];
                root->classes_attended[i] = temp->classes_attended[i];
            }
 
            root->right = deleteNode(root->right, temp->roll_no);
        }
    }
 
    if (root == NULL)
      return root;
 
    root->height = 1 + max(height(root->left),height(root->right));
 
    int balance = getBalance(root);
 
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

///////////////////////////////////////////////////////

void feePending(struct fee_status* fee,struct attendance_record* attend,struct student* stu)
{
    if(stu!=NULL)
    {
        feePending(fee,attend,stu->left);
        if(SearchAttendanceList(attend,stu->roll_no)==0 && SearchFeeStatus(fee,stu->roll_no)==0)
        {
            printf("Name:%s\nDepartmenr:%s\nSemester:%d\nRoll no:%s\n",stu->name,stu->dept,stu->sem,stu->roll_no);
        }
        feePending(fee,attend,stu->right);
    }
}

///////////////////////////////////////////////////////

int deptCount[5]={0,0,0,0,0};

void defaulter(struct fee_status* fee,struct attendance_record* attend,struct student* stu)
{
   if(stu!=NULL)
    {
        defaulter(fee,attend,stu->left);
        if(SearchAttendanceList(attend,stu->roll_no)==0 || SearchFeeStatus(fee,stu->roll_no)==0)
        {
            printf("Name:%s\nDepartmenr:%s\nSemester:%d\nRoll no:%s\n",stu->name,stu->dept,stu->sem,stu->roll_no);
            if(strcmp(stu->dept,"CIV")==0)
            {
               deptCount[0]++;
            }
            if(strcmp(stu->dept,"CSE")==0)
            {
               deptCount[1]++;
            }
            if(strcmp(stu->dept,"ECE")==0)
            {
               deptCount[2]++;    
            }
            if(strcmp(stu->dept,"EEE")==0)
            {
                deptCount[3]++;
            }
            if(strcmp(stu->dept,"MEC")==0)
            {
                deptCount[4]++;
            }
        }
        defaulter(fee,attend,stu->right);
    }
}  

void maxDefaulter()
{
    int i,temp;
    int max=0;
    for(i=0;i<5;i++)
    {
        if(deptCount[i]>max)
        {
            max=deptCount[i];
            temp=i;
        }
    }
    if(temp==0)
    {
        printf("\nCIV dept has maximum defaulters\n");
    }
    if(temp==1)
    {
        printf("\nCSE dept has maximum defaulters\n");
    }
    if(temp==2)
    {
        printf("\nECE dept has maximum defaulters\n");
    }
    if(temp==3)
    {
        printf("\nEEE dept has maximum defaulters\n");
    }
    if(temp==4)
    {
        printf("\nMEC dept has maximum defaulters\n");
    }
}

//////////////////////////////////////////////////////

void rangeSearch(struct student *root, char enrol1[], char enrol2[])
{
    if(root!=NULL)
    {
        rangeSearch(root->left,enrol1,enrol2);
        if(strcmp(root->roll_no,enrol1)>=0 && strcmp(root->roll_no,enrol2)<0)
        printf("Name:%s\nRoll no:%s\n",root->name,root->roll_no);
        rangeSearch(root->right,enrol1,enrol2);
    }
}

//////////////////////////////////////////////////////

int main()
{
    struct student* root=NULL;
    // struct fee_status* root1=NULL;
    // struct applicant_list* root2=NULL;
    // struct attendance_record* root3=NULL;

    // int a[5]={50,50,50,50,50};
    // int b[5]={30,20,10,10,10};
    // root=insertStudent(root,"Riddhi","CSE",4,"BT21CSE001",a,b);
    // int c[5]={50,50,50,50,50};
    // int d[5]={50,40,40,40,40};
    // root=insertStudent(root,"Rashmi","CSE",4,"BT21CSE022",c,d);

    // root1=insertFeeStatus(root1,"BT21CSE022","clear");
    // root1=insertFeeStatus(root1,"BT21CSE001","pending");

    // root2=insertApplicant(root2,"Rashmi","BT21CSE022","NA");
    // root2=insertApplicant(root2,"Riddhi","BT21CSE001","A");

    // root3=insertAttend(root3,"BT21CSE001","CSE",4,b,a);
    // root3=insertAttend(root3,"BT21CSE022","CSE",4,d,c);
    
    FILE *fp;
    char filename[] = "student_records.txt";
    fp = fopen(filename, "r");
    
    if (fp == NULL) 
    {
        printf("Error opening file %s", filename);
        return 1;
    }
    
    int i,j;
    char name[50];
    char deptCode[3];
    char rollNumber[11];
    int yearSem, numClasses[5], numAttended[5];
    char fee_status[7],app_status[2];
    for(i=0;i<3;i++)
    {
    
        fscanf(fp,"%s",name);
        fscanf(fp,"%s",deptCode);
        fscanf(fp,"%d",&yearSem);
        fscanf(fp,"%s",rollNumber);
        for(j=0;j<5;j++)
        {
            fscanf(fp,"%d",&numClasses[j]);
            fscanf(fp,"%d",&numAttended[j]);
        }
        fscanf(fp,"%s",fee_status);
        fscanf(fp,"%s",app_status);

        root = insertStudent(root, name, deptCode, yearSem, rollNumber, numClasses, numAttended);
       
    }

    printf("\nStudent details:\n");
    Inorder(root);
    // printf("\nFee details:\n");
    // Inorder1(root1);
    // printf("\nApplicant details:\n");
    // Inorder2(root2);
    // printf("\nAttendance details:\n");
    // Inorder3(root3);

    // root=deleteNode(root,"BT21CSE022");
    // printf("\nStudent details:\n");
    // Inorder(root);

    // printf("\nRoll Numbers between BT21CSE001 and BT21CSE010:\n");
    // rangeSearch(root,"BT21CSE001","BT21CSE010");

    // SearchRollNo(root,"BT21CSE001");
    // printf("\nStudents who did not apply for the exam:\n");
    // NonApplicant(root2,root);
    // printf("\nStudent with attendance less than 75 percent:\n");
    // lowAttendance(root3,root);
    // printf("\nEligible students:\n");
    // Eligible(root1,root2,root3,root);
    // printf("\nStudents with attendance less than 75 percent and fee pending:\n");
    // feePending(root1,root3,root);
    // printf("\nDefaulter students:\n");
    // defaulter(root1,root3,root);
    // maxDefaulter();

    return 0;
}