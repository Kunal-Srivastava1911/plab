        if (fwrite((char*)buf+nwritten,towrite,1,r->io.file.fp) == 0) return 0;
        nwritten += towrite;
        r->io.file.buffered += towrite;

        if (r->io.file.buffered >= r->io.file.autosync) {
            fflush(r->io.file.fp);

            size_t processed = r->processed_bytes + nwritten;
            serverAssert(processed % r->io.file.autosync == 0);
            serverAssert(r->io.file.buffered == r->io.file.autosync);

#if HAVE_SYNC_FILE_RANGE
            /* Start writeout asynchronously. */
            if (sync_file_range(fileno(r->io.file.fp),
                    processed - r->io.file.autosync, r->io.file.autosync,
                    SYNC_FILE_RANGE_WRITE) == -1)
                return 0;

            if (processed >= (size_t)r->io.file.autosync * 2) {
                /* To keep the promise to 'autosync', we should make sure last
                 * asynchronous writeout persists into disk. This call may block
