
#include "Precompiled.h"
#include "SoftRenderer.h"
#include <random>
using namespace CK::DD;

// ���ڸ� �׸��� �Լ�
void SoftRenderer::DrawGizmo2D()
{
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// �׸��� ����
	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	// ���� ���� ���
	Vector2 viewPos = g.GetMainCamera().GetTransform().GetPosition();
	Vector2 extent = Vector2(_ScreenSize.X * 0.5f, _ScreenSize.Y * 0.5f);

	// ���� �ϴܿ������� ���� �׸���
	int xGridCount = _ScreenSize.X / _Grid2DUnit;
	int yGridCount = _ScreenSize.Y / _Grid2DUnit;

	// �׸��尡 ���۵Ǵ� ���ϴ� ��ǥ �� ���
	Vector2 minPos = viewPos - extent;
	Vector2 minGridPos = Vector2(ceilf(minPos.X / (float)_Grid2DUnit), ceilf(minPos.Y / (float)_Grid2DUnit)) * (float)_Grid2DUnit;
	ScreenPoint gridBottomLeft = ScreenPoint::ToScreenCoordinate(_ScreenSize, minGridPos - viewPos);

	for (int ix = 0; ix < xGridCount; ++ix)
	{
		r.DrawFullVerticalLine(gridBottomLeft.X + ix * _Grid2DUnit, gridColor);
	}

	for (int iy = 0; iy < yGridCount; ++iy)
	{
		r.DrawFullHorizontalLine(gridBottomLeft.Y - iy * _Grid2DUnit, gridColor);
	}

	ScreenPoint worldOrigin = ScreenPoint::ToScreenCoordinate(_ScreenSize, -viewPos);
	r.DrawFullHorizontalLine(worldOrigin.Y, LinearColor::Red);
	r.DrawFullVerticalLine(worldOrigin.X, LinearColor::Green);
}

// ���� ������Ʈ ���


// ���� �� �ε��� ����ϴ� �Լ�
void SoftRenderer::LoadScene2D()
{
	// ���� �� �ε����� ����ϴ� ��� �� �ֿ� ���۷���
	auto& g = Get2DGameEngine();

}

// ���� ������ ������ ������ �����ϴ� ����
// 2024 07 02 VALUE START =================================================================================================
// ���� : ���� ������ ������ ������ �����ϴ� ������ �����Ѵ�.

Vector2 currentPosition(100.0f, 100.0f); // ���� ��ġ
// 2024 07 02 VALUE END ===================================================================================================

// ���� ������ ����ϴ� �Լ�
void SoftRenderer::Update2D(float InDeltaSeconds)
{
	// ���� �������� ����ϴ� ��� �� �ֿ� ���۷���
	auto& g = Get2DGameEngine();
	const InputManager& input = g.GetInputManager();

	// ���� ������ ���� ����

	// 2024 07 02 UPDATE START =============================================================================================
	// ���� : ���� ��ġ�� �̵���Ű�� ������ �����Ѵ�.

	static float moveSpeed = 100.0f;										// �̵� �ӵ�
	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)); // �Է� ����
	Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;		// �̵���

	currentPosition += deltaPosition;										// ���� ��ġ �̵�
	// 2024 07 02 UPDATE END ===============================================================================================
}

// ������ ������ ����ϴ� �Լ�
void SoftRenderer::Render2D()
{
	// ������ �������� ����ϴ� ��� �� �ֿ� ���۷���
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// ��濡 ���� �׸���
	DrawGizmo2D();

	// ������ ������ ���� ����

	// 2024 07 02 RENDER START =============================================================================================
	// ���� : DrawPoint() �Լ��� �̿��Ͽ� ���� ��ġ�� ǥ���ϰ�, DrawLine() �Լ��� �̿��Ͽ� ���� ��ġ���� ���� �׸���.
	
	static float lineLength = 500.0f;										// ���� ����
	Vector2 lineStart = currentPosition * lineLength;						// ���� ������
	Vector2 lineEnd = currentPosition * -lineLength;						// ���� ����		
	r.DrawLine(lineStart, lineEnd, LinearColor::LightGray);					// �� �׸���	

	r.DrawPoint(currentPosition, LinearColor::Blue);						// ���� ��ġ ǥ��
	r.DrawPoint(currentPosition + Vector2::UnitX, LinearColor::Blue);		// ���� ��ġ���� X������ 1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition - Vector2::UnitX, LinearColor::Blue);		// ���� ��ġ���� X������ -1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition + Vector2::UnitY, LinearColor::Blue);		// ���� ��ġ���� Y������ 1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition - Vector2::UnitY, LinearColor::Blue);		// ���� ��ġ���� Y������ -1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition + Vector2::One, LinearColor::Blue);			// ���� ��ġ���� �밢������ 1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition - Vector2::One, LinearColor::Blue);			// ���� ��ġ���� �밢������ -1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition + Vector2(1.f, 1.f), LinearColor::Blue);	// ���� ��ġ���� �밢������ 1��ŭ �̵��� ��ġ ǥ��
	r.DrawPoint(currentPosition - Vector2(1.f, 1.f), LinearColor::Blue);	// ���� ��ġ���� �밢������ -1��ŭ �̵��� ��ġ ǥ��

	r.PushStatisticText("Coordinate ; " + currentPosition.ToString());		// ���� ��ġ ��ǥ ���
	// 2024 07 02 RENDER END ===============================================================================================
}

// �޽ø� �׸��� �Լ�
void SoftRenderer::DrawMesh2D(const class DD::Mesh& InMesh, const Matrix3x3& InMatrix, const LinearColor& InColor)
{
}

// �ﰢ���� �׸��� �Լ�
void SoftRenderer::DrawTriangle2D(std::vector<DD::Vertex2D>& InVertices, const LinearColor& InColor, FillMode InFillMode)
{
}
