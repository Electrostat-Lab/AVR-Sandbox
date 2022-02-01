#ifndef FILE
struct FILE;
#endif

#define L_tmpnam 50

extern FILE* fopen (const char * __filename, const char * __modes);
extern FILE* freopen (const char * __filename, const char * __modes, FILE * __stream);
extern int fclose (FILE * __stream);
extern int _fflush (FILE *__stream);
extern int fseek (FILE * __stream, long off, int whence);
extern long ftell (FILE * __stream);
extern int remove (const char * __filename);
extern int rename (const char * __oldfilename, const char *__newfilename);
extern void rewind (FILE *__stream);
extern void setbuf (FILE * __stream, char * __buf);
extern FILE* tmpfile (void);
extern char* tmpnam (char *str);

#ifdef clearerr
#undef clearerr
#endif
extern void clearerr (FILE *__stream);

extern void __transmit (uint8_t __data);
extern uint8_t __receive (void);
