/*____________________________________________________________________________

  MusicBrainz -- The Internet music metadatabase
 
  Portions Copyright (C) 2000 Relatable
 
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
____________________________________________________________________________*/

#ifndef INCLUDED_SIGFFT_H_
#define INCLUDED_SIGFFT_H_
//------------------------------------
//  fft.h
//  Fast Fourier Transform
//  modified by Sean Ward, 2000
//  portions (c) Reliable Software, 1996
//------------------------------------

#ifdef WIN32
#include "config_win32.h"
#else
#include "config.h"
#endif

#include "sigcomplex.h"
#include <assert.h>

class SampleIter;

class FFT
{
public:
    FFT  (int Points, long sampleRate);
    ~FFT ();
    int  Points () const { return _Points; }
    void Transform ();
    void CopyIn(double* pBuffer, int nNumSamples);
    void CopyIn2(double* pBuf, double* pBuf2, int nNumSamples);

    double  GetIntensity (int i) const
    { 
        assert (i < _Points);
        return _X[i].Conjugate(); 
    }

    double GetPower1(int i) const
    {
        assert (i < _Points);
        if ((i == 0) || (i == _Points / 2)) // special cases
	        {
		            return _X[i].Re() * _X[i].Re();
		            }

        double dTemp = 0;
        double dA = (_X[_Points - i].Re() + _X[i].Re()) / 2;
        double dB = (_X[_Points - i].Im() - _X[i].Im()) / 2;
        dTemp = dA * dA + dB * dB;

        return dTemp;
    }

    double GetPower2(int i) const
    {
        assert ( i < _Points);

        if ((i == 0) || (i == _Points / 2)) // special cases
        {
            return _X[i].Im() * _X[i].Im();
        }

        double dTemp = 0;
        double dA = (_X[_Points - i].Im() + _X[i].Im()) / 2;
        double dB = (_X[_Points - i].Re() - _X[i].Re()) / 2;
        dTemp = dA * dA + dB * dB;

        return dTemp;
    }

    double GetRealPart(int i) const
    {
       assert( i < _Points);
       return _X[i].Re();
    }

    double GetIMPart(int i) const
    {
       assert( i < _Points);
       return _X[i].Im();
    }

    int     GetFrequency (int point) const
    {
        // return frequency in Hz of a given point
        assert (point < _Points);
        long x =_sampleRate * point;
        return x / _Points;
    }

    int     HzToPoint (int freq) const 
    { 
        return (long)_Points * freq / _sampleRate; 
    }

    int     MaxFreq() const { return _sampleRate; }

    int     Tape (int i) const
    {
        assert (i < _Points);
        return (int) _aTape[i];
    }

private:

    void PutAt ( int i, double val )
    {
        _X [_aBitRev[i]] = Complex (val);
    }

    void PutAt2 ( int i, double val, double val2 )
    {
        _X [_aBitRev[i]] = Complex(val, val2);
    }
    
    int        _Points;
    long       _sampleRate;
    int	       _logPoints;
    double     _sqrtPoints;
    int	      *_aBitRev;       // bit reverse vector
    Complex   *_X;             // in-place fft array
    Complex  **_W;             // exponentials
    double    *_aTape;         // recording tape
};

#endif
