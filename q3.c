#include<stdio.h>
#include<fcntl.h> 
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

typedef long long int ll;

ll source_file, dest_file, nread = 0, chunk_size = 1000; // initially nread contais 0 character
char c[100009], r[100009], B[101];

int solve(ll length)
{
    lseek(dest_file, nread, SEEK_SET); // to read first characters

    int len = length % chunk_size; // start from here and print upto end of the file
    nread += len;
    lseek(source_file, -nread, SEEK_END); // SEEK_END points to null char
    
    read(source_file, c, len); // read len characters
    read(dest_file, r, len); 

    for(int i=0, j = len-1; i<len; i++, j--) // now reverse the characters and input in the another
    {
        if (r[j] != c[i])
        {
            sprintf(B, "No\n");
            write(1, B, strlen(B)); // 1 is used for printing in console using system call
            return 0;
        }
    }

    // run the quotient number of times 
    for(int a=0; a < length/chunk_size; a++)
    {
        lseek(dest_file, nread, SEEK_SET);

        nread += chunk_size; // the number of characters read
        lseek(source_file, -nread, SEEK_END);
        
        read(source_file, c, chunk_size);  // read chunk_size characters
        read(dest_file, r, chunk_size);

        for(int i=0, j = chunk_size-1; i < chunk_size; i++, j--)
        {
            if (r[j] != c[i])
            {
                sprintf(B, "No\n");
                write(1, B, strlen(B)); // 1 is used for printing in console using system call
                return 0;
            }
        }
    }

    sprintf(B, "Yes\n");
    write(1, B, strlen(B)); // 1 is used for printing in console using system call
    return 0;
}

int main(int argc, char *argv[]) // to take the name of input file
{ 
    struct stat stats;

    // comparing the folder structure

    if (stat(argv[3], &stats) == 0) 
    {
        if (S_ISDIR(stats.st_mode)) 
        {
            sprintf(B, "Directory is Created: Yes\n");
            write(1, B, strlen(B));
        }

        else 
        {
            sprintf(B, "Directory is Created: No\n");
            write(1, B, strlen(B));
        }   
    }

    // comparing the 2 files 
    sprintf(B, "Whether file contents are reversed in newfile: ");
    write(1, B, strlen(B));

    source_file = open(argv[2], O_RDONLY);  // old file
    dest_file = open(argv[1], O_RDONLY);    // new file
    
    if (source_file<0 || dest_file<0 ) // error handling 
    {
        perror("Program"); // print program detail "Success or failure"  
        exit(0);                
    } 

    ll a = lseek(dest_file, 0, SEEK_END); // set cursor at the start of file
    ll b = lseek(source_file, 0, SEEK_END);

    if (a != b) // lengths of 2 files are not equal
    {
        sprintf(B, "No\n");
        write(1, B, strlen(B)); // 1 is used for printing in console using system call
    }

    ll filelength = a;

    solve(filelength);

    // checking permissions of new file

    if (stat(argv[1], &stats) == 0)
    {
        // checking permissions of new file for user : read , write and execute

        sprintf(B, "User has read permissions on newfile: %s\n", stats.st_mode & S_IRUSR ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "User has write permissions on newfile: %s\n", stats.st_mode & S_IWUSR ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "User has execute permissions on newfile: %s\n", stats.st_mode & S_IXUSR ? "Yes" : "No");
        write(1, B, strlen(B));   

        // checking permissions of new file for group

        sprintf(B, "Group has read permissions on newfile: %s\n", stats.st_mode & S_IRGRP ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Group has write permissions on newfile: %s\n", stats.st_mode & S_IWGRP ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Group has execute permissions on newfile: %s\n", stats.st_mode & S_IXGRP ? "Yes" : "No");
        write(1, B, strlen(B));  

        // checking permissions of new file for others

        sprintf(B, "Others has read permissions on newfile: %s\n", stats.st_mode & S_IROTH ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Others has write permissions on newfile: %s\n", stats.st_mode & S_IWOTH ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Others has execute permissions on newfile: %s\n", stats.st_mode & S_IXOTH ? "Yes" : "No");
        write(1, B, strlen(B));  
    }

    // checking permissions of old file

    if (stat(argv[2], &stats) == 0)
    {
        // checking permissions of old file for user : read, write and execute

        sprintf(B, "User has read permissions on oldfile: %s\n", stats.st_mode & S_IRUSR ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "User has write permissions on oldfile: %s\n", stats.st_mode & S_IWUSR ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "User has execute permissions on oldfile: %s\n", stats.st_mode & S_IXUSR ? "Yes" : "No");
        write(1, B, strlen(B));   

        // checking permissions of old file for group

        sprintf(B, "Group has read permissions on oldfile: %s\n", stats.st_mode & S_IRGRP ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Group has write permissions on oldfile: %s\n", stats.st_mode & S_IWGRP ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Group has execute permissions on oldfile: %s\n", stats.st_mode & S_IXGRP ? "Yes" : "No");
        write(1, B, strlen(B));  

        // checking permissions of old file for others

        sprintf(B, "Others has read permissions on oldfile: %s\n", stats.st_mode & S_IROTH ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Others has write permissions on oldfile: %s\n", stats.st_mode & S_IWOTH ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Others has execute permissions on oldfile: %s\n", stats.st_mode & S_IXOTH ? "Yes" : "No");
        write(1, B, strlen(B));  
    }

     if (stat(argv[3], &stats) == 0)
    {
        // checking permissions of new file for user

        sprintf(B, "User has read permissions on directory: %s\n", stats.st_mode & S_IRUSR ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "User has write permissions on directory: %s\n", stats.st_mode & S_IWUSR ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "User has execute permissions on directory: %s\n", stats.st_mode & S_IXUSR ? "Yes" : "No");
        write(1, B, strlen(B));   

        // checking permissions of new file for group

        sprintf(B, "Group has read permissions on directory: %s\n", stats.st_mode & S_IRGRP ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Group has write permissions on directory: %s\n", stats.st_mode & S_IWGRP ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Group has execute permissions on directory: %s\n", stats.st_mode & S_IXGRP ? "Yes" : "No");
        write(1, B, strlen(B));  

        // checking permissions of new file for others

        sprintf(B, "Others has read permissions on directory: %s\n", stats.st_mode & S_IROTH ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Others has write permissions on directory: %s\n", stats.st_mode & S_IWOTH ? "Yes" : "No");
        write(1, B, strlen(B));

        sprintf(B, "Others has execute permissions on directory: %s\n", stats.st_mode & S_IXOTH ? "Yes" : "No");
        write(1, B, strlen(B));  
    }
    
    close(source_file);
    close(dest_file);
} 