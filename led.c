#include <stdint.h>

void led_main(void)
{
        int acceso = 0;
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
	      
	      while(reg)
	      {
		    if (acceso & reg)
		    {
			  //spengo i led
			  *(volatile uint32_t *)0x5003003c = 0xf;
			  *(volatile uint32_t *)0x500203c0 = 0xfff;
			  acceso = 0;
			  TBV(valoreconteggio); //aggiorno il contatore
		    }
		    else if ((!acceso) & reg)
		    {
			  //accendo i led
			  *(volatile uint32_t *)0x5003003c = 0x0;
			  *(volatile uint32_t *)0x500203c0 = 0x0;
			  acceso = 1;
			  TBV(valoreconteggio); //aggiorno il contatore
		    }
	      }
        }
}