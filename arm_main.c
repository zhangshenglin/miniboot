

int arm_main()
{
    led_init();
    irqs_init();
    while(1);
    return 0;
}

