#include "common/str_util.h"
#include "frozen/frozen.h"
#include "mjs/src/mjs_array.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_conversion.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_util.h"

static void mjs_op_time_systime(struct mjs *jsm)
{
    mjs_val_t ret = MJS_UNDEFINED;

    char timestr[25] = {0};
    struct timeval tv;
    struct tm *tm;

    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);
    strftime(timestr, 25, "%Y-%m-%d %H:%M:%S", tm);
    timestr[24] = '\0';

    ret = mjs_mk_object(jsm);
    mjs_set(jsm, ret, "localtime", ~0, mjs_mk_string(jsm, timestr, ~0, 1));
    mjs_set(jsm, ret, "timestamp", ~0, mjs_mk_number(jsm, time(NULL)));

    mjs_return(jsm, ret);
}

static void mjs_op_os_usleep(struct mjs *jsm)
{
    if (mjs_nargs(jsm) < 1) {
        mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "missing a value to usleep");
    } else {
        int usec = 0;
        mjs_val_t val = mjs_arg(jsm, 0);
        if (mjs_is_number(val)) {
            usec = mjs_get_int(jsm, val);
            if (usec > 0) usleep(usec);
        }
    }

    mjs_return(jsm, MJS_UNDEFINED);
}

void mjs_init_local(struct mjs *jsm, mjs_val_t o)
{
    mjs_val_t time = mjs_mk_object(jsm);
    mjs_val_t os = mjs_mk_object(jsm);

    mjs_set(jsm, o, "TIME", ~0, time);
    mjs_set(jsm, time, "systime", ~0, mjs_mk_foreign(jsm, mjs_op_time_systime));

    mjs_set(jsm, o, "OS", ~0, os);
    mjs_set(jsm, os, "usleep", ~0, mjs_mk_foreign(jsm, mjs_op_os_usleep));
}
