
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>

int main()
{
    //Enable gpio17
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "17", 2);
    close(fd);

    //Set gpio17 as input
    fd = open("/sys/class/gpio/gpio17/direction", O_WRONLY);
    write(fd, "in", 2);
    close(fd);

    //Set gpio17 interrupt
    fd = open("/sys/class/gpio/gpio17/edge", O_WRONLY);
    //write(fd, "falling", 7);
    write(fd, "both", 4);
    close(fd);

    //Wait for event
    fd = open("/sys/class/gpio/gpio17/value", O_RDONLY);

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLPRI;

    for(int i=0; i<10; i++)
    {
        lseek(fd, 0, SEEK_SET);
        int ret = poll(&pfd, 1, 3000);
        char c;
        read(fd, &c, 1);
        if(ret == 0)
            printf("Timeout\n");
        else
            if(c == '0')
                printf("Push\n");
            else
                printf("Release\n");
    }
    close(fd);

    //Disable gpio17
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, "17", 2);
    close(fd);

    return(0);
}


