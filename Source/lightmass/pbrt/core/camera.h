
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

#ifndef PBRT_CORE_CAMERA_H
#define PBRT_CORE_CAMERA_H

// core/camera.h*
#include "pbrt.h"
#include "geometry.h"
#include "transform.h"

// Camera Declarations
class Camera 
{
public:
    // ���캯�� file��������ͼ����
    Camera(const AnimatedTransform &cam2world, float sopen, float sclose, Film *film);

	// ��������
    virtual ~Camera();

	// ����ͼ��Ĳ��������ɹ���
    virtual float GenerateRay(const CameraSample &sample, Ray *ray) const = 0;

	// ��������
    virtual float GenerateRayDifferential(const CameraSample &sample, RayDifferential *rd) const;

    // Camera Public Data
public:
    AnimatedTransform CameraToWorld;
    const float shutterOpen;			// �ع⿪ʼʱ��
	const float	shutterClose;			// �ع����ʱ��	
    Film*		film;
};

//-------------------------------
// ͶӰ����� 2011/12/27 pbrt
//-------------------------------
class ProjectiveCamera : public Camera 
{
public:
    // ProjectiveCamera Public Methods
    ProjectiveCamera(const AnimatedTransform &cam2world,
        const Transform &proj, const float screenWindow[4],
        float sopen, float sclose, float lensr, float focald, Film *film);

protected:
    // ProjectiveCamera Protected Data
    Transform CameraToScreen, RasterToCamera;
    Transform ScreenToRaster, RasterToScreen;
    float	  lensRadius;		// ��Ȧ��С(Ӱ�쾰��)
	float	  focalDistance;	// ����(Ӱ�쾰��)
};



#endif // PBRT_CORE_CAMERA_H
