# Tư duy thiết kế: Xóa nút thứ N từ cuối danh sách (Remove Nth Node From End of List)

Xóa một phần tử trong danh sách liên kết đơn là một thao tác cơ bản, nhưng xóa một phần tử được định vị từ phía cuối danh sách trong khi chỉ được phép duyệt qua danh sách đúng một lần (One Pass) đòi hỏi một tư duy thiết kế khéo léo về mặt không gian và thời gian.

## Vấn đề: Danh sách một chiều và sự giới hạn thông tin

Đặc thù của danh sách liên kết đơn là chúng ta chỉ có thể đi từ đầu đến cuối thông qua liên kết `next` mà không thể đi ngược lại. Do đó, nếu muốn biết nút nào nằm ở vị trí thứ $N$ tính từ cuối lên, cách tiếp cận thông thường là:
1. Duyệt một vòng từ đầu đến cuối danh sách để đếm tổng số nút (giả sử là $L$).
2. Duyệt vòng thứ hai đến vị trí thứ $L - N$ để thực hiện thao tác xóa.

Tuy nhiên, cách tiếp cận hai vòng duyệt này chưa tối ưu về mặt hiệu năng hệ thống. Thách thức đặt ra là làm thế nào để xác định chính xác nút cần xóa chỉ bằng một con đường đi thẳng duy nhất từ đầu tới cuối.

---

## Giải pháp: Kỹ thuật Hai con trỏ và Khoảng cách cố định

Để giải quyết bài toán này chỉ trong một lần duyệt, chúng ta sử dụng hình ảnh **"Hai người đi bộ duy trì khoảng cách bằng một sợi dây căng"**.

Nếu người đi trước (Fast) và người đi sau (Slow) cùng di chuyển với tốc độ như nhau và luôn duy trì khoảng cách chính xác là $N$ bước chân:
- Khi người đi trước (Fast) chạm tới điểm cuối của con đường (cuối danh sách), người đi sau (Slow) chắc chắn sẽ đứng ở vị trí cách điểm cuối đúng $N$ bước.
- Vị trí đó chính là nút cần xóa.

**Quy tắc hoạt động:**

1. **Sử dụng Nút giả (Dummy Node):** Chúng ta đặt một nút giả đứng trước nút đầu tiên (Head) của danh sách. Nút giả này đóng vai trò cực kỳ quan trọng, giúp đơn giản hóa việc xóa nút đầu tiên (khi $N$ bằng đúng độ dài danh sách) mà không cần viết thêm các điều kiện kiểm tra phức tạp.
2. **Tạo khoảng cách:** Cho con trỏ `Fast` xuất phát từ nút giả và tiến lên trước $N + 1$ bước. Lúc này, khoảng cách giữa `Fast` và `Slow` (vẫn đang đứng ở nút giả) là $N + 1$ nút.
3. **Đồng hành tiến bước:** Cho cả `Fast` và `Slow` cùng tiến lên từng nút một cho đến khi `Fast` đạt đến điểm kết thúc (`nullptr`).
4. **Thực hiện thao tác xóa:** Nhờ khoảng cách $N + 1$ nút được thiết lập ban đầu, khi `Fast` chạm `nullptr`, con trỏ `Slow` sẽ dừng lại ở nút **ngay trước** nút cần xóa. Chúng ta chỉ cần thay đổi liên kết: `Slow->next = Slow->next->next` để loại bỏ nút mục tiêu ra khỏi danh sách.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Duyệt một lần duy nhất (One Pass):** Thuật toán chỉ duyệt qua danh sách liên kết đúng một lần, đạt độ phức tạp thời gian cực hạn $O(M)$ với $M$ là số lượng nút trong danh sách.
- **Tiết kiệm bộ nhớ tối đa:** Không cần lưu trữ lại toàn bộ danh sách hay dùng mảng phụ trợ. Chúng ta chỉ cần 2 con trỏ chạy trên danh sách hiện có, đạt độ phức tạp không gian $O(1)$.
- **An toàn và sạch sẽ:** Việc sử dụng Nút giả giúp loại bỏ hoàn toàn nguy cơ lỗi truy cập vùng nhớ trống (Null Pointer Exception) khi nút cần xóa chính là nút đầu tiên.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử danh sách: `1 -> 2 -> 3 -> 4 -> 5`, và cần xóa nút thứ `N = 2` từ cuối lên (nút số 4).

**Khởi tạo:**
- Tạo nút giả `Dummy -> 1 -> 2 -> 3 -> 4 -> 5`
- `Slow` và `Fast` cùng đứng ở `Dummy`.

**Bước 1: Cho `Fast` chạy trước N + 1 bước (3 bước)**
- `Fast` di chuyển qua: `Dummy` -> `1` -> `2` -> `3`.
- Hiện tại: `Slow` ở `Dummy`, `Fast` ở `3`. Khoảng cách giữa chúng là 3 nút.

**Bước 2: Cả hai con trỏ cùng đồng hành tiến lên**
- Lần 1: `Slow` tiến tới `1`, `Fast` tiến tới `4`.
- Lần 2: `Slow` tiến tới `2`, `Fast` tiến tới `5`.
- Lần 3: `Slow` tiến tới `3`, `Fast` tiến tới `nullptr` (Kết thúc).

**Bước 3: Thực hiện xóa nút**
- Con trỏ `Slow` hiện tại đứng ở `3` (nút ngay trước nút cần xóa là `4`).
- Thực hiện kết nối lại: `Slow->next` (đang trỏ vào `4`) sẽ được gán bằng `Slow->next->next` (trỏ vào `5`).
- Danh sách sau khi kết nối lại: `1 -> 2 -> 3 -> 5`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt giúp đảm bảo tính đúng đắn và độ bền vững của thuật toán:

- **Case 1 (Xóa nút đầu tiên của danh sách):** Danh sách `[1, 2]`, `N = 2` -> Kết quả: `[2]` (Kiểm tra xem cơ chế Nút giả có xử lý chính xác trường hợp xóa nút gốc hay không).
- **Case 2 (Danh sách chỉ có duy nhất một phần tử):** Danh sách `[1]`, `N = 1` -> Kết quả: `[]` (Đảm bảo việc xóa phần tử duy nhất trả về danh sách rỗng an toàn).
- **Case 3 (Xóa nút cuối cùng của danh sách):** Danh sách `[1, 2, 3]`, `N = 1` -> Kết quả: `[1, 2]` (Đảm bảo liên kết cuối cùng được chuyển hướng sang `nullptr` một cách chính xác).
- **Case 4 (Danh sách dài hơn):** Danh sách `[10, 20, 30, 40, 50, 60]`, `N = 4` -> Kết quả: `[10, 20, 40, 50, 60]` (Xác nhận tính chính xác khi định vị nút nằm sâu trong danh sách lớn).

---

**Tổng kết:** Bí quyết của bài toán này nằm ở việc chuyển đổi tư duy từ đếm số lượng sang duy trì một khoảng cách vật lý cố định. Sự kết hợp giữa kỹ thuật Hai con trỏ và Nút giả tạo nên một giải pháp không chỉ đạt hiệu năng tối đa mà còn vô cùng ngắn gọn và an toàn.
