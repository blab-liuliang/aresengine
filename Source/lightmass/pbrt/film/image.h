
/*
    pbrt source code Copyright(c) 1998-2010 Matt Pharr and Greg Humphreys.

    This file is part of pbrt.

    pbrt is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.  Note that the text contents of
    the book "Physically Based Rendering" are *not* licensed under the
    GNU GPL.

    pbrt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_FILM_IMAGE_H
#define PBRT_FILM_IMAGE_H

// film/image.h*
#include "pbrt.h"
#include "film.h"
#include "sampler.h"
#include "filter.h"
#include "paramset.h"

//--------------------------------------
// Film��ʵ��, ImageFilm 2012-1-2
//--------------------------------------
class ImageFilm : public Film
{
private:
	// ����
	struct Pixel 
	{
		float Lxyz[3];
		float weightSum;
		float splatXYZ[3];
		float pad;

		// ���캯��
		Pixel() 
		{
			for (int i = 0; i < 3; ++i) 
				Lxyz[i] = splatXYZ[i] = 0.f;

			weightSum = 0.f;
		}
	};

public:
    // ���캯��
    ImageFilm(int xres, int yres, Filter *filt, const float crop[4], const string &filename, bool openWindow);
    
	// ��������
	~ImageFilm();

    void AddSample(const CameraSample &sample, const Spectrum &L);
    void Splat(const CameraSample &sample, const Spectrum &L);
    void GetSampleExtent(int *xstart, int *xend, int *ystart, int *yend) const;
    void GetPixelExtent(int *xstart, int *xend, int *ystart, int *yend) const;
    void WriteImage(float splatScale);
    void UpdateDisplay(int x0, int y0, int x1, int y1, float splatScale);
private:
    // ImageFilm Private Data
    Filter *filter;
    float cropWindow[4];
    string filename;
    int xPixelStart, yPixelStart, xPixelCount, yPixelCount;
    BlockedArray<Pixel> *pixels;
    float *filterTable;
};


ImageFilm *CreateImageFilm(const ParamSet &params, Filter *filter);

#endif // PBRT_FILM_IMAGE_H
