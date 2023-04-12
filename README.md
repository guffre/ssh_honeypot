# SSH Logging

The goal of this project is to log both the username and password of SSH login attempts.

# Background

The starting point of this project is "I want to log what passwords my ssh server is receiving". I will attempt to breakdown all the steps involved, starting with what components you will need and why.

The end result is producing two modules: a PAM module and an NSS module.

Used in conjuction, the PAM module will store the username and plaintext password into a sqlite3 database. The NSS module will prevent the sshd service from obfuscating passwords for users that don't exist on the system.

# Components

| Component | Function |
| --- | --- |
| PAM Module | Saves the actual username and password into a database |
| /etc/pam.d/sshd | Tells the OS to use the PAM module |
| NSS Module | sshd makes a call to `getpwnam` to check if the username is valid. If sshd detects an invalid username, a function called `fake_password` changes the password bytes to \x08\x0a\x0d\x7fINCORRECT |
| /etc/nsswitch.conf | Tells the OS to use the NSS module |

# PAM Module

PAM is normally used to authenticate SSH login attempts that use a password. This configuration can be found in `/etc/ssh/sshd_config`:

```
# Set this to 'yes' to enable PAM authentication, account processing,
# and session processing. If this is enabled, PAM authentication will
# be allowed through the KbdInteractiveAuthentication and
# PasswordAuthentication.  Depending on your PAM configuration,
# PAM authentication via KbdInteractiveAuthentication may bypass
# the setting of "PermitRootLogin prohibit-password".
# If you just want the PAM account and session checks to run without
# PAM authentication, then enable this but set PasswordAuthentication
# and KbdInteractiveAuthentication to 'no'.
UsePAM yes
```

Telling sshd to use PAM results in a configuration file found at `/etc/pam.d/sshd`

We will write our own implementation of `pam_sm_authenticate` in order to capture the plaintext password, and then store the username and password into a sqlite3 database. To compile you will need the `libpam0g-dev` and `libsqlite3-dev` packages.

On Ubuntu these can be installed with:

```
apt-get install libpam0g-dev
apt-get install libsqlite3-dev
```

After compiling, the PAM module should be placed into the `/usr/lib/x86_64-linux-gnu/security/` directory:

```
make
chmod 644 pam_logpassword.so
cp pam_logpassword.so /usr/lib/x86_64-linux-gnu/security/pam_logpassword.so
```

# /etc/pam.d/sshd

At the top of `/etc/pam.d/sshd` the following line should be added. This line tells PAM to use our module and "authenticate" against it.

```
auth      optional  pam_logpassword.so
```

# NSS Module

Unfortunately, our work is not done. sshd makes a call to `getpwnam` to check if the username is valid.

From the man page:

> The getpwnam() function returns a pointer to a structure containing the broken-out fields of the record in the password database (e.g., the local password file /etc/passwd, NIS, and LDAP) that matches the username name.

If the username is not valid, the sshd logic will wind up at a function called `fake_password`. This function will obfuscate the password, ruining our efforts to collect the plaintext.

This function is found in the `auth-pam.c` file in openssh-portable.

```c
/*
 * Returns a junk password of identical length to that the user supplied.
 * Used to mitigate timing attacks against crypt(3)/PAM stacks that
 * vary processing time in proportion to password length.
 */
static char *
fake_password(const char *wire_password)
{
    const char junk[] = "\b\n\r\177INCORRECT";
    char *ret = NULL;
    size_t i, l = wire_password != NULL ? strlen(wire_password) : 0;

    if (l >= INT_MAX)
        fatal("%s: password length too long: %zu", __func__, l);

    ret = malloc(l + 1);
    if (ret == NULL)
        return NULL;
    for (i = 0; i < l; i++)
        ret[i] = junk[i % (sizeof(junk) - 1)];
    ret[i] = '\0';
    return ret;
}
```

This NSS module code will respond to the `getpwnam` call, check if the call originates from a process that has `sshd` in the filename, and then respond with fake positive data.

# /etc/nsswitch.conf

In order to tell the OS to use our NSS module, we need to add it into the `/etc/nsswitch.conf` file.

This addition looks like this:

```
passwd:         files systemd identity
group:          files systemd identity
shadow:         files identity
```

This will tell the system to use the `identity` NSS service provider module to resolve user and group identities.
