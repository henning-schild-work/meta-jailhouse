#define CONFIG_ARM_GIC_V2		1
#define CONFIG_MACH_SUN7I		1

/* Enable error tracing,
 * c.f. https://github.com/siemens/jailhouse/blob/master/FAQ.md
 * (Redefine macro:
 *  jailhouse/hypervisor/include/jailhouse/printk.h:trace_error(code)).
 */
#define CONFIG_TRACE_ERROR
