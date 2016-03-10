/**
 * @file retarget.h
 * Header file contains minimal functions for retargeting STDIO operations.
 * @author Ivan Pavic
 */
#ifndef RETARGET_H
#define RETARGET_H

void retarget_init();

int _write (int fd, char *ptr, int len);

int _read (int fd, char *ptr, int len);

void _ttywrch(int ch);

#endif
