#pragma once
#include "util.h"
inline void reverseImage(ID2D1RenderTarget* RenderTarget, float x, float y, float height) {
	D2D1::Matrix3x2F matSkew = D2D1::Matrix3x2F::Skew(271, 271, D2D1::Point2F(x, y - height / 2));
	D2D1::Matrix3x2F matScale = D2D1::Matrix3x2F::Scale(0.0175f, 0.0175f, D2D1::Point2F(x, y- height / 2));
	D2D1::Matrix3x2F matRotation = D2D1::Matrix3x2F::Rotation(-90, D2D1::Point2F(x,y - height / 2));
	RenderTarget->SetTransform(matScale * matSkew * matRotation);
}

inline bool isinRight_AngledTriangle(D2D_POINT_2F point, D2D_POINT_2F first, D2D_POINT_2F second, bool fromRight) {
	D2D_POINT_2F start, end;
	if (first.x <= second.x && first.y <= second.y || first.x >= second.x && first.y <= second.y) {
		start = second;
		end = first;
	}
	else if (first.x >= second.x && first.y >= second.y || first.x <= second.x && first.y >= second.y) {
		start = first;
		end = second;
	}

	float Distance = MY_UTIL::getDistance(start.x, start.y, end.x, end.y);
	float compareDis = MY_UTIL::getDistance(start.x, start.y, point.x, point.y);
	if (compareDis <= Distance) {
		if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) >= 90.0f) {
			if (fromRight) {
				if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) >= MY_UTIL::getAngle(start.x, start.y, point.x, point.y) && MY_UTIL::getAngle(start.x, start.y, point.x, point.y) >= 90.0f) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) <= MY_UTIL::getAngle(start.x, start.y, point.x, point.y) && MY_UTIL::getAngle(start.x, start.y, point.x, point.y) <= 180.0f) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			if (fromRight) {
				if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) >= MY_UTIL::getAngle(start.x, start.y, point.x, point.y)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) <= MY_UTIL::getAngle(start.x, start.y, point.x, point.y) && MY_UTIL::getAngle(start.x, start.y, point.x, point.y) <= 90.0f) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	else return false;
}

inline bool CollisionLineRect(D2D_POINT_2F _start, D2D_POINT_2F _end, D2D_RECT_F rect) {
	// 0~180 사이로 계산하기 위함
	D2D_POINT_2F start, end;
	if (_start.y <= _end.y) {
		start = _end;
		end = _start;
	}
	else {
		start = _start;
		end = _end;
	}

	//Rect가 line을 포함하고 있을경우
	if (rect.left <= start.x && rect.left <= end.x && rect.right >= start.x && rect.right >= end.x &&
		rect.top <= start.y && rect.top <= end.y && rect.bottom >= start.y && rect.bottom >= end.y) {
		return true;
	}
	if (IsInRect(start, rect) || IsInRect(end, rect)) {
		return true;
	}

	//각도에 따라
	if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) == 90.0f) {
		if (((rect.top <= start.y && rect.top >= end.y) || (rect.bottom <= start.y && rect.bottom >= end.y)) && rect.left <= start.x && rect.right >= start.x) {
			return true;
		}
	}
	else if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) == 0.0f || MY_UTIL::getAngle(start.x, start.y, end.x, end.y) == 180.0f) {
		if (start.x <= end.x) {
			if (((rect.left >= start.x && rect.left <= end.x) || (rect.right >= start.x && rect.right <= end.x)) && rect.top <= start.y && rect.bottom >= start.y) {
				return true;
			}
		}
		else {
			if (((rect.left >= end.x && rect.left <= start.x) || (rect.right >= end.x && rect.right <= end.x)) && rect.top <= start.y && rect.bottom >= start.y) {
				return true;
			}
		}
	}
	else {
		if ((start.x >= rect.left && end.x >= rect.left && start.x <= rect.right && end.x <= rect.right && ((rect.top <= start.y && rect.top >= end.y) || (rect.bottom <= start.y && rect.bottom >= end.y)))) {
			return true;
		}
		if ((start.y >= rect.top && end.y >= rect.top && start.y <= rect.bottom && end.y <= rect.bottom)) {
			if (start.x <= end.x) {
				if (((rect.left >= start.x && rect.left <= end.x) || (rect.right >= start.x && rect.right <= end.x))) {
					return true;
				}
			}
			else {
				if (((rect.left >= end.x && rect.left <= start.x) || (rect.right >= end.x && rect.right <= end.x))) {
					return true;
				}
			}
		}

		if (MY_UTIL::getAngle(start.x, start.y, end.x, end.y) > 90) {
			//isinRight_AngledTriangle({ rect.left, rect.bottom }, start, end, false) && 
			if ((isinRight_AngledTriangle({ rect.right, rect.top }, start, end, true) && (MY_UTIL::getAngle(start.x, start.y, rect.left, rect.bottom) <= MY_UTIL::getAngle(start.x, start.y, end.x, end.y) + 180 && MY_UTIL::getAngle(start.x, start.y, rect.left, rect.bottom) >= MY_UTIL::getAngle(start.x, start.y, end.x, end.y))) ||
				(isinRight_AngledTriangle({ rect.left, rect.bottom }, start, end, false) && (MY_UTIL::getAngle(start.x, start.y, rect.right, rect.top) <= MY_UTIL::getAngle(start.x, start.y, end.x, end.y)))) {
				return true;
			}
		}
		else { // MY_UTIL::getAngle(start.x, start.y, end.x, end.y) < 90
			   //isinRight_AngledTriangle({ rect.right, rect.bottom }, start, end, false) && 
			if (isinRight_AngledTriangle({ rect.left, rect.top }, start, end, false) && (MY_UTIL::getAngle(start.x, start.y, rect.right, rect.bottom) >= MY_UTIL::getAngle(start.x, start.y, end.x, end.y) + 180 || MY_UTIL::getAngle(start.x, start.y, rect.right, rect.bottom) <= MY_UTIL::getAngle(start.x, start.y, end.x, end.y)) ||
				isinRight_AngledTriangle({ rect.right, rect.bottom }, start, end, true) && (MY_UTIL::getAngle(start.x, start.y, rect.left, rect.top) >= MY_UTIL::getAngle(start.x, start.y, end.x, end.y))) {
				return true;
			}
		}
	}
	return false;
}