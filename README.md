# Unreal Engine Speech Bubble Log Plugin

> 로그를 말풍선 형태로 월드에 출력하는 플러그인

---

# 📌 Overview

기존 로그 출력 방식:

* `UE_LOG`
* `PrintString`

여기에 말풍선을 추가해서
로그를 **월드에서 직접 확인할 수 있게 만든 플러그인**이다.

```text
Log
 ├─ Output Log
 ├─ Screen Debug
 └─ Speech Bubble
```

---

# 🎯 특징

* 로그를 말풍선으로 출력
* 월드 공간 UI 지원 (빌보드 처리)
* Blueprint에서 바로 사용 가능
* 스타일을 DataAsset으로 분리
* Component 기반 구조 (캐릭터 코드 분리)

---

# 🏗️ 구조

```text
MyNBCLog/
├── MyNBCLog.uplugin
├── Content/
│   └── Content/
│       ├── Data/
│       │   └── DA_MySpartaSpeechStyle.uasset
│       └── Widgets/
│           ├── TextBalloon.uasset
│           └── WBP_MySpartaSpeechBubble.uasset
│
└── Source/
    └── MySpartaLog/
        ├── Components/
        │   └── MySpartaSpeechComponent
        ├── Data/
        │   ├── MySpartaSpeechStyleDataAsset
        │   └── MySpartaLogDeveloperSettings
        ├── Widgets/
        │   └── MySpartaSpeechBubbleWidgetBase
        ├── MySpartaLogBPLibrary
        └── TestActor
```

---

# 🔄 동작 흐름

```text
Blueprint / C++
      ↓
BPLibrary
      ↓
SpeechComponent
      ↓
WidgetComponent
      ↓
Widget
```

---

# 🧠 설계 포인트

* 말풍선 = UI가 아니라 **로그 출력 방식**
* 코드 / 에셋 / UI 분리
* DataAsset 기반 스타일 관리
* 외부 → Component → Widget 구조 유지

---

# 🚀 사용 방법

## 1. Actor에 Component 추가

```text
MySpartaSpeechComponent
```

## 2. Blueprint에서 호출

```cpp
LogTextToActor(this, "Hello");
LogTypedTextToActor(this, "마나 부족", Warning);
```

---

# 🎨 로그 타입

```text
Info / Warning / Error
```

---

# ⚠️ 구현하면서 정리된 포인트

* 플러그인 모듈은 `.uplugin`에서만 관리 (Target.cs 등록 ❌)
* BPLibrary 함수는 반드시 `static`
* TargetActor는 `Self` 기준으로 넘기는 게 안전
* Widget 직접 접근하지 말고 Component 통해서 처리
* 말풍선 UI는 **MaxWidth + WrapText 기반**으로 잡아야 안정적
