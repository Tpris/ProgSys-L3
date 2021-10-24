/* DO NOT MODIFY THIS FILE */

/** @file cmdpipe.h */

#ifndef _CMDPIPE_H_
#define _CMDPIPE_H_

#include <stdio.h>
#include <sys/types.h>

/* *********************************************** */
/*                     cmdopen                     */
/* *********************************************** */

/**
 * @brief The function executes a shell command and redirects its
 * standard input or output depending on the type argument.
 *
 * @details Since a pipe is by definition unidirectional, the type
 * argument may specify only reading or writing, not both; the
 * resulting stream is correspondingly read-only or write-only. The
 * return value from cmdopen() is a normal standard I/O stream that
 * must be closed with cmdclose() rather than fclose().
 *
 * @param command The command argument is a pointer to a
 * null-terminated string containing a shell command line.  This
 * command is passed to /bin/sh using the -c flag.
 *
 * @param type The type argument is a pointer to a null-terminated
 * string which must contain either "r" for reading or "w" for writing.
 * - "r": reading from the stream reads the command's
 * standard output, while the command's standard input is not
 * changed;
 * - "w": writing to such a stream writes to the standard input of the
 * command, while the command's standard output is not
 * changed.
 *
 * @param pid A pointer used to store the command shell process ID.
 *
 * @return On success, returns a pointer to an open stream that can be used to
 * read or write to the pipe; on errors, NULL is returned.
 */

FILE * cmdopen(const char *command, const char *type, pid_t * pid);

/* *********************************************** */
/*                     cmdclose                    */
/* *********************************************** */

/**
 * @brief The function closes the shell command invoked by
 * cmdopen(). More precisely, it closes the associated stream and
 * waits for the associated process to terminate.
 *
 * @param stream The standard I/O stream to close.
 *
 * @param pid The process ID of the associated shell command to wait.
 *
 * @return On success, returns the exit status of the command (as
 * returned by wait()); on errors, -1 is returned.
 */
int cmdclose(FILE * stream, pid_t pid);

#endif
