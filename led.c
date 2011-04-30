#include <stdint.h>

void led_main(void)
{
        int acceso = 0, s = 0;
        //uint32_t valoreconteggio = 0x005B8D7F;
        uint32_t valoreconteggio = 0x000F423F;
        
        //programmo la porta 3 in uscita
        *(volatile uint32_t *)0x50038000 = 0x0f;
        
        //programmo la porta 2 in uscita (pin 4, 5, 6, 7)
        
        uint32_t reg = *(volatile uint32_t *)0x50028000;
        
        reg |= 0x0f0; //porte dei led in uscita
        
        *(volatile uint32_t *)0x50028000 = reg;
        
        
        //abilitazione del system time clock divider
        //imposto una divisione per 12 in modo da ottenere una frequenza di 1Mhz (la frequenza del chip è di
        //12 Mhz).
        
        reg = *(volatile uint32_t *)0x400480B0;
        reg |= 0xC;
        *(volatile uint32_t *)0x400480B0 = reg;
        
        //abilitazione del system tick timer e configurazione in modo tale che prenda il clock dal system timer
        //clock divider
        
        reg = *(volatile uint32_t *)0xE000E010;
        reg |= 0x1;
        *(volatile uint32_t *)0xE000E010 = reg;
        
        //carico una costante pari a 999999 in modo tale che il contatore scenda a zero dopo un secondo
        TBV(valoreconteggio);
        
        while(1)
        {
	      //verifico se si è alzato il flag di passaggio per lo zero
	      //in caso affermativo, accendo/spengo i led ricaricando la costante di partenza del contatore
	      reg = *(volatile uint32_t *)0xE000E010;
	      reg &= 0x00010000;
	      reg = (reg >> 16);
	      
	      if (acceso & reg)
	      {
		    switch(s)
		    {
			  case 0:
				//spengo i primi 2 led
				*(volatile uint32_t *)0x5003000c = 0xf;
				*(volatile uint32_t *)0x50030030 = 0x0;
				*(volatile uint32_t *)0x500203c0 = 0x0;
				break;
			  case 1:
				//spengo altri 2 led
				*(volatile uint32_t *)0x5003003c = 0xf;
				*(volatile uint32_t *)0x500203c0 = 0x0;
				break;
			  case 2:
				//spengo altri 2 led
				*(volatile uint32_t *)0x5003003c = 0xf;
				*(volatile uint32_t *)0x500200c0 = 0xfff;
				*(volatile uint32_t *)0x50020300 = 0x0;
				break;
			  case 3:
				//spengo altri 2 led
				*(volatile uint32_t *)0x5003003c = 0xf;
				*(volatile uint32_t *)0x500203c0 = 0xfff;
				acceso = 0;
				s = -1;
				break;
			  default:
				break;
		    }
		    //aggiorno la variabile di stato dei led
		    s++;
	      }
	      else if ((!acceso) & reg)
	      {
		    switch(s)
		    {
			  case 0:
				//accendo i primi 2 led
				*(volatile uint32_t *)0x5003000c = 0x0;
				*(volatile uint32_t *)0x50030030 = 0xf;
				*(volatile uint32_t *)0x500203c0 = 0xfff;
				break;
			  case 1:
				//accendo altri 2 led
				*(volatile uint32_t *)0x5003003c = 0x0;
				*(volatile uint32_t *)0x500203c0 = 0xfff;
				break;
			  case 2:
				//accendo altri 2 led
				*(volatile uint32_t *)0x5003003c = 0x0;
				*(volatile uint32_t *)0x500200c0 = 0x0;
				*(volatile uint32_t *)0x50020300 = 0xfff;
				break;
			  case 3:
				//accendo altri 2 led
				*(volatile uint32_t *)0x5003003c = 0x0;
				*(volatile uint32_t *)0x500203c0 = 0x0;
				acceso = 1;
				s = -1;
				break;
			  default:
				break;
		    }
		    //aggiorno la variabile di stato dei led
		    s++;
	      }
	      TBV(valoreconteggio); //aggiorno il contatore
        }
}