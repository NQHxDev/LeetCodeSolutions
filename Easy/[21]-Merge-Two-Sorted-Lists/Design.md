# Tư duy thiết kế: Hợp nhất hai danh sách đã sắp xếp (Merge Two Sorted Lists)

Hợp nhất hai danh sách không chỉ là việc nối chúng lại, mà là việc duy trì trật tự một cách nhịp nhàng như cách chúng ta xếp hai bộ bài đã được sắp xếp sẵn vào làm một.

## Vấn đề: Duy trì sự liên tục và trật tự

Khi có hai danh sách liên kết đã được sắp xếp tăng dần, thách thức là làm sao để tạo ra một danh sách mới cũng được sắp xếp mà không cần phải tốn thêm quá nhiều bộ nhớ hoặc thực hiện các thuật toán sắp xếp phức tạp. Chúng ta cần một cách tiếp cận "nhìn đâu đánh đó" (Greedy) để luôn chọn được phần tử nhỏ nhất hiện có.

---

## Giải pháp: Kỹ thuật Con trỏ và Nút giả (Dummy Node)

Để giải quyết bài toán này, hãy tưởng tượng chúng ta đang đứng ở đầu hai hàng học sinh đã xếp theo chiều cao từ thấp đến cao. Chúng ta sẽ chuẩn bị một hàng mới và thực hiện các bước sau:

1. **Chuẩn bị điểm bắt đầu:** Sử dụng một **Nút giả (Dummy Node)** đóng vai trò như một người dẫn hàng. Điều này giúp chúng ta không cần lo lắng về việc danh sách mới bắt đầu từ đâu.
2. **So sánh và lựa chọn:** Tại mỗi bước, ta nhìn vào học sinh đứng đầu ở cả hai hàng. Ai thấp hơn thì sẽ được mời sang hàng mới.
3. **Tiến bước:** Sau khi một học sinh chuyển đi, con trỏ của hàng đó sẽ tiến lên người tiếp theo.
4. **Xử lý phần dư:** Nếu một hàng đã hết người mà hàng kia vẫn còn, chúng ta đơn giản là nối toàn bộ phần còn lại của hàng đó vào cuối hàng mới (vì chúng đã được sắp xếp sẵn).

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Hiệu năng thời gian:** Chúng ta chỉ đi qua mỗi phần tử đúng một lần. Độ phức tạp là $O(N + M)$, trong đó $N$ và $M$ là độ dài của hai danh sách.
- **Tối ưu không gian:** Nếu chúng ta chỉ thay đổi các liên kết (`next`) thay vì tạo nút mới, độ phức tạp không gian chỉ là $O(1)$.
- **Đơn giản và sạch sẽ:** Việc sử dụng Nút giả giúp loại bỏ các điều kiện kiểm tra `if-else` rắc rối cho phần tử đầu tiên.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử: `L1 = [1, 2, 4]`, `L2 = [1, 3, 4]`
Khởi tạo: `Dummy -> NULL`, `Current` trỏ vào `Dummy`.

**Bước 1: So sánh L1(1) và L2(1)**
- Cả hai bằng nhau, ta chọn L1.
- `Current->next = L1`. Tiến `L1` lên (2). Tiến `Current` lên.
- Danh sách mới: `Dummy -> 1`

**Bước 2: So sánh L1(2) và L2(1)**
- L2(1) nhỏ hơn.
- `Current->next = L2`. Tiến `L2` lên (3). Tiến `Current` lên.
- Danh sách mới: `Dummy -> 1 -> 1`

**Bước 3: So sánh L1(2) và L2(3)**
- L1(2) nhỏ hơn.
- `Current->next = L1`. Tiến `L1` lên (4). Tiến `Current` lên.
- Danh sách mới: `Dummy -> 1 -> 1 -> 2`

**Bước 4: So sánh L1(4) và L2(3)**
- L2(3) nhỏ hơn.
- `Current->next = L2`. Tiến `L2` lên (4). Tiến `Current` lên.
- Danh sách mới: `Dummy -> 1 -> 1 -> 2 -> 3`

**Bước 5: So sánh L1(4) và L2(4)**
- Chọn L1. Tiến `L1` lên (NULL).
- Danh sách mới: `Dummy -> ... -> 3 -> 4`

**Bước 6: L1 đã NULL**
- Nối phần còn lại của L2 vào.
- Kết quả cuối cùng: `1 -> 1 -> 2 -> 3 -> 4 -> 4`

---

## Test Case mở rộng

- **Case 1 (Một danh sách rỗng):** `L1 = []`, `L2 = [1, 2]` -> Kết quả: `[1, 2]`.
- **Case 2 (Độ dài chênh lệch lớn):** `L1 = [1]`, `L2 = [2, 3, 4, 5, 6]` -> Kết quả: `[1, 2, 3, 4, 5, 6]`.
- **Case 3 (Giá trị trùng lặp nhiều):** `L1 = [1, 1, 1]`, `L2 = [1, 1]` -> Kết quả: `[1, 1, 1, 1, 1]`.
- **Case 4 (Danh sách rời rạc):** `L1 = [1, 5, 10]`, `L2 = [2, 4, 6]` -> Kết quả: `[1, 2, 4, 5, 6, 10]`.

---

**Tổng kết:** Bài toán này dạy chúng ta cách xử lý dữ liệu theo luồng (Stream) và sức mạnh của việc sử dụng các nút phụ trợ để làm cho mã nguồn trở nên thanh thoát và chuyên nghiệp hơn.
