#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define ESC 27
#define LEFT 75
#define RIGHT 77

struct book
{
    int copies;
    int available_copies;
    char title[1000];
    char author[1000];
    char category[1000];
    char publisher[1000];
    char isbn[1000];
    char date_of_publication[1000];
};

struct member{
    int id;
    char last_name[100];
    char first_name[100];
    char address[1000];
    char street[1000];
    char city[100];
    char phone_number[1000];
    int age;
    char email[1000];
};

struct borrowing
{
    char isbn[1000];
    int user_id;
    char issued_date[1000];
    char due_date[1000];
    char date_returned[1000];
};
struct member members[1000]={'\0'};
struct book books[1000]={'\0'};
struct borrowing borrowed[1000]={'\0'};

FILE *pointer1;
FILE *pointer2;
FILE *pointer3;

SYSTEMTIME str_t;
char key;

int validate_numbers(char step_var[])
{
    int i=0;
    for(i=0;step_var[i]!=NULL;i++)
    {
        if(isdigit(step_var[i])==0)
        {
            return -1;
        }
    }
    return 0;
}

int validate_id(int id,int j)
{
    int i;
    for(i=0;i<j;i++)
    {
        if(id==members[i].id)
        {
            return 0;
        }
    }
    return -1;
}

int validate_string(char arr[])
{
    int i;
    for(i=0;arr[i]!=NULL;i++);
    int arr_len=i;
    if(arr[0]!=NULL)
    {
    for(i=0;arr[i]!=NULL && arr[i]!=',';i++);
    if (i==arr_len)
        {
            return 0;
        }else
        {
            printf("\nINVALID FORMAT\n");
            return -1;
        }
    }else if(arr[0]==NULL)
    {
        printf("\n                         Warning:EMPTY STRING\n\n\n\n");
        return -1;
    }
}

int search_books_isbn(char isbn_search[],int n)
{
    int i,j;
    for(i=0;isbn_search[i]!='\0';i++);
    int word_len=i;
    int isbn_length;
    int z=0;
    for(j=0;j<n;j++)
        {
            for(i=0;books[j].isbn[i]!='\0';i++);
            isbn_length=i;
        for(i=0;books[j].isbn[i]==isbn_search[i];i++)
        {
            if (i==word_len-1 && i==isbn_length-1)
            {
                z=-1;
                return j;
                break;
            }
        }
        }
        if (z==0)
        {
            return -1;
        }
}

int validate_isbn(char arr[])
{
    int counter=0;
    int i,k;
    for(k=0;arr[k]!=NULL;k++);
    if(k<13)
    {
        return -1;
    }
    if (arr[0]=='-'|| arr[k-1]=='-')
    {
        printf("Invalid Format\n\n");
        return -1;
    }else
    {
        for(i=0;arr[i]!=NULL;i++)
        {
            if(arr[i]=='-'&& arr[i+1]=='-')
            {
                printf("Invalid Format\n\n");
                return -1;

            }
            else if (isdigit(arr[i])!=1 && arr[i]!='-')
            {
                printf("Invalid Format\n\n");
                return -1;

            }else if (isdigit(arr[i])==1)
            {
                counter++;
            }
        }
    }
        if(counter!=13 )
        {
            printf("ISBN must have 13-digits\n");
            return -1;
        }else
        {
            return 0;
        }
}

int validate_date(char arr[])
{
    int flag_year=0;
    int flag_day=0;
    int flag_month=0;
    int flag=0;
    int i;
    char test[100]={'\0'};
    strcpy(test,arr);
    for(i=0;test[i]!=NULL;i++);
    if(!((test[2]=='/'&& test[5]=='/')||(test[1]=='/'&&test[4]=='/')||(test[1]=='/'&& test[3]=='/')||(test[2]=='/'&&test[4]=='/')))
    {
        flag=-1;
    }
    int day=atoi(strtok(test,"/"));
    int month=atoi(strtok(NULL,"/"));
    int year=atoi(strtok(NULL,"/"));
    if(!(year<=2200 && year>=1900))
    {
        printf("Invalid year\n");
        flag_year=-1;
    }else if(!(month<=12 &&month>=1))
    {
        flag_month=-1;
    }else if(!(day<=30 &&day>=1))
    {
        flag_month=-1;
    }
    if(month==2 && day>=30)
        {
            flag_day=-1;
        }
    if(flag==-1 || flag_day==-1 || flag_month==-1 || flag_year==-1)
    {
        return -1;
    }else
    {
        return 0;
    }
}

int validate_age(int x)
{
    if(x<=100 && x>=10)
        {
            return 0;
        }else
        {
            return -1;
        }
}


void search_books_title(char title_search[],int i)
{
    int n=i;
    int j;
    for(i=0;title_search[i]!=NULL;i++);
    int word_len;
    word_len=i;
    int title_length;
    int z=0,k;
    for(j=0;j<n;j++)
    {
        for(i=0;books[j].title[i]!=NULL;i++);
        title_length=i;
        for(k=0;k<title_length;k++)
        {
            for(i=0;books[j].title[k]==tolower(title_search[i]) || books[j].title[k]==toupper(title_search[i]);i++)
            {
                if (i==word_len-1 && k!=title_length-1)
                {
                    z=-1;
                    printf("\nDo you mean?\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n-------------------------------------------------------------------------------",books[j].title,books[j].author,books[j].publisher,books[j].date_of_publication,books[j].isbn,books[j].copies,books[j].available_copies,books[j].category);
                    k=title_length+1;
                    break;
                }else if (i==word_len-1 && k==title_length-1)
                {
                    z=-1;
                    printf("\nMatch Found:\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n-------------------------------------------------------------------------------",books[j].title,books[j].author,books[j].publisher,books[j].date_of_publication,books[j].isbn,books[j].copies,books[j].available_copies,books[j].category);
                    k=title_length+1;
                    break;
                }else
                {
                    k++;
                }
            }
        }
    }
        if (z==0)
        {
            printf("\nNO MATCH FOUND\n");
        }
}

int validate_phonenumber(char step_var[])
{
    int k,counter=0;
    for(k=0;step_var[k]!=NULL;k++)
    {
        if(isdigit(step_var[k])==1)
        {
            counter++;
            continue;
        }else if(isdigit(step_var[k])!=1 && step_var[k]!='-' && step_var[k]!=' ')
        {
            return -1;
        }else if(step_var[k]=='-' && step_var[k+1]=='-')
        {
            return -1;
        }
    }
    if(!(counter==7 || counter ==11))
    {
        return -1;
    }else if(step_var[0]=='-' || step_var[0]==' ' || step_var[k-1]=='-')
    {
        return -1;
    }else
    {
        return 0;
    }
}

void search_books_author(char author_search[],int n)
{
    int i,j;
    for(i=0;author_search[i]!='\0';i++);
    int word_len=i;
    int author_length;
    int z=0,k;
    for(j=0;j<n;j++)
        {
            for(i=0;books[j].author[i]!='\0';i++);
            author_length=i;
            for(k=0;k<author_length;k++)
            {
                for(i=0;books[j].author[k]==tolower(author_search[i]) ||books[j].author[k]==toupper(author_search[i]) ;i++)
                {
                    if (i==word_len-1 && i!=author_length-1)
                    {
                        z=-1;
                        printf("\nDo you mean?\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n-------------------------------------------------------------------------------",books[j].title,books[j].author,books[j].publisher,books[j].date_of_publication,books[j].isbn,books[j].copies,books[j].available_copies,books[j].category);
                        k=author_length+1;
                        break;
                    }else if (i==word_len-1 && i==author_length-1)
                    {
                        z=-1;
                        printf("\nMatch Found:\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n-------------------------------------------------------------------------------",books[j].title,books[j].author,books[j].publisher,books[j].date_of_publication,books[j].isbn,books[j].copies,books[j].available_copies,books[j].category);
                        k=author_length+1;
                        break;
                    }else
                    {
                        k++;
                    }
                }
        }
        }
        if (z==0)
        {
            printf("NO MATCH FOUND");
        }
}

void search_books_category(char category_search[],int n)
{
    int i,j;
    for(i=0;category_search[i]!='\0';i++);
    int word_len=i;
    int category_length;
    int z=0,k;
    for(j=0;j<n;j++)
        {
            for(i=0;books[j].category[i]!='\0';i++);
            category_length=i;
            for(k=0;k<category_length;k++)
            {
                for(i=0;books[j].category[k]==tolower(category_search[i]) ||books[j].category[k]==toupper(category_search[i]) ;i++)
                {
                    if (i==word_len-1 && i!=category_length-1)
                    {
                        z=-1;
                        printf("\nDo you mean?\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n-------------------------------------------------------------------------------\n",books[j].title,books[j].author,books[j].publisher,books[j].date_of_publication,books[j].isbn,books[j].copies,books[j].available_copies,books[j].category);
                        k=category_length+1;
                        break;
                    }else if (i==word_len-1 && i==category_length-1)
                    {
                        z=-1;
                        printf("\nMatch Found:\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n-------------------------------------------------------------------------------\n",books[j].title,books[j].author,books[j].publisher,books[j].date_of_publication,books[j].isbn,books[j].copies,books[j].available_copies,books[j].category);
                        k=category_length+1;
                        break;
                    }else
                    {
                        k++;
                    }
                }
            }
        }
        if (z==0)
        {
            printf("NO MATCH FOUND");
        }
}
int validate_email(char arr[])
{
    int i,at=0,dot=0;
    for(i=0;arr[i]!='\0';i++);
    int len=i;
    for(i=0;arr[i]!='\0';i++)
    {
        if(arr[i]=='@')
        {
            at+=1;
        }else if(arr[i]==' ')
        {
            printf("Invalid email address");
            return -1;
        }else if(arr[i]=='.')
        {
            dot+=1;
        }else if(arr[i]=='@' && arr[i+1]=='.' || arr[i]=='.' && arr[i+1]=='.')
        {
            return -1;
        }

    }
    if(arr[0]==NULL||arr[0]=='@' || arr[0]=='.' || (arr[len-4]!='.' && arr[len-3]!='.') || at==0 || at>1 || dot==0)
    {
        printf("Invalid email adress\n");
        return -1;
    }else
    {
        return 0;
    }
}

int insert_books(int i)
{
   char ans[3]={'\0'};
   char book_publisher[1000]={'\0'};
   char book_title[1000]={'\0'};
   char book_author[1000]={'\0'};
   char book_isbn[1000]={'\0'};
   char book_publishing_date[1000]={'\0'};
   char book_category[1000]={'\0'};
   int valid,flag=0;
   char step_var[100]={'\0'};
   do{
    do{printf("Book Details\n------------\nTitle:");
    gets(book_title);
    valid=validate_string(book_title);
    }while(valid==-1);
    do{printf("Author:");
    gets(book_author);
    valid=validate_string(book_author);
    }while(valid==-1);
    do{printf("Publisher:");
    gets(book_publisher);
    valid=validate_string(book_publisher);
    }while(valid==-1);
    do{printf("ISBN:");
    gets(book_isbn);
    if(search_books_isbn(book_isbn,i)!=-1)
    {
        printf("This book aleady exists\n");
        flag=-1;
    }
    valid=validate_isbn(book_isbn);
    }while(valid==-1 || flag==-1);
    do{printf("Date of publication(dd/mm/yyyy):");
    gets(book_publishing_date);
    valid=validate_date(book_publishing_date);
    }while(valid==-1 ||validate_string(book_publishing_date)==-1);
    do{printf("Number of copies:");
    gets(step_var);
    }while(validate_string(step_var)==-1 || validate_numbers(step_var)==-1);
    do{printf("Category:");
    gets(book_category);
    valid=validate_string(book_category);
    }while(valid==-1);
    printf("Save changes?\n[Y/N]\n");
    gets(ans);
    if(ans[0]=='y' ||ans[0]=='Y')
    {
        books[i].copies=atoi(step_var);
        books[i].available_copies=books[i].copies;
        strcpy(books[i].category,book_category);
        strcpy(books[i].author,book_author);
        strcpy(books[i].isbn,book_isbn);
        strcpy(books[i].date_of_publication,book_publishing_date);
        strcpy(books[i].title,book_title);
        strcpy(books[i].publisher,book_publisher);
        i++;
        update_book_info(i);
        system("cls");
    }else
    {
        printf("            Book is not saved\n\n");
    }
    printf("\n\n                Insert another book?\n\n                [Y/N]:");
    gets(ans);
    }while(ans[0]=='y'||ans[0]=='Y');
    return i;

}

void update_members_info(int n)
{
    int i;
    pointer2=fopen("register.txt","w");
    for(i=0;i<n;i++)
    {
        fprintf(pointer2,"%d",members[i].id);
        fprintf(pointer2,",%s",members[i].first_name);
        fprintf(pointer2,"-%s",members[i].last_name);
        fprintf(pointer2,",%s",members[i].address);
        fprintf(pointer2,",%s",members[i].street);
        fprintf(pointer2,",%s",members[i].city);
        fprintf(pointer2,",%s",members[i].phone_number);
        fprintf(pointer2,",%d",members[i].age);
        if(strstr(members[i].email, "\n"))
            fprintf(pointer2,",%s",members[i].email);
        else
            fprintf(pointer2,",%s\n",members[i].email);
    }
    fclose(pointer2);

}
int registeration(int j)
{
    int valid;
    char step_var[100]={'\0'};
    char ans[3]={'\0'};
    char arr[100]={'\0'};
    char first_name[100]={'\0'};
    char last_name[100]={'\0'};
    char address[100]={'\0'};
    char city[100]={'\0'};
    char street[100]={'\0'};
    char phone[100]={'\0'};
    char email[100]={'\0'};
    int id;
    int age;
    do{
    id=j+1;
    do{printf("First name:");
    gets(first_name);
    valid=validate_string(first_name);
    }while(valid==-1);
    do{printf("Last name:");
    gets(last_name);
    valid=validate_string(last_name);
    }while(valid==-1);
    do{printf("Address:");
    gets(address);
    valid=validate_string(address);
    }while(valid==-1);
    do{printf("Street:");
    gets(street);
    valid=validate_string(street);
    }while(valid==-1);
    do{printf("City:");
    gets(city);
    valid=validate_string(city);
    }while(valid==-1);
    do{printf("Phone number(Home/mobile):");
    gets(step_var);
    }while( validate_phonenumber(step_var)==-1 ||validate_string(step_var)==-1);
    strcpy(phone,step_var);
    do{printf("Age:");
    gets(step_var);
    age=atoi(step_var);
    }while(validate_age(age)==-1||validate_numbers(step_var)==-1 ||validate_string(step_var)==-1);
    do{printf("E-mail:");
    gets(email);
    valid=validate_email(email);
    }while(valid==-1);
    printf("Save changes?\n[Y/N]\n");
    gets(ans);
    if(ans[0]=='Y' || ans[0]=='y')
    {
        members[j].age=age;
        strcpy(members[j].address,address);
        strcpy(members[j].city,city);
        strcpy(members[j].street,street);
        strcpy(members[j].email,email);
        strcpy(members[j].first_name,first_name);
        strcpy(members[j].last_name,last_name);
        strcpy(members[j].phone_number,phone);
        members[j].id=id;
        j++;
        update_members_info(j);
        printf("Member saved");
        system("cls");

    }else
    {
        printf("Member not saved");
    }
    printf("\n\n                Register another member?\n\n                [Y/N]:");
    gets(ans);
    }while(ans[0]=='Y' || ans[0]=='y');
    return j;
}

void update_book_info(int n)
{
    int i;
    pointer1=fopen("Mylibrary.txt","w");
    for(i=0;i<n;i++)
    {
        fprintf(pointer1,"%s",books[i].title);
        fprintf(pointer1,",%s",books[i].author);
        fprintf(pointer1,",%s",books[i].publisher);
        fprintf(pointer1,",%s",books[i].isbn);
        fprintf(pointer1,",%s",books[i].date_of_publication);
        fprintf(pointer1,",%d",books[i].copies);
        fprintf(pointer1,",%d",books[i].available_copies);
        if(strstr(books[i].category, "\n"))
            fprintf(pointer1,",%s",books[i].category);
        else
            fprintf(pointer1,",%s\n",books[i].category);
    }
    fclose(pointer1);

}

int search_borrow_id(int id,int k,int n)
{
    int i,x=0,book_entry;
    for(i=0;i<k;i++)
    {
        if(borrowed[i].user_id==id && (strcmp(borrowed[i].date_returned,"Not returned\n")==0 || strcmp(borrowed[i].date_returned,"Not returned")==0 ))
        {
                x=-1;
                book_entry=search_books_isbn(borrowed[i].isbn,n);
                break;
        }
    }
    return x;
}

void update_borrow(int n)
{
    int i;
    pointer3=fopen("borrow.txt","w");
    for(i=0;i<n;i++)
    {
        fprintf(pointer3,"%s",borrowed[i].isbn);
        fprintf(pointer3,",%d",borrowed[i].user_id);
        fprintf(pointer3,",%s",borrowed[i].issued_date);
        fprintf(pointer3,",%s",borrowed[i].due_date);
        if(strstr(borrowed[i].date_returned, "\n")){
            fprintf(pointer3,",%s",borrowed[i].date_returned);
        }else{
            fprintf(pointer3,",%s\n",borrowed[i].date_returned);
        }
    }
    fclose(pointer3);

}
int borrow(int n,int j,int b)
{
    int i,id;
    int valid;
    char step_var[10]={'\0'};
    char arr[20]={'\0'};
    char ans[3]={'\0'};
    char due[100]={'\0'};
    do{
        do{printf("Enter Book ISBN:");
        gets(arr);
        valid=validate_isbn(arr);
        }while(valid==-1 || search_books_isbn(arr,n)==-1 ||validate_string(arr)==-1);
        i=search_books_isbn(arr,n);
        do{printf("Enter User ID:");
        gets(step_var);
        id=atoi(step_var);
        }while(validate_numbers(step_var)==-1 || validate_id(id,b)==-1 ||validate_string(step_var)==-1);
        int x=0,k;
        for(k=0;k<j;k++)
        {
            if((strcmp(borrowed[k].date_returned,"Not returned")==0 || strcmp(borrowed[k].date_returned,"Not returned\n")==0 )&&(borrowed[k].user_id==id ))
            {

                    x++;
            }
        }
        if (x>=3)
        {
            printf("\nUser already has 3 Books!\n");
        }else if (books[i].available_copies!=0)
        {
            do{printf("Enter Due date:");
            gets(due);
            }while(validate_date(due)==-1 || validate_string(due)==-1);
            printf("Save changes?[Y/N]");
            gets(ans);
            if (ans[0]=='Y' ||ans[0]=='y')
            {
                books[i].available_copies-=1;
                update_book_info(n);
                strcpy(borrowed[j].date_returned,"Not returned");
                strcpy(borrowed[j].isbn,arr);
                borrowed[j].user_id=id;
                sprintf(borrowed[j].issued_date,"%d/%d/%d",str_t.wDay,str_t.wMonth,str_t.wYear);
                strcpy(borrowed[j].due_date,due);
                printf("%s",borrowed[j].due_date);
                j++;
                update_borrow(j);
                printf("\n            Saved!");
                system("cls");
            }else if(ans[0]!='Y' &&ans[0]!='y')
            {
            printf("\nNo changes saved!\n");
            }
        }else
        {
            printf("\nBook is not available");
        }
    printf("\n\n                Borrow another book?\n\n                [Y/N]:");
    gets(ans);
    }while(ans[0]=='Y' ||ans[0]=='y');
    return j;
}

void add_copies(int i)
{
    static n=0;
    int book_entry;
    int copies_added,j;
    char step_var[10]={'\0'};
    char isbn[100]={'\0'};
    do{printf("\nEnter Book ISBN:");
    gets(isbn);
    book_entry=search_books_isbn(isbn,i);
    }while(validate_isbn(isbn)==-1 || book_entry==-1 ||validate_string(isbn)==-1);
    do{printf("\nHow many copies do you want to add?");
    gets(step_var);
    }while(validate_numbers(step_var)==-1 || validate_string(step_var)==-1);
    copies_added=atoi(step_var);
    printf("%d",copies_added);
    j=book_entry;
    do{printf("\nPress ENTER to save changes     Press ESC to Exit");
    key=getch();
    if(key=='\n')
    {
        books[j].copies=books[j].copies+copies_added;
        update_book_info(i);
        printf("\nChanges saved\n\n");
        printf("%s...%s\n\nNumber of copies:%d",books[book_entry].title,books[book_entry].isbn,books[book_entry].copies);

    }else if(key==ESC)
    {
        printf("\nNo changes saved!");
    }
    }while(key!=ESC && key!='\n');

}

int delete_book(int n)
{
    char isbn[100]={'\0'};
    int book_entry;
    do{printf("Enter Book ISBN:");
    gets(isbn);
    book_entry=search_books_isbn(isbn,n);
    }while(validate_isbn(isbn)==-1 || book_entry==-1 || validate_string(isbn)==-1);
    int i;
    for(i=book_entry;i<n-1;i++)
    {
        strcpy(books[i].author,books[i+1].author);
        strcpy(books[i].title,books[i+1].title);
        strcpy(books[i].category,books[i+1].category);
        strcpy(books[i].date_of_publication,books[i+1].date_of_publication);
        books[i].available_copies=books[i+1].available_copies;
        books[i].copies=books[i+1].copies;
        strcpy(books[i].publisher,books[i+1].publisher);
        strcpy(books[i].isbn,books[i+1].isbn);
    }
    pointer1=fopen("Mylibrary.txt","w");
    for(i=0;i<n-1;i++)
    {
        fprintf(pointer1,"%s",books[i].title);
        fprintf(pointer1,",%s",books[i].author);
        fprintf(pointer1,",%s",books[i].publisher);
        fprintf(pointer1,",%s",books[i].isbn);
        fprintf(pointer1,",%s",books[i].date_of_publication);
        fprintf(pointer1,",%d",books[i].copies);
        fprintf(pointer1,",%d",books[i].available_copies);
        if(strstr(books[i].category, "\n"))
            fprintf(pointer1,",%s",books[i].category);
        else
            fprintf(pointer1,",%s\n",books[i].category);
    }
    fclose(pointer1);
    printf("\nBook is deleted successfully");
    system("cls");
    return n-1;
}

int search_borrowed_isbn(char isbn_search[],int k)
{
    int i,j;
    for(i=0;isbn_search[i]!='\0';i++);
    int word_len=i;
    int isbn_length;
    int z=0;
    for(j=0;j<k;j++)
         {
            for(i=0;borrowed[j].isbn[i]!='\0';i++);
            isbn_length=i;
        for(i=0;borrowed[j].isbn[i]==isbn_search[i];i++)
            {
                if (i==word_len-1 && i==isbn_length-1 && (strcmp(borrowed[j].date_returned,"Not returned\n")==0 || strcmp(borrowed[j].date_returned,"Not returned")==0) )
                {
                        z=-1;
                        printf("Match Found\n\n");
                        return j;

                }
            }
         }
    if (z==0)
        {
            printf("NO MATCH FOUND");
            return -1;
        }
}

void return_book(int n,int j,int k)
{
    GetSystemTime(&str_t);
    int book_entry,id;
    char isbn[100]={'\0'};
    char step_var[100]={'\0'};
    do{printf("Enter User ID:");
    gets(step_var);
    id=atoi(step_var);
    }while(validate_numbers(step_var)==-1 || validate_id(id,j)==-1 || validate_string(step_var)==-1);
    do{printf("\nEnter Book ISBN:");
    gets(isbn);
    book_entry=search_books_isbn(isbn,n);
    }while(validate_isbn(isbn)==-1 || book_entry==-1 ||validate_string(isbn)==-1);
    books[book_entry].available_copies+=1;
    book_entry=search_borrowed_isbn(isbn,k);
    update_book_info(n);
    sprintf(borrowed[book_entry].date_returned,"%d/%d/%d",str_t.wDay,str_t.wMonth,str_t.wYear);
    int i;
    pointer3=fopen("borrow.txt","w");
    for(i=0;i<k;i++)
    {
        fprintf(pointer3,"%s",borrowed[i].isbn);
        fprintf(pointer3,",%d",borrowed[i].user_id);
        fprintf(pointer3,",%s",borrowed[i].issued_date);
        fprintf(pointer3,",%s",borrowed[i].due_date);
        if(strstr(borrowed[i].date_returned, "\n"))
            fprintf(pointer3,",%s",borrowed[i].date_returned);
        else
            fprintf(pointer3,",%s\n",borrowed[i].date_returned);
    }
    fclose(pointer3);
    system("cls");
}

int search_members(int j,int n)
{
    int i,k=0;
    for(i=0;i<j;i++)
    {
        if(members[i].id==n)
        {
            k=-1;
            break;
        }
    }
    if(k==0)
    {
        return -1;
    }else
    {
        return i;
    }
}


int delete_member(int j,int k,int n)
{
    int id,i;
    char step_var[100]={'\0'};
    do{
        do{
        printf("Enter User ID:");
        gets(step_var);
        id=atoi(step_var);
        }while(validate_numbers(step_var)==-1 || validate_id(id,j)==-1 || validate_string(step_var)==-1);
    i=search_members(j,id);
    }while(i==-1);
    if(search_borrow_id(id,k,n)==-1)
    {
        printf("\nCan't delete user,un-returned books!");
    }else
    {
        for(i=i;i<j-1;i++)
        {
            members[i].id=members[i+1].id;
            strcpy(members[i].address,members[i+1].address);
            members[i].age=members[i+1].age;
            strcpy(members[i].city,members[i+1].city);
            strcpy(members[i].email,members[i+1].email);
            strcpy(members[i].first_name,members[i+1].first_name);
            strcpy(members[i].last_name,members[i+1].last_name);
            strcpy(members[i].phone_number,members[i+1].phone_number);
            strcpy(members[i].street,members[i+1].street);
        }
        pointer2=fopen("register.txt","w");
        for(i=0;i<j-1;i++)
        {
            fprintf(pointer2,"%d",members[i].id);
            fprintf(pointer2,",%s",members[i].first_name);
            fprintf(pointer2,"-%s",members[i].last_name);
            fprintf(pointer2,",%s",members[i].address);
            fprintf(pointer2,",%s",members[i].street);
            fprintf(pointer2,",%s",members[i].city);
            fprintf(pointer2,",%d",members[i].phone_number);
            fprintf(pointer2,",%d",members[i].age);
            if(strstr(members[i].email,"\n")){
                fprintf(pointer2,",%s",members[i].email);
            }else
                fprintf(pointer2,",%s\n",members[i].email);

        }
        fclose(pointer2);
        printf("Member deleted successfully\n");
        system("cls");
    }
    return j-1;
}

void overdue_list(int k,int i)
{
    int j,index;
    char today[100]={'\0'};
    sprintf(today,"%d/%d/%d",str_t.wDay,str_t.wMonth,str_t.wYear);
    int n=0;
    for(j=0;j<k;j++)
    {
        if((strcmp(borrowed[j].date_returned,"Not returned")==0 || strcmp(borrowed[j].date_returned,"Not returned\n")==0)  && strcmp((borrowed[j].due_date),today)!=0)
        {
                index=search_books_isbn(borrowed[j].isbn,i);
                n+=1;
                printf("%d.%s...%s\nMember ID:%d\n-------------------------------------------------------------------------",n,books[index].title,books[index].isbn,borrowed[j].user_id);
                printf("\n");
        }
    }
}
void most_popular_books(int i,int k)
{
    int borrowcounter_bookindex[i][2];
    int n=0;
    int j,s;
    for (j=0;j<i;j++)
    {
        borrowcounter_bookindex[j][0]=0;
    }

    for(j=0;j<i;j++)
    {
        int z=0;
        for(s=0;s<k;s++)
        {
            if(strcmp(books[j].isbn,borrowed[s].isbn)==0)
            {
                z++;
                //borrowcounter_bookindex[j][0]=z;
               // borrowcounter_bookindex[n][1];
            }

        }
        borrowcounter_bookindex[j][0] = z;
        borrowcounter_bookindex[j][1]=j;
        //n++;
    }
   /* printf("%d...%s\n",borrowcounter_bookindex[0][1],books[0].title);
    printf("%d...%s\n",borrowcounter_bookindex[1][1],books[1].title);*/
    printf("Before Sorting:\n");
    for(j=0; j<i; j++){
        printf("%d, %d\n", borrowcounter_bookindex[j][0], borrowcounter_bookindex[j][1]);
    }
    printf("=========================\n\n");
    int flag=-1;
    for(j=0;flag==-1;j++)
    {
        flag=0;
        for(s=1;s<i-j;s++)
        {
            if(borrowcounter_bookindex[s][0]>borrowcounter_bookindex[s-1][0])
            {
                borrowcounter_bookindex[s][0]^=borrowcounter_bookindex[s-1][0];
                borrowcounter_bookindex[s-1][0]^=borrowcounter_bookindex[s][0];
                borrowcounter_bookindex[s][0]^=borrowcounter_bookindex[s-1][0];
                borrowcounter_bookindex[s][1]^=borrowcounter_bookindex[s-1][1];
                borrowcounter_bookindex[s-1][1]^=borrowcounter_bookindex[s][1];
                borrowcounter_bookindex[s][1]^=borrowcounter_bookindex[s-1][1];
                flag=-1;
            }
        }
    }
    printf("After Sorting:\n");
    for(j=0; j<i; j++){
        printf("%d, %d\n", borrowcounter_bookindex[j][0], borrowcounter_bookindex[j][1]);
    }
    printf("=========================\n\n");

    /*

    printf("\n\n%s...%s\n",borrowcounter_bookindex[0][1],books[borrowcounter_bookindex[0][1]].title);
    printf("\n%d...%s\n",borrowcounter_bookindex[1][1],books[borrowcounter_bookindex[1][1]].title);*/
    int x;
    if(i<10)
    {
        x=i;
    }else
    {
        x=10;
    }
    for(j=x;j>0;j--)
    {
        //printf("%d\n",borrowcounter_bookindex[j][1]);
       // printf("%d\n",borrowcounter_bookindex[j][0]);
        printf("%s...%s\n",books[borrowcounter_bookindex[j][1]].isbn,books[borrowcounter_bookindex[j][1]].title);
    }
}

int main()
{
    GetSystemTime(&str_t);
    system("COLOR F1");
    char title_search[1000]={'\0'},author_search[1000]={'\0'},isbn_search[1000]={'\0'},category_search[1000]={'\0'};
    char str1[10000]={'\0'};
    char str2[10000]={'\0'};
    char str3[10000]={'\0'};
    int i=0;
    int j=0;
    int k=0;
    int index;
    char ans[3]={'\0'};
    char test[100]={'\0'};
    int choice;

    pointer1=fopen("Mylibrary.txt","r");
    while(!feof(pointer1))
    {
        if(fgets(str1,10000,pointer1) == NULL)
            break;
        strcpy(books[i].title,strtok(str1,","));
        strcpy(books[i].author,strtok(NULL, ","));
        strcpy(books[i].publisher,strtok(NULL, ","));
        strcpy(books[i].isbn,strtok(NULL, ","));
        strcpy(books[i].date_of_publication,strtok(NULL, ","));
        books[i].copies=atoi(strtok(NULL, ","));
        books[i].available_copies=atoi(strtok(NULL, ","));
        strcpy(books[i].category,strtok(NULL, "\n"));
        i++;
    }
    fclose(pointer1);

    pointer2=fopen("register.txt","r");
    while(!feof(pointer2))
    {
        if(fgets(str2,10000,pointer2)==NULL)
           break;
        members[j].id=atoi(strtok(str2,","));
        strcpy(members[j].first_name,strtok(NULL,"-"));
        strcpy(members[j].last_name,strtok(NULL,","));
        strcpy(members[j].address,strtok(NULL,","));
        strcpy(members[j].street,strtok(NULL,","));
        strcpy(members[j].city,strtok(NULL,","));
        strcpy(members[j].phone_number,strtok(NULL,","));
        members[j].age=atoi(strtok(NULL,","));
        strcpy(members[j].email,strtok(NULL,"\n"));
        j++;
    }
    fclose(pointer2);
    pointer3=fopen("borrow.txt","r");
    while(!feof(pointer3))
    {
        if(fgets(str3,10000,pointer3)==NULL)
            break;
        strcpy(borrowed[k].isbn,strtok(str3,","));
        borrowed[k].user_id=atoi(strtok(NULL,","));
        strcpy(borrowed[k].issued_date,strtok(NULL,","));
        strcpy(borrowed[k].due_date,strtok(NULL,","));
        strcpy(borrowed[k].date_returned,strtok(NULL,"\n"));
        k++;
    }
    fclose(pointer3);
    printf("\n\n\n\n\n\n\n                                  WELCOME\n                              LIBRARY SYSTEM\n                       press any key to continue....");
    getchar();
    system("cls");
    int options;
    do{printf("\n   MAIN MENU\n   ---------\n\n      Enter (1) for Books Management\n\n      Enter (2) for Members Transfactions\n\n      Enter (3) for Adminstrative Actions\n\nChoice: ");
    gets(test);
    printf("-------------------------------------------------------------------------------\n");
    }while(validate_numbers(test)==-1 || validate_string(test)==-1);
    options=atoi(test);

    while(options!=1 && options!=2 &&options!=3)
    {
        do{printf("PLease Enter a valid choice\nChoice:");
        gets(test);
        printf("----------------------------------------------------------------------\n");
        }while(validate_numbers(test)==-1 || validate_string(test)==-1);
        options=atoi(test);
    }
    switch(options)
        {
        case 1:
            system("cls");
            do{printf("\n   Books Management Menu\n   ----------------------\n\n      0.Main menu\n\n      1.Insert new book\n\n      2.Search for a Book\n\n      3.Add new copies\n\n      4.Delete a Book\n\nChoice:");
            gets(test);
            printf("----------------------------------------------------------------------\n");
            }while(validate_numbers(test)==-1 || validate_string(test)==-1);
            choice=atoi(test);
            while(choice!=0 && choice!=1 && choice!=2 && choice!=3 && choice!=4)
            {
                do{printf("PLease Enter a valid choice\nChoice:");
                gets(test);
                printf("-------------------------------------------------------------------------\n");
                }while(validate_numbers(test)==-1 || validate_string(test)==-1);
                choice=atoi(test);
            }

            if (choice==0)
            {
                system("cls");
                main();
            }else if(choice==1)
            {
                system("cls");
                i=insert_books(i);
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }else if (choice==2)
            {
               do{
                system("cls");
                do{printf("\n   Search by\n   ---------\n    1.Title\n    2.Author\n    3.ISBN\n    4.Category\nChoice:");
                    gets(test);
                    printf("----------------------------------------------------------------------\n");
                }while(validate_numbers(test)==-1 || validate_string(test)==-1);
                choice=atoi(test);
                while(choice!=0 && choice!=1 && choice!=2 && choice!=3 && choice!=4)
                {
                    do{printf("PLease Enter a valid choice\nChoice:");
                        gets(test);
                        printf("-------------------------------------------------------------------------\n");
                    }while(validate_numbers(test)==-1 || validate_string(test)==-1);
                choice=atoi(test);
                }
                if(choice==1)
                {
                    system("cls");
                    do{printf("\nBook Title:");
                        gets(title_search);
                    }while(validate_string(title_search)==-1);
                    search_books_title(title_search,i);
                    printf("\n\n                Search for another book?\n\n                [Y/N]:");
                    gets(ans);
                }else if (choice==2)
                {
                    system("cls");
                    do{printf("\Book Author:");
                        gets(author_search);
                    }while(validate_string(author_search)==-1);
                    search_books_author(author_search,i);
                    printf("\n\n                Search for another book?\n\n                [Y/N]:");
                    gets(ans);
                }else if(choice==3)
                {
                    system("cls");
                    do{printf("\nBook ISBN:");
                        gets(isbn_search);
                    }while(validate_isbn(isbn_search)==-1);
                    index=search_books_isbn(isbn_search,i);
                    if(index==-1)
                    {
                        printf("NO MATCH FOUND");
                    }else
                    {
                        printf("Title:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nISBN:%s\nNumber of copies:%d\nAvailable copies:%d\nCategory:%s\n------------------------------------------------------------------------\n",books[index].title,books[index].author,books[index].publisher,books[index].date_of_publication,books[index].isbn,books[index].copies,books[index].available_copies,books[index].category);
                    }
                    printf("\n\n                Search for another book?\n\n                [Y/N]:");
                    gets(ans);
                }else if(choice==4)
                {
                    system("cls");
                    do{printf("\nBook Category:");
                        gets(category_search);
                    }while(validate_string(category_search)==-1);
                    search_books_category(category_search,i);
                    printf("\n\n                Search for another book?\n\n                [Y/N]:");
                    gets(ans);
                }
              }while(ans[0]=='y' || ans[0]=='Y');
              do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
              key=getch();
              if(key==ESC)
              {
                system("cls");
                printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                break;
              }else if(key==LEFT)
              {
                system("cls");
                main();
              }
              }while(key!=ESC && key!=LEFT);
            }else if(choice==3)
            {
                do{system("cls");
                add_copies(i);
                printf("\n\n                Add Copies to another book?\n\n                [Y/N]:");
                gets(ans);
                }while(ans[0]=='y'||ans[0]=='Y');
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }else if(choice==4)
            {
                do{system("cls");
                i=delete_book(i);
                printf("\n\n                Delete another Book?\n\n                [Y/N]:");
                gets(ans);
                }while(ans[0]=='y' || ans[0]=='Y');
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }
            break;
        case 2:
            system("cls");
            do{printf("\n   Members Transactions Menu\n   -------------------------\n\n      0.Main menu\n\n      1.Registeration\n\n      2.Borrowing\n\n      3.Returning a book\n\n      4.Remove a member\n\nChoice:");
            gets(test);
            printf("----------------------------------------------------------------------\n");
            }while(validate_numbers(test)==-1 || validate_string(test)==-1);
            choice=atoi(test);
            while(choice!=0 && choice!=1 && choice!=2 && choice!=3 && choice!=4)
            {
                do{printf("PLease Enter a valid choice\nChoice:");
                gets(test);
                printf("-------------------------------------------------------------------------\n");
                }while(validate_numbers(test)==-1 || validate_string(test)==-1);
                choice=atoi(test);
            }
            if(choice==0)
            {
                system("cls");
                main();
            }else if(choice==1)
            {
                system("cls");
                j=registeration(j);
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }else if(choice==2)
            {
                system("cls");
                k=borrow(i,k,j);
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }else if(choice==3)
            {
                do{system("cls");
                return_book(i,j,k);
                printf("\n\n                Return another book?\n\n                [Y/N]:");
                gets(ans);
                }while(ans[0]=='y'||ans[0]=='Y');
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }
            else if(choice==4)
            {
                do{system("cls");
                j=delete_member(j,k,i);
                printf("\n\n                Delete another member?\n\n                [Y/N]:");
                gets(ans);
                }while(ans[0]=='y'||ans[0]=='Y');
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);

            }
            break;
        case 3:
            system("cls");
            do{printf(" \nAdministrative Actions Menu\n-------\n\n      0.Main menu\n\n      1.Overdue Books\n\n      2.Most popular Books\n\n      3.Quit\n\nChoice:");
            gets(test);
            printf("----------------------------------------------------------------------\n");
            }while(validate_numbers(test)==-1 || validate_string(test)==-1);
            choice=atoi(test);
            while(choice!=0 && choice!=1 && choice!=2 && choice!=3 && choice!=4)
            {
                do{printf("PLease Enter a valid choice\nChoice:");
                gets(test);
                printf("-------------------------------------------------------------------------\n");
                }while(validate_numbers(test)==-1 || validate_string(test)==-1);
                choice=atoi(test);
            }
            if(choice==0)
            {
                system("cls");
                main();
            }else if(choice==1)
            {
                system("cls");
                overdue_list(k,i);
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }else if(choice==2)
            {
                system("cls");
                most_popular_books(i,k);
                do{printf("\n         Press ESC to EXIT        Press LEFT to go to MAIN MENU\n");
                key=getch();
                if(key==ESC)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                }else if(key==LEFT)
                {
                    system("cls");
                    main();
                }
                }while(key!=ESC && key!=LEFT);
            }else if(choice==3)
            {
                system("cls");
                printf("\n\n\n\n\n\n\n                              HAVE A GOOD-DAY...\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            }
            break;
        }
    return 0;
}
