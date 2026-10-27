                 * if last writeout is not finished since disk is slow. */
                if (sync_file_range(fileno(r->io.file.fp),
                        processed - r->io.file.autosync*2,
                        r->io.file.autosync, SYNC_FILE_RANGE_WAIT_BEFORE|
                        SYNC_FILE_RANGE_WRITE|SYNC_FILE_RANGE_WAIT_AFTER) == -1)
                    return 0;
            }
#else
            if (redis_fsync(fileno(r->io.file.fp)) == -1) return 0;
#endif
            if (r->io.file.reclaim_cache) {
                /* In Linux sync_file_range just issue a writeback request to
                 * OS, and when posix_fadvise is called, the dirty page may
                 * still be in flushing, which means it would be ignored by
                 * posix_fadvise.
                 * 
                 * So we posix_fadvise the whole file, and the writeback-ed 
                 * pages will have other chances to be reclaimed. */
