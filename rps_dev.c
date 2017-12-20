/*
 * /dev/rps skeleton code
 *
 * Wonsun Ahn <wahn@pitt.edu>
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>
#include "header.h"
/*
 * rps_read is the function called when a process calls read() on
 * /dev/rps.  It writes count bytes to the buffer passed in the
 * read() call.
 */


unsigned char get_random_byte(int max, int min) {
    unsigned char c;
    get_random_bytes(&c, 1);
    return c%max + min;
}

static ssize_t rps_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{

    unsigned char bufcopy;

    if(mode == 0)
        bufcopy = get_random_byte(3, 1);
    else if(mode == 1)
        bufcopy = (unsigned char)(1);
    else if(mode == 2)
        bufcopy = (unsigned char)(2);
    else if(mode == 3)
        bufcopy = (unsigned char)(3);



	int len = sizeof(unsigned char); 
	if (count < len)
		return -EINVAL; 
	
	if (copy_to_user(buf, &bufcopy, sizeof(bufcopy)))
		return -EINVAL;

	*ppos = len;

	return len;
}

/*
 * rps_write is the function called when a process calls write() on
 * /dev/rps.  It reads count bytes from the buffer passed in the
 * write() 
 */

static ssize_t rps_write(struct file * file, const char * buf, size_t count, loff_t *ppos)
{
	printk(KERN_ERR "MODE: %s", buf);

	char *zero = "0";
	char *one = "1";
	char *two = "2";
	char *three = "3";
    if(*buf == *zero)
        mode = 0;
    else if(*buf == *one)
        mode = 1;
    else if(*buf == *two)
        mode = 2;
    else if(*buf == *three)
        mode = 3;

	return count;
}



/*
 * Now we have two file operations: read, write
 */

static const struct file_operations rps_fops = {
	.owner		= THIS_MODULE,
	.read		= rps_read,
        .write          = rps_write,
};

static struct miscdevice rps_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/hello.
	 */
	"rps",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&rps_fops
};

static int __init
rps_init(void)
{
	int ret;

	/*
	 * Create the "rps" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/rps device using
	 * the default rules.
	 */
	ret = misc_register(&rps_dev);
	if (ret)
                printk(KERN_ERR "Unable to register \"Hello, world!\" misc device\n");
        else {
                printk(KERN_ERR "Registered device under <MAJOR , MINOR><%d %d>\n" , 10, rps_dev.minor);
                printk(KERN_ERR "Create device file using: mknod /dev/rps c %d %d\n", 10, rps_dev.minor);
        }

	return ret;
}

module_init(rps_init);

static void __exit
rps_exit(void)
{
	misc_deregister(&rps_dev);
}

module_exit(rps_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wonsun Ahn <wahn@pitt.edu>");
MODULE_DESCRIPTION("/dev/rps skeleton code");
MODULE_VERSION("dev");
