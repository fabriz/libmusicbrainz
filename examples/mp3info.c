/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "mb_c.h"

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    int           bitrate, stereo, duration, samplerate;

    if (argc < 2)
    {
        printf("Usage: mp3info <mp3 files>\n");
        exit(0);
    }

    // Create the musicbrainz object, which will be needed for subsequent calls
    o = mb_New();

    if (mb_GetMP3Info (o, argv[1], &duration, &bitrate, &stereo, &samplerate))
    {
        printf("%s:\n", argv[1]);
        duration /= 1000;
        printf("  duration: %d:%02d\n", duration / 60, duration % 60);
        printf("   bitrate: %d\n", bitrate);
        printf("    stereo: %d\n", stereo);
        printf("samplerate: %d\n", samplerate);
    }
    else
        printf("Cannot get file stats\n");

    // and clean up the musicbrainz object
    mb_Delete(o);

    return 0;
}
