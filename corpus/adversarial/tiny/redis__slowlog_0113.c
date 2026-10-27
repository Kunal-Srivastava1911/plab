        listIter li;
        listNode *ln;
        slowlogEntry *se;

        if (c->argc == 3) {
            /* Consume count arg. */
            if (getRangeLongFromObjectOrReply(c, c->argv[2], -1,
                    LONG_MAX, &count, "count should be greater than or equal to -1") != C_OK)
                return;

            if (count == -1) {
                /* We treat -1 as a special value, which means to get all slow logs.
                 * Simply set count to the length of server.slowlog.*/
                count = listLength(server.slowlog);
            }
        }

        if (count > (long)listLength(server.slowlog)) {
            count = listLength(server.slowlog);
        }
        addReplyArrayLen(c, count);
        listRewind(server.slowlog, &li);
        while (count--) {
            int j;

            ln = listNext(&li);
            se = ln->value;
            addReplyArrayLen(c,6);
            addReplyLongLong(c,se->id);
