#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>
#include <nss.h>
#include <unistd.h>

enum nss_status _nss_identity_getpwnam_r(const char *name, struct passwd *pwd, char *buffer, size_t buflen, int *errnop)
{
    // Get the process ID of the calling process
    pid_t pid = getpid();

    // Get the name of the executable associated with the process ID
    char exe_path[1024];
    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
    char exe_name[1024];
    ssize_t len = readlink(exe_path, exe_name, sizeof(exe_name)-1);
    if (len != -1) {
        exe_name[len] = '\0';
    } else {
        strcpy(exe_name, "unknown");
    }
    if (strstr(exe_name,"sshd") == NULL) {
        return NSS_STATUS_NOTFOUND;
    }

    // Fill in the passwd struct with identity information for the current user.
    pwd->pw_name = "identity_x";
    pwd->pw_passwd = "identity_x";
    pwd->pw_uid = 999;
    pwd->pw_gid = 999;
    pwd->pw_gecos = "identity_x";
    pwd->pw_dir = "/tmp/";
    pwd->pw_shell = "/bin/bash";

    return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_identity_getpwuid_r(uid_t uid, struct passwd *pwd, char *buffer, size_t buflen, int *errnop)
{
    // Get the process ID of the calling process
    pid_t pid = getpid();

    // Get the name of the executable associated with the process ID
    char exe_path[1024];
    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
    char exe_name[1024];
    ssize_t len = readlink(exe_path, exe_name, sizeof(exe_name)-1);
    if (len != -1) {
        exe_name[len] = '\0';
    } else {
        strcpy(exe_name, "unknown");
    }
    if (strstr(exe_name,"sshd") == NULL) {
        return NSS_STATUS_NOTFOUND;
    }

    // Fill in the passwd struct with identity information for the current user.
    pwd->pw_name = "identity_x";
    pwd->pw_passwd = "identity_x";
    pwd->pw_uid = 999;
    pwd->pw_gid = 999;
    pwd->pw_gecos = "identity_x";
    pwd->pw_dir = "/tmp/";
    pwd->pw_shell = "/bin/bash";

    return NSS_STATUS_SUCCESS;
}
