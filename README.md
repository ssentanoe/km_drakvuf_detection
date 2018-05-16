# DRAKVUF PRESENCE DETECTION

## How to use
* Enable debug in DRAKVUF
* Set a breakpoint and run DRAKVUF
* In the target machine, clone this code and put the RPA address from the debug
* information for _BP1_ and _my\_ptr1_
```
Trap added @ PA 0x38ed7930 RPA 0xff006930 Page 233175 for name.
```
* Put the second address for _BP2_ and _my\_ptr2_ where the offset should be the same, for instance 0xff00**7**930
* Compile
```
make
```
* Load the kernel module
```
insmod detect.ko
```
* Look at the _kern.log_
```
tail -f /var/log/kern.log
```
