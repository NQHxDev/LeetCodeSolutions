# Tư duy thiết kế: Block Placement Queries

## Vấn đề

Chúng ta cần quản lý một trục số vô hạn bắt đầu từ gốc tọa độ 0 và thực hiện hai loại thao tác:
- Thêm một rào chắn tại tọa độ x.
- Tìm xem có thể đặt một khối có kích thước sz vào trong đoạn [0, x] sao cho khối này không đè lên bất kỳ rào chắn nào đã có hay không.

Khó khăn cốt lõi là các thao tác thêm rào chắn và truy vấn diễn ra xen kẽ nhau với số lượng truy vấn lên tới $1.5 \times 10^5$, và giá trị tọa độ x có thể lên tới $5 \times 10^4$. Nếu thực hiện tìm kiếm tuyến tính để quét các khoảng trống mỗi lần truy vấn, độ phức tạp sẽ là $O(Q \times X)$, dẫn đến quá thời gian cho phép (Time Limit Exceeded).

---

## Giải pháp

Để giải quyết bài toán hiệu quả, chúng ta có thể liên tưởng trục số giống như một con đường cao tốc bắt đầu từ vạch số 0.
- Các chướng ngại vật giống như các trạm thu phí được xây dựng trên con đường đó.
- Việc đặt một khối kích thước sz tương ứng với việc đỗ một chiếc xe tải có độ dài sz vào một khoảng đất trống không có trạm thu phí nào trên đoạn đường từ 0 đến x.

Chúng ta sử dụng sự kết hợp của hai cấu trúc dữ liệu:
- Sách danh sách trạm thu phí (std::set): Dùng để lưu trữ vị trí các trạm thu phí hiện có theo thứ tự tăng dần. Nhờ tính chất tự động sắp xếp, ta có thể nhanh chóng tra cứu trạm thu phí đứng ngay trước hoặc ngay sau một vị trí bất kỳ bằng tìm kiếm nhị phân trong thời gian $O(\log N)$.
- Ban quản lý phân đoạn (Segment Tree): Để quản lý khoảng trống lớn nhất. Mỗi nút trong Segment Tree quản lý khoảng trống lớn nhất giữa hai trạm thu phí kề nhau trong một vùng tọa độ cụ thể.

Khi xây dựng thêm trạm thu phí tại x:
- Ta tra cứu trạm thu phí ngay trước `prev` và ngay sau `next` của x thông qua `std::set`.
- Đoạn đường thông thoáng trước đây từ `prev` đến `next` giờ bị chia làm hai đoạn nhỏ hơn: từ `prev` đến x và từ x đến `next`.
- Ta cập nhật lại hai khoảng trống mới này vào Segment Tree tại vị trí x (khoảng cách `x - prev`) và tại vị trí `next` (khoảng cách `next - x`).

Khi kiểm tra khả năng đỗ xe tải độ dài sz trước vị trí x:
- Ta tìm trạm thu phí cuối cùng `prev` nằm trước hoặc bằng x.
- Khoảng trống cuối cùng kéo dài từ `prev` đến điểm chặn x có độ dài là `x - prev` (khoảng trống này có thể bị rút ngắn do giới hạn x).
- Các khoảng trống nằm hoàn toàn phía trước `prev` được quản lý trực tiếp bởi Segment Tree. Ta chỉ cần truy vấn khoảng trống lớn nhất trong đoạn từ 0 đến `prev`.
- Khoảng trống lớn nhất khả dụng trong đoạn [0, x] sẽ là giá trị lớn nhất giữa khoảng trống lớn nhất từ Segment Tree và khoảng trống cuối cùng `x - prev`. Nếu giá trị này lớn hơn hoặc bằng sz, ta trả về true, ngược lại trả về false.

---

## Tại sao tối ưu?

- Khởi tạo và quét trước: Chúng ta tìm tọa độ lớn nhất `max_x` trong tất cả các truy vấn để giới hạn kích thước cho Segment Tree. Điều này giúp tối ưu hóa bộ nhớ và hiệu năng của cây phân đoạn, tránh việc cấp phát thừa.
- Thêm chướng ngại vật: Tìm kiếm `prev` và `next` mất $O(\log Q)$ bằng `std::set`. Cập nhật Segment Tree mất $O(\log (\max X))$. Tổng thời gian cho mỗi lần thêm là $O(\log Q + \log (\max X))$.
- Truy vấn khoảng trống: Tìm kiếm `prev` mất $O(\log Q)$. Truy vấn Segment Tree trên đoạn $[0, prev]$ mất $O(\log (\max X))$. Tổng thời gian cho mỗi truy vấn là $O(\log Q + \log (\max X))$.
- Tổng độ phức tạp thời gian là $O(Q \log (\max X))$ với $Q \le 1.5 \times 10^5$ và $\max X \le 5 \times 10^4$. Thuật toán chạy cực kỳ nhanh và vượt qua mọi giới hạn thời gian một cách dễ dàng.

---

## Mô phỏng chạy thực tế

Giả sử chúng ta có chuỗi truy vấn sau:
1. Thêm chướng ngại vật tại 3.
2. Kiểm tra khối kích thước 2 trong [0, 5].
3. Thêm chướng ngại vật tại 2.
4. Kiểm tra khối kích thước 2 trong [0, 5].

Quy trình xử lý diễn ra như sau:

- Ban đầu, tập hợp chướng ngại vật chỉ có `{0}`. Segment Tree trống (tất cả các vị trí bằng 0).
- Bước 1: Thêm chướng ngại vật tại 3.
  - Tìm phần tử lớn hơn 3 trong tập hợp -> không có (`next` không tồn tại).
  - Phần tử ngay trước là `prev = 0`.
  - Cập nhật Segment Tree tại vị trí 3 với giá trị `3 - 0 = 3`.
  - Thêm 3 vào tập hợp -> `{0, 3}`.
- Bước 2: Kiểm tra kích thước 2 trong [0, 5].
  - Chướng ngại vật lớn nhất $\le 5$ là `prev = 3`.
  - Truy vấn Segment Tree trong đoạn [0, 3] trả về khoảng trống lớn nhất là 3 (tại vị trí 3).
  - Khoảng trống cuối cùng từ `prev` đến x là `5 - 3 = 2`.
  - Khoảng trống lớn nhất khả dụng là $\max(3, 2) = 3$. Vì $3 \ge 2$, kết quả là `true`.
- Bước 3: Thêm chướng ngại vật tại 2.
  - Tìm phần tử lớn hơn 2 trong tập hợp `{0, 3}` -> `next = 3`.
  - Phần tử ngay trước là `prev = 0`.
  - Cập nhật Segment Tree tại vị trí `next = 3` với giá trị mới `3 - 2 = 1`.
  - Cập nhật Segment Tree tại vị trí 2 với giá trị `2 - 0 = 2`.
  - Thêm 2 vào tập hợp -> `{0, 2, 3}`.
- Bước 4: Kiểm tra kích thước 2 trong [0, 5].
  - Chướng ngại vật lớn nhất $\le 5$ là `prev = 3`.
  - Truy vấn Segment Tree trong đoạn [0, 3] trả về khoảng trống lớn nhất là $\max(\text{vị trí 2}, \text{vị trí 3}) = \max(2, 1) = 2$.
  - Khoảng trống cuối cùng từ `prev` đến x là `5 - 3 = 2`.
  - Khoảng trống lớn nhất khả dụng là $\max(2, 2) = 2$. Vì $2 \ge 2$, kết quả là `true`.

---

## Các trường hợp kiểm thử mở rộng

Dưới đây là các trường hợp kiểm thử bổ sung để xác minh tính đúng đắn của thuật toán:

### Trường hợp kiểm thử 1
- **Đầu vào:**
  ```text
  5
  1 5
  2 5 5
  2 5 6
  1 2
  2 5 3
  ```
- **Giải thích:**
  - Thêm chướng ngại vật tại 5.
  - Kiểm tra khối cỡ 5 trong [0, 5]: lúc này khoảng trống duy nhất là [0, 5] cỡ 5. Trả về `true`.
  - Kiểm tra khối cỡ 6 trong [0, 5]: không đủ chỗ vì khoảng trống chỉ có 5. Trả về `false`.
  - Thêm chướng ngại vật tại 2. Các khoảng trống bây giờ là [0, 2] (cỡ 2) và [2, 5] (cỡ 3).
  - Kiểm tra khối cỡ 3 trong [0, 5]: đoạn [2, 5] có cỡ 3, đủ chỗ. Trả về `true`.
- **Đầu ra mong đợi:**
  ```text
  true false true
  ```

### Trường hợp kiểm thử 2
- **Đầu vào:**
  ```text
  4
  2 10 5
  1 3
  1 6
  2 8 4
  ```
- **Giải thích:**
  - Kiểm tra khối cỡ 5 trong [0, 10] khi chưa có chướng ngại vật nào: khoảng trống [0, 10] cỡ 10, đủ chỗ. Trả về `true`.
  - Thêm chướng ngại vật tại 3 và 6. Các khoảng trống hiện có là [0, 3] (cỡ 3), [3, 6] (cỡ 3) và [6, $\infty$].
  - Kiểm tra khối cỡ 4 trong [0, 8]: các khoảng trống trong [0, 8] là [0, 3] (cỡ 3), [3, 6] (cỡ 3), và [6, 8] (cỡ 2). Khoảng trống lớn nhất chỉ là 3. Trả về `false`.
- **Đầu ra mong đợi:**
  ```text
  true false
  ```

### Trường hợp kiểm thử 3
- **Đầu vào:**
  ```text
  5
  1 1
  2 1 1
  1 2
  2 2 1
  2 2 2
  ```
- **Giải thích:**
  - Thêm chướng ngại vật tại 1.
  - Kiểm tra khối cỡ 1 trong [0, 1]: khoảng trống là [0, 1] cỡ 1. Trả về `true`.
  - Thêm chướng ngại vật tại 2. Các khoảng trống là [0, 1] (cỡ 1) và [1, 2] (cỡ 1).
  - Kiểm tra khối cỡ 1 trong [0, 2]: có hai khoảng trống cỡ 1. Trả về `true`.
  - Kiểm tra khối cỡ 2 trong [0, 2]: khoảng trống lớn nhất chỉ là 1. Trả về `false`.
- **Đầu ra mong đợi:**
  ```text
  true true false
  ```
