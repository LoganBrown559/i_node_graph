/*
Name: Logan Brown
Date: 4/23/20203
File: inode_scanner.c
Description: Implementation of the "i-node graph" assignment
*/
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#define dir_str_len 200


///////////////////////////
// Function Declarations //
///////////////////////////
// See implemetation at the bottom of the code
// for more deatails on each funtion


// Scans target directory recursively, add each entry to the graphviz output
void scan_dir(DIR *directory, char *pre_path, int *entry_count, FILE *output);


// Initializes the graphviz output file
void init_output(FILE *output);


// The tool that adds nodes/node connections to the graphviz output file
void connect_nodes(char *parent_node, char *child_node, FILE *output, struct stat *child_info, struct stat *parent_info);




/////////////////////
//  Main Function  //
/////////////////////
int main()
{
char current_dir[dir_str_len];
int entries_found = 0;
char output_name[50];
FILE *output;
DIR *dir_obj;


// Grab target directory name
printf("Enter Directory to start Scan (Do not end with /): ");
scanf("%s", current_dir);

// [output_name].gv, our file to be turned into a graph
printf("Enter Output Graphviz file name (remember the .gv!): ");
scanf("%s", output_name);

// We open this to write to it all over the place, very important
output = fopen(output_name, "w");

// Initialize boiler-plate things for output file
printf("\nInitializing output...");
init_output(output);

printf("\n\nDirectory Starting Point: %s\n", current_dir);
printf("Starting data collection...\n\n");

// Open up target directory
dir_obj = opendir(current_dir);
// "If we get nothing when trying to open the target directory, throw an error and exit.
//  Otherwise, scan the directory reccursively.
if(dir_obj == NULL)
{
  printf("ERROR: Directory either doesn't exist or won't let the program open it.");
  fclose(output);
  return 1;
}
else
{
  scan_dir(dir_obj, current_dir, &entries_found, output);
}

// This finishes up the syntax for the Graphviz output file
fprintf(output, "\n\n}\n");

printf("%d entries scanned!\n\n", entries_found);
fclose(output);
return 0;
}



//////////////////////////////
// Function Implementations //
//////////////////////////////



//////////////
// scan_dir //
//////////////
/*

Variables:


DIR *directory -
	Directory object that can have contents read.

char *pre_path -
	Path of the directory we are scanning, in string form.

int *entry_count -
	Pointer to an integer that keeps track of all entries processed

FILE *output -
	A pointer to the Graphviz output file. Used for passing to
	the connect_nodes function, whcih does the actual writing.


Purpose:

Being the biggest of the helper functions, this is the main heavy lifter
of the program. Firstly, hidden files are ignored, as well as the two
special directories. Then directories are picked out from normal files,
and are given paths as names instead of a simply entry->d_name. The
function recurses when a directory is found.


*/
void scan_dir(DIR *directory, char *pre_path, int *entry_count, FILE *output)
{


  struct dirent *entry;;
  struct stat entry_info;
  struct stat active_info;
  char full_path[dir_str_len];
  char active_dir[dir_str_len];
  strcpy(active_dir, pre_path);;
  DIR *next_dir;


  printf("\n***Scanning %s***\n", pre_path);


  // Start reading entries, stop when no more are found.
  while( (entry = readdir(directory)) != NULL  )
  {

    if( entry->d_name[0] == '.')
    {
      continue; // Skip this iteration, we don't want to process these (or forbid recurse them)
    }
    else
    {
      *entry_count++;
      // Full path is used to gather the stat info for the graph
      // Active (which is the original pre_path) is the directory we're scanning
      strcat(pre_path, "/");
      strcpy(full_path, (strcat(pre_path, entry->d_name)));

      stat(full_path, &entry_info);
      stat(active_dir, &active_info);

      // "If this entry is a directory, make the name a directory. Otherwise, the name is just the filename."
      if( S_ISDIR(entry_info.st_mode) )
      {
        // We use full path since this IS a directory
        connect_nodes(active_dir, full_path, output, &entry_info, &active_info);
        next_dir = opendir(full_path);
        // Recursion here
        scan_dir(next_dir, full_path, entry_count, output);
      }
      else
      {
        // We use entry->d_name here because this is a file, we don't need a full path.
        connect_nodes(active_dir, entry->d_name, output, &entry_info, &active_info);
      }

      // This resets the prepath so that entries don't stack on each other, as if subdirectories.
      strcpy(pre_path, active_dir);

    }
  }
  closedir(directory);
}



/////////////////
// init_output //
/////////////////
/*

Variables:

FILE  *output -
	A pointer to the output file, ready to write.


Purpose:

Initializes the boiler-plate things needed in a graphviz file,
can be changed for preffered taste and graphing needs. A simple tool,
an important job.


*/
void init_output(FILE *output)
{
  fprintf(output, "digraph files{\n");
  fprintf(output, "\trankdir=LR\n\tnode [shape=box];\n\n");
}




///////////////////
// connect_nodes //
///////////////////
/*

Variables:


char *parent_node -
	Name of the parent node, in string form. This is the node that points to another.

char *child_node -
	Name of the child node, in string form. This is the node that gets pointed to.

FILE *output -
	A pointer to the Graphviz output file. Where we write nodes to.

struct stat *child_info -
	This is a pointer to a struct that contains all wanted info about the child_node's
	corresponding entry.

struct stat *parent_inf -
	This is a pointer to a struct that contains all wanted info about the parent_node's
	corresponding entry.


Purpose:

Even God himself had to look away as I typed this abomination, for he could not process the
horrors that man had made.

In all seriousness, it looks gross, but works. I only had to type it once, and I will not touch
it less it explodes and never works again.


*/
void connect_nodes(char *parent_node, char *child_node, FILE *output, struct stat *child_info, struct stat *parent_info)
{

  // Writes a node connection in standard graphviz script, includeing all information wanted in a node.
  fprintf(output, "\n\t\"%s\\nSize (Bytes): %ld\\nBlocks: %ld\\nI-Node #: %ld\\nHard Links: %ld\" -> \"%s\\nSize (Bytes): %ld\\nBlocks: %ld\\nI-Node #: %ld\\nHard Links: %ld\";\n", parent_node, parent_info->st_size, parent_info->st_blocks, parent_info->st_ino, parent_info->st_nlink,
                                                                                                                                                                            child_node, child_info->st_size, child_info->st_blocks, child_info->st_ino, child_info->st_nlink);

}
