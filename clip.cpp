#include <cmath>
#include <iostream>
#include "vec3.h"
#include "clip.h"


namespace egc {
	float max(float a, float b) {
		if (a > b) return a;
		return b;
	}

	float min(float a, float b) {
		if (a < b) return a;
		return b;
	}

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		std::vector<vec3> normal = std::vector<vec3>(clipWindow.size());
		std::vector<vec3> pei = std::vector<vec3>(clipWindow.size());
		vec3 D = p2 - p1;
		vec3 z = vec3(0, 0, -1);
		float dx, dy;
		if (p1 == p2) {
			return 0;
		}
		for (int i = 0; i < clipWindow.size(); i++) {
			pei[i] = clipWindow[i];
			normal[i] = crossProduct(clipWindow[(i + 1) % clipWindow.size()] - clipWindow[i], z);
		}
		float t = 0, tE = 0, tL = 1;
		for (int i = 0; i < clipWindow.size(); i++) {
			float dotProd = dotProduct(normal[i], D);
			if (dotProd != 0) {
				t = dotProduct(normal[i], p1 - pei[i]) / (-dotProd);
				if (dotProd < 0) {
					tE = max(tE, t);
				}
				else {
					tL = min(tL, t);
				}
			}
		}
		if (tE > tL) {
			return -1;
		}
		vec3 v1 = p1, v2 = p2;
		p1 = v1 + (v2 - v1)*tE;
		p2 = v1 + (v2 - v1)*tL;
		return 0;
	}


	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code = std::vector<int>(4);
		float xMin = clipWindow[0].x, xMax = clipWindow[0].x, yMin = clipWindow[0].y, yMax = clipWindow[0].y;
		for (int i = 1; i < clipWindow.size(); i++) {
			if (clipWindow[i].x > xMax) xMax = clipWindow[i].x;
			if (clipWindow[i].x < xMin) xMin = clipWindow[i].x;
			if (clipWindow[i].y > yMax) yMax = clipWindow[i].y;
			if (clipWindow[i].y < yMin) yMin = clipWindow[i].y;
		}
		code[0] = 0; code[1] = 0; code[2] = 0; code[3] = 0;
		if (p.y < yMin) code[0] = 1;
		if (p.y > yMax) code[1] = 1;
		if (p.x > xMax) code[2] = 1;
		if (p.x < xMin) code[3] = 1;
		return code;
	}

	bool inDispalyArea(std::vector<int> cod) {
		if (cod[0] + cod[1] + cod[2] + cod[3] == 0) return true;
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		if (inDispalyArea(cod1) && inDispalyArea(cod2)) return true;
		return false;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		for (int i = 0; i < 3; i++) {
			if (cod1[i] + cod2[i] == 2) return true;
		}
		return false;
	}

	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		std::vector<int> cod1 = std::vector<int>(4);
		std::vector<int> cod2 = std::vector<int>(4);
		float xMin = clipWindow[0].x, xMax = clipWindow[0].x, yMin = clipWindow[0].y, yMax = clipWindow[0].y;
		for (int i = 1; i < clipWindow.size(); i++) {
			if (clipWindow[i].x > xMax) xMax = clipWindow[i].x;
			if (clipWindow[i].x < xMin) xMin = clipWindow[i].x;
			if (clipWindow[i].y > yMax) yMax = clipWindow[i].y;
			if (clipWindow[i].y < yMin) yMin = clipWindow[i].y;
		}

		if (p1 == p2) {
			cod1 = computeCSCode(clipWindow, p1);
			if (inDispalyArea(cod1)) return true;
			return false;
		}
		while (true) {
			cod1 = computeCSCode(clipWindow, p1);
			cod2 = computeCSCode(clipWindow, p2);
			if (simpleAcceptance(cod1, cod2)) return 0;
			if (simpleRejection(cod1, cod2)) return -1;
			if (inDispalyArea(cod1)) {
				vec3 aux = p1;
				p1 = p2;
				p2 = aux;
				std::vector<int> aux2 = cod1;
				cod1 = cod2;
				cod2 = aux2;
			}
			if (cod1[0] == 1 && p1.y != p2.y) {
				p1.x += (p2.x - p1.x) / (p2.y - p1.y)*(yMin - p1.y);
				p1.y = yMin;
			}
			if (cod1[1] == 1 && p1.y != p2.y) {
				p1.x += (p2.x - p1.x) / (p2.y - p1.y)*(yMax - p1.y);
				p1.y = yMax;
			}
			if (cod1[2] == 1 && p1.x != p2.x) {
				p1.y += ((p2.y - p1.y) / (p2.x - p1.x))*(xMax - p1.x);
				p1.x = xMax;
			}
			if (cod1[3] == 1 && p1.x != p2.x) {
				p1.y += ((p2.y - p1.y) / (p2.x - p1.x))*(xMin - p1.x);
				p1.x = xMin;
			}
		}

	}
}