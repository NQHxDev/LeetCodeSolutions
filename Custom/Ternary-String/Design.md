# Tư duy thiết kế: Ternary String

## Vấn đề

Đếm số lượng xâu tam phân (chỉ gồm các ký tự `0`, `1`, `2`) có độ dài $n$ sao cho không có hai ký tự `1` nào đứng cạnh nhau. Kết quả cần được lấy dư cho $10^9 + 7$.
Ràng buộc: $1 \le n \le 10^5$.

---

## Ý tưởng thiết kế

Hãy tưởng tượng bạn đang lát một con đường có độ dài $n$ bằng các viên gạch có 3 màu sắc khác nhau: Đỏ (0), Vàng (1), và Xanh (2). Quy tắc duy nhất là bạn không được xếp hai viên gạch màu Vàng (1) đứng liền kề nhau.

Khi xếp viên gạch cuối cùng ở vị trí thứ $i$:
- Nếu bạn xếp viên gạch màu Đỏ hoặc Xanh (có 2 cách chọn): Viên gạch trước đó ở vị trí $i-1$ có thể là bất kỳ màu nào. Do đó, số lượng cách lát hợp lệ sẽ bằng 2 nhân với số cách lát con đường độ dài $i-1$.
- Nếu bạn muốn xếp viên gạch màu Vàng (có 1 cách chọn): Viên gạch trước đó ở vị trí $i-1$ bắt buộc phải là Đỏ hoặc Xanh (không thể là Vàng). Điều này có nghĩa là hai vị trí cuối cùng bắt buộc phải là cặp màu (Đỏ-Vàng) hoặc (Xanh-Vàng). Do đó, số lượng cách lát hợp lệ sẽ bằng 2 nhân với số cách lát con đường độ dài $i-2$.

Từ suy luận này, ta xây dựng được công thức truy hồi đơn giản cho số lượng xâu thỏa mãn độ dài $i$ (ký hiệu là $S_i$):
$$S_i = 2 \times S_{i-1} + 2 \times S_{i-2}$$

---

## Phân tích không gian tìm kiếm

Với mỗi độ dài $i$ từ $1$ đến $n$, trạng thái của bài toán chỉ phụ thuộc vào kết quả của hai bước trước đó ($S_{i-1}$ và $S_{i-2}$).
Do đó, chúng ta có thể sử dụng phương pháp **Quy hoạch động (Dynamic Programming)** hoặc **Tối ưu hóa không gian trạng thái** để tính toán tuần tự từ $1$ đến $n$.

---

## Giải thích chi tiết thuật toán

Để giải quyết bài toán với thời gian và bộ nhớ tối ưu nhất:
- Định nghĩa mảng $DP$ có kích thước $n+1$, trong đó $DP[i]$ lưu trữ số lượng xâu hợp lệ độ dài $i$.
- Các trường hợp nền tảng (Base cases):
  - Với $n = 0$: $DP[0] = 1$ (xâu rỗng được coi là hợp lệ).
  - Với $n = 1$: $DP[1] = 3$ (các xâu `0`, `1`, `2`).
- Với mỗi bước $i$ từ $2$ đến $n$, áp dụng công thức chuyển trạng thái:
  $$DP[i] = (2 \times DP[i-1] + 2 \times DP[i-2]) \pmod{10^9 + 7}$$
- Để tối ưu hóa không gian bộ nhớ từ $O(n)$ xuống $O(1)$, chúng ta chỉ cần duy trì ba biến liên tiếp đại diện cho $S_{i}$, $S_{i-1}$ và $S_{i-2}$ vì ta không cần lưu trữ lại toàn bộ lịch sử các bước trước đó.

---

## Mô phỏng từng bước chạy thực tế

Giả sử cần tính số lượng xâu thỏa mãn với độ dài $n = 3$:

Khởi tạo các giá trị ban đầu:
- $S_0 = 1$
- $S_1 = 3$

Tính toán tuần tự:
- Bước 1 (với $i = 2$):
  $$S_2 = (2 \times S_1 + 2 \times S_0) \pmod{10^9 + 7} = (2 \times 3 + 2 \times 1) = 8$$
- Bước 2 (với $i = 3$):
  $$S_3 = (2 \times S_2 + 2 \times S_1) \pmod{10^9 + 7} = (2 \times 8 + 2 \times 3) = 22$$

Kết quả cuối cùng cho độ dài $n = 3$ là `22`.

---

## Phân tích hiệu năng

Thời gian thực thi:
- Chúng ta chỉ thực hiện một vòng lặp chạy từ $2$ đến $n$ với các phép toán cộng, nhân và lấy dư cơ bản.
- Độ phức tạp thời gian: $O(n)$, chạy mất khoảng $1$ ms với $n = 10^5$, hoàn toàn đáp ứng thời gian chạy của hệ thống.

Không gian bộ nhớ:
- Bằng cách chỉ sử dụng ba biến trạng thái thay vì lưu cả mảng, ta đạt hiệu quả bộ nhớ tối ưu tuyệt đối.
- Độ phức tạp không gian: $O(1)$.

---

## Các trường hợp kiểm thử bổ sung

Trường hợp kiểm thử 1:
- Đầu vào: `4`
- Đầu ra: `60`
- Giải thích: Áp dụng công thức: $S_4 = 2 \times S_3 + 2 \times S_2 = 2 \times 22 + 2 \times 8 = 60$.

Trường hợp kiểm thử 2:
- Đầu vào: `5`
- Đầu ra: `164`
- Giải thích: Áp dụng công thức: $S_5 = 2 \times S_4 + 2 \times S_3 = 2 \times 60 + 2 \times 22 = 164$.

Trường hợp kiểm thử 3:
- Đầu vào: `10`
- Đầu ra: `24960`
- Giải thích: Tính toán lũy tiến qua các bước ta có $S_6 = 448$, $S_7 = 1224$, $S_8 = 3344$, $S_9 = 9136$, và cuối cùng $S_{10} = 24960$.
