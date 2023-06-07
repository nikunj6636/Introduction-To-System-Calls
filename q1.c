#include<stdio.h>
#include<fcntl.h> 
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

typedef long long int ll;

ll source_file, dest_file, nread = 0, chunk_size = 1000, filelength; // initially nread contais 0 character
char c[100001], r[100001];

void solve(ll length)
{
    int len = length % chunk_size; // start from here and print upto end of the file
    nread += len;

    lseek(source_file, -nread, SEEK_END); // SEEK_END points to null char
    read(source_file, c, len); // read len characters 

    for(int i=0, j = len-1; i<len; i++, j--) // now reverse the characters and input in the another
    {
        r[j] = c[i]; // reversing the string.
    }

    char B[100];

    write(dest_file, r, len); // hence written in reverse order to sedt file
    sprintf(B, "\rProgress = %f %%", (100.0 * nread) / filelength);
    write(1, B, strlen(B));

    // run the quotient number of times 
    for(int a=0; a < length/chunk_size; a++)
    {
        nread += chunk_size; // the number of characters read
        lseek(source_file, -nread, SEEK_END);
        read(source_file, c, chunk_size);  // read chunk_size characters

        for(int i=0, j = chunk_size-1; i < chunk_size; i++, j--)
        {
            r[j] = c[i]; // reversing the string.
        }

        write(dest_file, r, chunk_size);
        sprintf(B, "\rProgress = %f %%", (100.0 * nread) / filelength);
        write(1, B, strlen(B));
    }
}

int main(int argc, char *argv[]) // to take the name of input file
{     
    size_t old_mask = umask(0);

    char src[101], dst[21] = "1_", name[21];

    // opening the source file.
    int flag = 0, l, f; 

    strcpy(src, argv[1]);
    for(l = strlen(src) - 1; l >=0 ; l--)
    {
        if (src[l] == '/') 
        {
            flag = 1; // if encounterd a \ at end
            break;
        }
    }

    if (flag)
    {
        src[l++] = '\0';
        for(f = l; src[f] != '\0'; f++) name[f-l] = src[f];
        name[f-l] = '\0';

        if (chdir(src) < 0)
        {
            perror("program");
        }
        source_file = open(name, O_RDONLY);
        strcat(dst, name);
    }

    else{
        source_file = open(src, O_RDONLY);
        strcat(dst, src);
    }

    int retx = mkdir("Assignment", 0777); // make folder in current directory
    if (retx)
    {
        perror("Directory not created\n"); // if retx = 1 error occured
        exit(0);
    }

    chdir("Assignment"); // move in that directory
    dest_file = open(dst, O_CREAT | O_WRONLY, 0644); // opening in write only flag
    
    if (source_file<0 || dest_file<0 ) // error handling 
    {
        perror("Program"); // print program detail "Success or failure"                  
    } 

    // calling the fuction
    lseek(dest_file, 0, SEEK_SET); // set cursor at the start of file
    filelength = lseek(source_file, 0, SEEK_END); // returns current file size + offset

    solve(filelength); // copy the 3 parts of the file
    
    write(1, "\n", 1);
    close(source_file);
    close(dest_file);

    umask(old_mask);
} 