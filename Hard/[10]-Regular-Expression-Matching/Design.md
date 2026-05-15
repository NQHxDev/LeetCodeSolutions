# Tư duy thiết kế: Máy quét biểu thức chính quy (Regular Expression Matching)

Regular Expression Matching không chỉ là việc so khớp đơn thuần, mà là bài toán đưa ra quyết định tại mỗi bước đi. Đặc biệt, ký tự `*` đóng vai trò như một "thẻ vạn năng" đầy quyền năng nhưng cũng đầy rắc rối.

## Vấn đề: Sự không xác định của ký tự `*`

Khi máy quét gặp một ký tự thông thường hoặc dấu `.`, việc quyết định rất dễ dàng: "Khớp hoặc không khớp". Nhưng khi gặp `*`, máy quét rơi vào tình huống tiến thoái lưỡng nan:

- Liệu nên coi `*` là **0 lần** xuất hiện (tức là xóa bỏ ký tự đứng trước nó)?
- Hay nên coi `*` là **nhiều lần** xuất hiện (tức là giữ lại ký tự đó và tiếp tục quét)?

Việc thử mọi khả năng bằng cách vét cạn sẽ dẫn đến sự bùng nổ về thời gian tính toán (độ phức tạp lũy thừa).

---

## Giải pháp: Chia để trị và Ghi nhớ (Top-Down DP)

Để giải quyết sự không xác định này, chúng ta sử dụng tư duy **Chia để trị**: Giải quyết phần đầu của chuỗi và phó mặc phần còn lại cho một bài toán con tương tự.

**Quy tắc quét:**

1. **Kiểm tra phần đầu:** Ký tự hiện tại của `s` và `p` có khớp nhau không? (Khớp nếu giống nhau hoặc `p` là `.`).
2. **Xử lý `*` (Trường hợp quan trọng):** Nếu ký tự tiếp theo trong mẫu `p` là `*`:
   - **Lựa chọn 1 (Bỏ qua):** Coi cụm `ký tự + *` là 0 lần xuất hiện. Ta nhảy qua 2 ký tự trong `p` và giữ nguyên `s`.
   - **Lựa chọn 2 (Sử dụng):** Nếu phần đầu đã khớp, ta giữ nguyên `p` và tiến tới ký tự tiếp theo trong `s` (để `*` tiếp tục khớp với các ký tự sau).
3. **Trường hợp thông thường:** Nếu không có `*`, đơn giản là tiến lên 1 bước ở cả `s` và `p` nếu phần đầu đã khớp.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Sổ tay ghi nhớ (Memoization):** Trong quá trình đệ quy, chúng ta sẽ gặp lại những cặp `(vị trí s, vị trí p)` giống hệt nhau. Thay vì tính lại từ đầu, ta chỉ cần lật "cuốn sổ tay" (bảng 2 chiều) ra để lấy kết quả đã có.
- **Độ phức tạp:** Thời gian tính toán giảm từ lũy thừa xuống còn $O(M \times N)$ (với $M, N$ là độ dài của `s` và `p`), vì mỗi trạng thái chỉ được ghi vào sổ đúng một lần.
- **Tính bao quát:** Cách tiếp cận này xử lý cực tốt các trường hợp `*` chồng lấp hoặc chuỗi rỗng.

---

## Mô phỏng luồng xử lý chi tiết

Hãy tưởng tượng chúng ta có hai con trỏ `i` (quét chuỗi `s`) và `j` (quét mẫu `p`). 
Ví dụ: `s = "aab"`, `p = "c*a*b"`

**Bước 1: Trạng thái ban đầu (i=0, j=0)**
- `s[0] = 'a'`, `p[0] = 'c'`. 
- Nhìn phía trước: `p[1]` là `*`.
- **Quyết định:** Vì `'a'` khác `'c'`, máy quét không thể "Sử dụng" cụm `c*`. Nó bắt buộc phải **Bỏ qua** `c*` (nhảy `j` từ 0 sang 2).
- *Trạng thái mới:* (i=0, j=2).

**Bước 2: Đối mặt với "ngã ba đường" (i=0, j=2)**
- `s[0] = 'a'`, `p[2] = 'a'`.
- Nhìn phía trước: `p[3]` là `*`. 
- Đây là lúc máy quét phải phân thân để thử cả hai hướng:
   - **Nhánh A (Bỏ qua a*):** Nhảy `j` lên 4. Trạng thái (i=0, j=4).
   - **Nhánh B (Sử dụng a*):** Vì `'a' == 'a'`, giữ nguyên `j=2` và tiến `i` lên 1. Trạng thái (i=1, j=2).

**Bước 3: Theo dấu Nhánh B (i=1, j=2)**
- `s[1] = 'a'`, `p[2] = 'a'`.
- Nhìn phía trước: `p[3]` vẫn là `*`.
- Lại tiếp tục phân thân:
   - **Nhánh B1 (Bỏ qua a*):** Nhảy `j` lên 4. Trạng thái (i=1, j=4).
   - **Nhánh B2 (Sử dụng a*):** Vì `'a' == 'a'`, giữ nguyên `j=2` và tiến `i` lên 2. Trạng thái (i=2, j=2).

**Bước 4: Về đích (Nhánh B2 rẽ sang Bỏ qua)**
- Tại trạng thái (i=2, j=2): `s[2] = 'b'`, `p[2] = 'a'`.
- Vì `'b' != 'a'`, máy quét bắt buộc phải **Bỏ qua** `a*`. Nhảy `j` lên 4.
- *Trạng thái mới:* (i=2, j=4).
- Tại đây: `s[2] = 'b'`, `p[4] = 'b'`. Khớp hoàn toàn! 
- Cả hai con trỏ cùng tiến lên và chạm vạch đích (hết chuỗi).

**Kết luận:** Nhánh B2 dẫn đến thành công, máy quét trả về `true`. Nhánh A và B1 sẽ bị cụt và được "cuốn sổ tay" ghi lại là `false` để không bao giờ phải thử lại.

---

## Test Case mở rộng

- **Case 1 (Bỏ qua nhiều cụm `*`):** `s = "a"`, `p = "ab*c*d*"` -> Kết quả: `true` (Các cụm `b*`, `c*`, `d*` đều tính là 0 lần).
- **Case 2 (`*` đứng sau `.`):** `s = "abcdef"`, `p = ".*"` -> Kết quả: `true` (`.*` khớp với bất kỳ thứ gì).
- **Case 3 (`*` phải khớp nhiều lần):** `s = "aaa"`, `p = "a*a"` -> Kết quả: `true`.
- **Case 4 (Chuỗi rỗng với mẫu phức tạp):** `s = ""`, `p = "a*b*c*"` -> Kết quả: `true`.
- **Case 5 (Khớp sai ở cuối):** `s = "ab"`, `p = ".*c"` -> Kết quả: `false`.

---

**Tổng kết:** Bí quyết của bài toán này là sự "kiên nhẫn" của máy quét: Tại mỗi ngã rẽ với `*`, hãy thử mọi khả năng khả thi và ghi nhớ kết quả để không bao giờ phải đi lại con đường cũ.
