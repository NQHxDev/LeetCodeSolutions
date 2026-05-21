# Tư duy thiết kế: Divide Two Integers

## Vấn đề: Cơn ác mộng đo đạc và vách đá giới hạn

Hãy tưởng tượng chúng ta được giao một nhiệm vụ đo đạc địa lý: Tìm xem có thể đặt bao nhiêu cây thước tiêu chuẩn có chiều dài `divisor` xếp tiếp nối nhau trên một đoạn đường dài `dividend`.
Tuy nhiên, có hai trở ngại cực kỳ khắc nghiệt:
- Chúng ta không được phép sử dụng bất kỳ công cụ nhân (`*`), chia (`/`) hay chia lấy dư (`%`) nào.
- Chúng ta phải làm việc trong một môi trường có giới hạn nghiêm ngặt về kích thước của các con số (signed 32-bit integer). 

Nếu sử dụng cách **Trừ liên tiếp (Naive Subtraction)**:
- Ta lấy đoạn đường dài `dividend` rồi cứ trừ đi từng đoạn `divisor` một cho đến khi phần còn lại nhỏ hơn thước đo.
- **Hệ quả cực đoan**: Nếu đoạn đường dài tới 2 tỷ mét mà thước đo chỉ dài 1 mét, chúng ta sẽ phải thực hiện tới 2 tỷ bước đi bộ. Máy tính sẽ hoàn toàn kiệt sức và chương trình sẽ bị treo (lỗi quá giới hạn thời gian TLE).

**Vách đá giới hạn (Tràn số)**:
Trong thế giới số nguyên 32-bit có ký hiệu, dãy số giống như một cái cân bập bênh bất đối xứng.
- Bên số dương chỉ có thể đi lên tới tối đa `2.147.483.647` (INT_MAX).
- Bên số âm lại có thể đi xuống sâu hơn một chút, tới `-2.147.483.648` (INT_MIN).
Điều này tạo ra một cái bẫy nguy hiểm: Nếu ta cố tình chuyển số âm nhỏ nhất `-2.147.483.648` thành số dương, cái cân sẽ bị gãy (tràn số) vì bên số dương không có đủ chỗ để chứa giá trị dương `2.147.483.648`. Do đó, bất kỳ phép biến đổi dấu dương thông thường nào cũng có thể khiến chương trình đổ vỡ.

---

## Giải pháp: Chiếc thước xếp gấp đôi thần kỳ

Để giải quyết bài toán một cách an toàn và thần tốc, chúng ta sẽ sử dụng hai tư duy thiết kế mang tính đột phá:

**Bước 1: Quy ước về "Thế giới âm" an toàn**
Vì vùng đất số âm rộng hơn vùng đất số dương một đơn vị (`-2.147.483.648` so với `2.147.483.647`), chúng ta chọn một giải pháp thiết kế thông minh: **Chuyển tất cả các con số đầu vào về dạng số âm**.
Bằng cách này, chúng ta có thể thoải mái xử lý các trường hợp cực hạn mà không bao giờ lo sợ bị tràn số trong quá trình biến đổi dấu. Chúng ta chỉ cần ghi nhớ dấu ban đầu để khôi phục lại ở bước cuối cùng.

**Bước 2: Chiếc thước xếp nhân đôi liên tục (Dịch bit)**
Thay vì đo đạc thủ công bằng một chiếc thước đơn lẻ, chúng ta sử dụng một chiếc **Thước xếp ma thuật** có khả năng tự động nhân đôi chiều dài của nó sau mỗi lần gấp:
- Ban đầu ta có thước dài `B` (tương ứng với 1 lần đo).
- Ta gấp đôi thước thành `2 * B` (tương ứng với 2 lần đo).
- Ta tiếp tục gấp đôi thành `4 * B` (4 lần đo), rồi `8 * B` (8 lần đo), `16 * B` (16 lần đo)...
- Ta dừng việc gấp đôi lại ngay trước khi chiếc thước xếp trở nên dài hơn đoạn đường cần đo.
- Ta đặt chiếc thước siêu dài này xuống, trừ bớt đoạn đường đã đo được, ghi nhận số lần thước tương ứng, rồi lấy đoạn đường còn lại tiếp tục quy trình gấp thước mới.

**Bước 3: Trả lại kết quả và rào chắn bảo vệ**
Sau khi hoàn tất, ta khôi phục lại dấu của kết quả. Nếu kết quả cần trả về là số dương nhưng lại vượt quá giới hạn cực đại của số dương (ví dụ trường hợp lấy `-2.147.483.648` chia cho `-1`), ta sẽ chặn nó lại ở giá trị giới hạn tối đa `2.147.483.647` để đảm bảo an toàn tuyệt đối cho hệ thống.

---

## Tại sao cách tiếp cận này lại hiệu quả?

Thiết kế này đạt điểm tối ưu tuyệt đối nhờ các yếu tố sau:

- **Tốc độ Logarit siêu tốc**: Nhờ cơ chế nhân đôi độ dài liên tục, số bước đo đạc của chúng ta giảm từ tuyến tính xuống logarit. Đối với một đoạn đường dài tối đa 2 tỷ mét, chúng ta chỉ mất khoảng tối đa 30 lần gấp thước để chạm tới đích. Thuật toán chạy cực kỳ nhanh và vượt qua các bài kiểm thử dễ dàng.
- **Hoạt động an toàn 100%**: Việc thống nhất đưa về số âm giúp tránh hoàn toàn các lỗi tràn số phức tạp thường gặp ở các bài toán thao tác số nguyên lớn.
- **Tối ưu hóa phần cứng**: Phép nhân đôi độ dài của thước được thực hiện bằng toán tử dịch bit trái (`<< 1`), đây là phép toán cơ bản nhất của vi xử lý nên tốc độ thực thi nhanh hơn bất kỳ phép toán nào khác.

---

## Mô phỏng luồng xử lý thực tế

Hãy cùng mô phỏng việc chia đoạn đường `10` cho thước đo `3`:

**Chuẩn bị:**
- Dấu của kết quả: Số dương (vì hai số cùng dấu).
- Chuyển sang thế giới âm: `dividend = -10`, `divisor = -3`.

**Lượt đo thứ nhất:**
- Thước ban đầu: `-3` (tương ứng 1 lần đo).
- Nhân đôi thước: `-6` (tương ứng 2 lần đo).
- Nhân đôi thước: `-12` (tương ứng 4 lần đo). Nhận thấy `-12` nhỏ hơn `-10` (tức là dài hơn đoạn đường cần đo trong thế giới số âm), ta dừng lại.
- Thước tốt nhất tìm được là `-6` (khớp với 2 lần đo).
- Cập nhật đoạn đường còn lại: `-10 - (-6) = -4`.
- Tích lũy kết quả tạm thời: `2`.

**Lượt đo thứ hai:**
- Quay lại thước ban đầu: `-3` (tương ứng 1 lần đo).
- Nhân đôi thước: `-6` (tương ứng 2 lần đo). Nhận thấy `-6` nhỏ hơn `-4`, dừng lại.
- Thước tốt nhất tìm được là `-3` (khớp với 1 lần đo).
- Cập nhật đoạn đường còn lại: `-4 - (-3) = -1`.
- Tích lũy kết quả tạm thời: `2 + 1 = 3`.

**Lượt đo thứ ba:**
- Quay lại thước ban đầu: `-3` (tương ứng 1 lần đo). Nhận thấy thước `-3` dài hơn đoạn đường còn lại `-1`.
- Kết thúc đo đạc!

**Kết quả:**
- Khôi phục dấu dương: kết quả cuối cùng là `3`.

---

## Các trường hợp kiểm thử mở rộng

- **Thử thách vách đá tràn số (Overflow cực hạn)**:
  - Đầu vào: `dividend = -2147483648`, `divisor = -1`
  - Mô tả: Kết quả lý thuyết là số dương `2147483648`, vượt quá giới hạn của số dương 32-bit. Hệ thống phải nhận biết và trả về giá trị giới hạn tối đa.
  - Kết quả kỳ vọng: `2147483647`

- **Thử thách thước đo vô ảnh (Chia cho 1 hoặc -1)**:
  - Đầu vào: `dividend = 12345`, `divisor = -1`
  - Mô tả: Thước đo có độ dài tối thiểu. Kết quả chỉ cần đổi dấu mà không phải thực hiện các bước gấp thước phức tạp.
  - Kết quả kỳ vọng: `-12345`

- **Thử thách đường đua dài (Chia số lớn)**:
  - Đầu vào: `dividend = 1000`, `divisor = 7`
  - Mô tả: Đoạn đường tương đối dài so với thước đo, kiểm tra xem các bước gấp thước và trừ lũy tiến có hoạt động mượt mà không.
  - Kết quả kỳ vọng: `142`

- **Thử thách hai thế cực đối đầu (Trùng trị tuyệt đối nhưng ngược dấu)**:
  - Đầu vào: `dividend = -15`, `divisor = 15`
  - Mô tả: Hai số có trị tuyệt đối giống hệt nhau nhưng ngược dấu. Thước đo vừa vặn khít ngay ở lượt gấp đầu tiên.
  - Kết quả kỳ vọng: `-1`

---

**Tổng kết:** Bằng cách áp dụng tư duy "gấp đôi thước đo" và đưa toàn bộ tính toán về "thế giới số âm", chúng ta đã giải quyết trọn vẹn bài toán chia số nguyên lớn một cách an toàn và cực tốc mà không cần đến các phép nhân chia truyền thống.
