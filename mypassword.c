#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
int main()
{
    FILE *f=fopen("/etc/shadow","r");
    FILE *ftmp=fopen("/home/change.tmp","w");
    
    char *user = getenv("USER");
    
    char *old = getpass("Nhap mat khau cu: ");
    struct spwd *p = getspnam(user);
    char *encrypt = crypt(old,p->sp_pwdp);
    if(strcmp(encrypt,p->sp_pwdp) == 0)
    {
        if(f==NULL)
        {
	     printf("Khong Mo Duoc File f\n");
	     return 0;
	}
	if(ftmp==NULL)
	{
	     printf("Khong Mo Duoc File ftmp\n");
	     return 0;
	}
    	char *new = getpass("Nhap mat khau moi: ");
    	char *encryptnew = crypt(new,p->sp_pwdp);
    	p->sp_pwdp = encryptnew;
    	
	char *read;
	size_t nread=0;
	while(getline(&read,&nread,f)!=-1){
	     if(strstr(read,user)) putspent(p,ftmp);
	     else fputs(read,ftmp);
	}
	
	remove("/etc/shadow");
	if(!rename("/home/change.tmp","/etc/shadow"))
	{
		printf("Doi mat khau thanh cong\n");
	}
	fclose(ftmp);
	fclose(f);
    }
    else printf("Sai mat khau");
}
