# 📌 Text RPG: 모험의 시작
**간단하고 클래식한 CLI(Text 기반) RPG 게임!**
* **1조 : 고수 아닙니다[(Notion)](https://teamsparta.notion.site/1-1ff2dc3ef51480ac981efcf0ba530ff3)**
* 팀원: 고명수, 김세훈, 김영훈, 김혁, 장주만

---

## 🎮 게임 소개

**Text RPG: 모험의 시작**은 C++로 구현된 콘솔 기반 RPG 게임입니다.  
플레이어는 다양한 몬스터와 전투를 벌이고, 아이템과 장비를 활용하여 성장합니다.  
상점에서 아이템을 사고팔 수 있으며, 보스를 물리치면 게임을 클리어할 수 있습니다.

- **플랫폼:** Windows 콘솔
- **언어:** C++
- **목표:** 보스 몬스터(드래곤) 처치 후 게임 클리어!
- **빌드버전:** C++14, Visual Studio 2022(17.14)

---
🔗🍀🖼️
## 🛝 구상도 및 흐름
![image](https://github.com/user-attachments/assets/c143e03b-d7ba-424a-9270-8e9c0ebdf78c)
--
![image](https://github.com/user-attachments/assets/f2711352-be8c-473d-b1c1-1306bf99bd34)
--
![image](https://github.com/user-attachments/assets/374fff45-f8ef-40cc-87ff-9e44906c9c08)
--
![image](https://github.com/user-attachments/assets/b83eb71d-f602-4107-8b65-7df86c1ce57b)

---

## 🏗️ 프로젝트 구조

```
├── main.cpp            : 프로그램 진입점, 메인 루프  
├── GameManager.{h,cpp} : 게임 전체 진행 및 관리  
├── Player.{h,cpp}      : 플레이어(싱글턴) 관리  
├── Monster.{h,cpp}     : 몬스터 및 파생 클래스 (Goblin, Orc, Troll, Boss)  
├── Item.{h,cpp}        : 아이템(소모품) 클래스  
├── Equipments.{h,cpp}  : 무기/방어구(장비) 클래스  
├── Shop.{h,cpp}        : 상점 시스템  
├── InputUtil.h         : 입력 유틸리티 함수  
├── PrintUtil.h         : 출력(타이틀, 메뉴) 유틸리티  
├── RandomUtil.h        : 난수 생성 유틸리티  
├── Constants.h         : 각종 상수(ENUM 등) 정의  
└── (기타 인터페이스 및 부속 파일)   
```

---

## ⛏️ 실행 방법
**01_TextRPG.exe** 다운로드 후 실행

---

## 🎥 데모(Demo) 영상
**[Youtube Link](https://www.youtube.com/watch?v=jYlGAG_jHOo)**

**TODO: 발표자료 링크 첨부**

---
## 🌟 주요 기능
> 직관적 CLI 기반 RPG
> * 플레이어 상태/전투/레벨업/상점/인벤토리 등 RPG의 핵심 요소 구현
> 
> 몬스터/보스와의 전투
> 
> 아이템/장비 관리
> * 소모품 사용, 무기/방어구 장착/해제
>   
> 상점 시스템
> * 아이템 구매/판매, 인벤토리 확인
>   
> 확장성 높은 OOP 설계
> * 추상 클래스/인터페이스/스마트포인터 등 활용

---

## 🛠️ 테스트
![image](https://github.com/user-attachments/assets/df04fdf3-5577-4394-8e9b-d34022e91305)
![image](https://github.com/user-attachments/assets/ce926112-633f-4dcf-af39-56fca0474344)

---

## 💻 코드 스타일 & 특징
* 객체지향적 구조(클래스/상속/추상화)
* 스마트포인터(std::unique_ptr) 기반 메모리 관리
* 입력/출력 유틸리티 분리
* 상수/ENUM 네임스페이스 관리
* 팀 단위 GitHub 협업/버전 관리

---

## 🚀 프로젝트 후기
![image](https://github.com/user-attachments/assets/3df85b48-6ba1-4339-b5d6-9366cf36abef)

---

## 🙏 참고
본 프로젝트는 스파르타 내일배움캠프(언리얼과정) 'C++ 게임 프로그래밍' 팀 프로젝트 과제를 위해 개발되었습니다.
