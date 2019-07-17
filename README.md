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
```