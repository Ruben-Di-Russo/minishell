/* This is the exact same code as above run through clang-format */
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define cl(x)                                                                  \
  if (x != 0 && x != 1)                                                        \
    close(x);
#define m(x) memset(x, 0, sizeof(x));
#define rw(x)                                                                  \
  while (isspace((c = getchar())))                                             \
    ;                                                                          \
  i = 0;                                                                       \
  ungetc(c, stdin);                                                            \
  while (!isspace(c = getchar())) {                                            \
    x[i++] = c;                                                                \
  }                                                                            \
  x[i] = '\0';                                                                 \
  ungetc(c, stdin);
int main() {
  char b[BUFSIZ], *cb[BUFSIZ], **eb[BUFSIZ], in[BUFSIZ], ou[BUFSIZ];
  char c, **cmd = cb, ***e = eb;
  int bi = 0, p, i, pf[2], cin, cout, next, ws[BUFSIZ], wsi = -1, o, d = 1;
run:
  m(b);
  m(cb);
  m(eb);
  bi = 0;
  *in = '\0';
  *ou = '\0';
  cmd = cb, e = eb, o = 0;
  if (d) {
    printf("$ ");
    fsync(1);
    d = 0;
  };
  while ((c = getchar()) != EOF) {
    switch (c) {
    case ' ':
      bi++;
      cmd++;
      break;
    case '|':
      bi++;
      cmd++;
      e++;
      break;
    case '>':
      if ((c = getchar()) == '>') {
        o = O_APPEND;
      } else {
        ungetc(c, stdin);
        o = O_TRUNC;
      }
      rw(ou);
      break;
    case '<':
      rw(in);
      break;
    case '\n':
      d = 1;
    case ';':
      cin = *in ? open(in, O_RDONLY) : 0;
      for (i = 0; eb[i]; i++) {
        if (!strcmp(eb[i][0], "exit")) {
          exit(0);
        }
        if (!strcmp(eb[i][0], "cd") && eb[i][1]) {
          chdir(eb[i][1]);
          goto run;
        }
        if (eb[i + 1]) {
          pipe(pf);
          next = *pf;
          cout = pf[1];
        } else {
          next = 0;
          cout = *ou ? open(ou, O_WRONLY | O_CREAT | o, 420) : 1;
        }
        if ((p = fork())) {
          cl(cin);
          cl(cout);
          cin = next;
          ws[++wsi] = p;
        } else {
          dup2(cin, 0);
          dup2(cout, 1);
          cl(next);
          execvp(eb[i][0], eb[i]);
          exit(1);
        }
      }
      while (wsi >= 0) {
        waitpid(ws[wsi--], 0, 0);
      }
      goto run;
    default:
      if (!*cmd) {
        *cmd = b + bi;
      }
      if (!*e) {
        *e = cmd;
      }
      b[bi] = c;
      bi++;
      break;
    }
  }
}