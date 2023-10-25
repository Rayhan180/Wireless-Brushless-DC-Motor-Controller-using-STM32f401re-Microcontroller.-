#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum {T_CHAR, T_INT, T_FLOAT, T_HEX} type_t;


/*
B  print_memory - prints a block of memory

  ptr - address of start of memory to print
  n - how many items to print
  type - what data type are the items
  label - name of the variable, or other string to print
 */
void print_memory(const void *ptr, int n, type_t type, const char *label) {
  printf("%s(%p): ", label, ptr);

  switch(type) {
  case T_CHAR:
    const char *pc = ptr;
    for(int i=0; i < n; i++) {
      if (isprint(*pc))
    printf("%c ", *pc);
      else
    printf("[0x%x] ", (unsigned char)*pc);
      pc++;
    }
    break;
    ////////////
      case T_INT:
    const int *pi;
    for(int i=0; i < n; i++) {
      printf("%d ", pi[i]);
      pi++;
    }
    break;

  case T_FLOAT:
    for(int i=0; i < n; i++) {
      printf("%f ", ((float *)ptr) [i]);
    }
    break;

  case T_HEX:
  default:
    for(int i=0; i < n; i++) {
      printf("%x", ((char *)ptr)[i]);
    }
    break;
  }
  printf("\n");
}

///////////////
void ask_password(char *s) {
  printf("password: ");
  scanf("%s", s);
}

////////////////
void ask_password_safe(char *s, int max_chars) {
printf("password: ");
  if (max_chars <= 0) return;
  int c;
  int i=0;
  while (i <= max_chars -1 ){


  c = getchar();

  if (c == EOF ||  isspace(c)){
    break;
  }
  s[i++] = (char) c;

  }

  s[i] = '\0';

}

//////////////////

char * read_string(int *length) {
  // first scanf an integer to see how many characters should be read
  // if there is a problem reading this in, return NULL and set *length to
    int num_chars;

    if (scanf("%d", &num_chars) != 1) {
        *length = 0;
        return NULL;
    }

    // Consume any remaining whitespace characters, including the newline
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        // Consume characters until a newline or EOF is encountered
    }

    char *str = (char *)malloc((num_chars + 1) * sizeof(char));

    if (str == NULL) {
        *length = 0;
        return NULL;
    }

    // Read the string including spaces up to the newline character
    if (fgets(str, num_chars + 1, stdin) == NULL) {
        free(str);
        *length = 0;
        return NULL;
    }

    // Remove the trailing newline character if present
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    *length = num_chars;
    return str;
}

///////////////////

int is_pal(char *s, int n) {
  // check paramters, if don't make sense return 0
  if (s == NULL || n <= 0) return 0;

  // loop through checking the characters, return 0 if
  // ever find characters that don't match that should
  int i, j;
  for(i=0, j=n-1; i < j; i++, j--) {
    if (s[i] != s[j]) return 0;
  }


  // return 1 if didn't fall any checks
  return 1;
}


/*
  is_double - returns 1 if the string is a "double", of the form w w
note that the overall code will be similar to is_pal

 */
int is_double(char *s, int n) {
// check paramters, if don't make sense return 0
  if (s == NULL || n <= 0) {
        return 0;
  }
// n - how long it is, how many characters to check
//need to devide j=n/2 to start  to get i++, j++
int i,j;
for ( i=0,j=n/2; j<n; i++,j++) {
// s - pointer to string
if (s[i] != s[j]) {
        return 0;
}
}
return 1;
}

////////////////

int is_triple(char *s, int n) {
// check paramters, if don't make sense return 0
  if (s == NULL || n <= 0) return 0;
int i,j,k;

for(i=0,j=n/3,k=j*2; k<n; i++,j++,k++){
// s - pointer to string
if (s[i] != s[j] || s[i] != s[k] || s[j] != s[k]) {
        return 0;
}
return 1;

}

//////////////////
int is_smallest_k(char *s, int n) {

for (int k = 2; k <= n / 2; k++) {
    int substring_length = n / k;
 int valid = 1;
    for (int i = 0; i < n; i += substring_length) {
      for (int j = i + substring_length; j < i + 2 * substring_length; j++)
{
        if (s[i] != s[j]) {
          valid = 0;
          break;
        }
      }
      if (!valid) break;
    }

    if (valid) {
      return k;
    }
  }
  return 0;
}

// print usage statement and exit
void usage() {
  printf("Usage: ./memory.o safe|unsafe [debug]\n");
  exit(0);
}

///////////////////
char msg1[12]; // global variable
char msg2[12];


int main(const int argc, const char *argv[]) {
  int mode_safe = 1;
  int debug = 1;



  // check command-line arguments
if (argc < 2) usage();

if (strcmp(argv[1],"safe") ==0) mode_safe = 1;
else if (strcmp(argv[1], "unsafe") == 0) mode_safe =0;
else usage();



  // two arrays allocated from the heap
  char *auth1 = (char *) malloc(sizeof(char)*12);
  char *auth2 = (char *) malloc(sizeof(char)*12);
  strcpy(auth1, "other");
  strcpy(auth2, "other");


    char password[12]; // local variables
  char from_user[12];
  strcpy(password,"cs500"); // the "correct" password
  strcpy(from_user,"");     // initialize to be empty


  // putting something in the global arrays
  strcpy(msg1, "hello");
  strcpy(msg2, "bye");


  // ask the user for the password until it matches the correct password
  while (strncmp(password, from_user,12) != 0) {
    // print out what is in the variables
    if (debug) {
      print_memory(msg1, 12, T_CHAR, "msg1");
      print_memory(msg2, 12, T_CHAR, "msg2");
      print_memory(auth1, 12, T_CHAR, "auth1");
      print_memory(auth2, 12, T_CHAR, "auth2");
      print_memory(password, 12, T_CHAR, "password");
      print_memory(from_user, 12, T_CHAR, "from_user");
      print_memory(ask_password, 8, T_HEX, "ask_password()");
    }

    // ask for the password again
    if (mode_safe)
      ask_password_safe(from_user, 12);
    else
      ask_password(from_user);
  }


   if (debug) {
    print_memory(msg1, 12, T_CHAR, "msg1");
    print_memory(msg2, 12, T_CHAR, "msg2");
    print_memory(auth1, 12, T_CHAR, "auth1");
    print_memory(auth2, 12, T_CHAR, "auth2");
    print_memory(password, 12, T_CHAR, "password");
    print_memory(from_user, 12, T_CHAR, "from_user");
    print_memory(ask_password, 8, T_HEX, "ask_password()");
  }


  // read in a string to test for palindrome, etc.
  int n;
  char *s = read_string(&n);
////
 if (s != NULL) {
        printf("String Length: %d\n", n);
        printf("String: %s\n", s);
        free(s); // Free the allocated memory for the string
    } else {
        printf("Failed to read the string.\n");
    }


      if (is_pal(s, n))
    printf("is a palindrome\n");

  // test: string is of the form w w (i.e. same first half as second half)

  if (is_double(s, n))
    printf("is a double\n");

  // test: string is of the form w w w

  if (is_triple(s, n))
    printf("is a triple\n");

  // test: smallest k>1 such that string is of the form w**k, if there

  if (is_smallest_k(s, n))
    printf("is a smallest k \n");

  //       exists such a k
  // only run this test if n <= 1000


  return 0;
}


//////////
