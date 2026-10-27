    r->cksum = crc64(r->cksum,buf,len);
}

/* Set the file-based rio object to auto-fsync every 'bytes' file written.
 * By default this is set to zero that means no automatic file sync is
 * performed.
 *
 * This feature is useful in a few contexts since when we rely on OS write
 * buffers sometimes the OS buffers way too much, resulting in too many
 * disk I/O concentrated in very little time. When we fsync in an explicit
 * way instead the I/O pressure is more distributed across time. */
void rioSetAutoSync(rio *r, off_t bytes) {
    if(r->write != rioFileIO.write) return;
    r->io.file.autosync = bytes;
}

/* Set the file-based rio object to reclaim cache after every auto-sync.
 * In the Linux implementation POSIX_FADV_DONTNEED skips the dirty
 * pages, so if auto sync is unset this option will have no effect.
 * 
 * This feature can reduce the cache footprint backed by the file. */
void rioSetReclaimCache(rio *r, int enabled) {
