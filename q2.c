#include <stdio.h>
#include <fcntl.h>                                       // function control command
#include <sys/types.h>                                   // typedef symbols, structures
#include <sys/stat.h>
#include <unistd.h>                                      // provides access to API
#include <math.h>
#include <string.h>
#include <stdlib.h>

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

    ll inp_file = open(argv[1], O_RDONLY);                // Opening Input file
    off_t inp_file_length = lseek(inp_file, 0, SEEK_END); // Calculating file size
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
    mkdir("Assignment", 0700);                              // Creating new directory and giving Permissions to it
    strcpy(string, "Assignment/2_");                        // Copying the string
    strcat(string, f_name);                                // Concatenating the string
    // creat(string,0700);
    ll out_file = creat(string, 0600);                      // Creating Output file
    // off_t out_file_length = lseek(out_file, 0, SEEK_END);
    if (inp_file < 0 || out_file < 0)
    {
        perror("Error: ");
        return 0;
    }

    ll chunk_size;
    chunk_size = 100000;                                    // Taking chunk size as 100000
    char inp[chunk_size + 1];                               // Taking an array
    char reverse[chunk_size + 1];                           // Taking another array to create reverse of input file
    ll start_character;
    ll end_character;
    // atoi converts a string to an integer
    start_character = atoi(argv[2]);                        // stores the 2nd string i.e.. argv[2] in start_character
    end_character = atoi(argv[3]);                          // stores the 3rd string i.e.. argv[3] in end_character


    // Doing in 3 Parts

    off_t flength1 = lseek(inp_file, start_character, SEEK_SET);  // Calculating the size of file upto start character
    ll lgth1;
    lgth1 = flength1;

    ll rev;
    ll count;
    count = 0;
    // ll a = inp_file_length - chunk_size;

    double percentage;

    while (1)
    {
        if (lgth1 > chunk_size)                              // if length of file  >  chunk size
        {
            ll a = lgth1 - chunk_size;
            lseek(inp_file, a, SEEK_SET);                    // Reading from a th byte
            ll kd = read(inp_file, inp, chunk_size);         // Reading 10*5 bytes(chunk_size) from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }

            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                reverse[i] = inp[j];                         // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);              // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            lgth1 = lgth1 - chunk_size;
            count += rev;
             percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);   // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
        }
        else if (lgth1 == chunk_size)
        {
            ll a = lgth1 - chunk_size;
            lseek(inp_file, a, SEEK_SET);                    // Reading from a th byte
            ll kd = read(inp_file, inp, lgth1);              // Reading lgth1 bytes from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                reverse[i] = inp[j];                         // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);              // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            lgth1 = lgth1 - chunk_size;
            count += rev;
             percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);   // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
            break;
        }
        else
        {
            lseek(inp_file, 0, SEEK_SET);                    // Reading from 0 th byte
            ll kd = read(inp_file, inp, start_character);    // Returns specified number of bytes from the file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
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
            lgth1 = lgth1 - chunk_size;
            count += rev;
             percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);   // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
            break;
        }
    }

    ll flength2;
    flength2 = end_character - start_character;
    flength2 += 1;
    ll lgth2;
    lgth2 = flength2;
    ll count2 = 0;

    while (1)
    {
        if (lgth2 > chunk_size)                                // if length of file  >  chunk size
        {
            // ll a = lgth1 - chunk_size;
            lseek(inp_file, start_character, SEEK_SET);        // Reading from a th byte
            ll kd = read(inp_file, inp, chunk_size);           // Reading 10*5 bytes(chunk_size) from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            rev = write(out_file, inp, kd);                    // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            count += rev;
            lgth2 = lgth2 - chunk_size;
            start_character += kd;
            count2 += rev;
             percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);    // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
        }
        else if (lgth2 == chunk_size)
        {
            // ll a = lgth1 - chunk_size;
            lseek(inp_file, start_character, SEEK_SET);         // Reading from a th byte
            ll kd = read(inp_file, inp, chunk_size);            // Reading 10*5 bytes(chunk_size) from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            rev = write(out_file, inp, kd);                     // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            count += rev;
            lgth2 = lgth2 - chunk_size;
            start_character += kd;
            count2 += rev;
             percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);    // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
            break;
        }
        else
        {
            lseek(inp_file, start_character, SEEK_SET);          // Reading from 0 th byte
            ll kd = read(inp_file, inp, lgth2);                  // Reading lgth2 bytes from the input file               // Returns specified numer of bytes from the file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            rev = write(out_file, inp, kd);                      // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file                   // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            count += rev;
            lgth2 = lgth2 - chunk_size;
            count2 += rev;
             percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);    // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);

            break;
        }
    }
    ll a = length;
    ll flength3;
    flength3 = length - end_character;
    flength3 -= 1;
    ll lgth3;
    lgth3 = flength3;

    while (1)
    {
        if (lgth3 > chunk_size) // if length of file  >  chunk size
        {
            ll a = a - chunk_size;
            lseek(inp_file, a, SEEK_SET); // Reading from a th byte
            ll kd = read(inp_file, inp, chunk_size);   // Reading 10*5 bytes(chunk_size) from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }

            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                reverse[i] = inp[j]; // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);         // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file                     // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            lgth3 = lgth3 - chunk_size;

            count += rev;
            percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);    // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
        }
        else if (lgth3 == chunk_size)
        {
            ll a = a - chunk_size;
            lseek(inp_file, a, SEEK_SET); // Reading from a th byte
            ll kd = read(inp_file, inp, chunk_size);   // Reading 10*5 bytes(chunk_size) from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }

            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                reverse[i] = inp[j]; // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd);          // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            lgth3 = lgth3 - chunk_size;
            count += rev;
            percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);     // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
            break;
        }
        else
        {
            a = a - lgth3;

            lseek(inp_file, a, SEEK_SET);       // Reading from 0 th byte
            ll kd = read(inp_file, inp, lgth3); // Reading lgth3 bytes from the input file
            if(kd<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }

            ll i = 0;
            ll j = kd - 1;
            for (i, j; i < kd; i++, j--)
            {
                reverse[i] = inp[j]; // first bit of reverse string is the last bit of input file
            }
            rev = write(out_file, reverse, kd); // writes count bytes from the buffer starting at buf to the file referred to by the file descriptor inp_file
            if(rev<0)
            {
                perror("Error: ");                                    // Using perror()
                return 0;
            }
            // count += rev;
            lgth3 = lgth3 - chunk_size;
            // start_character +=
            count += rev;
            percentage = (count / ((double)inp_file_length)) * 100;
            sprintf(percent_string, "percentage of file written : %lf \r", percentage);    // '\r' can be used to move the cursor back to the beginning of the line, to overwrite it with new contents.
            l = strlen(percent_string);
            write(1, percent_string, l);
            break;
        }
    }
    // percentage = (count / ((double)inp_file_length)) * 100;
    // l = strlen(percent_string);
    sprintf(percent_string, "percentage of file written : %lf \n", percentage);
    l = strlen(percent_string);
    write(1, percent_string, l);

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