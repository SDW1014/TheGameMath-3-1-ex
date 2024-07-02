# README

## 프로젝트 개요
이 프로젝트는 2D 게임의 객체 위치를 업데이트하고, 그걸 화면에 렌더링하는 기능을 구현한 거야. 게임 로직이랑 렌더링 로직이 공유하는 변수를 사용해서, 사용자 입력에 따라 객체의 위치를 변경하고, 그 위치를 기반으로 화면에 시각적 요소를 그리는 구조야.

## 코드 설명

### 1. 변수 선언
Vector2 currentPosition(100.0f, 100.0f); // 현재 위치
- `currentPosition` 변수는 객체의 현재 위치를 저장해. 초기값은 (100.0, 100.0)으로 설정돼 있어.

### 2. 게임 로직 업데이트 함수: `SoftRenderer::Update2D`
이 함수는 게임 로직을 업데이트해.

```cpp
void SoftRenderer::Update2D(float InDeltaSeconds)
{
    auto& g = Get2DGameEngine();
    const InputManager& input = g.GetInputManager();

    static float moveSpeed = 100.0f;

    Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis));
    Vector2 deltaPosition = inputVector * moveSpeed * InDeltaSeconds;

    currentPosition += deltaPosition;
}
```

- `Get2DGameEngine()`를 통해 게임 엔진을 참조해.
- `InputManager`를 사용해서 입력을 받아와.
- `moveSpeed`는 이동 속도를 나타내는 상수야.
- `inputVector`는 X축과 Y축 입력을 받아서 벡터로 저장해.
- `deltaPosition`은 입력 벡터에 속도랑 시간(`InDeltaSeconds`)을 곱해서 구한 이동 거리야.
- `currentPosition`에 `deltaPosition`을 더해서 현재 위치를 업데이트해.

### 3. 렌더링 함수: `SoftRenderer::Render2D`
이 함수는 업데이트된 위치를 기반으로 객체를 렌더링해.

```cpp
void SoftRenderer::Render2D()
{
    auto& r = GetRenderer();
    const auto& g = Get2DGameEngine();

    DrawGizmo2D();

    static float lineLength = 500.0f;
    Vector2 lineStart = currentPosition * lineLength;
    Vector2 lineEnd = currentPosition * -lineLength;
    r.DrawLine(lineStart, lineEnd, LinearColor::LightGray);

    r.DrawPoint(currentPosition, LinearColor::Blue);
    r.DrawPoint(currentPosition + Vector2::UnitX, LinearColor::Blue);
    r.DrawPoint(currentPosition - Vector2::UnitX, LinearColor::Blue);
    r.DrawPoint(currentPosition + Vector2::UnitY, LinearColor::Blue);
    r.DrawPoint(currentPosition - Vector2::UnitY, LinearColor::Blue);
    r.DrawPoint(currentPosition + Vector2::One, LinearColor::Blue);
    r.DrawPoint(currentPosition - Vector2::One, LinearColor::Blue);
    r.DrawPoint(currentPosition + Vector2(1.f, 1.f), LinearColor::Blue);
    r.DrawPoint(currentPosition - Vector2(1.f, 1.f), LinearColor::Blue);

    r.PushStatisticText("Coordinate ; " + currentPosition.ToString());
}
```

- `GetRenderer()`를 통해 렌더러를 참조해.
- `DrawGizmo2D()`를 호출해서 배경에 격자를 그려.
- `lineLength`는 선의 길이를 나타내는 상수야.
- `lineStart`와 `lineEnd`는 현재 위치를 기준으로 그려질 선의 시작과 끝 지점이야.
- `r.DrawLine`을 사용해서 선을 그려.
- `r.DrawPoint`를 사용해서 현재 위치랑 그 주변 여러 지점에 점을 그려.
- `PushStatisticText`를 통해 현재 좌표를 텍스트로 출력해.
