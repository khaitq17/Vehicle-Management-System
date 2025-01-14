# HỆ THỐNG QUẢN LÝ XE

## 1. Giới thiệu
Hệ thống quản lý xe được thiết kế để kiểm soát và quản lý phương tiện ra/vào thông qua thẻ RFID. 

Hệ thống hoạt động trên vi điều khiển STM32F1, sử dụng các thiết bị ngoại vi để nhận diện thẻ, lưu trữ dữ liệu, và điều khiển các thành phần liên quan.

## 2. Các thiết bị và giao tiếp
- **STM32F1**: Vi điều khiển trung tâm, điều phối toàn bộ hệ thống
- **RFID Module** (MFRC522 - SPI): Đọc UID từ thẻ RFID
- **SD Card** (SPI): Lưu trữ danh sách UID trong file CSV
- **Servo** (180°): Điều khiển mở/đóng thanh chắn
- **LED** (tích hợp trong STM32F1): Đèn LED thông báo  
- **USB to TTL** (UART): Theo dõi trạng thái của chương trình 

## 3. Kiến trúc phần mềm

### 3.1. Cấu trúc thư mục

![image](https://github.com/user-attachments/assets/c5f3e58e-ab89-4efe-bdb5-0a83635a5e93)


### 3.2. Thuật toán chính
- Load UID từ file CSV vào Linked List.
- Quét thẻ và lấy UID.
- Kiểm tra UID bằng thuật toán Binary Search trên Linked List:
	- Nếu thẻ hợp lệ, quay Servo để mở thanh chắn
	- Nếu thẻ không hợp lệ, không thực hiện thao tác nào
- Ghi trạng thái thao tác file, thông tin thẻ và tính hợp lệ của thẻ hiển thị qua UART.

## 4. Hướng dẫn sử dụng
### 4.1. Kết nối phần cứng
- **RFID module**: Sử dụng SPI2  
    - SDA (PB12)  
    - SCK (PB13)  
    - MOSI (PB15)  
    - MISO (PB14)  
    - GND (GND)  
    - 3.3V (3.3V)  

- **SD Card module**: Sử dụng SPI1  
    - CS (PA4)  
    - SCK (PA5)  
    - MOSI (PA7)  
    - MISO (PA6)  
    - VCC (5V)  
    - GND (GND)  

- **Servo**: Sử dụng PWM (PA0)

- **LED**: Tích hợp trong chân PC13 

- **USB to TTL**: Sử dụng USART1  
    - GND (GND)  
    - RXD (PA9)  
    - TXD (PA10)  
    - 3.3V (3.3V)  

### 4.2. Chạy chương trình
- Nạp chương trình vào STM32F1 qua ST-Link
- Cấp nguồn và khởi động hệ thống

## 5. Kiểm thử
### 5.1. Unit Test
#### 5.1.1. RFID module
- Mục đích: Đảm bảo rằng module RFID có thể đọc UID từ thẻ RFID chính xác.
- Phương pháp: Sử dụng 1 thẻ và 1 khóa từ đưa lại gần module RFID, sử dụng LED để nhận biết.
- Kết quả:
	- Sáng LED ở chân PC13 nếu thẻ/khóa từ được phát hiện
	- Mở debug để xem UID đọc được
	
#### 5.1.2. SD Card module
- Mục đích: Kiểm tra khả năng đọc và ghi file CSV trên thẻ SD.
- Phương pháp: Kiểm tra việc ghi dữ liệu vào file CSV và sau đó đọc lại dữ liệu để xác minh.
- Kết quả: 
	- Nháy LED ở chân PC13 nếu ghi thông tin vào file thành công
	- Mở debug để xem thông tin vừa ghi vào file 

#### 5.1.3. Servo
- Mục đích: Kiểm tra khả năng điều khiển servo quay đến các góc 0° và 90°.
- Phương pháp: Kiểm tra servo để đảm bảo rằng nó có thể quay đúng các góc yêu cầu.
- Kết quả: Servo sẽ quay được các góc quay theo mong muốn.

#### 5.1.4. USB to TTL
- Mục đích: Kiểm tra khả năng giao tiếp UART qua USB to TTL và gửi log hiển thị lên máy tính.
- Phương pháp: Kiểm tra việc gửi dữ liệu (log) từ thiết bị qua cổng USB tới máy tính và đảm bảo dữ liệu được hiển thị đúng.
- Kết quả: Dữ liệu truyền qua UART sẽ được hiển thị trong phần mềm Hercules trên máy tính.

### 5.2. Integration Test
#### 5.2.1. Kết hợp RFID và USB to TTL để xem UID của thẻ
- Mục đích: Kiểm tra module RFID có thể đọc UID từ thẻ RFID chính xác và ghi UID đọc được lên phần mềm Hercules trên máy tính.
- Phương pháp: Sử dụng các thẻ và khóa từ đưa lại gần module RFID, khi phát hiện thẻ sẽ đọc và in UID lên màn hình.
- Kết quả: UID của các thẻ/khóa từ được quét sẽ hiển thị trên Hercules.

#### 5.2.2. Kết hợp SD Card và USB to TTL để xem thông tin ghi trong file CSV
- Mục đích: Kiểm tra khả năng đọc và ghi file CSV trên thẻ SD và hiển thị lên phần mềm Hercules trên máy tính.
- Phương pháp: Thực hiện các thao tác đọc, ghi, xóa file, sau mỗi thao tác kiểm tra nội dung trong file trên Hercules.
- Kết quả: Nội dung file sẽ được hiển thị trên Hercules sau các thao tác.

#### 5.2.3. Kết hợp RFID và SD Card để lưu UID thẻ vào file CSV
- Mục đích: Lưu trữ toàn bộ thẻ/khóa từ sử dụng cho hệ thống vào file được lưu trong SD Card.
- Phương pháp: Sử dụng các thẻ và khóa từ đưa lại gần module RFID, khi phát hiện thẻ sẽ ghi UID của thẻ đó vào 1 file CSV và lưu vào SD Card.
- Kết quả: SD Card sẽ chứa 1 file CSV bao gồm tất cả các thẻ/khóa từ sử dụng cho hệ thống. 

### 5.3. System Test
Quét thẻ, kiểm tra tính hợp lệ của thẻ và kiểm tra toàn bộ hệ thống

## 6. Tính năng mở rộng
