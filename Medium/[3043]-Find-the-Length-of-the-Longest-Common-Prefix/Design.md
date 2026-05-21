# Tư duy thiết kế: Find the Length of the Longest Common Prefix

## Vấn đề: Cơn ác mộng của việc đối chiếu thủ công

Hãy tưởng tượng chúng ta là những nhà khảo cổ đang sở hữu hai chiếc rương chứa đầy các bản đồ chỉ đường cổ xưa bằng con số:
- Rương thứ nhất (`arr1`) chứa 50.000 tấm bản đồ chỉ đường.
- Rương thứ hai (`arr2`) cũng chứa 50.000 tấm bản đồ tương tự.

Nhiệm vụ của chúng ta là tìm ra một con đường xuất phát từ gốc (tiền tố) chung dài nhất có thể giữa bất kỳ tấm bản đồ nào của rương thứ nhất và rương thứ hai. Ví dụ: Bản đồ mang mã số `1234` và bản đồ mang mã số `1289` có chung đoạn đường khởi hành là `12` (chiều dài chung bằng 2 chữ số).

Nếu chúng ta chọn cách **Vét cạn (Brute Force)**:
- Ta lấy từng tấm bản đồ ở rương thứ nhất mang đi so sánh lần lượt với từng tấm bản đồ ở rương thứ hai.
- Với mỗi cặp bản đồ, ta lại căng mắt ra đếm xem chúng giống nhau từ những chữ số đầu tiên được bao xa.

=> **Hệ quả cực đoan:** Chúng ta sẽ phải thực hiện tới hàng tỷ phép so sánh tẻ nhạt. Bộ óc của nhà khảo cổ (máy tính) sẽ hoàn toàn kiệt quệ và đình trệ (gây ra lỗi quá giới hạn thời gian TLE). Chúng ta cần một tư duy đột phá để chuyển từ việc "tìm kiếm" mò mẫm vất vả sang việc "tra cứu" tức thì.

---

## Giải pháp: Chiếc gương tra cứu thần tốc

Thay vì mò mẫm ghép đôi hai mảng lớn một cách mù quáng, chúng ta hãy chế tạo ra một chiếc **Gương ma thuật** (Bảng băm - Hash Set). Chiếc gương này có năng lực đặc biệt: ghi nhớ vĩnh viễn mọi ký tự xuất hiện và trả lời câu hỏi "Mảnh bản đồ này có tồn tại không?" chỉ trong một tích tắc.

**Bước 1: Khắc họa dấu vết từ rương thứ nhất**
Chúng ta đi qua từng tấm bản đồ trong rương thứ nhất. Với mỗi tấm bản đồ, ví dụ mang số `123`, chúng ta sẽ chia nó thành các đoạn đường xuất phát từ điểm xuất phát ban đầu:
- Đoạn ngắn nhất: `1`
- Đoạn tiếp theo: `12`
- Đoạn đầy đủ: `123`
Chúng ta ném tất cả các mảnh đường xuất phát này vào chiếc Gương ma thuật. Gương sẽ lập tức lưu trữ lại toàn bộ các mảnh đường độc nhất này vào bộ nhớ của nó.

**Bước 2: Soi chiếu rương thứ hai và quy tắc cắt tỉa**
Bây giờ, chúng ta lần lượt lấy từng tấm bản đồ ở rương thứ hai để soi trước chiếc Gương ma thuật.
Với mỗi số, ví dụ `128`:
- Đầu tiên, ta hỏi Gương xem có lưu mảnh `128` không? Gương báo: Không có.
- Ta cắt bớt chữ số cuối cùng đi, còn `12`. Hỏi Gương: Có mảnh `12` không? Gương lập tức sáng lên báo: **Có tồn tại!**
Vì chúng ta đi từ đoạn dài nhất đến ngắn nhất, ngay khi chiếc Gương báo có, ta biết chắc chắn đó là đoạn đường xuất phát chung dài nhất mà tấm bản đồ này có thể tạo ra. Ta ghi nhận chiều dài này (2 chữ số) và cập nhật kỷ lục chung.

**Quy tắc ngắt ngọn thông minh (Nhánh cận):**
Hãy tưởng tượng chúng ta đang giữ kỷ lục đoạn đường chung dài 3 chữ số. Khi cầm lên một tấm bản đồ mới từ rương thứ hai chỉ có độ dài là 2 chữ số (ví dụ `45`), ta có thể bỏ qua tấm bản đồ này ngay lập tức mà không cần hỏi Gương ma thuật. Tại sao phải mất công tra cứu một thứ mà ngay cả khi hoàn hảo nhất cũng không thể phá vỡ kỷ lục hiện tại? Việc ngắt ngọn này giúp chúng ta quét sạch mọi phép tính thừa thãi!

---

## Tại sao cách tiếp cận này lại hiệu quả?

Sự kỳ diệu của thiết kế này đến từ việc tối ưu hóa thông minh trong thực tế:

- **Tốc độ tra cứu tức thì**: Việc tra cứu trên Gương ma thuật diễn ra trong nháy mắt. Thay vì phải so sánh hàng tỷ cặp, chúng ta chỉ cần đi qua các tấm bản đồ đúng một lần duy nhất.
- **Tiết kiệm tài nguyên tuyệt đối**: Chúng ta thu nhỏ các tấm bản đồ số bằng các phép toán học đơn giản (chia cho 10) thay vì chuyển chúng thành các chuỗi chữ viết dài dòng. Điều này giúp máy tính không phải tốn công cắt dán bộ nhớ liên tục, giữ cho hệ thống luôn nhẹ nhàng và chạy cực nhanh.
- **Khả năng tự động dừng**: Việc duyệt từ dài đến ngắn giúp ta dừng lại ngay lập tức khi tìm thấy kết quả đầu tiên, kết hợp với quy tắc ngắt ngọn giúp ta bỏ qua hàng ngàn phép tính vô ích.

---

## Mô phỏng luồng xử lý thực tế

Hãy cùng theo chân nhà khảo cổ xử lý hai rương bản đồ nhỏ:
`arr1 = [123, 45]`
`arr2 = [128, 456]`

**Khởi tạo Gương ma thuật từ rương thứ nhất**
- Bản đồ `123`: ta lấy các đoạn gốc `123`, `12`, `1` ném vào Gương.
- Bản đồ `45`: ta lấy các đoạn gốc `45`, `4` ném vào Gương.
Chiếc Gương lúc này ghi nhớ tập hợp các đoạn đường: `{1, 4, 12, 45, 123}`.

**Soi chiếu rương thứ hai**
Khởi tạo chiều dài kỷ lục hiện tại là `0`.

- Xét bản đồ `128` (chiều dài ban đầu là 3):
  - Hỏi Gương về `128`: Gương báo Không.
  - Cắt bớt còn `12` (chiều dài 2):
    - Hỏi Gương về `12`: Gương báo **Có!**
    - Chiều dài 2 lớn hơn kỷ lục hiện tại (0), cập nhật kỷ lục mới là `2`.
    - Dừng xét bản đồ này vì đã tìm thấy đoạn dài nhất của nó.
- Xét bản đồ `456` (chiều dài ban đầu là 3):
  - Hỏi Gương về `456`: Gương báo Không.
  - Cắt bớt còn `45` (chiều dài 2):
    - Lúc này, chiều dài của mảnh đường đang xét (2) đã bằng kỷ lục hiện tại (2). Kể từ đây, dù có khớp thì độ dài cũng chỉ bằng hoặc ngắn hơn kỷ lục.
    - **Áp dụng quy tắc ngắt ngọn**: Dừng cuộc tìm kiếm cho bản đồ `456` ngay lập tức!

Kết quả cuối cùng thu được đoạn đường chung dài nhất có chiều dài bằng `2`.

---

## Các trường hợp kiểm thử mở rộng

- **Thử thách sa mạc (Không có lối đi chung)**:
  - Đầu vào: `arr1 = [9, 99, 999]`, `arr2 = [1, 22, 333]`
  - Mô tả: Hai bên hoàn toàn xa lạ, không có bất kỳ điểm xuất phát nào tương đồng. Chiếc Gương ma thuật sẽ im lặng suốt quá trình soi chiếu.
  - Kết quả kỳ vọng: `0`

- **Thử thách bản sao (Một bên nằm trọn trong bên kia)**:
  - Đầu vào: `arr1 = [123456]`, `arr2 = [12345678]`
  - Mô tả: Bản đồ ở rương thứ nhất là một phần đầu hoàn hảo và trọn vẹn của bản đồ ở rương thứ hai.
  - Kết quả kỳ vọng: `6` (đoạn chung dài nhất chính là `123456`)

- **Thử thách lối đi tối giản (Chỉ khớp một bước chân)**:
  - Đầu vào: `arr1 = [1, 2, 3]`, `arr2 = [3, 4, 5]`
  - Mô tả: Điểm chung duy nhất là con số `3` đơn độc ở đầu đường chạy.
  - Kết quả kỳ vọng: `1`

- **Thử thách so tài kỷ lục (Nhiều điểm khớp nhưng độ dài khác biệt)**:
  - Đầu vào: `arr1 = [1200, 567]`, `arr2 = [12, 56789]`
  - Mô tả: Cặp bản đồ đầu tiên cho đoạn chung `12` dài 2 chữ số. Cặp bản đồ thứ hai cho đoạn chung `567` dài 3 chữ số. Kỷ lục mới 3 chữ số sẽ đánh bại kỷ lục cũ 2 chữ số.
  - Kết quả kỳ vọng: `3`

---

**Tổng kết:** Bằng cách áp dụng tư duy ghi nhớ thông minh, chúng ta biến một bài toán so sánh từng cặp phức tạp thành một quy trình tra cứu nhanh chóng và loại biên hiệu quả. Việc lưu trữ tiền tố giúp tìm kiếm điểm tương đồng dài nhất một cách nhanh chóng và tối ưu nhất.
