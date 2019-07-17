# nullfs

Try to implement a file system that works like `/dev/null`, 
any files copied or moved into it would just disappear.

## Build

```bash
make
```

## Usage

```bash
./nullfs <mountpoint>
```

## Test

```bash
$ ./nullfs mnt/
$ ls mnt/hello
mnt/hello
$ cp nullfs.c mnt
$ ls mnt/
ls: reading directory 'mnt': Function not implemented
$ mv hello mnt/
mv: cannot create regular file 'mnt/hello': File exists
$ mkdir mnt2
$ cp -r mnt2/ mnt
cp: cannot overwrite non-directory 'mnt/mnt2' with directory 'mnt2/'
```

## Analysis

Use `strace` to analyze the reason of failures.

```bash
$ touch hello
$ strace mv hello mnt/
...
access("mnt/hello", W_OK)               = 0
rename("hello", "mnt/hello")            = -1 EXDEV (Invalid cross-device link)
unlink("mnt/hello")                     = 0
openat(AT_FDCWD, "hello", O_RDONLY|O_NOFOLLOW) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=0, ...}) = 0
openat(AT_FDCWD, "mnt/hello", O_WRONLY|O_CREAT|O_EXCL, 0600) = -1 EEXIST (File exists)
...
```

`mv` will call `rename` to move the file. Since the source file and the target file was not in the same file system, it returns `EXDEV` indicating an `Invalid cross-device link` error.

`mv` will then give up to call `rename`, turn to copy file first and then delete it. It will `unlink` the target file and create a new one, and copy the file content. But it fails to create a new file because the `openat` call returns `EEXIST` indicating the target file exists.

Therefore, it's impossible to move file to nullfs.

```bash
$ strace cp -r mnt2/ mnt
...
lstat("mnt/mnt2", {st_mode=S_IFREG|0755, st_size=0, ...}) = 0
...
```

`lstat` call is corresponding to `nullfs_getattr` function, which couldn't
judge whether `mnt/mnt2` is a regular file or directory.

Therefore, it's impossible to copy directories to nullfs.
