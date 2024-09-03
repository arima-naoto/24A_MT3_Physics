#include "Graphics.h"
#include "Calculator.h"

void Graphics::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {

	const float kGirdHalfWidth = 2.0f;
	const int32_t kSubdivision = 10;
	const float kGirdEvery = (kGirdHalfWidth * 2.0f) / float(kSubdivision);

	for (int32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		float x = -kGirdHalfWidth + (xIndex * kGirdEvery);
		
		Vector3 start ={ x,0,-kGirdHalfWidth };
		Vector3 end = { x,0,kGirdHalfWidth };

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewPortMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewPortMatrix);

		Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, x == 0.0f ? BLACK : color);

	}

	for (int32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		float z = -kGirdHalfWidth + (xIndex * kGirdEvery);

		Vector3 start = { -kGirdHalfWidth,0,z };
		Vector3 end = { kGirdHalfWidth,0,z };

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewPortMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewPortMatrix);

		Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, z == 0.0f ? BLACK : color);

	}

}

void Graphics::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const int32_t kSubdivision = 10; // 分割数
	const float kLonEvery = (2.0f * float(M_PI)) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision; // 緯度分割1つ分の角度

	// 緯度の方向に分割 -π/2～π/2
	for (int32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; // 現在の緯度
		float nextLat = lat + kLatEvery; // 次の緯度

		// 経度の方向に分割 0～2π
		for (int32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			float nextLon = lon + kLonEvery; // 次の経度

			// ワールド座標系のa, b, cを求める
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(nextLat) * cosf(nextLon),
				sphere.center.y + sphere.radius * sinf(nextLat),
				sphere.center.z + sphere.radius * cosf(nextLat) * sinf(nextLon)
			};

			// ワールド座標系のa, b, cをスクリーン座標系まで変換
			Vector3 ScreenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 ScreenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			// abで線を引く
			Novice::DrawLine((int)ScreenA.x, (int)ScreenA.y, (int)ScreenB.x, (int)ScreenB.y, color);

			// bcで線を引く
			Novice::DrawLine((int)ScreenB.x, (int)ScreenB.y, (int)ScreenC.x, (int)ScreenC.y, color);
		}
	}

}

void Graphics::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 center = plane.distance* plane.normal;

	Vector3 perpendiculars[4];
	perpendiculars[0] = Calculator::Normalize(Calculator::Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Calculator::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = 2.0f * perpendiculars[index];
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	///pointsをそれぞれ結んで、DrawLineで平面を描画する
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
}

void Graphics::DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	int segments = 32; // ベジエ曲線を分割するセグメント数
	Vector3 previousPoint = Transform(controlPoint0, viewProjectionMatrix);
	previousPoint = Transform(previousPoint, viewportMatrix);

	for (int i = 1; i <= segments; i++) {
		float t = static_cast<float>(i) / static_cast<float>(segments);

		// ベジエ曲線の各点を計算
		Vector3 p0p1 = Lerp(controlPoint0, controlPoint1, t);
		Vector3 p1p2 = Lerp(controlPoint1, controlPoint2, t);
		Vector3 currentPoint = Lerp(p0p1, p1p2, t);

		currentPoint = Transform(currentPoint, viewProjectionMatrix);
		currentPoint = Transform(currentPoint, viewportMatrix);

		// 座標を整数に変換して線を描画
		Novice::DrawLine(static_cast<int>(previousPoint.x), static_cast<int>(previousPoint.y),
			static_cast<int>(currentPoint.x), static_cast<int>(currentPoint.y),
			color);

		// 現在の点を次の線の始点として設定
		previousPoint = currentPoint;
	}
}
