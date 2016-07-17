#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/init.h>
#include <asm/uaccess.h>

#define    GPFSEL0   0x3f200000   /* function select register */
#define    GPSET0    0x3f20001c   /* bit set */
#define    GPCLR0    0x3f200028   /* bit clear */
#define    GPLEV0    0x3f200034   /* level holder register */

volatile int *gpio_fsel;
volatile int *gpio_clr;
volatile int *gpio_set;
volatile int *gpio_level;

ssize_t gpio_read(struct file *fp, char *buff, size_t n, loff_t *f)
{
    int val, i;
    val = *gpio_level;
    i = copy_to_user(buff, &val, 4);
    return 4;
}

ssize_t gpio_write(struct file *fp, const char *buff, size_t n, loff_t *f)
{
    int val, i;
    i = copy_from_user(&val, buff, 4);
    printk("write %d\n", val);
    val = val & 4;
    if (val)
        *gpio_set = val;
    else
        *gpio_clr = (~val & 4);
    return 4;
}

int gpio_open(struct inode *node, struct file *fp)
{
    int var = *gpio_fsel;
    var &= ~(7<<6);
    var |= (1<<6);             /* set GPIO2 as output (001) */
    printk("GPFSEL = %x\n", var);
    *gpio_fsel = var;
    return 0;
}

int gpio_close(struct inode *node, struct file *fp)
{
    return 0;
}

struct file_operations gpio = {
    read: gpio_read,
    write: gpio_write,
    open: gpio_open,
    release: gpio_close,
};

int init_module()
{
    int n;
    n = register_chrdev(123, "gpiogpio", &gpio);
    if(n==0) {
        printk("device registered\n");

        gpio_fsel  = ioremap(GPFSEL0, 4);
        gpio_set   = ioremap(GPSET0, 4);
        gpio_clr   = ioremap(GPCLR0, 4);
        gpio_level = ioremap(GPLEV0, 4);
        return 0;
    } else
        return -1;
}

void cleanup_module()
{
    unregister_chrdev(123, "gpiogpio");
    iounmap(gpio_fsel);
    iounmap(gpio_set);
    iounmap(gpio_clr);
    iounmap(gpio_level);
    printk("device removed\n");
}

