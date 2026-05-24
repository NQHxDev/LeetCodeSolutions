# Tư duy thiết kế: Tìm kiếm chuỗi ghép từ tập từ khóa (Substring with Concatenation of All Words)

Tìm kiếm các chuỗi con được ghép từ một tập từ khóa cho trước có cùng độ dài là một bài toán nâng cao, yêu cầu tối ưu hóa việc phân đoạn chuỗi và quản lý tần suất xuất hiện của các từ hiệu quả.

## Vấn đề

Hãy tưởng tượng một nhà thiết kế trang sức đang kiểm tra một chuỗi hạt ngọc dài (`s`). Họ có một tập hợp các viên ngọc mẫu (`words`), các viên ngọc này đều có cùng độ dài (ví dụ: mỗi viên dài đúng 3cm). Nhà thiết kế muốn tìm tất cả các đoạn liên tục trên chuỗi hạt mà chứa đầy đủ các viên ngọc mẫu theo bất kỳ thứ tự sắp xếp nào.

Nếu tại mỗi hạt ngọc, ta lại cắt ra một đoạn và so khớp từ đầu với tập ngọc mẫu:
- Thao tác này tương đương với việc duyệt lại từ đầu tại mỗi vị trí chỉ số, gây lặp lại phép so sánh rất nhiều lần.
- Kích thước chuỗi hạt lớn sẽ khiến thuật toán chạy cực kỳ chậm, dẫn tới độ phức tạp thời gian lớn.
- Thay vào đó, chúng ta cần tận dụng đặc điểm các từ khóa có **cùng độ dài** để phân chia luồng quét và trượt cửa sổ đếm hạt một cách liên tục mà không phải đếm lại từ đầu.

---

## Giải pháp

Thuật toán tối ưu nhất là sử dụng kỹ thuật **Cửa sổ trượt đa khởi đầu (Multi-start Sliding Window)** kết hợp với **Bảng băm (Hash Map)**:

### Phân chia luồng quét theo độ dài từ
Gọi `wordLen` là độ dài của mỗi từ trong `words`, và `numWords` là số lượng từ. Bất kỳ chuỗi ghép hợp lệ nào cũng phải có tổng độ dài là `totalLen = wordLen * numWords`.
Vì mỗi từ dài đúng `wordLen` ký tự, ta có thể chia việc tìm kiếm thành `wordLen` luồng quét độc lập, bắt đầu từ các vị trí lệch (offset) từ `0` đến `wordLen - 1`. Điều này đảm bảo ta bao phủ toàn bộ các phân đoạn từ có thể có mà không bị sót.

### Cơ chế cửa sổ trượt trên mỗi luồng
Với mỗi luồng bắt đầu tại chỉ số `i` (từ `0` đến `wordLen - 1`), ta duy trì một cửa sổ trượt di chuyển theo từng bước nhảy có độ dài đúng bằng `wordLen`:
1. **Bảng tần suất mẫu (`wordCount`):** Đếm tần suất xuất hiện của từng từ trong tập `words`.
2. **Bảng tần suất cửa sổ (`currentCount`):** Đếm tần suất các từ hợp lệ đang nằm trong cửa sổ hiện tại.
3. **Mở rộng cửa sổ bên phải:** Ta lấy ra từ tiếp theo có độ dài `wordLen` ở biên phải:
   - Nếu từ này không nằm trong tập `words`, ta lập tức bỏ qua toàn bộ cửa sổ hiện tại, dịch biên trái tới ngay sau từ này và reset bộ đếm.
   - Nếu từ này hợp lệ, ta tăng tần suất của nó trong `currentCount`.
   - Nếu tần suất của từ này trong cửa sổ vượt quá tần suất cho phép trong `wordCount`, ta liên tục dịch biên trái của cửa sổ sang phải (từng bước `wordLen` một) cho đến khi tần suất của từ này trở về mức hợp lệ.
4. **Kiểm tra khớp hoàn toàn:** Khi số lượng từ khớp trong cửa sổ đạt đúng `numWords`, ta ghi nhận chỉ số biên trái của cửa sổ là một kết quả hợp lệ. Sau đó, ta dịch biên trái sang phải một bước `wordLen` để tiếp tục tìm kiếm các vị trí tiếp theo.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian:** Với mỗi luồng trong số `wordLen` luồng quét, hai con trỏ biên trái và biên phải của cửa sổ trượt chỉ di chuyển từ đầu đến cuối chuỗi `s` theo các bước nhảy `wordLen`. Do đó, mỗi ký tự trong `s` được duyệt qua số lần cố định. Tổng độ phức tạp thời gian là $O(wordLen \times \frac{sLen}{wordLen}) = O(sLen)$, tối ưu hơn rất nhiều so với duyệt thô.
- **Tiết kiệm bộ nhớ:** Độ phức tạp không gian là $O(numWords \times wordLen)$ để lưu trữ bảng băm tần suất của các từ khóa. Đây là lượng bộ nhớ tối thiểu bắt buộc để nhận diện các từ.

---

## Mô phỏng luồng xử lý

Giả sử chuỗi `s = "barfoothefoobarman"`, tập từ khóa `words = ["foo", "bar"]`.
Độ dài từ `wordLen = 3`, số lượng từ `numWords = 2`. Tổng độ dài cửa sổ cần tìm là `6`.
Ta phân chia làm 3 luồng quét (bắt đầu từ chỉ số 0, 1, 2).

### Luồng quét 1: Bắt đầu từ chỉ số 0 (các từ phân đoạn: "bar", "foo", "the", "foo", "bar", "man")
- Khởi tạo: `left = 0`, `right = 0`, `count = 0`.
- Biên phải lấy từ `"bar"` (hợp lệ): `currentCount["bar"] = 1`, `count = 1`. Dịch biên phải `right = 3`.
- Biên phải lấy từ `"foo"` (hợp lệ): `currentCount["foo"] = 1`, `count = 2`. Dịch biên phải `right = 6`.
- Đạt điều kiện `count == 2`: Ghi nhận kết quả bắt đầu tại `left = 0`.
- Dịch biên trái để tiếp tục: Loại bỏ từ `"bar"` ở biên trái, `currentCount["bar"] = 0`, `count = 1`, `left = 3`.
- Biên phải lấy từ `"the"` (không hợp lệ): Reset toàn bộ cửa sổ, đặt `left = 9` (ngay sau `"the"`), `count = 0`, `currentCount` rỗng.
- Biên phải lấy từ `"foo"` (hợp lệ): `currentCount["foo"] = 1`, `count = 1`. Dịch biên phải `right = 12`.
- Biên phải lấy từ `"bar"` (hợp lệ): `currentCount["bar"] = 1`, `count = 2`. Dịch biên phải `right = 15`.
- Đạt điều kiện `count == 2`: Ghi nhận kết quả bắt đầu tại `left = 9` (vị trí bắt đầu của `"foobar"`).
- Quá trình tiếp tục tương tự cho các phân đoạn tiếp theo.

Kết quả luồng 1 tìm được các vị trí: `0` và `9`.

---

## Các trường hợp kiểm thử bổ sung

- **Trường hợp 1:** `s = "wordgoodgoodgoodbestword"`, `words = ["word", "good", "best", "word"]`
  - Mô tả: Tập từ khóa có các từ trùng nhau (`"word"` xuất hiện 2 lần). Thuật toán phải đếm chính xác tần suất xuất hiện thay vì chỉ kiểm tra sự tồn tại đơn thuần.
  - Kết quả mong đợi: `[]` (không có phân đoạn nào chứa đủ 2 từ `"word"`, 1 từ `"good"`, 1 từ `"best"` đứng liền kề nhau).

- **Trường hợp 2:** `s = "barfoobarfoobar"`, `words = ["foo", "bar"]`
  - Mô tả: Các kết quả hợp lệ nằm đè lên nhau (overlapping), kiểm tra tính liên tục của cửa sổ trượt khi thu hẹp biên trái.
  - Kết quả mong đợi: `0, 3, 6, 9`

- **Trường hợp 3:** `s = "abc"`, `words = ["abcd", "efgh"]`
  - Mô tả: Độ dài chuỗi `s` nhỏ hơn tổng độ dài tối thiểu của chuỗi ghép.
  - Kết quả mong đợi: `[]`

- **Trường hợp 4:** `s = "lingmindraboofooowingdingbarrwingmonkeyconey"`, `words = ["fooo", "barr", "wing", "ding"]`
  - Mô tả: Chuỗi chứa các từ gần giống từ khóa mẫu nhưng không khớp hoàn toàn, kiểm tra tính chính xác của bộ lọc từ khóa không hợp lệ.
  - Kết quả mong đợi: `13` (bắt đầu tại cụm `"foooowingdingbarrwing"`)
