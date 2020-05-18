#ifndef DEFINATION_H /* This is an "include guard" */
#define DEFINATION_H /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
char *getfield(char *line, int num);
void process();

#endif /* FOO_DOT_H */