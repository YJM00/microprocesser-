### 수업 실습키트

<img width="755" height="484" alt="image" src="https://github.com/user-attachments/assets/44b2d370-59d4-4b22-b7e2-1474ad702f11" />

--- 

---







# Term Project: 스마트 쓰레기통


## 프로젝트의 개발 목적
 우리는 이번 프로젝트의 모토를 ‘실생활에서 사용할 수 있는 유용한 제품’으로 정했다. 
 그러한 점에서 봤을 때 스마트 쓰레기통은 우리의 모토와 잘 어울리는 주제라고 할 수 있다.
 스마트 쓰레기통은 물체를 감지해 자동으로 뚜껑을 열고 닫을 수 있으며 쓰레기통 내부의 용량이 얼마나 찼는지도 한눈에 알 수 있다. 
 이러한 기능들을 구현하기 위해 한 학기 동안 마이크로프로세서 실험 수업을 통해 배운 내용을 정확히 이해하고 제품의 적절한 곳에 적용 및 응용해 스마트 쓰레기통을 제작해 나간다.

 ---
 
 ### HW 블록도
 <img width="618" height="197" alt="image" src="https://github.com/user-attachments/assets/b4fdc2a4-34be-4242-9af4-d89adede8c33" />

 ---

 ### SW 흐름도
 <img width="337" height="548" alt="image" src="https://github.com/user-attachments/assets/34bfec95-7b0a-43e6-94e9-877eabfe412c" />
 <img width="291" height="325" alt="image" src="https://github.com/user-attachments/assets/f2b5b819-45c6-4621-901a-29c584db1508" />

---

### 회로도
<img width="636" height="353" alt="image" src="https://github.com/user-attachments/assets/bbda19f6-37af-4567-822d-ec4f4d901683" />

PE4: 전면 초음파 센서 Trigger

PE5: 전면 초음파 센서 Echo

PE6: 내부 초음파 센서 Trigger

PE7: 내부 초음파 센서 Echo

PB6: 서보 모터

PD0: LCD Display(I2C 방식) SCL

PD1: LCD Display(I2C 방식) SDA

PG0: 3색 LED RED

PG1: 3색 LED GREEN

PG2: 3색 LED BLUE

---

### 부품

1.AVR 나노

<img width="358" height="254" alt="image" src="https://github.com/user-attachments/assets/6fbe5f1a-0d53-44b7-862b-b1076b8820e8" />

2. 초음파 센서(HC-SR04)
   
<img width="263" height="160" alt="image" src="https://github.com/user-attachments/assets/f40c481b-c8ea-4c65-b924-e2a6596e15d0" />

3.서보 모터(SG90)

<img width="204" height="197" alt="image" src="https://github.com/user-attachments/assets/24ad7a69-a645-4845-84f9-226a39a12aae" />

4. 3색 LED

<img width="185" height="172" alt="image" src="https://github.com/user-attachments/assets/3dc477d4-1d35-487a-b368-1939c207a1ea" />

5.i2c LCD 16x2

<img width="312" height="216" alt="image" src="https://github.com/user-attachments/assets/cc6ed8f6-b54d-4db0-9f69-cb728daa275f" />

6. 만능기판

<img width="558" height="383" alt="image" src="https://github.com/user-attachments/assets/9181ee50-6b66-4cd3-bcfe-3b81a11dbc6a" />

7. AA배터리
   
<img width="288" height="359" alt="image" src="https://github.com/user-attachments/assets/b0167177-783d-4c69-8c6f-b76a1cbf2857" />

   
-----

### 개발 환경## 프로젝트의 개발 목적
 우리는 이번 프로젝트의 모토를 ‘실생활에서 사용할 수 있는 유용한 제품’으로 정했다. 
 그러한 점에서 봤을 때 스마트 쓰레기통은 우리의 모토와 잘 어울리는 주제라고 할 수 있다.
 스마트 쓰레기통은 물체를 감지해 자동으로 뚜껑을 열고 닫을 수 있으며 쓰레기통 내부의 용량이 얼마나 찼는지도 한눈에 알 수 있다. 
 이러한 기능들을 구현하기 위해 한 학기 동안 마이크로프로세서 실험 수업을 통해 배운 내용을 정확히 이해하고 제품의 적절한 곳에 적용 및 응용해 스마트 쓰레기통을 제작해 나간다.

 ---
 
 ### HW 블록도
 <img width="618" height="197" alt="image" src="https://github.com/user-attachments/assets/b4fdc2a4-34be-4242-9af4-d89adede8c33" />

 ---

 ### SW 흐름도
 <img width="337" height="548" alt="image" src="https://github.com/user-attachments/assets/34bfec95-7b0a-43e6-94e9-877eabfe412c" />
 <img width="291" height="325" alt="image" src="https://github.com/user-attachments/assets/f2b5b819-45c6-4621-901a-29c584db1508" />

---

### 회로도
<img width="636" height="353" alt="image" src="https://github.com/user-attachments/assets/bbda19f6-37af-4567-822d-ec4f4d901683" />

PE4: 전면 초음파 센서 Trigger

PE5: 전면 초음파 센서 Echo

PE6: 내부 초음파 센서 Trigger

PE7: 내부 초음파 센서 Echo

PB6: 서보 모터

PD0: LCD Display(I2C 방식) SCL

PD1: LCD Display(I2C 방식) SDA

PG0: 3색 LED RED

PG1: 3색 LED GREEN

PG2: 3색 LED BLUE

---

### 부품

1.AVR 나노

<img width="358" height="254" alt="image" src="https://github.com/user-attachments/assets/6fbe5f1a-0d53-44b7-862b-b1076b8820e8" />

2. 초음파 센서(HC-SR04)
   
<img width="263" height="160" alt="image" src="https://github.com/user-attachments/assets/f40c481b-c8ea-4c65-b924-e2a6596e15d0" />

3.서보 모터(SG90)

<img width="204" height="197" alt="image" src="https://github.com/user-attachments/assets/24ad7a69-a645-4845-84f9-226a39a12aae" />

4. 3색 LED

<img width="185" height="172" alt="image" src="https://github.com/user-attachments/assets/3dc477d4-1d35-487a-b368-1939c207a1ea" />

5.i2c LCD 16x2

<img width="312" height="216" alt="image" src="https://github.com/user-attachments/assets/cc6ed8f6-b54d-4db0-9f69-cb728daa275f" />

6. 만능기판

<img width="558" height="383" alt="image" src="https://github.com/user-attachments/assets/9181ee50-6b66-4cd3-bcfe-3b81a11dbc6a" />

7. AA배터리

   
-----

### 개발 환경
![1123](https://github.com/user-attachments/assets/42405df8-6305-416b-83f9-ded88c5665b1)
<img width="192" height="192" alt="teraterm" src="https://github.com/user-attachments/assets/411a40a1-f743-4981-acdd-f12c5ba7782d" />


---

### 시제품 사진
 <img width="643" height="408" alt="image" src="https://github.com/user-attachments/assets/42f9d67d-4999-48b7-80bb-9bfbf783d541" />
 
<img width="463" height="303" alt="image" src="https://github.com/user-attachments/assets/168cf465-cc63-426f-940a-ef564362968e" />

---

### 후기 및 배운점
이번 프로젝트를 통해 학부 시절 배운 C언어 프로그래밍, 전기전자회로 실험 등의 기초지식을 실제 제작 과정에 적용할 수 있었다. 특히 라디오 제작 기판 납땜을 바탕으로 브레드보드를 사용하지 않고 직접 만능기판에 부품을 납떔하여 하드웨어적 지식을 쌓을 수 있었고, 부품 데이터시트를 참고해 배선을 효율적으로 설계하는 능력도 키울 수 있었다. 진행 과정에서 LCD와 로드셀 같은 부품 문제로 시행착오가 많았지만, 팀원 간 협력과 역할 분담을 통해 문제를 극복하며 프로젝트를 완성할 수 있었다. 이번 경험은 실무 능력과 자신감을 크게 높여주는 계기가 되었다.
