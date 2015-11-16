
#define GPGCON              (*((volatile unsigned long *)0x56000060))
#define BUTTONS_CON         ((2<<0)|(2<<6)|(2<<10)|(2<<12)|(2<<14)|(2<<22))
#define BUTTONS_MSK         ((3<<0)|(3<<6)|(3<<10)|(3<<12)|(3<<14)|(3<<22))
#define SRCPND              (*((volatile unsigned long *)0x4A000000)) 
#define INTMOD              (*((volatile unsigned long *)0x4A000004))
#define INTMSK              (*((volatile unsigned long *)0x4A000008))
#define PRIORITY            (*((volatile unsigned long *)0x4A00000c))
#define INTPND              (*((volatile unsigned long *)0x4A000010))
#define INTOFFSET           (*((volatile unsigned long *)0x4A000014))
#define SUBSRCPND           (*((volatile unsigned long *)0x4A000018))
#define INTSUBMSK           (*((volatile unsigned long *)0x4A00001c))

#define EINTMASK            (*((volatile unsigned long *)0x560000a4)) 
#define EINTPEND            (*((volatile unsigned long *)0x560000a8))

void button_irq_init()
{

    /***configure Pins as EINT ***/
    GPGCON &= ~BUTTONS_MSK;
    GPGCON |= BUTTONS_CON;
    
    /***enable irqs in EINTMASK***/
    EINTMASK &= (~(1<<8)) & (~(1<<11)) & (~(1<<13)) & (~(1<<14)) & (~(1<<15))& (~(1<<19));
    
    /***enable irqs in INTMSK***/
    INTMSK &=~(1<<5);        
     /***enable irqs in cpsr***/
     __asm__(
    "mrs r0,cpsr\n"
    "bic r0, r0, #0x80\n"
    "msr cpsr_c, r0\n"            
    : 
    : 
    );
}
void irqs_init()
{
    button_irq_init();
}

void handle_int()
{
    /**read irq source**/
    unsigned long irq_source = EINTPEND &((1<<8)|(1<<11)|(1<<13)|(1<<14)|(1<<15)|(1<<19));
    switch(irq_source)
    {
        case (1<<8):
        	led_on();
        	break;
        case (1<<11):
        	led_off();
        	break;        		
        case (1<<13):
        	led_on();
        	break; 
        case (1<<14):
        	led_off();
        	break;
        case (1<<15):
        	led_on();
        	break; 
        case (1<<19):
        	led_off();
        	break;  
        default:
        	break;  
    }
    /**clear irq source**/
    EINTPEND = irq_source;
    SRCPND |= 1<<5;
    INTPND |= 1<<5;	
}


