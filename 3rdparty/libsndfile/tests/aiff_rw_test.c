/*
** Copyright (C) 2003-2012 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>


#include <sndfile.h>

#include "utils.h"


static unsigned char aifc_data [] =
{   'F' , 'O' , 'R' , 'M' ,
    0x00, 0x00, 0x01, 0xE8, /* FORM length */

    'A' , 'I' , 'F' , 'C' ,
    0x43, 0x4F, 0x4D, 0x4D, /* COMM */
    0x00, 0x00, 0x00, 0x26, /* COMM length */
    0x00, 0x01, 0x00, 0x00, 0x00, 0xAE, 0x00, 0x10, 0x40, 0x0D, 0xAC, 0x44,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4E, 0x4F, 0x4E, 0x45, 0x0D, 'N' ,
    'o' , 't' , ' ' , 'c' , 'o' , 'm' , 'p' , 'r' , 'e' , 's' , 's' , 'e' ,
    'd' , 0x00,

    'F' , 'V' , 'E' , 'R' , 0x00, 0x00, 0x00, 0x04, 0xA2, 0x80, 0x51, 0x40,

    /* A 'MARK' chunk. */
    'M' , 'A' , 'R' , 'K' , 0x00, 0x00, 0x00, 0x36, 0x00, 0x05,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 'A' ,
    0x00, 0x02, 0x00, 0x00, 0x11, 0x3A, 0x02, 'B' , 'C' , 0x00,
    0x00, 0x03, 0x00, 0x00, 0x22, 0x74, 0x03, 'D' , 'E' , 'F',
    0x00, 0x04, 0x00, 0x00, 0x33, 0xAE, 0x04, 'G' , 'H' , 'I', 'J' , 0x00,
    0x00, 0x05, 0x00, 0x00, 0x44, 0xE8, 0x05, 'K' , 'L' , 'M', 'N' , 'O' ,

    'S' , 'S' , 'N' , 'D' ,
    0x00, 0x00, 0x01, 0x64, /* SSND length */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xE0, 0xFF, 0xDB, 0xFF, 0xD0, 0xFF, 0xD5, 0xFF, 0xD6, 0xFF, 0xD0,
    0xFF, 0xBF, 0xFF, 0xBE, 0xFF, 0xB9, 0xFF, 0xC8, 0xFF, 0xBF, 0xFF, 0xD5,
    0xFF, 0xC3, 0xFF, 0xBF, 0xFF, 0xB3, 0xFF, 0xBE, 0xFF, 0xB4, 0xFF, 0xAD,
    0xFF, 0xAC, 0xFF, 0xAF, 0xFF, 0xB9, 0xFF, 0xB3, 0xFF, 0xA4, 0xFF, 0xA5,
    0xFF, 0x93, 0xFF, 0x95, 0xFF, 0x97, 0xFF, 0x98, 0xFF, 0x99, 0xFF, 0x9E,
    0xFF, 0x90, 0xFF, 0x80, 0xFF, 0x81, 0xFF, 0x7C, 0xFF, 0x80, 0xFF, 0x7C,
    0xFF, 0x72, 0xFF, 0x72, 0xFF, 0x6C, 0xFF, 0x75, 0xFF, 0x6E, 0xFF, 0x6F,
    0xFF, 0x66, 0xFF, 0x62, 0xFF, 0x5C, 0xFF, 0x64, 0xFF, 0x50, 0xFF, 0x56,
    0xFF, 0x56, 0xFF, 0x4A, 0xFF, 0x4A, 0xFF, 0x49, 0xFF, 0x44, 0xFF, 0x49,
    0xFF, 0x3B, 0xFF, 0x3F, 0xFF, 0x48, 0xFF, 0x46, 0xFF, 0x42, 0xFF, 0x49,
    0xFF, 0x43, 0xFF, 0x36, 0xFF, 0x40, 0xFF, 0x35, 0xFF, 0x3F, 0xFF, 0x36,
    0xFF, 0x37, 0xFF, 0x2E, 0xFF, 0x23, 0xFF, 0x23, 0xFF, 0x21, 0xFF, 0x1F,
    0xFF, 0x25, 0xFF, 0x2C, 0xFF, 0x1E, 0xFF, 0x22, 0xFF, 0x24, 0xFF, 0x2B,
    0xFF, 0x35, 0xFF, 0x27, 0xFF, 0x2E, 0xFF, 0x21, 0xFF, 0x18, 0xFF, 0x21,
    0xFF, 0x20, 0xFF, 0x0F, 0xFF, 0x21, 0xFF, 0x1A, 0xFF, 0x10, 0xFF, 0x09,
    0xFF, 0x1E, 0xFF, 0x19, 0xFF, 0x21, 0xFF, 0x13, 0xFF, 0x1B, 0xFF, 0x18,
    0xFF, 0x21, 0xFF, 0x0F, 0xFF, 0x1A, 0xFF, 0x16, 0xFF, 0x21, 0xFF, 0x1B,
    0xFF, 0x1B, 0xFF, 0x23, 0xFF, 0x1A, 0xFF, 0x21, 0xFF, 0x26, 0xFF, 0x23,
    0xFF, 0x26, 0xFF, 0x27, 0xFF, 0x30, 0xFF, 0x27, 0xFF, 0x2F, 0xFF, 0x28,
    0xFF, 0x2C, 0xFF, 0x27, 0xFF, 0x33, 0xFF, 0x29, 0xFF, 0x33, 0xFF, 0x3A,
    0xFF, 0x42, 0xFF, 0x3B, 0xFF, 0x4D, 0xFF, 0x4B, 0xFF, 0x4D, 0xFF, 0x4A,
    0xFF, 0x67, 0xFF, 0x77, 0xFF, 0x73, 0xFF, 0x7B, 0xFF, 0xDE, 0xFF, 0xAD,
    0x00, 0x4A, 0x00, 0x63, 0xEC, 0x8C, 0x03, 0xBB, 0x0E, 0xE4, 0x08, 0xF2,
    0x00, 0x70, 0xE3, 0xD1, 0xE5, 0xE4, 0x01, 0x6E, 0x0A, 0x67, 0x1C, 0x74,
    0xF8, 0x8E, 0x10, 0x7B, 0xEA, 0x3C, 0x09, 0x87, 0x1B, 0x24, 0xEF, 0x05,
    0x17, 0x76, 0x0D, 0x5B, 0x02, 0x43, 0xF5, 0xEF, 0x0C, 0x1D, 0xF7, 0x61,
    0x05, 0x95, 0x0B, 0xC2, 0xF1, 0x69, 0x1A, 0xA1, 0xEC, 0x75, 0xF4, 0x11,
    0x13, 0x4F, 0x13, 0x71, 0xFA, 0x33, 0xEC, 0x32, 0xC8, 0xCF, 0x05, 0xB0,
    0x0B, 0x61, 0x33, 0x19, 0xCE, 0x37, 0xEF, 0xD4, 0x21, 0x9D, 0xFA, 0xAE,
} ;

static void rw_test (const char *filename) ;

int
main (void)
{   const char *filename = "rw.aifc" ;

    print_test_name ("aiff_rw_test", filename) ;

    dump_data_to_file (filename, aifc_data, sizeof (aifc_data)) ;

    rw_test (filename) ;

    unlink (filename) ;

    puts ("ok") ;
    return 0 ;
} /* main */

/*==============================================================================
*/

static void
rw_test (const char *filename)
{   SNDFILE *file ;
    SF_INFO sfinfo_rd, sfinfo_rw ;

    memset (&sfinfo_rd, 0, sizeof (sfinfo_rd)) ;
    memset (&sfinfo_rw, 0, sizeof (sfinfo_rw)) ;

    /* Open the file in read only mode and fill in the SF_INFO struct. */
    if ((file = sf_open (filename, SFM_READ, &sfinfo_rd)) == NULL)
    {   printf ("\n\nLine %d : sf_open SFM_READ failed : %s\n\n", __LINE__, sf_strerror (NULL)) ;
        exit (1) ;
        } ;
    check_log_buffer_or_die (file, __LINE__) ;
    sf_close (file) ;

    /* Now open read/write and close the file. */
    if ((file = sf_open (filename, SFM_RDWR, &sfinfo_rw)) == NULL)
    {   printf ("\n\nLine %d : sf_open SFM_RDWR failed : %s\n\n", __LINE__, sf_strerror (NULL)) ;
        exit (1) ;
        } ;
    check_log_buffer_or_die (file, __LINE__) ;
    sf_close (file) ;

    /* Open again as read only again and fill in a new SF_INFO struct.  */
    memset (&sfinfo_rw, 0, sizeof (sfinfo_rw)) ;
    if ((file = sf_open (filename, SFM_READ, &sfinfo_rw)) == NULL)
    {   printf ("\n\nLine %d : sf_open SFM_RDWR failed : %s\n\n", __LINE__, sf_strerror (NULL)) ;
        exit (1) ;
        } ;
    check_log_buffer_or_die (file, __LINE__) ;
    sf_close (file) ;

    /* Now compare the two. */
    if (sfinfo_rd.format != sfinfo_rw.format)
    {   printf ("\n\nLine %d : format mismatch (0x%08X != 0x%08X).\n\n", __LINE__,
            sfinfo_rd.format, sfinfo_rw.format) ;
        exit (1) ;
        } ;

    if (sfinfo_rd.channels != sfinfo_rw.channels)
    {   printf ("\n\nLine %d : channel count mismatch (%d != %d).\n\n", __LINE__,
            sfinfo_rd.channels, sfinfo_rw.channels) ;
        exit (1) ;
        } ;

    if (sfinfo_rd.frames != sfinfo_rw.frames)
    {   printf ("\n\nLine %d : frame count mismatch (rd %" PRId64 " != rw %" PRId64 ").\n\n", __LINE__,
            sfinfo_rd.frames, sfinfo_rw.frames) ;
        exit (1) ;
        } ;

    return ;
} /* rw_test */
