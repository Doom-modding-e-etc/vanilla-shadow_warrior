//-------------------------------------------------------------------------
/*
Copyright (C) 1997, 2005 - 3D Realms Entertainment

This file is part of Shadow Warrior version 1.2

Shadow Warrior is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Original Source: 1997 - Frank Maddin and Jim Norwood
Prepared for public release: 03/28/2005 - Charlie Wiederhold, 3D Realms
*/
//-------------------------------------------------------------------------

#include <string.h>
#include "mytypes.h"
#include "build.h"
#include "proto.h"
#include "keys.h"
#include "names2.h"
//#include "panel.h"
#include "game.h"

// macros this function needs
//#define MK_FP(seg,ofs)       ((void _seg *)(seg)+(void near *)(ofs))
//#define PokeByte(a,b,c)      (*((char far *)MK_FP((a),(b)))=(char)(c))

//#if DEBUG
VOID 
PokeStringMono(BYTE Attr, BYTEp String)
    {
    // Scrolls the monochrome display up one line, then prints the
    // string with the desired attribute on the bottom line.

    // EXAMPLE: PokeStringMono(MDA_NORMAL, "Hello, world.");

    BYTEp Src, Dest;
    LONGp s,d;
    static char MonoBuf[4000];
    
    #define BASE (MonoBuf)
    #define LINE_SIZE 160
    #define LINE_OFFSET(num) ((80*2)*(num))
    
    // First scroll the screen up one line.
    // copy lines 1-24 up to 0
    s = (LONGp)(BASE + LINE_SIZE);
    d = (LONGp)BASE;
    memmove(d,s,LINE_OFFSET(24));

    // clear bottom line
    Dest = BASE + LINE_OFFSET(24);
    //memset(Dest,0,LINE_SIZE);
    memset(Dest,'.',LINE_SIZE);

    // Now print the string on the bottom line.
    Src = String;
    Dest = BASE + LINE_OFFSET(24);
    
    while (*Src)
        {
        *Dest++ = *Src++;
        *Dest++ = Attr;
        }
    
    memcpy((char *)0xB0000, MonoBuf, sizeof(MonoBuf));    
    }
//#endif
    
