/// By Henry
#include "lib/include.h"

char *reading_string(char delimiter, int *ptr){
    char letter;
    static char array[50];
    int counter = 0;
    letter = readChar();  
    while (letter != delimiter){
        array[counter] = letter;
        letter = readChar();
        counter ++;
    }
    *ptr = strlen(array);
    return &array[0];
}

char *inverting_name(char *name, int length){
    static char inverted_name[50];
    int counter = 0;
    int idx = 0; 
    for (int i = length; i > 0; i--){
        inverted_name[counter] = *(name + (i -1));
        inverted_name[counter + 1] = idx + '0';
        idx ++; 
        counter = counter + 2;
    }
    inverted_name[counter - 1] = '\n'; 
    return &inverted_name[0];
}

int main(void)
{
    //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz
 */
//Experimento 2
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
 * para controlar la posicion de tres servos sg90 o otros.
 *
 */
//Experimento 3
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz , utilizando el uart de la practica 3
 * se enviara dato desde interfaz de simulink para controlar la intensidad luminosa 
 * usando un led RGB externa 
 *
 */
    Configurar_PLL(_20MHZ);  //Configuracion de velocidad de reloj
    Configurar_GPIO();
    UART_2_CONFIG();
    ADC_CONFIGURATION();
    SEQ_CONFIGURATION();
    unsigned int adc_read;  
    //PWM_CONFIGURATION(0, 64, 50, 20000000, 72);
    //PWM_CONFIGURATION(int module, int divisor, int freq, int f_clk, int duty_cycle)
    
    while (1){
        ADC0 -> PSSI |= (1 << 3); //| (1 << 0);
        while ((ADC0 -> RIS & 8) == 0);
        adc_read = ADC0 -> SSFIFO3 & 0xFFFF;
        ADC0 -> ISC = 8; // Clearing 0b1000
        if (adc_read < 2040){
            GPIOF -> DATA |= (1 << 1);
            GPIOF -> DATA &= ~(1 << 2); 
        }
        else if (adc_read > 2040){
            GPIOF -> DATA &= ~(1 << 1);
            GPIOF -> DATA |= (1 << 2);  
        }

    }   
}

