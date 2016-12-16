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

void do_pam_passwd(const char *user, bool silent, bool change_expired)
{
    pam_handle_t * pamh  = NULL;
    int            flags = 0;
    int            ret;

    if (silent) flags |= PAM_SILENT;
    if (change_expired) flags |= PAM_CHANGE_EXPIRED_AUTHTOK;

    char            hash[1024];
    struct pam_conv conv = { misc_conv, (void *)&hash[0] };

    /* The 1st argument to pam_start() (i.e. "clish") identifies which
     * file in the directory /etc/pam.d (i.e. /etc/pam.d/clish) will be
     * used to retrieve the PAM configuration.
     */
    ret = pam_start("clish", user, &conv, &pamh);
    if (ret != PAM_SUCCESS)
    {
        fprintf(stderr, PROGRAM ": pam_start() failed, error %s\n",
                pam_strerror(pamh, ret));
        exit(EXIT_FAILURE);
    }

    ret = pam_chauthtok(pamh, flags);
    (void)pam_end(pamh, ret);

    if (ret != PAM_SUCCESS)
    {
        fprintf(stderr, PROGRAM ": pam_chauthtok() failed, error %s\n",
                pam_strerror(pamh, ret));
        exit(EXIT_FAILURE);
    }

    printf("New password hash: %s\n", &hash[0]);
}

int main(int argc, char *argv[])
{
    if ((argc < 2) || (argv[1] == '\0'))
    {
        fprintf(stderr, "Syntax is: " PROGRAM " [username]\n");
        exit(EXIT_FAILURE);
    }

    printf("Generating new password hash for user: %s\n", argv[1]);

    do_pam_passwd(argv[1], 1, 0);
    exit(EXIT_SUCCESS);
}

