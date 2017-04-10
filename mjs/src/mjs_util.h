/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_UTIL_H_
#define MJS_UTIL_H_

#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_util_public.h"

MJS_PRIVATE const char *opcodetostr(uint8_t opcode);
MJS_PRIVATE size_t mjs_disasm_single(const uint8_t *code, size_t i, FILE *fp);
MJS_PRIVATE const char *mjs_stringify_type(enum mjs_type t);

/*
 * Checks that the given argument is provided, and checks its type. If check
 * fails, sets error in the mjs context, and returns 0; otherwise returns 1.
 *
 * If `arg_num` >= 0, checks argument; otherwise (`arg_num` is negative) checks
 * `this`. `arg_name` is used for the error message only. If `parg` is not
 * NULL, writes resulting value at this location in case of success.
 */
MJS_PRIVATE int mjs_check_arg(struct mjs *mjs, int arg_num,
                              const char *arg_name, enum mjs_type expected_type,
                              mjs_val_t *parg);

/*
 * mjs_normalize_idx takes and index in the string and the string size, and
 * returns the index which is >= 0 and <= size. Negative index is interpreted
 * as size + index.
 */
MJS_PRIVATE int mjs_normalize_idx(int idx, int size);

#endif /* MJS_UTIL_H_ */
