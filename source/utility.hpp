#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

#define CACHE_DIR "/cmenu/cache"

class Utility {
public:
    static void openSD();

    static void closeSD();

    static void debug(const char *fmt, ...);

    static bool fileExist(const std::string &path);

    static bool createDir(const std::string &path);

    static bool createDirRec(const std::string &path);

    static void reboot();

    static void shutdown();

    static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

    static std::vector<std::string> split(const std::string &s, char delim);

    static void unicodeToChar(char *dst, char16_t *src, int max);
};

#endif
