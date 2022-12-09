#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define INPUT_DELIM "\n"

void solution_a(const char *input)
{
  int current_max = 0;
  int current_sum = 0;
  int current_digit = 0;
  char prev_char = '\0';

  for (char c = *input; c != '\0'; c = *++input)
  {
    if (c == '\n')
    {
      if (prev_char == '\n')
      {
        current_max = current_sum > current_max ? current_sum : current_max;
        current_digit = 0;
        current_sum = 0;
      }
      else
      {
        current_sum += current_digit;
        current_digit = 0;
      }
    }
    else
    {
      current_digit *= 10;
      current_digit += c - 48;
    }
    prev_char = c;
  }
  printf("Solution A: %u\n", current_max);
}

void solution_b(const char *input)
{
  int max_1 = 0;
  int max_2 = 0;
  int max_3 = 0;
  int current_sum = 0;
  int current_digit = 0;
  char prev_char = '\0';

  for (char c = *input; c != '\0'; c = *++input)
  {
    if (c == '\n')
    {
      if (prev_char == '\n')
      {
        if (current_sum > max_1)
        {
          max_3 = max_2;
          max_2 = max_1;
          max_1 = current_sum;
        }
        else if (current_sum > max_2)
        {
          max_3 = max_2;
          max_2 = current_sum;
        }
        else if (current_sum > max_3)
        {
          max_3 = current_sum;
        }
        current_digit = 0;
        current_sum = 0;
      }
      else
      {
        current_sum += current_digit;
        current_digit = 0;
      }
    }
    else
    {
      current_digit *= 10;
      current_digit += c - 48;
    }
    prev_char = c;
  }

  int answer = max_1 + max_2 + max_3;
  printf("Solution B: %u\n", answer);
}

int main(int argc, char **argv)
{
  const char *filepath = "./input.txt";
  int fd = open(filepath, O_RDONLY);
  if (fd < 0)
  {
    printf("\n\"%s \" could not open\n", filepath);
    exit(1);
  }

  struct stat statbuf;
  int err = fstat(fd, &statbuf);
  if (err < 0)
  {
    printf("\n\"%s \" could not open\n", filepath);
    exit(2);
  }

  char *input_buffer = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (input_buffer == MAP_FAILED)
  {
    printf("Mapping failed\n");
    exit(3);
  }
  close(fd);

  solution_a(input_buffer);
  solution_b(input_buffer);

  err = munmap(input_buffer, statbuf.st_size);
  if (err != 0)
  {
    printf("Unmapping failed\n");
    exit(4);
  }
  return 0;
}
