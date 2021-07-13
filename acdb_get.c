/*
 * Copyright (C) 2017-2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>

typedef int (*platform_get_snd_device_acdb_id_t)(int);
typedef const char *(*platform_get_snd_device_name_t)(int);

int main() {
    void *handle;
    platform_get_snd_device_acdb_id_t platform_get_snd_device_acdb_id;
    platform_get_snd_device_name_t platform_get_snd_device_name;
    unsigned int device_id;
    int device_acdb;

    handle = dlopen("audio.primary.kona.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    platform_get_snd_device_acdb_id = (platform_get_snd_device_acdb_id_t) dlsym(handle, "platform_get_snd_device_acdb_id");

    if (!platform_get_snd_device_acdb_id)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    platform_get_snd_device_name = (platform_get_snd_device_name_t) dlsym(handle, "platform_get_snd_device_name");

    if (!platform_get_snd_device_name)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    printf("    <acdb_ids>\n");
    for (device_id = 1; device_acdb = platform_get_snd_device_acdb_id(device_id), device_acdb != -EINVAL; device_id++)
        printf("        <device name=\"%s\" acdb_id=\"%i\"/>\n", platform_get_snd_device_name(device_id), device_acdb);
    printf("    </acdb_ids>\n");

    dlclose(handle);
    return 0;
}
