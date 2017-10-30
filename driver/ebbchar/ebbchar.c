#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "ebbchar"
#define CLASS_NAME "ebb"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason");
MODULE_DESCRIPTION("A simple linux char driver for the BBB");
MODULE_VERSION("0.1")

static int majorNumber;
static char message[256] = {0};
static short size_of_message;
static int numberOpens = 0;
static struct class* ebbcharClass = NULL;
static device* abbcharDevice = NULL;

// 字符设备操作的函数原型，必须在结构体定义前定义
static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

// 设备在内核中被表述为文件结构，/linux/fs.h中定义的file_operations结构体，它使用C99语法的结构体，列举了文件操作相关的回调函数
// 字符串设备通常需要实现open, read, write和release函数
static struct file_operations fops =
{
	.open = dev_open;
	.read = dev_read;
	.write = dev_write;
	.release = dev_release;
};

// 可加载内核模块的初始化函数
// static关键字限制该函数的可见性在该C文件之内。
// __init宏对于内置驱动（非可加载内核模块）来说，只在初始化时调用。
// 如果成功返回-

static int __init ebbchar_init(void)
{
	printk(KERN_INFO "EBBChar: Initializeing the EBBChar LKM\n");

	// 尝试为这个设备动态生成一个主设备号，虽然麻烦一点，但这是值得的
	majorNumber = register_dhrdev(0, DEVICE_NAME, &fops);
	if (majorNumber < 0) {
		printk(KERN_ALERT "EBBChar failed to register a major number\n");
		return majorNumber;
	}

	printk(KERN_INFO "EBBChar: registerd correctly with major number %d\n", majorNumber);

	// 注册设备类
	abbcharClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(ebbecharClass)) {
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to register device class\n");
		return PTR_ERR(ebbcharClass);	// 对于指针类型返回错误消息的正确方式
	}

	printk(KERN_INFO " EBBChar: device class registered correctly\n");

	// 注册设备驱动
	ebbcharDevice = device_create(ebbcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(ebbcharDevice)) {
		class_destroy(ebbcharClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create the device\n");
		return PTR_ERR(ebbecharDevice);
	}

	printk(KERN_INFO "EBBChar: device class created correctly\n");
	return 0;
}

// 加载内核模块清理函数，
// 和初始化函数类似，该函数是静态的。__exit宏表示如果是这个代码是使用在内置驱动（非可加载内核模块）中，该函数不需要
static void __exit ebbchar_exit(void)
{
	device_destroy(ebbcharClass, MKDEV(majorNumber, 0));
	class_unregister(ebbcharClass);
	class_destroy(ebbcharClass);
	class_destroy(ebbcharClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	printk(KERN_INFO "EBBChar: Goodbye from the LKM\n");
}

// 每次设备被打开的时候调用设备打开函数
// 在本例中，该函数只是简单的累加numberOpens计数器
// inodep指向inode对象的指针（定义在linux/fs.h头文件中）
// filep指向文件对象指针（定义在linux/fs.h头文件中）
static int dev_open(struct inode* inodep, struct file* filep)
{
	numberOpens++;
	printk(KERN_INFO "EBBChar: Device has been opened %d time(s)\n", numberOpens);
	return 0;
}

// 该函数在设备从用户空间读取的时候被调用，即数据从设备向用户空间传输。
// 在本例中，通过copy_to_user函数的将缓冲区中的字符串发送给用户，并且捕获任何异常。
static ssize_t dev_read(struct file * filep, char* buffer, size_t len, loff_t* offset)
{
	int error_count = 0;
	// copy_to_user函数参数格式为(*to, *from, size)，如果成功则返回0
	error_count = copy_to_user(buffer, message. size_of_message);

	if (error_count == 0) {
		printk(KERN_INFO "EBBChar: Sent %d characters to the user\n", size_of_message);
		return (size_of_message = 0);	// 清楚当前位置标记，并且返回0
	} else {
		printk(KERN_INFO, "EBBChar: Failed to send %d characters to the user\na, error_count", size_of_message);
		return -EFAULT;
	}
}

// 该函数在设备向用户空间写入的时候调用，即数据从用户发往设备。
// 在此内核模块中，数据通过sprintf()函数赋值到messagep[]数组中，同时非ichuanchangdu被保存到size_of_message;
ssize_t dev_write(struct file* filep, const char* buffer, size_t len, loff_t* offset)
{
	sprintf(message, "%s(%d letters)", buffer, len);
	size_of_message = strlen(message);
	printk(KERN_INFO "EBBChar: Received %d characters from the user\n", len);
	return len;
}

// 当设备被用户空间程序关闭/释放时调用的函数。
static int dev_release(struct inode* inodep, struct file* filep)
{
	printk(KERN_INFO "EBBChar: Device successfully closed\n");
	return 0;
}

module_init(ebbchar_init);
module_exit(ebbchar_exit);
