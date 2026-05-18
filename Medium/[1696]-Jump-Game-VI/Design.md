# Tư duy thiết kế: Cửa sổ trượt tối ưu và Hàng đợi đơn điệu (Jump Game VI)

Bài toán tìm đường đi đạt điểm số lớn nhất trên chuỗi các bước nhảy giới hạn đại diện cho một mô hình tối ưu hóa quy hoạch động trên không gian một chiều. Ở đây, mỗi ô có một giá trị điểm số có thể là dương hoặc âm. Ta được phép nhảy tối đa `k` bước về phía trước. Mục tiêu duy nhất là tìm đường đi về đích sao cho tổng điểm tích lũy là lớn nhất. Thách thức lớn nhất của bài toán này nằm ở giới hạn thời gian. Nếu áp dụng quy hoạch động trực diện thông thường, thuật toán sẽ bị sa lầy vào việc tìm kiếm điểm số tối đa trong quá khứ ($O(n \times k)$), dẫn đến lỗi quá thời gian chạy khi `n` và `k` lên tới $10^5$.

## Vấn đề: Cơn ác mộng tìm kiếm trong cửa sổ quá khứ

Ta gọi `dp[i]` là điểm số lớn nhất có thể tích lũy được khi đi từ đầu mảng đến ô `i`. 

Công thức chuyển trạng thái của quy hoạch động là:
$$\text{dp}[i] = \text{nums}[i] + \max_{i - k \le j < i} (\text{dp}[j])$$

Hai thách thức chính phát sinh:
- **Chi phí tìm kiếm cực đại ($O(k)$):** Để tính được `dp[i]`, ta phải quét ngược lại `k` trạng thái trước đó để tìm giá trị `dp[j]` lớn nhất. Khi $n = 10^5$ và $k = 10^5$, tổng số thao tác tính toán lên tới $n \times k = 10^{10}$, vượt quá xa giới hạn thời gian chạy cho phép trong các cuộc thi lập trình (thông thường chỉ cho phép dưới $10^8$ thao tác).
- **Tính chất trùng lặp vùng quét:** Khi ta dịch chuyển từ `i` sang `i + 1`, cửa sổ tìm kiếm quá khứ dịch chuyển từ `[i - k, i - 1]` sang `[i - k + 1, i]`. Vùng chồng lấn giữa hai cửa sổ này là cực kỳ lớn, nhưng việc quét lại từ đầu làm lãng phí nghiêm trọng tài nguyên tính toán.

---

## Giải pháp: Hàng đợi đơn điệu giảm dần (Monotonic Deque DP)

Để đạt hiệu năng tối đa, ta cần một cơ chế tra cứu giá trị lớn nhất trong cửa sổ trượt kích thước `k` với thời gian hằng số $O(1)$. Giải pháp hoàn hảo ở đây là kết hợp Quy hoạch động với **Hàng đợi hai đầu đơn điệu (Monotonic Deque)**.

Hãy tưởng tượng bạn là một vận động viên lướt sóng trượt và đang duy trì một **"đoàn hộ tống năng lượng" (energy escort convoy)**. Thay vì nhìn lại tất cả `k` điểm tựa cũ ở mỗi bước, bạn chỉ giữ lại những ứng viên mạnh nhất trong hàng đợi `dq`:

1. **Tính đơn điệu:** Hàng đợi `dq` lưu trữ các chỉ số của mảng `dp` sao cho giá trị điểm số tương ứng luôn giảm dần nghiêm ngặt từ đầu đến cuối hàng đợi (`dp[dq.front()] > dp[dq.back()]`). Do đó, ứng viên tốt nhất (đạt điểm cao nhất) luôn luôn nằm ở đầu hàng đợi (`dq.front()`).
2. **Quy trình tịnh tiến mượt mà:** Tại mỗi vị trí `i` từ `1` đến `n - 1`:
   - **Nghỉ hưu các ứng viên quá hạn:** Ta kiểm tra phần tử ở đầu hàng đợi. Nếu chỉ số của nó đã nằm ngoài phạm vi cửa sổ trượt (`dq.front() < i - k`), ta loại bỏ nó ra khỏi hàng đợi (`pop_front()`).
   - **Nạp điểm tối đa:** Nhờ tính đơn điệu, ta lấy trực tiếp điểm tối đa ở đầu hàng đợi để tính điểm cho ô hiện tại trong $O(1)$ thời gian:
     $$\text{dp}[i] = \text{nums}[i] + \text{dp}[\text{dq.front()}]$$
   - **Thanh lọc hàng đợi (Duy trì tính đơn điệu):** Trước khi đưa `i` vào hàng đợi, ta kiểm tra từ cuối hàng đợi ngược lên. Bất kỳ ứng viên `j` nào trong hàng đợi có điểm `dp[j] <= dp[i]` sẽ bị loại bỏ ngay lập tức (`pop_back()`). Tại sao? Bởi vì ô `i` vừa mới hơn (tồn tại lâu hơn trong tương lai) lại vừa có điểm số cao hơn hoặc bằng `j`. Do đó, `j` không bao giờ có cơ hội được chọn làm điểm nhảy tối ưu nữa.
   - **Ghi nhận ứng viên mới:** Đưa chỉ số `i` vào cuối hàng đợi (`push_back()`).
3. **Kết quả:** Trả về `dp[n - 1]`.

---

## Tại sao tối ưu?

- **Hiệu năng tuyến tính thực tế ($O(n)$ Time Complexity):** Dù có vòng lặp `while` dùng để loại bỏ các phần tử yếu hơn từ cuối hàng đợi, hãy lưu ý rằng mỗi chỉ số từ `0` đến `n - 1` chỉ được đưa vào hàng đợi đúng 1 lần duy nhất (`push_back`) và bị loại bỏ tối đa 1 lần duy nhất (`pop_back` hoặc `pop_front`). Vì thế, tổng số thao tác trên hàng đợi trong suốt toàn bộ thuật toán bị chặn trên bởi $2 \times n$, đạt độ phức tạp thời gian tuyến tính $O(n)$ hoàn hảo.
- **Không gian tối ưu ($O(n)$ Space Complexity):** Bộ nhớ bổ trợ cần dùng gồm mảng `dp` kích thước $n$ và hàng đợi `dq` chứa tối đa $k$ phần tử, hoàn toàn gọn nhẹ.
- **Tư duy thiết kế vượt trội:** Sự kết hợp giữa cấu trúc dữ liệu Monotonic Deque và Quy hoạch động đã biến đổi một phép toán quét dải phức tạp $O(k)$ thành một phép tra cứu hằng số $O(1)$ siêu tốc.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ cụ thể:

Mảng đầu vào: `nums = [1, -1, -2, 4, -7, 3]` với `k = 2`. Độ dài `n = 6`.

### Khởi tạo cấu trúc
- Mảng kết quả DP: `dp = [1, 0, 0, 0, 0, 0]` (vạch xuất phát `dp[0] = 1`)
- Hàng đợi đơn điệu: `dq = [0]` (lưu chỉ số `0`)

### Tiến trình duyệt

**Vòng lặp chạy từ `i = 1` đến `5`:**

- **Duyệt `i = 1`:**
   - Đầu hàng đợi `dq.front() = 0` nằm trong cửa sổ `[1-2, 1-1] = [-1, 0]`. Giữ nguyên.
   - Tính điểm: `dp[1] = nums[1] + dp[0] = -1 + 1 = 0`.
   - Thanh lọc hàng đợi: `dp[dq.back()] = dp[0] = 1 > dp[1] = 0`. Không có phần tử nào bị loại từ cuối.
   - Đưa `1` vào cuối hàng đợi: `dq = [0, 1]`.
   - Trạng thái: `dp = [1, 0, 0, 0, 0, 0]`, `dq = [0, 1]`.

- **Duyệt `i = 2`:**
   - Đầu hàng đợi `dq.front() = 0` nằm trong cửa sổ `[0, 1]`. Giữ nguyên.
   - Tính điểm: `dp[2] = nums[2] + dp[0] = -2 + 1 = -1`.
   - Thanh lọc hàng đợi: `dp[dq.back()] = dp[1] = 0 > dp[2] = -1`. Không có phần tử bị loại.
   - Đưa `2` vào cuối hàng đợi: `dq = [0, 1, 2]`.
   - Trạng thái: `dp = [1, 0, -1, 0, 0, 0]`, `dq = [0, 1, 2]`.

- **Duyệt `i = 3`:**
   - Đầu hàng đợi `dq.front() = 0` nằm ngoài cửa sổ `[1, 2]`. **Loại bỏ `0` từ đầu hàng đợi!** Hiện tại `dq = [1, 2]`.
   - Tính điểm: `dp[3] = nums[3] + dp[dq.front()] = dp[3] = 4 + dp[1] = 4 + 0 = 4`.
   - Thanh lọc hàng đợi: 
     - Xét cuối hàng đợi: `dp[2] = -1 <= dp[3] = 4` -> Loại bỏ `2` từ cuối. `dq = [1]`.
     - Xét tiếp cuối hàng đợi: `dp[1] = 0 <= dp[3] = 4` -> Loại bỏ `1` từ cuối. `dq = []`.
   - Đưa `3` vào hàng đợi trống: `dq = [3]`.
   - Trạng thái: `dp = [1, 0, -1, 4, 0, 0]`, `dq = [3]`.

- **Duyệt `i = 4`:**
   - Đầu hàng đợi `dq.front() = 3` nằm trong cửa sổ `[2, 3]`. Giữ nguyên.
   - Tính điểm: `dp[4] = nums[4] + dp[3] = -7 + 4 = -3`.
   - Thanh lọc hàng đợi: `dp[dq.back()] = dp[3] = 4 > -3`. Giữ nguyên.
   - Đưa `4` vào cuối hàng đợi: `dq = [3, 4]`.
   - Trạng thái: `dp = [1, 0, -1, 4, -3, 0]`, `dq = [3, 4]`.

- **Duyệt `i = 5` (đích):**
   - Đầu hàng đợi `dq.front() = 3` nằm trong cửa sổ `[3, 4]`. Giữ nguyên.
   - Tính điểm: `dp[5] = nums[5] + dp[3] = 3 + 4 = 7`.
   - Thuật toán kết thúc vòng lặp.

### Kết quả cuối cùng
Giá trị tại vạch đích `dp[5] = 7` được trả về làm kết quả tối ưu nhất.

---

## Phân tích chuyên sâu Test Case: `nums = [10, -5, -10]` với `k = 1`

Hãy xem cách thuật toán xử lý trường hợp bước nhảy cực ngắn bắt buộc này:

1. Khởi đầu: `dp[0] = 10`, `dq = [0]`.
2. **Duyệt `i = 1`:**
   - `dq.front() = 0` (trong tầm nhảy 1 bước).
   - `dp[1] = nums[1] + dp[0] = -5 + 10 = 5`.
   - Thanh lọc hàng đợi: `dp[0] = 10 > 5` -> `dq = [0, 1]`.
3. **Duyệt `i = 2`:**
   - `dq.front() = 0` nằm ngoài tầm nhảy 1 bước (`0 < 2 - 1 = 1`). **Loại bỏ `0` từ đầu hàng đợi!** Hiện tại đầu hàng đợi là `1`.
   - Tính điểm: `dp[2] = nums[2] + dp[1] = -10 + 5 = -5`.
4. Trả về kết quả tại đích: `-5`. Mọi quyết định bước nhảy đều được cưỡng chế theo từng ô một cách chính xác.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Mảng toàn số âm cực lớn):**
   - Đầu vào: `nums = [-1, -2, -3, -4, -5]`, `k = 2`
   - Mô tả: Mọi phiến đá đều mang giá trị âm, tức là ta bị trừ điểm khi bước qua. Thuật toán phải chọn lộ trình thông minh để số lần nhảy là ít nhất và chọn các ô có điểm trừ nhỏ nhất.
   - Kết quả kỳ vọng: `-9` (Lộ trình tối ưu: `0 -> 2 -> 4`, tổng điểm: `-1 + (-3) + (-5) = -9`)

- **Case 2 (Độ dài mảng tối thiểu):**
   - Đầu vào: `nums = [100]`, `k = 5`
   - Mô tả: Mảng chỉ có duy nhất 1 phần tử. Không cần thực hiện bất kỳ cú nhảy nào, điểm số chính là phần tử duy nhất.
   - Kết quả kỳ vọng: `100`

- **Case 3 (Cây cầu số dương cực lớn ở giữa các thung lũng số âm):**
   - Đầu vào: `nums = [1, -10, -10, 20, -10, -10, 1]`, `k = 3`
   - Mô tả: Các ô xung quanh đều có điểm âm cực lớn, nhưng ở giữa có ô `20` dương rất to. Với `k = 3`, ta có thể nhảy phóng qua thung lũng số âm để tiếp đất tại ô `20` rồi từ `20` nhảy phóng thẳng về đích `6`.
   - Kết quả kỳ vọng: `22` (Lộ trình tối ưu: `0 -> 3 -> 6`, tổng điểm: `1 + 20 + 1 = 22`)

- **Case 4 (Cơ hội lựa chọn vô tận):**
   - Đầu vào: `nums = [1, 2, 3, 4, 5]`, `k = 10`
   - Mô tả: Khoảng cách bước nhảy `k` lớn hơn cả chiều dài mảng. Explorer có thể tự do nhảy một bước thẳng từ vạch xuất phát tới đích hoặc đi qua các ô trung gian. Vì tất cả các ô đều dương, đường đi tối ưu nhất là đi qua toàn bộ các ô để thu thập toàn bộ điểm.
   - Kết quả kỳ vọng: `15` (Lộ trình tối ưu: `0 -> 1 -> 2 -> 3 -> 4`, tổng điểm: `1 + 2 + 3 + 4 + 5 = 15`)

- **Case 5 (Mảng có chướng ngại vật âm xen kẽ):**
   - Đầu vào: `nums = [5, -2, 3, -1, 4]`, `k = 2`
   - Mô tả: Các ô âm và dương đan xen nhau. Với `k = 2`, ta có thể chọn bỏ qua ô `-2` để nhảy thẳng tới `3`, sau đó nhảy tới `4` để thu được điểm số tối đa mà tránh được các ô âm.
   - Kết quả kỳ vọng: `12` (Lộ trình tối ưu: `0 -> 2 -> 4`, tổng điểm: `5 + 3 + 4 = 12`)

---

**Tổng kết:** Bản chất bài toán Jump Game VI là sự giao thoa hoàn hảo giữa tư duy Quy hoạch động và cấu trúc dữ liệu nâng cao. Bằng cách áp dụng hàng đợi hai đầu đơn điệu (Monotonic Deque), chúng ta đã triệt tiêu hoàn toàn sự tính toán trùng lặp, mở khóa tốc độ xử lý tuyến tính $O(n)$ siêu tốc giúp giải bài toán có giới hạn cực lớn này một cách vô cùng ngoạn mục.
