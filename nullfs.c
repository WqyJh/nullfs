/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall null.c `pkg-config fuse --cflags --libs` -o null
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>

static int nullfs_getattr(const char *path, struct stat *stbuf)
{
	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0)
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 1;
	}
	else
	{
		stbuf->st_mode = S_IFREG | 0755;
	}

	return 0;
}

static int nullfs_truncate(const char *path, off_t size)
{
	return 0;
}

static int nullfs_open(const char *path, struct fuse_file_info *fi)
{
	return 0;
}

static int nullfs_read(const char *path, char *buf, size_t size,
					   off_t offset, struct fuse_file_info *fi)
{
	return size;
}

static int nullfs_write(const char *path, const char *buf, size_t size,
						off_t offset, struct fuse_file_info *fi)
{
	return size;
}

static int nullfs_unlink(const char *path)
{
	return 0;
}

static int nullfs_rename(const char *src, const char *dst)
{
	return 0;
}

int nullfs_utimens(const char *path, const struct timespec tv[2])
{
	return 0;
}

static struct fuse_operations nullfs_oper = {
	.getattr = nullfs_getattr,
	.truncate = nullfs_truncate,
	.open = nullfs_open,
	.read = nullfs_read,
	.write = nullfs_write,
	.unlink = nullfs_unlink,
	.rename = nullfs_rename,
	.utimens = nullfs_utimens,
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &nullfs_oper, NULL);
}
