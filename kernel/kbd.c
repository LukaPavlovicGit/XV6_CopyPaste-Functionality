#include "types.h"
#include "x86.h"
#include "defs.h"
#include "kbd.h"
#include "memlayout.h"

#define CRTPORT 0x3d4
#define INPUT_BUF 128

static ushort *crt = (ushort*)P2V(0xb8000); 

int copy_paste_mode=0, copy_flag=0, paste_flag=0;;
int entry_pos, entry_selection_pos, pos;
int buffer[INPUT_BUF];
int i=0, n=0; 		// i-pokazivac na trenutni element u bufferu
			// n-velicina kopiranog sadrzaja
int
kbdgetc(void)
{	
	if(paste_flag){ // 	PASTE LOGIKA
		if((n--)==0){
			paste_flag=0;
			i=0;
			return NO;
		}		
		return buffer[i++ % INPUT_BUF]&0xff;	
	}

	static uint shift;
	static uchar *charcode[5] = {
		normalmap, shiftmap, ctlmap, ctlmap, shift_alt_c_map
	};
	uint st, data, c;

	st = inb(KBSTATP);
	if((st & KBS_DIB) == 0)
		return -1;
	data = inb(KBDATAP);

	if(data == 0xE0){
		shift |= E0ESC;
		return 0;
	} else if(data & 0x80){
		// Key released
		data = (shift & E0ESC ? data : data & 0x7F);
		shift &= ~(shiftcode[data] | E0ESC);
		return 0;
	} else if(shift & E0ESC){
		// Last character was an E0 escape; or with 0x80
		data |= 0x80;
		shift &= ~E0ESC;
	}

	if(shift==5 && data==0x2E){ // ako je shift = 00000101 i scan_code unetog tastera 0x2E ('c');
		if(!copy_paste_mode){
			outb(CRTPORT, 14);
			entry_pos = inb(CRTPORT+1) << 8;
			outb(CRTPORT, 15);
			entry_pos |= inb(CRTPORT+1);

			copy_paste_mode=1;		
		}
		else{
			outb(CRTPORT, 14);
			outb(CRTPORT+1, entry_pos>>8);
			outb(CRTPORT, 15);
			outb(CRTPORT+1, entry_pos);
	
			int letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x0700;

 			if(copy_flag){  			// ako smo u procesu selekcije, prvo deselektujem pa tek onda izlazimo iz copy/paste moda
				copy_flag=0;
				int mini, maxi;
				if(entry_selection_pos<pos) 
					mini=entry_selection_pos, maxi=pos;			
				else 
					maxi=entry_selection_pos, mini=pos;			
				
				for(int i=mini;i<maxi;++i){
					letter=*(crt+i);
					crt[i] = (letter&0xff) | 0x0700;
				}	
			}
			 	
			copy_paste_mode=0;
		}

		return NO;
	}

	shift |= shiftcode[data];
	shift ^= togglecode[data];

	if(copy_paste_mode){
		c = charcode[4][data];
		if(c==NO) 
			return NO;
		
		outb(CRTPORT, 14);
		pos = inb(CRTPORT+1) << 8;
		outb(CRTPORT, 15);
		pos |= inb(CRTPORT+1);

		int letter, X=0, Y=0;
		
		switch(c){
		case 'w':
			letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x0700;		
			if(copy_flag){ 							           // LOGIKA DESELEKTOVANJA KADA JE TRENUTNA POZICIJA VECA OD POZICIJE POCETKA SELEKCIJE
				if(pos-entry_selection_pos>80)   				   // razlika izmedju trenutne pozicije i pocetka selekcije je veca od 80
					 X=pos-80, Y=pos;
				else if(pos-entry_selection_pos>=0 && pos-entry_selection_pos<=80) // razlika izmedju trenutne pozicije i pocetka selekcije je izmedju 0 i 80
					 X=entry_selection_pos ,Y=pos;	
			}
			pos=(pos/80>0) ? pos-80 : pos;
			break;
		case 'a':
			letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x0700;
			pos=(pos>0) ? pos-1 : pos;
			break;
		case 's':
			letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x0700;
			if(copy_flag){ 								    // LOGIKA DESELEKTOVANJA KADA JE POZICIJA POCETKA SELEKCIJE VECA OD TRENUTNE POZICIJA VECA.  
				if(entry_selection_pos-pos>80) 					    // razlika izmedju pocetka selekcije i trenutne pozicije je veca od 80
					X=pos, Y=pos+80;
				else if(entry_selection_pos-pos>=0 && entry_selection_pos-pos<=80)  // razlika izmedju pocetka selekcije i trenutne pozicije je izmedju 0 i 80
					X=pos, Y=entry_selection_pos;	
			}	
			pos=(pos/80<24) ? pos+80 : pos;
			break;	
		case 'd':
			letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x0700;
			pos=(pos<1999) ? pos+1 : pos; 
			break;
		case 'q':
			if(!copy_flag){
				outb(CRTPORT, 14);
				entry_selection_pos = inb(CRTPORT+1) << 8;
				outb(CRTPORT, 15);
				entry_selection_pos |= inb(CRTPORT+1);
				
				n=0; 			// resetujemo velicinu kopiranog sadrzaja na 0 kada pokrenemo kopiranje 
				copy_flag=1;
			}
			break;
		case 'e':
			if(copy_flag){
				int mini, maxi;
				if(entry_selection_pos<pos) 
					mini=entry_selection_pos, maxi=pos;			
				else 
					maxi=entry_selection_pos, mini=pos;			
				
				for(int i=mini;i<maxi;++i){
					letter=*(crt+i);
					crt[i] = (letter&0xff) | 0x0700;
					buffer[n++ % INPUT_BUF]=letter;
				}
				n = (n>=INPUT_BUF) ? INPUT_BUF-1 : n;
				copy_flag=0;			
			}
			break;

		default:
			return NO;
		}

		if(!copy_flag){
			letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x7000;
		}else{	
			letter=*(crt+pos);
			crt[pos] = (letter&0xff) | 0x0700;
			for(int i=X;i<Y;++i){ 			//DESELEKTOVANJE
				letter=*(crt+i);
				crt[i] = (letter&0xff) | 0x0700;			
			}

			int mini, maxi;
			if(entry_selection_pos<pos)
				mini=entry_selection_pos, maxi=pos;			
			else
				maxi=entry_selection_pos, mini=pos;			
			
			for(int i=mini;i<maxi;++i){		// SELEKTOVANJE
				letter=*(crt+i);
				crt[i] = (letter&0xff) | 0x7000;
			}
		}
		
		outb(CRTPORT, 14);
		outb(CRTPORT+1, pos>>8);
		outb(CRTPORT, 15);
		outb(CRTPORT+1, pos);

		return NO;	
	}

	if(shift==5 && data==0x19 && n>0 && !copy_paste_mode){ // ako je shift = 00000101 i scan_code unetog tastera 0x19 ('p') i u baferu ima karaktera i ako je copypaste mod;
		paste_flag=1;		
		return NO;
	}
		
	c = charcode[shift & (CTL | SHIFT)][data];	

	if(shift & CAPSLOCK){
		if('a' <= c && c <= 'z')
			c += 'A' - 'a';
		else if('A' <= c && c <= 'Z')
			c += 'a' - 'A';
	}
	return c;
}

void
kbdintr(void)
{
	consoleintr(kbdgetc);
}
