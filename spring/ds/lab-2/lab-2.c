#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

char *join_paths(char *path_1, char *path_2) {
  /*
   * joins two paths with '/' if necessary
   */

  char *retval, *seperator;

  if (path_1[strlen(path_1) - 1] == '/' || path_2[0] == '/')
    seperator = "";
  else if (path_1[strlen(path_1) - 1] == '/' && path_2[0] == '/') {
    path_1[strlen(path_1) - 1] = '\0';
    seperator = "";
  } else
    seperator = "/";

  if (asprintf(&retval, "%s%s%s", path_1, seperator, path_2) == -1)
    return NULL;
  else
    return retval;
}

int depth_first_apply(char *pathname, int pathfun(char *pathname)) {
  /*
   * apply function 'pathfun' to each file in directory
   */

  DIR *directory;
  struct dirent *directory_entry;
  char *absolute_path;
  int funret, ret = 0;

  if ((directory = opendir(pathname)) == NULL) {
    perror("Cannot open directory");
    return -1;
  }

  /* iterate over directory */
  while ((directory_entry = readdir(directory)) != NULL) {
    if (strcmp(directory_entry->d_name, ".") == 0
        || strcmp(directory_entry->d_name, "..") == 0)
        continue;

    absolute_path = join_paths(pathname, directory_entry->d_name);
    if (absolute_path != NULL) {
      if ((funret = pathfun(absolute_path)) != -1) ret += funret;
      free(absolute_path);
    }
  }

  if (closedir(directory) == -1) {
    perror("Failed to close directory");
    return -1;
  }

  return ret;
}

int path_size(char *pathname) {
  /*
   * Finds the size of a file or directory recursively, in bytes
   */

  /* stat file */
  struct stat path_stat;
  if (lstat(pathname, &path_stat) == -1) {
    perror("Cannot stat");
    return -1;
  }

  /* recurse if directory */
  if (S_ISDIR(path_stat.st_mode))
    return depth_first_apply(pathname, path_size);
  else
    return (int)path_stat.st_size;
}

int main(int argc, char** argv) {
  int size;
  if (argc != 2) {
    printf("Usage: %s path\n", argv[0]);
    return 1;
  }

  if ((size = path_size(argv[1])) == -1)
    return 1;

  printf("%d bytes\n", size);
  return 0;
}