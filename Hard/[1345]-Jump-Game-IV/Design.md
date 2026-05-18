# Tư duy thiết kế: Cổng dịch chuyển tức thời và hành trình tối ưu (Jump Game IV)

Di chuyển trên một mảng số nguyên với các quy tắc phức tạp là một dạng bài toán tìm đường đi ngắn nhất trên đồ thị ẩn. Ở đây, mỗi vị trí trong mảng đóng vai trò như một nút (node), và các bước nhảy hợp lệ đóng vai trò là các cạnh (edge) liên kết các nút đó. Thách thức lớn nhất của Jump Game IV so với các phần trước là sự xuất hiện của các "cổng dịch chuyển tức thời" — tức là khả năng nhảy đến bất kỳ ô nào có cùng giá trị trong mảng. Điều này đòi hỏi một chiến thuật tinh tế để tránh việc lặp lại vô tận và tối ưu hóa thời gian xử lý.

## Vấn đề: Cạm bẫy của việc dịch chuyển tức thời

Quy tắc di chuyển cho phép ta đi từ chỉ số `i` sang:
- `i + 1` (tiến lên 1 bước).
- `i - 1` (lùi lại 1 bước).
- `j` với `arr[i] == arr[j]` và `i != j` (dịch chuyển tức thời đến bất kỳ ô nào cùng giá trị).

Nếu ta giải quyết bằng cách thử mọi khả năng duyệt (ví dụ như DFS hoặc BFS thông thường không tối ưu):
- **Chu kỳ lặp vô hạn:** Việc nhảy qua nhảy lại giữa các ô cùng giá trị hoặc các ô kề nhau sẽ nhanh chóng đưa ta vào vòng lặp không lối thoát nếu không đánh dấu những ô đã đi qua.
- **Bùng nổ thời gian xử lý ($O(n^2)$):** Khi một giá trị xuất hiện rất nhiều lần trong mảng (ví dụ mảng có 50,000 phần tử có cùng giá trị), từ mỗi ô ta lại duyệt qua toàn bộ các ô khác có cùng giá trị. Nếu không vô hiệu hóa mạng lưới liên kết này sau lần dùng đầu tiên, thuật toán sẽ liên tục kiểm tra lại các đỉnh đã thăm, dẫn tới việc quá tải thời gian chạy và gây ra lỗi quá thời gian (Time Limit Exceeded).

---

## Giải pháp: Thuật toán Duyệt theo chiều rộng kết hợp Đóng cổng dịch chuyển

Vì bài toán yêu cầu tìm số bước nhảy **ít nhất** (đường đi ngắn nhất) trên một đồ thị không có trọng số, thuật toán Duyệt theo chiều rộng (BFS) là sự lựa chọn tối ưu và tự nhiên nhất. BFS đảm bảo rằng lần đầu tiên ta chạm tới đích `n - 1`, số bước đi được ghi nhận chắc chắn là ngắn nhất.

Để giải quyết triệt để vấn đề bùng nổ liên kết giữa các ô cùng giá trị, ta sử dụng chiến thuật **"Đóng cổng dịch chuyển đã sử dụng"**:

1. **Thiết lập danh bạ liên kết:** Trước khi bắt đầu, ta dùng một bảng băm (Hash Map) để lưu trữ danh sách tất cả các chỉ số (indices) của từng giá trị xuất hiện trong mảng. Bảng băm này đóng vai trò như một cuốn "danh bạ cổng dịch chuyển", giúp ta tra cứu nhanh các điểm đến cùng giá trị chỉ với thời gian $O(1)$.
2. **Khởi hành BFS:** Bắt đầu từ chỉ số `0`, đưa nó vào hàng đợi (Queue) và đánh dấu là đã duyệt (Visited).
3. **Lan tỏa theo từng lớp (Level-by-Level):** Tại mỗi bước:
   - Ta lấy phần tử hiện tại ra khỏi hàng đợi.
   - Thử di chuyển đến `curr + 1` và `curr - 1`. Nếu các vị trí này hợp lệ và chưa từng đi qua, ta thêm chúng vào hàng đợi và đánh dấu đã duyệt.
   - Tra cứu trong "danh bạ" các ô có cùng giá trị `arr[curr]`. Duyệt qua tất cả các ô này, đưa chúng vào hàng đợi và đánh dấu đã duyệt.
4. **Đóng cổng dịch chuyển:** Đây là bước then chốt. Ngay sau khi đã duyệt qua và đưa tất cả các ô cùng giá trị `arr[curr]` vào hàng đợi, ta **xóa hoàn toàn** khóa `arr[curr]` ra khỏi bảng băm. Việc này đảm bảo rằng ở các bước sau, nếu ta vô tình gặp lại một ô khác cũng có giá trị `arr[curr]`, ta sẽ không tốn thời gian lặp lại việc kiểm tra các ô cùng giá trị này nữa.

---

## Tại sao tối ưu?

- **Thời gian xử lý tuyến tính ($O(n)$):** Nhờ việc xóa danh sách liên kết trong bảng băm ngay sau lần đầu tiên truy cập, mỗi cạnh nối giữa các ô cùng giá trị chỉ được duyệt qua đúng một lần duy nhất. Tổng số đỉnh và số cạnh được duyệt qua tối đa là $O(n)$, giúp thuật toán chạy cực kỳ nhanh chóng ngay cả với các bộ test lớn nhất ($n = 50,000$).
- **Không gian bộ nhớ hiệu quả ($O(n)$):** Bộ nhớ bổ trợ cần dùng bao gồm bảng băm chứa vị trí của các phần tử, hàng đợi BFS, và mảng đánh dấu trạng thái `visited`. Tất cả đều tỷ lệ thuận với số lượng phần tử $n$ của mảng.
- **Tính chính xác tuyệt đối:** BFS duyệt theo từng lớp sóng đồng tâm, lan tỏa đều ra các hướng. Lần đầu tiên lớp sóng này chạm tới đích `n - 1`, số bước sóng lan truyền chính là số bước di chuyển tối thiểu.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ cụ thể để hiểu rõ cơ chế "Đóng cổng dịch chuyển":

Mảng xuất phát: `arr = [11, 22, 33, 22, 11, 44, 44, 33]` với `n = 8`.
Mục tiêu: Tìm số bước ngắn nhất từ chỉ số `0` đến chỉ số `7` (giá trị `33`).

### Khởi tạo cấu trúc

1. **Danh bạ cổng dịch chuyển (Bảng băm):**
   ```text
   11 -> [0, 4]
   22 -> [1, 3]
   33 -> [2, 7]
   44 -> [5, 6]
   ```
2. **Hàng đợi (Queue):** `q = [0]`
3. **Mảng đánh dấu đã duyệt:** `visited = [true, false, false, false, false, false, false, false]`
4. **Số bước di chuyển:** `steps = 0`

### Các bước duyệt

**Bước 1: Xét lớp xuất phát (steps = 0)**
- Lấy chỉ số `0` (giá trị `11`) ra khỏi hàng đợi.
- Kiểm tra các hướng đi:
   - Di chuyển sang trái: `0 - 1 = -1` (không hợp lệ).
   - Di chuyển sang phải: `0 + 1 = 1` (giá trị `22`). Chưa duyệt -> Đưa `1` vào hàng đợi, đánh dấu `visited[1] = true`.
   - Dịch chuyển tức thời qua giá trị `11`: Tra cứu thấy chỉ số `4`. Chỉ số `4` chưa duyệt -> Đưa `4` vào hàng đợi, đánh dấu `visited[4] = true`.
- **Đóng cổng dịch chuyển `11`:** Xóa danh sách liên kết của `11` khỏi bảng băm.
- Kết thúc lớp 0, tăng `steps` lên `1`.
- Hàng đợi lúc này: `q = [1, 4]`

**Bước 2: Xét lớp tiếp theo (steps = 1)**
- **Lấy chỉ số `1` (giá trị `22`) ra khỏi hàng đợi:**
   - Di chuyển sang trái: `1 - 1 = 0` (đã duyệt -> bỏ qua).
   - Di chuyển sang phải: `1 + 1 = 2` (giá trị `33`). Chưa duyệt -> Đưa `2` vào hàng đợi, đánh dấu `visited[2] = true`.
   - Dịch chuyển tức thời qua giá trị `22`: Tra cứu thấy chỉ số `3`. Chỉ số `3` chưa duyệt -> Đưa `3` vào hàng đợi, đánh dấu `visited[3] = true`.
   - **Đóng cổng dịch chuyển `22`:** Xóa danh sách liên kết của `22` khỏi bảng băm.
- **Lấy chỉ số `4` (giá trị `11`) ra khỏi hàng đợi:**
   - Di chuyển sang trái: `4 - 1 = 3` (chỉ số `3` vừa được đưa vào hàng đợi ở trên nên đã được đánh dấu duyệt -> bỏ qua).
   - Di chuyển sang phải: `4 + 1 = 5` (giá trị `44`). Chưa duyệt -> Đưa `5` vào hàng đợi, đánh dấu `visited[5] = true`.
   - Dịch chuyển tức thời qua giá trị `11`: Tra cứu thấy khóa `11` đã bị xóa khỏi bảng băm -> Bỏ qua không cần duyệt trùng lặp.
- Kết thúc lớp 1, tăng `steps` lên `2`.
- Hàng đợi lúc này: `q = [2, 3, 5]`

**Bước 3: Xét lớp tiếp theo (steps = 2)**
- **Lấy chỉ số `2` (giá trị `33`) ra khỏi hàng đợi:**
   - Di chuyển sang trái: `2 - 1 = 1` (đã duyệt -> bỏ qua).
   - Di chuyển sang phải: `2 + 1 = 3` (đã duyệt -> bỏ qua).
   - Dịch chuyển tức thời qua giá trị `33`: Tra cứu thấy chỉ số `7` (chỉ số cuối cùng). Chưa duyệt -> Đưa `7` vào hàng đợi, đánh dấu `visited[7] = true`.
   - **Đóng cổng dịch chuyển `33`:** Xóa danh sách liên kết của `33`.
- **Lấy chỉ số `3` (giá trị `22`) ra khỏi hàng đợi:**
   - Cổng dịch chuyển `22` đã bị xóa từ trước, chỉ kiểm tra hai bên kề nhưng các ô kề đều đã duyệt -> bỏ qua.
- **Lấy chỉ số `5` (giá trị `44`) ra khỏi hàng đợi:**
   - Di chuyển sang phải: `6` (chưa duyệt -> đưa vào hàng đợi `q = [7, 6]`).
   - Dịch chuyển tức thời qua `44`: Đóng cổng `44` và đưa `6` vào hàng đợi (nếu chưa duyệt).
- Kết thúc lớp 2, tăng `steps` lên `3`.
- Hàng đợi lúc này: `q = [7, 6]`

**Bước 4: Xét lớp tiếp theo (steps = 3)**
- Lấy chỉ số `7` ra khỏi hàng đợi.
- Phát hiện `7 == n - 1` (Đã chạm đích!).
- **Kết quả:** Thuật toán dừng lại và trả về `steps = 3`. Con đường ngắn nhất là: `0 -> 1 -> 2 -> 7`.

---

## Phân tích chuyên sâu Test Case: `arr = [7, 7, 7, 7, 7, 7]` với `n = 6`

Trường hợp mảng toàn các giá trị trùng nhau là "cơn ác mộng" đối với các thuật toán BFS thông thường nếu không có cơ chế đóng cổng dịch chuyển. Hãy xem thiết kế của chúng ta xử lý cực kỳ thông minh thế nào:

1. Bắt đầu tại chỉ số `0`. `visited[0] = true`.
2. Truy vấn danh sách các ô cùng giá trị `7`: `[0, 1, 2, 3, 4, 5]`.
3. Đưa tất cả các ô `1, 2, 3, 4, 5` vào hàng đợi và đánh dấu `visited` cho toàn bộ các ô này.
4. **Xóa hoàn toàn khóa `7` khỏi bảng băm**.
5. Khi xét các phần tử tiếp theo trong hàng đợi (như chỉ số `1`, `2`...), việc cố gắng tra cứu cổng dịch chuyển của giá trị `7` sẽ trả về kết quả rỗng. Nhờ đó, ta hoàn toàn không tốn bất kỳ phép duyệt lặp nào.
6. Kết quả trả về `1` ngay lập tức ở bước tiếp theo khi pop chỉ số `5` (đích). Thời gian thực thi là $O(n)$ thay vì $O(n^2)$.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Chỉ số kề nhau và cùng giá trị đan xen):**
   - Đầu vào: `arr = [10, 20, 30, 40, 10, 50, 40]`
   - Mô tả: Đi từ `0` (10) -> nhảy cổng dịch chuyển đến `4` (10) -> nhảy tiến đến `5` (50) -> nhảy tiến đến `6` (40) (đích). Hoặc đi từ `0` (10) -> nhảy cổng dịch chuyển đến `4` (10) -> nhảy lùi đến `3` (40) -> nhảy cổng dịch chuyển đến `6` (40) (đích).
   - Kết quả kỳ vọng: `3` (Đường đi tối ưu: `0 -> 4 -> 3 -> 6`)

- **Case 2 (Độ dài mảng tối thiểu):**
   - Đầu vào: `arr = [9]`
   - Mô tả: Mảng chỉ có duy nhất 1 phần tử. Bạn đã đứng sẵn ở đích.
   - Kết quả kỳ vọng: `0`

- **Case 3 (Đường đi bắt buộc phải đi lùi):**
   - Đầu vào: `arr = [100, -2, 3, -2, 100, 5, 6, 7]`
   - Mô tả: Từ `0` (100) -> nhảy cổng dịch chuyển đến `4` (100) -> nhảy lùi đến `3` (-2) -> nhảy cổng dịch chuyển đến `1` (-2) -> nhảy tiến đến `2` (3) (Không tối ưu). Thay vào đó, đường đi tối ưu là `0` -> `4` -> `5` -> `6` -> `7`.
   - Kết quả kỳ vọng: `4` (Đường đi tối ưu: `0 -> 4 -> 5 -> 6 -> 7`)

- **Case 4 (Mảng tịnh tiến không có cổng trùng nhau):**
   - Đầu vào: `arr = [1, 2, 3, 4, 5]`
   - Mô tả: Mọi phần tử đều độc nhất, các cổng dịch chuyển không hoạt động. BFS sẽ chỉ hoạt động dựa trên các bước nhảy `+1`.
   - Kết quả kỳ vọng: `4` (Đường đi tối ưu: `0 -> 1 -> 2 -> 3 -> 4`)

- **Case 5 (Mảng có chu kỳ trùng lặp lớn ở sát đích):**
   - Đầu vào: `arr = [8, 8, 8, 8, 8, 8, 8, 9]`
   - Mô tả: Tất cả các phần tử đầu tiên đều là `8`, phần tử cuối cùng là `9`. Từ `0` (8) -> nhảy cổng dịch chuyển đến `6` (8) (ô chứa `8` cuối cùng) -> nhảy tiến 1 bước đến `7` (9) (đích).
   - Kết quả kỳ vọng: `2` (Đường đi tối ưu: `0 -> 6 -> 7`)

---

**Tổng kết:** Vẻ đẹp của thiết kế giải pháp cho Jump Game IV nằm ở việc biến đổi khéo léo một bài toán duyệt đồ thị có nguy cơ bùng nổ tổ hợp thành một thuật toán tuyến tính mượt mà. Bằng cách áp dụng cấu trúc dữ liệu hàng đợi (Queue) của BFS kết hợp với tư duy "Đóng cổng dịch chuyển" trong bảng băm, chúng ta vừa đảm bảo tính chính xác của đường đi ngắn nhất, vừa triệt tiêu hoàn toàn các phép tính dư thừa, đạt được hiệu năng tối đa trên mọi bộ dữ liệu kiểm thử.
