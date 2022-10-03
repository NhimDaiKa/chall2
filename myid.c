#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <unistd.h>

int main() {
    char name[100]={0};
    struct passwd *p;
    scanf("%s", name);
    p = getpwnam(name);
    int ngroups = 0;
    if (p != NULL) 
    {
        printf("Username:"); puts(p->pw_name);
        printf("Home directory: "); puts(p->pw_dir);
        printf("User id: %d\n", p->pw_uid);
        
        struct group* gr = getgrgid(p->pw_gid);
        getgrouplist(p->pw_name, p->pw_gid, NULL, &ngroups);
        __gid_t groups[ngroups];
        getgrouplist(p->pw_name, p->pw_gid, groups, &ngroups);
        printf("Group: ");
        for (int i = 0; i < ngroups; i++) 
        {
            struct group* gr = getgrgid(groups[i]);
            puts(gr->gr_name);
        }
        printf("\n");
    }
    else printf("Khong ton tai nguoi dung %s\n", name);
}
