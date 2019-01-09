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

#ifndef PBRT_ACCELERATORS_BVH_H
#define PBRT_ACCELERATORS_BVH_H

// accelerators/bvh.h*
#include "pbrt.h"
#include "primitive.h"

//-----------------------------------------
// BVHAccel Declarations
//-----------------------------------------
struct BVHBuildNode;
struct BVHPrimitiveInfo;
struct LinearBVHNode;
class BVHAccel : public Aggregate 
{
public:
	// split method enumeration
	enum SplitMethod 
	{ 
		SPLIT_MIDDLE, 
		SPLIT_EQUAL_COUNTS, 
		SPLIT_SAH 
	};

public:
    // ���캯��
    BVHAccel(const vector<Reference<Primitive> > &p, uint32_t max_pri_in_node = 1, const string &sm = "sah");
   
	// ��������
	~BVHAccel();

	// �����Χ��
	BBox WorldBound() const;

	// �Ƿ�ɽ����ཻ���
    bool CanIntersect() const { return true; }

	// ���߼��<ϸ>
    bool Intersect(const Ray &ray, Intersection *isect) const;

	// ������<��>,���ཻ��Ϣ����
    bool IntersectP(const Ray &ray) const;

private:
    // BVHAccel Private Methods
    BVHBuildNode *recursiveBuild(MemoryArena &buildArena, vector<BVHPrimitiveInfo> &buildData, uint32_t start, uint32_t end, uint32_t *totalNodes, vector<Reference<Primitive> > &orderedPrims);
    
	// δ֪
	uint32_t flattenBVHTree(BVHBuildNode *node, uint32_t *offset);

private:
    uint32_t					  maxPrimsInNode;	// ÿ���ӵ����ܴ洢������Ա��
    SplitMethod					  splitMethod;		// ��ַ�ʽ
    vector<Reference<Primitive> > primitives;		// ��Ա(˳������)
    LinearBVHNode*				  nodes;			// BVH�ӵ�
};

BVHAccel *CreateBVHAccelerator(const vector<Reference<Primitive> > &prims, const ParamSet &ps);

#endif // PBRT_ACCELERATORS_BVH_H
