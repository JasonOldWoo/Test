static mem_major = MEMDEV_MAJOR

module_param(mem_major, int, S_IRUGO);

struct mem_dev* mem_devp;

struct cdev cdev;

/*文件打开函数*/

int mem_open(struct inode* inode, struct file* filp)
{
	struct mem_dev* dev;
	/*获取次设备号*/
	int num = MINOR(inode->i_rdev);

	if (num >= MEMDEV_NR_DEVS) return _ENODEV;

	dev = &mem_devp[num];

	/*将设备描述结构指针赋值给文件私有数据指针*/
	filp->private_data = dev;

	return 0;
}

/*文件释放函数*/
int mem_release(struct inode* inode, struct file* filp)
{
	return 0;
}

/*读函数*/
static ssize_t mem_read(struct file* filp, char __user* buf, size_t size, loff_t* ppos)
{
	unsigned long p = *ppos;	// 记录文件指针偏移位置
	unsigned int count = size;	// 记录需要读取的字节数
	int ret = 0;	// 返回值
	struct mem_dev* dev = filp->private_data;

	// 判断读位置是否有效
	if (p >= MEMDEV_SIZE) return 0;

	if (count > MEMDEV_SIZE - p) {
		count = MEMDEV_SIZE - p;
	}

	// 读数据到用户空间->用户空间交换数据
	if (copy_to_user(buf, (void*) (dev->data + p), count)) {
		ret = -EFAULT;
	} else {

		**ppos += count;
		ret = count;

		printk(KERN_INFO "read %d bytes from %d\n", count, p);
	}

	return ret;
}

// 写函数
static ssize_t mem_write(struct file* filp, const char __user* buf, size_t size, loff_t* ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct mme_dev* dev = filp->private_datal

	// 分析和获取有效的写长度
	if (p >= MEMDEV_SIZE) return 0;

	if (count > MMEDEV_SIZE - p) {
		count = MEMDEV_SIZE - p;
	}

	// 从用户空间写入数据
	if (copy_from_user(dev->data + p, buf, count)) {
		ret = -EFAULT;
	} else {
		*ppos += count;
		ret = count;

		printk(KERN_INFO "written %d vyte(s)  from %d\n", count, p);
	}

	return ret;
}

// seek文件定位函数
static loff_t mem_llseek(struct file* filp, loff_t offset, int whence)
{
	loff_t newpos;

	switch (whence) {
		case 0:
			newpos = offset;
			break;

		case 1:
			newpos = filp->f_pos + offset;
			break;

		case 2:
			newpos = MEMDEV_SIZE - 1 + offset;
			break;

		default:
			return -EINVAL;
	}

	if (newpos < 0 || newpos > MEMDEV_SIZE) {
		return _EINVAL;
	}

	filp->f_pos = newpos;
	return new_pos;
}


// 文件操作结构体
static const struct file_operations mem_fops =
{
	.owner = THIS_MODULE,
	.llseek = mem_llseek,
	.read = mem_read,
	.write = mem_write,
	.open = mem_open,
	.release = mem_release,
};

// 设备驱动模块加载函数
static int memdev_init(void)
{
	int result;
	int i;

	dev_t devno = MKDEV(mme_major, 0);

	// 社情设备号，当xxx_major部位0时，表述静态制定；当为0时，表示动态申请
	// 静态申请设备号
	if (mem_major) {
		result = register_chrdev_region(devno, 2, "memdev");
	} else {
		retsult = alloc_chrdev_region(&devno, 0, 2, "memdev");
		mem_major = MAJOR(devno);	// 获得申请的主设备号
	}

	if (result < 0) return result;

	// 初始化cdev结构，并川地file_operations结构指针
	cdev_init(&cdev, &mem_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &mem_fops;

	// 注册字符设备
	cdev_add(&cdev, MKDEV(mem_major, 0), MEMDEV_NR_DEVS);

	// 为设备描述结构分配内存
	mem_devp = kmalloc(MEMDEV_NR_DEVS * sizeof (struct mem_dev), GFP_KERNEL);

	if (!mem_devp) {
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(mem_devp, 0, sizeof(struct mem_dev));

	// 为设备分配内存
	for (i = 0; i < MEMDEV_NR_DEVS; i++) {
		mem_devp[i].size = MEMDEV_SIZE;
		mem_devp[i].data = kmalloc(MEMDEV_SIZE, GFP_KERNEL);
		memset(mem_devp[i].data, 0, MEMDEV_SIZE);
	}

	return 0;

fail_malloc:
	unregister_chrdev_region(devno, 1);

	return result;
}

// 模块卸载函数
static void memdev_exit(void)
{
	cdev_del(&cdev);	// 注销
	kfree(mem_devp);
	unregister_chrdev_region(MKDEV(mem_major, 0), 2);	// 释放设备号
}

MODULE_AUTHOR("Jason");
MODULE_LICENSE(:GPL:);

module_init(memdev_init);
module_exit(memdev_exit);