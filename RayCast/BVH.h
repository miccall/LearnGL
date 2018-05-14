#pragma once

#include "hitable.h"

class bvh_node : public hitable {

public:
	hitable *left;
	hitable *right;
	aabb box;

public:
	bvh_node() {}
	bvh_node(hitable **l, int n, float time0, float time1);
	virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const;

};

// 排序函数  比较两个数的大小 ，a >= b ? 1 : -1  
int box_x_compare(const void * a, const void * b) {
	aabb box_left, box_right;
	hitable *ah = *(hitable**)a;
	hitable *bh = *(hitable**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
		std::cerr << "no bounding box in bvh_node constructor\n";
	if (box_left.min().x() - box_right.min().x() < 0.0)
		return -1;
	else
		return 1;
}

// 排序函数  比较两个数的大小 ，a >= b ? 1 : -1  
int box_y_compare(const void * a, const void * b)
{
	aabb box_left, box_right;
	hitable *ah = *(hitable**)a;
	hitable *bh = *(hitable**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
		std::cerr << "no bounding box in bvh_node constructor\n";
	if (box_left.min().y() - box_right.min().y() < 0.0)
		return -1;
	else
		return 1;
}

// 排序函数  比较两个数的大小 ，a >= b ? 1 : -1  
int box_z_compare(const void * a, const void * b)
{
	aabb box_left, box_right;
	hitable *ah = *(hitable**)a;
	hitable *bh = *(hitable**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
		std::cerr << "no bounding box in bvh_node constructor\n";
	if (box_left.min().z() - box_right.min().z() < 0.0)
		return -1;
	else
		return 1;
}


bvh_node::bvh_node(hitable **l, int n, float time0, float time1)
{
	int axis = int(3 * drand48());

	// 排序 ：排序数组 ， 数组个数 每个元素的大小 ， 排序函数 
	if (axis == 0)
		qsort(l, n, sizeof(hitable *), box_x_compare);
	else if (axis == 1)
		qsort(l, n, sizeof(hitable *), box_y_compare);
	else
		qsort(l, n, sizeof(hitable *), box_z_compare);
	
	if (n == 1) {
		left = right = l[0];
	}
	else if (n == 2) {
		left = l[0];
		right = l[1];
	}
	
	else {
		left = new bvh_node(l, n / 2, time0, time1);
		right = new bvh_node(l + n / 2, n - n / 2, time0, time1);
	}
	
	aabb box_left, box_right;

	if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
		std::cerr << "no bounding box in bvh_node constructor\n";
	
	box = surrounding_box(box_left, box_right);

}

bool bvh_node::hit(const Ray & r, float tmin, float tmax, hit_record & rec) const
{
	if (box.hit(r, tmin, tmax)) {
		hit_record left_rec, right_rec;
		bool hit_left = left->hit(r, tmin, tmax, left_rec);
		bool hit_right = right->hit(r, tmin, tmax, right_rec);
		if (hit_left && hit_right) {
			if (left_rec.t < right_rec.t)
				rec = left_rec;
			else
				rec = right_rec;
			return true;
		}
		else if (hit_left) {
			rec = left_rec;
			return true;
		}
		else if (hit_right) {
			rec = right_rec;
			return true;
		}
		else
			return false;
	}
	else return false;
}

bool bvh_node::bounding_box(float t0, float t1, aabb& b) const
{
	b = box;
	return true;
}