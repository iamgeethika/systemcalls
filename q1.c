#include <stdio.h>
#include <fcntl.h>                                           // function control command
#include <sys/types.h>                                       // typedef symbols, structures
#include <sys/stat.h>
#include <unistd.h>                                          // provides access to API
#include <math.h>
#include <string.h>

typedef long long int ll;

int main(int argc, char *argv[])
{
    char *s=argv[1];
    char string[50];
    char percent_string[50];
    char *ptr;
  
    // ll l;
    // l = strlen(percent_string);

    // READING THE INPUT FILE

    ll inp_file = open(argv[1], O_RDONLY);                    // Opening Input file
    off_t inp_file_length = lseek(inp_file, 0, SEEK_END);     // Calculating file size
    ll length;
    ll l;
    length = inp_file_length;

    ptr = strrchr(s,'/');
    char f_name[50];

    if(ptr)
    {
       int i;
      int j;
      j = 0;
      int  pf;
      pf = ptr - argv[1];
      for (int i = pf + 1; s[i - 1] != '\0'; i++)
        {
            f_name[j++] = s[i];                            // getting the input file name from the path given
        }
    }
    else
    {
      strcpy(f_name,s);
    }
    // if(inp_file < 0)
    // {
    //     perror("Error: ");
    //     return 0;
    // }
                                   // Creating new directory and giving Permissions to it
    strcpy(string, "Assignment/1_");  
    mkdir("Assignment", 0700);                         // Copying the string
    strcat(string, f_name);                                  // Concatenating the string
    // creat(string,0700);
    ll out_file = creat(string, 0600);                        // Creating Output file
    // off_t out_file_length = lseek(out_file, 0, SEEK_END);
    if (inp_file < 0 || out_file < 0)
    {
        perror("Error: ");                                    // Using perror()
        return 0;
    }

    ll chunk_size;
    chunk_size = 100000;                                      // Taking chunk size as 100000
    char inp[chunk_size + 1];                                 // Taking an array
    char reverse[chunk_size + 1];                             // Taking another array to create reverse of input file
    ll rev;
    ll count;
    count = 0;
    // ll a = inp_file_length - chunk_size;

    double percentage;
    while (1)
    {
        if (length > chunk_size)                              // if length of file  >  chunk size
        {
            ll a = length - chunk_size;
            lseek(inp_file, a, SEEK_SET);                     // Reading from a th byte
            ll kd = read(inp_file, inp, chunk_size);          // Reading 10*5 bytes(chunk_size) from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }

            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                reverse[i] = inp[j];                          // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);               // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            length = length - chunk_size;                     // decrementing length by chunk size
            count += rev;                                     // incrementing count by rev
        }
        else if (length == chunk_size)                        // if length of file = chunk size
        {
            ll a = length - chunk_size;
            lseek(inp_file, a, SEEK_SET);                     // Reading from a th byte
            ll kd = read(inp_file, inp, length);
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                reverse[i] = inp[j];                          // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);               // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            length = length - chunk_size;
            count += rev;
            break;
        }
        else
        {
            lseek(inp_file, 0, SEEK_SET);                    // Reading from 0 th byte
            ll kd = read(inp_file, inp, length);             // Returns specified numer of bytes from the file
            if(kd<0)
            {
                perror("Error: ");                           // Using perror()
                return 0;
            }

            ll i = 0;
            ll j = kd - 1;
            for (i, j; i < kd; i++, j--)
            {
                reverse[i] = inp[j];                         // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);              // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            count += rev;
            break;
        }

        percentage = (count / ((double)inp_file_length)) * 100;
        // l = strlen(percent_string);
        sprintf(percent_string,"percentage of file written : %lf \r", percentage);  // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
        l = strlen(percent_string);
        write(1,percent_string,l);
    }
    percentage = (count / ((double)inp_file_length)) * 100;
    // l = strlen(percent_string);
    sprintf(percent_string,"percentage of file written : %lf \n", percentage);
    l = strlen(percent_string);
    write(1,percent_string,l);

                                              // Closing the Input file   
    if(close(inp_file) <0)
    {
        perror("Error: ");                                   // Error Handling
        return 0;
    } 
                                              // Closing the Output file
    if(close(out_file) <0)
    {
        perror("Error: ");                                    // Error Handling
        return 0;
    } 
    return 0;
}