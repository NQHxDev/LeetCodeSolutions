# Tư duy thiết kế: Bản đồ phân vùng và lớp sóng lan truyền tối ưu (Jump Game II)

Bài toán tìm số bước nhảy ít nhất để đi từ đầu mảng đến cuối mảng đại diện cho một mô hình tìm đường đi ngắn nhất trên đồ thị ẩn. Khác với phần đầu (chỉ cần xác định có tới đích hay không), Jump Game II yêu cầu ta phải đưa ra số bước di chuyển tối thiểu. Điều này đòi hỏi một chiến thuật tối ưu hóa khắt khe. Nếu áp dụng các phương pháp tìm kiếm thông thường hoặc quy hoạch động trực diện, ta sẽ dễ dàng bị cuốn vào việc tính toán lặp lại các dải nhảy chồng chéo, khiến thuật toán bị quá tải thời gian chạy ($O(n^2)$) trên các bộ dữ liệu lớn.

## Vấn đề: Cạm bẫy chồng lấn tầm nhảy và sự bùng nổ tổ hợp

Tại mỗi vị trí `i`, con số `nums[i]` đại diện cho phạm vi bước nhảy tối đa. Ta có thể chọn nhảy tới bất kỳ ô nào nằm trong khoảng `[i + 1, i + nums[i]]`.

Nếu ta giải quyết bằng cách thử mọi khả năng nhảy (DFS/Queue BFS thông thường):
- **Bùng nổ tổ hợp:** Việc duyệt từng cách chọn bước nhảy để tìm số bước ít nhất tạo ra cây quyết định khổng lồ với độ phức tạp lũy thừa ($O(2^n)$).
- **Quy hoạch động thông thường ($O(n^2)$):** Ta định nghĩa `dp[i]` là số bước ít nhất để về đích từ ô `i`. Để tính `dp[i]`, ta phải quét qua toàn bộ các ô trong tầm nhảy của nó và lấy giá trị nhỏ nhất. Việc này dẫn đến độ phức tạp thời gian $O(n^2)$. Với $n = 10^4$ hoặc $10^5$, thuật toán này sẽ ngay lập tức bị lỗi quá thời gian chạy (TLE).

---

## Giải pháp: Bản đồ phân vùng và Lớp sóng lan truyền (Greedy Algorithm)

Để đạt được sự tối ưu tuyệt đối, ta có thể mô hình hóa thuật toán Duyệt theo chiều rộng (BFS) ẩn dưới dạng một thuật toán Tham lam (Greedy) tinh gọn mà không cần sử dụng cấu trúc hàng đợi thực tế. 

Hãy tưởng tượng bạn đứng ở vạch xuất phát và đang khám phá một chuỗi hòn đảo. Thay vì nhảy lung tung, bạn phân chia hành trình thành các **"lớp sóng lan truyền"** (tương ứng với số bước nhảy):

1. **Khái niệm phân vùng:** 
   - `jumps`: Số bước nhảy đã thực hiện (số lớp sóng).
   - `currentEnd`: Biên giới giới hạn xa nhất có thể đạt được trong lớp sóng hiện tại (lãnh địa hiện tại).
   - `furthest`: Chỉ số xa nhất ta có thể đứng từ bất kỳ ô nào thuộc lãnh địa hiện tại để chuẩn bị phóng sang lãnh địa tiếp theo.
2. **Quy trình tịnh tiến:** Ta duyệt qua từng ô `i` từ `0` đến `n - 2` (không cần duyệt ô cuối cùng vì ta chỉ muốn biết bước nhảy để *đạt được* đích chứ không nhảy tiếp từ đích):
   - Tại mỗi ô `i`, ta liên tục cập nhật điểm xa nhất có thể phóng tới từ ô này:
     $$\text{furthest} = \max(\text{furthest}, i + \text{nums}[i])$$
   - **Chạm biên giới lãnh địa:** Khi chỉ số `i` tịnh tiến tới sát biên giới hiện tại (`i == currentEnd`), điều này có nghĩa là ta đã khám phá hết toàn bộ lãnh địa hiện tại. Để đi tiếp, ta **bắt buộc phải thực hiện thêm 1 cú nhảy nữa** sang lãnh địa mới.
     - Ta tăng `jumps` lên 1.
     - Thiết lập biên giới lãnh địa mới bằng điểm xa nhất ta từng quan sát được từ trước tới nay: `currentEnd = furthest`.
     - **Thoát sớm (Early Exit):** Nếu biên giới mới đã bao phủ hoặc vượt quá vạch đích (`currentEnd >= n - 1`), ta có thể dừng ngay lập tức vì chắc chắn ta sẽ về đích trong cú nhảy này.

---

## Tại sau tối ưu?

- **Tốc độ xử lý tuyến tính tuyệt đối ($O(n)$ Time Complexity):** Ta chỉ cần duyệt qua mảng đúng một vòng duy nhất từ trái sang phải. Không có vòng lặp lồng nhau, không có đệ quy hay tính toán trùng lặp. Thuật toán chạy cực nhanh ngay cả với $n = 10^5$.
- **Triệt tiêu bộ nhớ phụ trợ ($O(1)$ Space Complexity):** Thay vì duy trì một hàng đợi BFS cồng kềnh tốn bộ nhớ $O(n)$, thuật toán chỉ dùng 3 biến nguyên đơn giản để theo dõi trạng thái biên giới. Bộ nhớ phụ trợ là hằng số tuyệt đối.
- **Tính đúng đắn toán học:** Vì BFS luôn tìm ra đường đi ngắn nhất trên đồ thị không trọng số, việc gom nhóm các phần tử theo biên giới `currentEnd` tương đương với việc duyệt BFS theo tầng lớp, đảm bảo kết quả trả về luôn là số bước nhảy ít nhất.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ thực tế:

Mảng đầu vào: `nums = [2, 3, 1, 1, 4]` với `n = 5`.
Mục tiêu: Đạt tới chỉ số `4`.

### Khởi tạo cấu trúc
- `jumps = 0` (chưa thực hiện cú nhảy nào)
- `currentEnd = 0` (lãnh địa hiện tại chỉ giới hạn ở ô xuất phát)
- `furthest = 0` (chưa quan sát thấy điểm xa hơn)

### Tiến trình duyệt

**Vòng lặp chạy từ `i = 0` đến `3` (n - 2):**

- **Duyệt `i = 0`:**
   - Cập nhật điểm quan sát xa nhất: $\text{furthest} = \max(0, 0 + 2) = 2$.
   - **Chạm biên lãnh địa (`i == currentEnd` -> `0 == 0`):** Ta phải nhảy!
     - Tăng số bước nhảy: `jumps = 1`.
     - Thiết lập biên giới mới: `currentEnd = furthest = 2`.
     - Trạng thái hiện tại: `jumps = 1`, `currentEnd = 2`, `furthest = 2`.

- **Duyệt `i = 1`:**
   - Cập nhật điểm quan sát xa nhất: $\text{furthest} = \max(2, 1 + 3) = 4$.
   - Chưa chạm biên giới lãnh địa hiện tại (`1 != 2`): Tiếp tục đi dò đường trong lãnh địa `1`.
     - Trạng thái hiện tại: `jumps = 1`, `currentEnd = 2`, `furthest = 4`.

- **Duyệt `i = 2`:**
   - Cập nhật điểm quan sát xa nhất: $\text{furthest} = \max(4, 2 + 1) = 4$.
   - **Chạm biên lãnh địa (`i == currentEnd` -> `2 == 2`):** Ta phải nhảy!
     - Tăng số bước nhảy: `jumps = 2`.
     - Thiết lập biên giới mới: `currentEnd = furthest = 4`.
     - **Thoát sớm:** Phát hiện biên giới mới đã phủ qua vạch đích (`4 >= 4`). Thuật toán ngắt vòng lặp ngay lập tức và trả về `jumps = 2`.

Hành trình tối ưu nhất gồm 2 bước nhảy: `0 -> 1 -> 4`.

---

## Phân tích chuyên sâu Test Case: `nums = [1, 2, 0, 1]` với `n = 4`

Hãy xem thuật toán xử lý trường hợp có ô số `0` cản đường này như thế nào:

1. Khởi đầu: `jumps = 0`, `currentEnd = 0`, `furthest = 0`.
2. **Duyệt `i = 0`:**
   - $\text{furthest} = \max(0, 0 + 1) = 1$.
   - Chạm biên (`0 == 0`): `jumps = 1`, `currentEnd = 1`.
3. **Duyệt `i = 1`:**
   - $\text{furthest} = \max(1, 1 + 2) = 3$.
   - Chạm biên (`1 == 1`): `jumps = 2`, `currentEnd = 3`.
   - **Thoát sớm:** Vì `currentEnd >= 3` (đích), ngắt vòng lặp và trả về `jumps = 2`.
4. Nhờ cơ chế thoát sớm, thuật toán hoàn toàn bỏ qua ô số `0` ở chỉ số `2`, đảm bảo ta nhảy trực tiếp từ ô `1` phóng qua ô `2` để tới thẳng ô `3`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Chuỗi nhảy tuần tự bắt buộc):**
   - Đầu vào: `nums = [1, 1, 1, 1]`
   - Mô tả: Mỗi ô chỉ có đúng tầm xa 1 bước. Explorer bắt buộc phải thực hiện nhảy qua từng ô một cách tuần tự để về đích.
   - Kết quả kỳ vọng: `3` (Đường đi: `0 -> 1 -> 2 -> 3`)

- **Case 2 (Độ dài mảng tối thiểu):**
   - Đầu vào: `nums = [5]`
   - Mô tả: Mảng chỉ có duy nhất 1 phần tử. Không cần thực hiện bất kỳ cú nhảy nào.
   - Kết quả kỳ vọng: `0`

- **Case 3 (Đường đi chứa hố sâu số 0 nhưng có thể nhảy phóng qua):**
   - Đầu vào: `nums = [3, 0, 0, 4, 0, 0, 1]`
   - Mô tả: Ô chỉ số `1` và `2` đều có giá trị `0`, nhưng từ ô `0` ta có tầm xa là `3` nên có thể nhảy phóng trực tiếp qua hố sâu này để tiếp đất tại ô chỉ số `3` (nơi có sức mạnh `4` giúp ta nhảy thẳng về đích `6`).
   - Kết quả kỳ vọng: `2` (Đường đi: `0 -> 3 -> 6`)

- **Case 4 (Sức mạnh nhảy tối đa ngay từ ô đầu):**
   - Đầu vào: `nums = [10, 1, 2, 3, 4]`
   - Mô tả: Ô đầu tiên có tầm xa `10`, dư sức phóng thẳng về đích chỉ trong đúng 1 cú nhảy duy nhất.
   - Kết quả kỳ vọng: `1`

- **Case 5 (Mảng zic-zac có các ô năng lượng đan xen):**
   - Đầu vào: `nums = [2, 4, 1, 1, 1, 1, 1]`
   - Mô tả: Từ ô `0` ta có thể nhảy tới `1` hoặc `2`. Nếu nhảy tới `1` (năng lượng `4`), ta có thể tiếp tục nhảy tới chỉ số `5` rồi tới đích `6` (tổng cộng 3 bước). Nếu nhảy tới `2` (năng lượng `1`), ta bị kẹt trong chuỗi các bước nhảy 1. Quy hoạch tham lam sẽ tự động nhận diện ô `1` có biên giới xa nhất để chọn lộ trình 3 bước.
   - Kết quả kỳ vọng: `3` (Đường đi tối ưu: `0 -> 1 -> 5 -> 6`)

---

**Tổng kết:** Vẻ đẹp của thiết kế giải pháp cho Jump Game II nằm ở việc thu gọn một bài toán tìm kiếm đường đi ngắn nhất BFS cồng kềnh thành một cấu trúc tham lam (Greedy) tuyến tính cực kỳ thanh thoát. Bằng cách gom nhóm các bước nhảy theo phân vùng biên giới `currentEnd`, thuật toán đã triệt tiêu hoàn toàn sự tính toán trùng lặp, mang lại hiệu năng tối đa trên mọi khía cạnh bộ nhớ và thời gian chạy.
