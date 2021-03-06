/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2015 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef FLB_IN_LIB_H
#define FLB_IN_LIB_H

#include <fluent-bit/flb_config.h>
#include <fluent-bit/flb_input.h>
#include <fluent-bit/flb_utils.h>

#define LIB_BUF_SIZE   65536*2

/* Library input configuration & context */
struct flb_in_lib_config {
    int fd;                     /* channel file descriptor */
    int buf_len;                /* read buffer length      */
    char buf[LIB_BUF_SIZE];     /* read buffer: 65Kb max   */

    int  msgp_len;              /* msgpack data length   */
    char msgp[LIB_BUF_SIZE];    /* msgpack static buffer */
};

int in_lib_init(struct flb_config *config);
int in_lib_collect(struct flb_config *config, void *in_context);
void *in_lib_flush(void *in_context, int *size);

extern struct flb_input_plugin in_lib_plugin;

#endif
