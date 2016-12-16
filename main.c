#include <stdlib.h>     /* exit(), EXIT_SUCCESS */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>

void do_pam_passwd (const char *user, bool silent, bool change_expired)
{
    pam_handle_t *pamh = NULL;
    int flags = 0, ret;

    if (silent)
        flags |= PAM_SILENT;
    if (change_expired)
        flags |= PAM_CHANGE_EXPIRED_AUTHTOK;

    char hash[1024];
    struct pam_conv conv = { /*conversation*/ misc_conv, (void *)&hash[0] };

    ret = pam_start ("clish", user, &conv, &pamh);
    if (ret != PAM_SUCCESS) {
        fprintf (stderr, "clish: pam_start() failed, error %d\n", ret);
        exit (10);  /* XXX */
    }

    ret = pam_chauthtok (pamh, flags);
    if (ret != PAM_SUCCESS) {
        fprintf (stderr, "clish: %s\n", pam_strerror (pamh, ret));
        fputs ("clish: password unchanged\n", stderr);
        pam_end (pamh, ret);
        exit (10);  /* XXX */
    }

    (void) pam_end (pamh, PAM_SUCCESS);

    printf("New password hash: %s\n", &hash[0]);
}

int main(int argc, char *argv[])
{
    if ((argc < 2) || (argv[1] == '\0'))
    {
        fprintf (stderr, "Syntax is: %s [username]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Generating new password hash for user: %s\n", argv[1]);

    do_pam_passwd(argv[1], 1, 0);
    exit(EXIT_SUCCESS);
}

