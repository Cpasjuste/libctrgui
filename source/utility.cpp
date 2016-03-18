#include <3ds.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sstream>
#include <vector>

#include "utility.hpp"

static FS_Archive sdmcArchive;
static bool open = false;

void Utility::debug(const char *fmt, ...) {
    char s[512];
    memset(s, 0, 512);
    va_list args;
    va_start(args, fmt);
    int len = vsprintf(s, fmt, args);
    va_end(args);
#ifdef CITRA
    svcOutputDebugString(s, len);
#else
    printf(s);
#endif
}

void Utility::openSD() {
    if(!open) {
        fsInit();
        sdmcInit();
        sdmcArchive = (FS_Archive) {0x00000009, (FS_Path) {PATH_EMPTY, 1, (u8 *) ""}};
        FSUSER_OpenArchive(&sdmcArchive);
        open = true;
    }
}
void Utility::closeSD() {
    if(open) {
        FSUSER_CloseArchive(&sdmcArchive);
        sdmcExit();
        fsExit();
    }
}

bool Utility::fileExist(const std::string &path) {
    if (path.empty())
        return false;

    Result ret;
    Handle fileHandle;

    ret = FSUSER_OpenFile(&fileHandle, sdmcArchive, fsMakePath(PATH_ASCII, path.c_str()), FS_OPEN_READ, 0);
    if (ret != 0)return false;

    ret = FSFILE_Close(fileHandle);
    if (ret != 0)return false;

    return true;
}

bool Utility::createDir(const std::string &path) {
    FS_Path filePath = fsMakePath(PATH_ASCII, path.c_str());
    return FSUSER_CreateDirectory(sdmcArchive, filePath, 0) == 0;
}

bool Utility::createDirRec(const std::string &path) {
    char tmp[512];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path.c_str());
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    for (p = tmp + 1; *p; p++)
        if (*p == '/') {
            *p = 0;
            if (!createDir(tmp))
                return false;
            *p = '/';
        }
    return createDir(tmp);
}


void Utility::reboot() {
    aptInit();
    aptOpenSession();
    APT_HardwareResetAsync();
    aptCloseSession();
    aptExit();
}

void Utility::shutdown() {
    Handle handle;
    Result ret = srvGetServiceHandle(&handle, "ptm:s");
    if (ret != 0) {
        debug("Err: srvGetServiceHandle(ptm:s)");
        return;
    }

    u32 *cmdbuf = getThreadCommandBuffer();
    cmdbuf[0] = 0x040700C0; //ShutdownAsync
    cmdbuf[1] = 0; //?
    cmdbuf[2] = 0; //?
    cmdbuf[3] = 0; //?
    ret = svcSendSyncRequest(handle);
    if (ret != 0) {
        debug("Err: srvGetServiceHandle(ptm:s)");
    }
    svcCloseHandle(handle);
}

std::vector<std::string> &Utility::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Utility::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void Utility::unicodeToChar(char *dst, char16_t *src, int max) {
    if (!src || !dst)return;
    int n = 0;
    while (*src && n < max - 1) {
        *(dst++) = (*(src++)) & 0xFF;
        n++;
    }
    *dst = 0x00;
}
