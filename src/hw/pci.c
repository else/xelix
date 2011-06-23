/* pci.c: Description of what this file does
 * Copyright © 2011 Barbers
 *
 * This file is part of Xelix.
 *
 * Xelix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Xelix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Xelix. If not, see <http://www.gnu.org/licenses/>.
 */

#include "pci.h"

// Other header includes

// Your code
#define PCI_CONFIG_DATA    0x0CFC
#define PCI_CONFIG_ADDRESS 0x0CF8
/**
 * Liest ein Dword aus einem PCI-Konfigurations-Register
 *  @param bus Bus
 *  @param dev GerĂ¤t
 *  @param func Funktion
 *  @param offset Registernummer
 *  @return Register content
 */
int pci_config_read(int bus,int dev,int func,int offset) {
  int val;
  int address = 0x80000000|(bus<<16)|(dev<<11)|(func<<8)|(offset&0xFC);
  outl(PCI_CONFIG_ADDRESS,address);
  val = inl(PCI_CONFIG_DATA);
  return val;
}
int pow (int basis, int potenz){
	int counter;
	int ret;
	ret = basis;
	counter = 1;
	while (counter <= potenz){
		ret = ret * basis;
		++counter;
	}
	printf("ergebnis von pow: %d\n",ret);
	return ret;
}
//summiert die bits auf, nachdem sie nach  rechts vershcoben wurden
int bitsum(int fullregister, int startbit, int stopbit){
	int summe;
	int stelle;
	int zielstelle;
	int tmp;
	fullregister = fullregister >> startbit;
	summe = 0;
	stelle = 1;
	zielstelle = pow(2,(stopbit-startbit))+1;
	while ( stelle < zielstelle){
		tmp = fullregister & stelle;
		summe = summe + tmp;
		stelle=stelle*2;
	}
	printf("ergebnis von bitsum: %d\n",summe);
	return summe;
}
int get_vendor_id(int bus,int dev,int func) {
	int fullreg;
	int vendor_id;
	fullreg=pci_config_read(bus,dev,func,0x000);
	printf("fullreg:%d\n",fullreg);
	vendor_id=bitsum(fullreg,0,15);
	return vendor_id;
}
