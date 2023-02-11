#include <stdio.h>
#include <fcntl.h>     // function control command
#include <sys/types.h> // typedef symbols, structures
#include <sys/stat.h>
#include <unistd.h> // provides access to API
#include <math.h>
#include <string.h>

// STAT COMMANDS
// S_ISDIR, true when the file is a directory

typedef long long int ll;

int main(int argc, char *argv[])
{
    // ll inp_file = open(argv[1], O_RDONLY);

    struct stat directory, in_fl, ot_fl;                     // stat - to check the status of a file such as to check when the file was accessed
    
    // pointer to stat structure

    ll dir,inp,out;

    inp = stat(argv[1],&in_fl);                              // stat system calls
    out = stat(argv[2],&ot_fl);
    dir = stat(argv[3],&directory);

    if((inp !=0) || (out !=0) || (dir !=0) )
    {
       perror("Error: ");                                    // Using perror()  -- Error Handling
        return 0;
    }

    char dir_per[50];
    char inp_per[50];
    char out_per[50];

    char Directory[50];
    ll dirp;

    // Checking whether the directory is created or not

    if(S_ISDIR(directory.st_mode))                          // S_ISDIR, true when the file is a directory
    {
        sprintf(Directory,"Directory is created: Yes\n");
        dirp = strlen(Directory);
        write(1,Directory,dirp);                            // it will print the string
    }
    else
    {
        sprintf(Directory,"Directory is created: No\n");
        dirp = strlen(Directory);
        write(1,Directory,dirp);                            // it will print the string
    }



    // For checking whether the file contents are reversed in the new file

    ll chunk_size;
    chunk_size = 1000000;

    char inpfl[chunk_size + 1];
    char inpflrev[chunk_size + 1];
    char outfl[chunk_size + 1];

    ll inp_file = open(argv[1],O_RDONLY);                                 // Opening the Newfile
    ll inp_length = lseek(inp_file,0,SEEK_END);                           // Calculating the size of the new file
    ll il;
    il = inp_length;                                                      // size of new file = il

    ll out_file = open(argv[2],O_RDONLY);                                 // Opening the Oldfile
    ll out_length = lseek(out_file,0,SEEK_END);                           // Calculating the size of the old file
    ll ol;
    ol = out_length;                                                      // size of the old file = ol


    if(inp_file == -1 || out_file == -1)                                  // Error Handling
    {
        perror("Error: ");                                                // using perror()
        return 0;
    }


    ll a=0,fg=0;                                                          // Taking a flag fg

    char ck[100];


    if(il != ol)                                                          // if the given 2 files sizes are not equal, then obviously they are not reverse of each other
    {
        sprintf(ck,"Whether file contents are reversed in newfile: No\n");         // printing No
        ll c = strlen(ck);
        write(1,ck,c);
        fg =1;
    }

    while(il > 0 && ol>0)
    {
        if(il>chunk_size && ol>chunk_size)                 // if both the sizes are equal and their size > chunk_size
        {
            il = il - chunk_size;
            lseek(out_file,a,SEEK_SET);                    // Calculating the size of the output file upto a th byte
            lseek(inp_file,il,SEEK_SET);                   // Calculating the size of the input file upto il th byte
            read(inp_file,inpfl,chunk_size);               // Reading the input file (new file) upto chunk_size(10^5 bytes)
            read(out_file,outfl,chunk_size);               // Reading the output file (new file) upto chunk_size(10^5 bytes)

            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                inpflrev[i] = inpfl[j];                    // Creating the reverse of the newfile
            }
            ll b = chunk_size - 1;
            for(i=0;i<b;i++)
            {
                if(inpflrev[i] != outfl[i])                // if any of the contents of the oldfile and the reversed newfile are not equal
                {
                    sprintf(ck,"Whether file contents are reversed in newfile: No\n");   // printing No
                    ll c = strlen(ck);
                    write(1,ck,c);                         // it will print the string
                    fg = 1;                                // making the flag 1
                    break;
                }
            }
            if(fg == 1)
            {
                break;
            }

            a = a + chunk_size;
            ol = ol - chunk_size;

        }

        else if(il==chunk_size && ol == chunk_size)
        {
            il = il - chunk_size;
            lseek(out_file,a,SEEK_SET);                     // Calculating the size of the output file upto a th byte
            lseek(inp_file,il,SEEK_SET);                    // Calculating the size of the input file upto il th byte
            read(inp_file,inpfl,chunk_size);                // Reading the input file (new file) upto chunk_size(10^5 bytes)
            read(out_file,outfl,chunk_size);                // Reading the output file (new file) upto chunk_size(10^5 bytes)

            ll i = 0;
            ll j = chunk_size - 1;
            for (i, j; i < chunk_size; i++, j--)
            {
                inpflrev[i] = inpfl[j];                       // Creating the reverse of the newfile
            }
            
            ll b = chunk_size - 1;
            for(i=0;i<b;i++)
            {
                if(inpflrev[i] != outfl[i])                  // if any of the contents of the oldfile and the reversed newfile are not equal
                {
                    sprintf(ck,"Whether file contents are reversed in newfile: No\n");        //printing No
                    ll c = strlen(ck);
                    write(1,ck,c);                           // it will print the string
                    fg = 1;
                    break;
                }
            }
            if(fg == 1)
            {
                break;
            }

            a = a + chunk_size;
            ol = ol - chunk_size;
            break;

        }

        else
        {
            lseek(out_file,a,SEEK_SET);                        // Calculating the size of the output file upto a th byte
            lseek(inp_file,0,SEEK_SET);

            ll id = read(inp_file,inpfl,il);                   // Reading the input file (new file) upto il bytes
            ll od = read(out_file,outfl,ol);                   // Reading the output file (old file) upto ol bytes

            ll i = 0;
            ll j = id - 1;
            for (i, j; i < id; i++, j--)
            {
                inpflrev[i] = inpfl[j];                          // Creating the reverse of the newfile
            }

            for(i=0;i<id-1;i++)
            {
                if(inpflrev[i] != outfl[i])                      // if any of the contents of the oldfile and the reversed newfile are not equal
                {
                    sprintf(ck,"Whether file contents are reversed in newfile: No\n");       // printing No
                    ll c = strlen(ck);
                    write(1,ck,c);                               // it will print the string
                    fg = 1;
                    break;
                }
            }
            if(fg == 1)
            {
                break;
            }

            a = a + id;
            ol = ol - id;
            il = il - id;

        }
    }

    if(fg == 0)                    // if it doesn't follow any of the above cases, that means the file contents are reversed in the newfile
    {
        sprintf(ck,"Whether file contents are reversed in newfile: Yes\n");         // printing Yes
        ll c = strlen(ck);
        write(1,ck,c);           // it will print the string
    }

    ll dp, ip, op;

    // NEW FILE

    // USER PERMISSIONS

    if (in_fl.st_mode & S_IRUSR) // USR -> USER (Owner)   R -> Read Permissions
    {
        sprintf(inp_per, "User has read permissions on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "User has read permissions on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    if (in_fl.st_mode & S_IWUSR) // USR -> USER (Owner)   W -> Write Permission
    {
        sprintf(inp_per, "User has write permission on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "User has write permission on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    if (in_fl.st_mode & S_IXUSR) // USR -> USER (Owner)   X -> Execute Permission
    {
        sprintf(inp_per, "User has execute permission on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "User has execute permission on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    // GROUP PERMISSIONS

    if (in_fl.st_mode & S_IRGRP) // GRP -> Group   R -> Read Permissions
    {
        sprintf(inp_per, "Group has read permissions on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "Group has read permissions on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    if (in_fl.st_mode & S_IWGRP) // GRP -> Group   W -> Write Permissions
    {
        sprintf(inp_per, "Group has write permission on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "Group has write permission on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    if (in_fl.st_mode & S_IXGRP) // GRP -> Group   X -> Execute Permission
    {
        sprintf(inp_per, "Group has execute permission on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "Group has execute permission on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    // OTHERS PERMISSIONS

    if (in_fl.st_mode & S_IROTH) // OTH -> Others   R -> Read Permissions
    {
        sprintf(inp_per, "Others has read permissions on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "Others has read permissions on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    if (in_fl.st_mode & S_IWOTH) // OTH -> Others   W -> Write Permission
    {
        sprintf(inp_per, "Others has write permission on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);   // it will print the string
    }
    else
    {
        sprintf(inp_per, "Others has write permission on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    if (in_fl.st_mode & S_IXOTH) // OTH -> Others   X -> Execute Permission
    {
        sprintf(inp_per, "Others has execute permission on newfile: Yes\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }
    else
    {
        sprintf(inp_per, "Others has execute permission on newfile: No\n");
        ip = strlen(inp_per);
        write(1, inp_per, ip);  // it will print the string
    }

    // OLD FILE

    // USER PERMISSIONS

    if (ot_fl.st_mode & S_IRUSR) // USR -> USER (Owner)   R -> Read Permissions
    {
        sprintf(out_per, "User has read permissions on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "User has read permissions on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    if (ot_fl.st_mode & S_IWUSR) // USR -> USER (Owner)   W -> Write Permission
    {
        sprintf(out_per, "User has write permission on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "User has write permission on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    if (ot_fl.st_mode & S_IXUSR) // USR -> USER (Owner)   X -> Execute Permission
    {
        sprintf(out_per, "User has execute permission on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "User has execute permission on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    // GROUP PERMISSIONS

    if (ot_fl.st_mode & S_IRGRP) // GRP -> Group   R -> Read Permissions
    {
        sprintf(out_per, "Group has read permissions on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "Group has read permissions on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    if (ot_fl.st_mode & S_IWGRP) // GRP -> Group   W -> Write Permissions
    {
        sprintf(out_per, "Group has write permission on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "Group has write permission on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    if (ot_fl.st_mode & S_IXGRP) // GRP -> Group   X -> Execute Permission
    {
        sprintf(out_per, "Group has execute permission on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "Group has execute permission on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    // OTHERS PERMISSIONS

    if (ot_fl.st_mode & S_IROTH) // OTH -> Others   R -> Read Permissions
    {
        sprintf(out_per, "Others has read permissions on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "Others has read permissions on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    if (ot_fl.st_mode & S_IWOTH) // OTH -> Others   W -> Write Permission
    {
        sprintf(out_per, "Others has write permission on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "Others has write permission on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    if (ot_fl.st_mode & S_IXOTH) // OTH -> Others   X -> Execute Permission
    {
        sprintf(out_per, "Others has execute permission on oldfile: Yes\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }
    else
    {
        sprintf(out_per, "Others has execute permission on oldfile: No\n");
        op = strlen(out_per);
        write(1, out_per, op);  // it will print the string
    }

    // DIRECTORY

    // USER PERMISSIONS

    if (directory.st_mode & S_IRUSR) // USR -> USER (Owner)   R -> Read Permissions
    {
        sprintf(dir_per, "User has read permissions on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "User has read permissions on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    if (directory.st_mode & S_IWUSR) // USR -> USER (Owner)   W -> Write Permission
    {
        sprintf(dir_per, "User has write permission on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "User has write permission on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    if (directory.st_mode & S_IXUSR) // USR -> USER (Owner)   X -> Execute Permission
    {
        sprintf(dir_per, "User has execute permission on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "User has execute permission on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    // GROUP PERMISSIONS

    if (directory.st_mode & S_IRGRP) // GRP -> Group   R -> Read Permissions
    {
        sprintf(dir_per, "Group has read permissions on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "Group has read permissions on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    if (directory.st_mode & S_IWGRP) // GRP -> Group   W -> Write Permissions
    {
        sprintf(dir_per, "Group has write permission on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "Group has write permission on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    if (directory.st_mode & S_IXGRP) // GRP -> Group   X -> Execute Permission
    {
        sprintf(dir_per, "Group has execute permission on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "Group has execute permission on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    // OTHERS PERMISSIONS

    if (directory.st_mode & S_IROTH) // OTH -> Others   R -> Read Permissions
    {
        sprintf(dir_per, "Others has read permissions on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "Others has read permissions on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    if (directory.st_mode & S_IWOTH) // OTH -> Others   W -> Write Permission
    {
        sprintf(dir_per, "Others has write permission on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "Others has write permission on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }

    if (directory.st_mode & S_IXOTH) // OTH -> Others   X -> Execute Permission
    {
        sprintf(dir_per, "Others has execute permission on directory: Yes\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }
    else
    {
        sprintf(dir_per, "Others has execute permission on directory: No\n");
        dp = strlen(dir_per);
        write(1, dir_per, dp);  // it will print the string
    }                                          // Closing the Input file   
    if(close(inp_file) <0)
    {
        perror("Error: ");                                   // Error Handling
        return 0;
    }                                           // Closing the Output file
    if(close(out_file) <0)
    {
        perror("Error: ");                                    // Error Handling
        return 0;
    } 
    return 0;
}
