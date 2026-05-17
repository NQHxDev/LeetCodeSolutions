# Tư duy thiết kế: Sinh các chuỗi ngoặc hợp lệ (Generate Parentheses)

Sinh ra tất cả các tổ hợp dấu ngoặc hợp lệ từ $N$ cặp ngoặc là một bài toán kinh điển về thiết kế giải thuật duyệt có chọn lọc. Thử thách ở đây không chỉ là sinh ra các chuỗi, mà là làm thế nào để **chỉ đi trên các con đường chắc chắn dẫn đến kết quả hợp lệ**, tránh lãng phí tài nguyên cho các nhánh lỗi.

## Vấn đề: Sự bùng nổ tổ hợp và tính hợp lệ

Với $N$ cặp ngoặc, tổng số ký tự trong chuỗi kết quả sẽ là $2N$. Nếu chúng ta sinh ra tất cả các tổ hợp chuỗi có độ dài $2N$ bằng cách vét cạn (Brute Force) rồi mới dùng ngăn xếp để kiểm tra xem chuỗi đó có hợp lệ hay không:
- Tổng số chuỗi cần sinh ra là $2^{2N}$. Khi $N = 8$, chúng ta phải sinh ra và kiểm tra $65,536$ chuỗi.
- Độ phức tạp thời gian sẽ bùng nổ lên tới $O(2^{2N} \times N)$, phần lớn thời gian bị lãng phí để sinh ra các chuỗi sai quy tắc như `))))((((`.

Chúng ta cần một cơ chế thông minh giúp ngăn chặn và loại bỏ các chuỗi sai ngay từ ký tự đầu tiên.

---

## Giải pháp: Quay lui kết hợp Quy tắc chi tiêu tài chính (Backtracking with Pruning)

Để đảm bảo mọi chuỗi được sinh ra từ đầu đến cuối đều tuyệt đối hợp lệ, chúng ta áp dụng một hình ảnh liên tưởng thực tế: **"Quy tắc quản lý chi tiêu tài chính"**.

Hãy coi việc mở dấu ngoặc `(` là việc **Kiếm tiền (Thu nhập)** và đóng dấu ngoặc `)` là việc **Tiêu tiền (Chi tiêu)**. Một hệ thống tài chính lành mạnh và hợp lệ phải tuân thủ nghiêm ngặt hai quy tắc sau:

1. **Giới hạn tổng thu nhập:** Bạn chỉ được phép kiếm tối đa là $N$ đồng. Tương đương số dấu mở `( ` được sinh ra không vượt quá $N$.
2. **Không tiêu quá số tiền đã kiếm:** Tại bất kỳ thời điểm nào, số tiền bạn tiêu không được vượt quá số tiền bạn đã kiếm được trước đó. Tương đương tại mọi vị trí trong chuỗi, số dấu đóng `)` được sinh ra luôn phải nhỏ hơn hoặc bằng số dấu mở `(` hiện có.

**Quy tắc hoạt động của thuật toán Quay lui:**
- Chúng ta theo dõi hai biến đếm: `open` (số dấu mở hiện tại) và `close` (số dấu đóng hiện tại).
- Nếu `open < N`: Chúng ta có quyền thêm dấu mở `(`.
- Nếu `close < open`: Chúng ta có quyền thêm dấu đóng `)`.
- **Trạng thái dừng:** Khi độ dài chuỗi tạm thời đạt đến $2N$, ta lưu kết quả và quay lui để thử nhánh khác.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Tỉa nhánh tuyệt đối (Perfect Pruning):** Nhờ hai điều kiện ràng buộc trên, thuật toán hoàn toàn không đi vào bất kỳ nhánh sai nào. Tất cả các chuỗi chạm tới trạng thái dừng đều chắc chắn hợp lệ.
- **Độ phức tạp thời gian tối thiểu:** Thời gian chạy tỷ lệ thuận với số lượng số Catalan thứ $N$ ($C_N = \frac{1}{N+1}\binom{2N}{N}$), đây là số lượng tổ hợp ngoặc hợp lệ thực tế. Đây là giới hạn tối ưu tuyệt đối vì chúng ta bắt buộc phải sinh ra toàn bộ kết quả.
- **Độ phức tạp không gian tối ưu:** $O(N)$ do độ sâu lớn nhất của ngăn xếp đệ quy chỉ bằng $2N$.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử: `N = 2` (Cần sinh các chuỗi ngoặc từ 2 cặp ngoặc).
Quy tắc: Tối đa 2 dấu `(`, số dấu `)` luôn $\le$ số dấu `(`.

**Bước 1: Khởi đầu với chuỗi rỗng `""` (open = 0, close = 0)**
- Chỉ có thể thêm `(` vì `open < 2` và không thể thêm `)` vì `close (0) == open (0)`.
- *Chuỗi tạm thời:* `"("` (open = 1, close = 0).

**Bước 2: Từ `"("` (open = 1, close = 0)**
- Nhánh A (Thêm `(`): Hợp lệ vì `open (1) < 2`. Chuỗi mới: `"(("` (open = 2, close = 0).
- Nhánh B (Thêm `)`): Hợp lệ vì `close (0) < open (1)`. Chuỗi mới: `"()"` (open = 1, close = 1).

**Bước 3: Phát triển tiếp các nhánh**
- Từ Nhánh A `"(("` (open = 2, close = 0):
  - Không thể thêm `(` vì đã đạt giới hạn 2.
  - Bắt buộc thêm `)` liên tiếp cho đến hết: `"(("` -> `"(()"` -> `"(())"` (Độ dài 4, Lưu kết quả **`"(())"`**).
- Từ Nhánh B `"()"` (open = 1, close = 1):
  - Không thể thêm `)` vì `close == open`.
  - Bắt buộc thêm `(`: `"()"` -> `"()("` (open = 2, close = 1).
  - Tiếp theo bắt buộc thêm `)`: `"()("` -> `"()()"` (Độ dài 4, Lưu kết quả **`"()()"`**).

**Kết quả cuối cùng:** `["(())", "()()"]`

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử độc lập giúp đánh giá độ chính xác toàn diện của giải thuật:

- **Case 1 (Không có cặp ngoặc nào):** `N = 0` -> Kết quả: `[]` (Xử lý biên an toàn).
- **Case 2 (Chỉ có 1 cặp ngoặc):** `N = 1` -> Kết quả: `["()"]` (Kiểm thử cấu trúc cơ sở).
- **Case 3 (Độ phức tạp vừa phải):** `N = 3` -> Kết quả gồm 5 chuỗi: `["((()))", "(()())", "(())()", "()(())", "()()()"]`.
- **Case 4 (Kiểm tra tải lớn):** `N = 4` -> Kết quả gồm 14 chuỗi hợp lệ (Đảm bảo thuật toán hoạt động nhanh nhạy, không bị trễ thời gian và kiểm soát đệ quy sâu tốt).

---

**Tổng kết:** Bằng việc áp dụng quy tắc "kiếm tiền trước - chi tiêu sau" vào từng bước sinh ký tự, giải thuật quay lui đã biến một bài toán tìm kiếm mù quáng thành một quy trình ra quyết định chuẩn xác, thanh thoát và đạt hiệu năng tối đa.
