[WJ2440]# ls  
Qt            driver_test   lib           root          udisk  
TQLedtest     etc           linuxrc       sbin          usr  
app_test      first_drv.ko  mnt           sddisk        var  
bin           first_test    opt           sys           web  
dev           home          proc          tmp  
[WJ2440]# ls -l /dev/xxx  
ls: /dev/xxx: No such file or directory  
[WJ2440]# insmod first_drv.ko   
[WJ2440]# lsmod   
first_drv 2300 0 - Live 0xbf003000  
[WJ2440]# ls -l /dev/xxx  
crw-rw----    1 root     root      252,   0 Jan  2 00:23 /dev/xxx  
[WJ2440]# ./first_test   
first_drv_open  
Usage:  
./first_test <on|off>  
[WJ2440]# ./first_test off  
first_drv_open  
first_drv_write  
[WJ2440]# ./first_test on   
first_drv_open  
first_drv_write  
[WJ2440]#   



turn off 4 LED
[WJ2440]# ./first_test off
turn on 4 LED
[WJ2440]# ./first_test on


