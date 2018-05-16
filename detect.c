#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stewart Sentanoe");
MODULE_DESCRIPTION("A simple Linux driver for detect DRAKVUF presence");
MODULE_VERSION("0.1");

static int __init detect_init(void){
	//declare 2 pointers
	unsigned char *my_ptr1;
	unsigned char *my_ptr2;
	
	//need to use this function since DRAKVUF will add another memory
	//beyond the physical 
	request_mem_region((unsigned long)0xff006930,2,"BP1");

	//point the first pointer to the shadow copy address (RPA)
	my_ptr1 = (unsigned char *) ioremap((unsigned long)0xff006930,2);
	
	//write 'A' to it
	writeb('A',my_ptr1);

	//check if 'A' is there
	printk(KERN_INFO "BP1: %02X\n", *my_ptr1);
	
	//unmap
	iounmap(my_ptr1); 
		
	//point to the second address where we expect 'A' to be there
	request_mem_region((unsigned long)0xff007930,2,"BP2");
	my_ptr2 = (unsigned char *) ioremap((unsigned long)0xff007930,2);
	
	//print the content of BP2
	printk(KERN_INFO "BP2: %02X\n", *my_ptr2);

	if(*my_ptr2 == 'A')
		printk(KERN_INFO "DRAKVUF detected");
	else
		printk(KERN_INFO "Seems DRAKVUF is not there");
   	
	return 0;
}


static void __exit detect_exit(void){
}

module_init(detect_init);
module_exit(detect_exit);
