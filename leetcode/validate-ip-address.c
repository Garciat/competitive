// https://leetcode.com/problems/validate-ip-address/

static int parseV4(char* ip);
static int parseV6(char* ip);
static int ishex(char c);

const char* validIPAddress(char* ip) {
    if (strchr(ip, ':')) {
        return parseV6(ip) ? "IPv6" : "Neither";
    } else if (strchr(ip, '.')) {
        return parseV4(ip) ? "IPv4" : "Neither";
    } else {
        return "Neither";
    }
}

int parseV6(char *ip) {
    int p = 0;
    for (int i = 0; i < 8; ++i) {
        int n = 0;
        while (ishex(ip[p])) {
            n += 1;
            if (n > 4)
                return 0;
            p += 1;
        }
        if (n == 0)
            return 0;
        if (i == 7)
            break;
        if (ip[p] != ':')
            return 0;
        p += 1;
    }
    if (ip[p] != '\0')
        return 0;
    return 1;
}

int parseV4(char *ip) {
    int p = 0;
    for (int i = 0; i < 4; ++i) {
        if (ip[p] == '0' && ip[p+1] && ip[p+1] != '.')
            return 0;
        int x = 0;
        int n = 0;
        while (isdigit(ip[p])) {
            x *= 10;
            x += ip[p] - '0';
            if (x > 255)
                return 0;
            n += 1;
            p += 1;
        }
        if (n == 0)
            return 0;
        if (i == 3)
            break;
        if (ip[p] != '.')
            return 0;
        p += 1;
    }
    if (ip[p] != '\0')
        return 0;
    return 1;
}

int ishex(char c) {
    if (c >= '0' && c <= '9')
        return 1;
    if (c >= 'a' && c <= 'f')
        return 1;
    if (c >= 'A' && c <= 'F')
        return 1;
    return 0;
}
