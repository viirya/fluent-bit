/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit - Output data to Treasure Data
 *  =========================================
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

#include <unistd.h>
#include <fluent-bit.h>

int main(int argc, char **argv)
{
    int i;
    int n;
    int ret;
    char tmp[256];
    struct flb_config *config;

    if (argc < 2) {
        fprintf(stderr, "Usage: td /path/to/configuration.file\n");
        exit(EXIT_FAILURE);
    }

    /* Create configuration context */
    config = flb_config_init();
    if (!config) {
        exit(EXIT_FAILURE);
    }

    /* Enable verbose messages */
    flb_config_verbose(FLB_TRUE);

    /* Load a configuration file (required by TD output plugin) */
    ret = flb_lib_config_file(config, argv[1]);

    /* Initialize library */
    ret = flb_lib_init(config, (char *) "td");
    if (ret != 0) {
        exit(EXIT_FAILURE);
    }

    /* Start the background worker */
    flb_lib_start(config);

    /* Push some data */
    for (i = 0; i < 100; i++) {
        n = snprintf(tmp, sizeof(tmp) - 1, "{\"key\": \"val %i\"}", i);
        flb_lib_push(config, tmp, n);
    }

    flb_lib_stop(config);

    return 0;
}
