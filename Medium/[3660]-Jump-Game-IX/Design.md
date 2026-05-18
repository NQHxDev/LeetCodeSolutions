# Tư duy thiết kế: Phân rã khối liên thông và Chiến thuật tịnh tiến hai chiều (Jump Game IX)

Bài toán tìm giá trị tối đa có thể đạt được từ mỗi vị trí trong một chuỗi số dựa theo các quy tắc nhảy hai chiều đại diện cho một mô hình đồ thị vô hướng ẩn vô cùng độc đáo. Từ một chỉ số bất kỳ, ta được phép nhảy về phía trước tới một ô nhỏ hơn, hoặc nhảy về phía sau tới một ô lớn hơn. Mục tiêu duy nhất là trả về giá trị lớn nhất có thể ghé thăm được từ mỗi vị trí. Thách thức lớn nhất ở đây là việc tìm kiếm lộ trình có thể rất lắt léo và việc xây dựng đồ thị trực tiếp rồi tìm các thành phần liên thông bằng BFS/DFS sẽ tiêu tốn $O(n^2)$ thời gian và không gian bộ nhớ, dẫn đến lỗi quá tải thời gian chạy (TLE) trên các bộ test lớn.

## Vấn đề: Cơn ác mộng dựng đồ thị và Phép toán nghịch thế khổng lồ

Quy tắc bước nhảy cho phép ta nhảy từ chỉ số `i` sang `j` nếu:

- **Nhảy tiến (j > i):** `nums[j] < nums[i]`.
- **Nhảy lùi (j < i):** `nums[j] > nums[i]`.

Một quan sát cực kỳ quan trọng xuất hiện:

- Giả sử có hai chỉ số $a < b$. Điều kiện để nhảy tiến từ $a$ sang $b$ là `nums[b] < nums[a]`.
- Điều kiện để nhảy lùi từ $b$ về $a$ là `nums[a] > nums[b]`.
- Hai điều kiện này là **hoàn toàn trùng khớp**!
- Điều này có nghĩa là, nếu tồn tại một cặp nghịch thế $a < b$ mà `nums[a] > nums[b]`, thì ta luôn có thể di chuyển hai chiều tự do giữa $a$ và $b$. Cạnh nối giữa chúng là **vô hướng (bidirectional)**.
- Ngược lại, nếu `nums[a] <= nums[b]` với mọi $a < b$, ta hoàn toàn không thể di chuyển trực tiếp giữa $a$ và $b$.

Từ đó, bài toán thực chất là tìm các thành phần liên thông trên một đồ thị vô hướng, nơi mỗi cạnh đại diện cho một cặp nghịch thế. Tuy nhiên:

- Số lượng nghịch thế trong mảng có thể lên tới $O(n^2)$. Việc dựng toàn bộ các cạnh và chạy thuật toán tìm thành phần liên thông (như DFS hoặc Union-Find) sẽ tốn $O(n^2)$ thời gian và không gian. Khi $n = 10^5$, thuật toán sẽ lập tức bị quá tải.

---

## Giải pháp: Điểm chia cắt và Phân rã khối liên thông Contiguous (PrefixMax - SuffixMin Division)

Để đạt hiệu năng tối đa, ta cần khai thác cấu trúc topo đặc biệt của đồ thị nghịch thế này.

Ta đặt câu hỏi: Khi nào đồ thị bị **chia cắt hoàn toàn** tại một ranh giới `p`?

- Đồ thị sẽ bị chia cắt tại `p` (không có bất kỳ cạnh nào kết nối phần bên trái $\{0 \dots p-1\}$ và phần bên phải $\{p \dots n-1\}$) nếu và chỉ nếu mọi phần tử bên trái đều nhỏ hơn hoặc bằng mọi phần tử bên phải.
- Điều này tương đương với điều kiện:
  $$\max_{0 \le k < p} (\text{nums}[k]) \le \min_{p \le j < n} (\text{nums}[j])$$
- Khi điều kiện này xảy ra, ta gọi `p` là một **"điểm chia cắt" (split point)**. Rõ ràng, không có hành trình nhảy nào có thể vượt qua ranh giới `p` từ bất kỳ hướng nào.

Từ quan sát trên, ta xây dựng thuật toán phân rã khối liên thông tuyến tính:

1. **Khái niệm Khối liên thông (Contiguous Block):** Đồ thị sẽ được phân chia thành các khối chỉ số liên tục kế tiếp nhau, phân tách bởi các điểm chia cắt `p`. Bên trong mỗi khối, vì không có điểm chia cắt nào khác, đồ thị con tương ứng chắc chắn sẽ **liên thông hoàn toàn** (mọi đỉnh đều có thể đi tới nhau thông qua một chuỗi các bước nhảy).
2. **Tính toán cực đại khối:** Do mọi đỉnh trong cùng một khối đều liên thông với nhau, giá trị tối đa reachable từ bất kỳ đỉnh nào trong khối đó chính là **giá trị lớn nhất nằm trong khối**.
3. **Tiến trình tịnh tiến tuyến tính:**
    - Precompute mảng cực đại tiền tố: `prefixMax[i] = max(nums[0...i])`.
    - Precompute mảng cực tiểu hậu tố: `suffixMin[i] = min(nums[i...n-1])`.
    - Duyệt `i` từ `1` đến `n - 1`. Nếu phát hiện `prefixMax[i - 1] <= suffixMin[i]`, ta ghi nhận một điểm chia cắt tại `i`.
    - Toàn bộ các ô thuộc khối trước đó `[start, i - 1]` sẽ được gán giá trị lớn nhất của khối là `prefixMax[i - 1]`. Sau đó dịch chuyển `start = i`.
    - Gán giá trị cho khối cuối cùng từ `start` đến `n - 1`.

---

## Tại sao tối ưu?

- **Hiệu năng siêu tốc ($O(n)$ Time Complexity):** Ta chỉ cần duyệt qua mảng 3 lần (một lần tính cực đại tiền tố, một lần tính cực tiểu hậu tố, và một lần quét tìm điểm chia cắt để điền kết quả). Thuật toán chạy cực kỳ mượt mà trong thời gian tuyến tính, vượt qua mọi bộ test khổng lồ chỉ trong chớp mắt.
- **Không gian tối ưu ($O(n)$ Space Complexity):** Bộ nhớ bổ trợ chỉ gồm hai mảng `prefixMax` và `suffixMin` có kích thước $n$, hoàn toàn tối giản.
- **Tính chính xác tuyệt đối:** Thiết kế này dựa trên định lý graph học chặt chẽ: một khối chỉ số liên tục không chứa bất kỳ điểm cắt phân ly nào thì chắc chắn đồ thị con tương ứng của nó là liên thông. Điều này đảm bảo tính đúng đắn toán học 100%.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ cụ thể:

Mảng đầu vào: `nums = [3, 1, 2, 4, 5]` với `n = 5`.

### Khởi tạo cấu trúc

- Mảng tiền tố cực đại: `prefixMax = [3, 3, 3, 4, 5]`
- Mảng hậu tố cực tiểu: `suffixMin = [1, 1, 2, 4, 5]`
- Điểm bắt đầu khối hiện tại: `start = 0`

### Tiến trình duyệt tìm điểm chia cắt

- **Duyệt `i = 1`:**
    - So sánh: `prefixMax[0] = 3`, `suffixMin[1] = 1`.
    - Ta thấy `3 > 1` (không có điểm chia cắt). Tiếp tục.

- **Duyệt `i = 2`:**
    - So sánh: `prefixMax[1] = 3`, `suffixMin[2] = 2`.
    - Ta thấy `3 > 2` (không có điểm chia cắt). Tiếp tục.

- **Duyệt `i = 3`:**
    - So sánh: `prefixMax[2] = 3`, `suffixMin[3] = 4`.
    - Ta phát hiện `prefixMax[2] <= suffixMin[3]` (`3 <= 4`). **Ghi nhận điểm chia cắt tại `3`!**
    - Khối liên thông đầu tiên được xác định trong khoảng `[start, i - 1] = [0, 2]` (các giá trị: `[3, 1, 2]`).
    - Cực đại của khối này: `blockMax = prefixMax[2] = 3`.
    - Điền kết quả: `ans[0] = 3`, `ans[1] = 3`, `ans[2] = 3`.
    - Cập nhật điểm khởi đầu khối tiếp theo: `start = 3`.

- **Duyệt `i = 4`:**
    - So sánh: `prefixMax[3] = 4`, `suffixMin[4] = 5`.
    - Ta phát hiện `prefixMax[3] <= suffixMin[4]` (`4 <= 5`). **Ghi nhận điểm chia cắt tại `4`!**
    - Khối liên thông tiếp theo được xác định trong khoảng `[3, 3]` (giá trị: `[4]`).
    - Cực đại khối: `blockMax = prefixMax[3] = 4`.
    - Điền kết quả: `ans[3] = 4`.
    - Cập nhật điểm khởi đầu: `start = 4`.

- **Kết thúc vòng lặp:**
    - Điền kết quả cho khối cuối cùng từ `start = 4` đến `n - 1 = 4` (giá trị: `[5]`).
    - Cực đại khối: `blockMax = prefixMax[4] = 5`.
    - Điền kết quả: `ans[4] = 5`.

### Kết quả cuối cùng

Mảng kết quả nhận được: `ans = [3, 3, 3, 4, 5]`.

---

## Phân tích chuyên sâu Test Case: `nums = [2, 4, 1, 3]`, `n = 4`

Hãy xem cách thuật toán xử lý trường hợp mảng liên thông hoàn toàn:

1. Khởi tạo:
    - `prefixMax = [2, 4, 4, 4]`
    - `suffixMin = [1, 1, 1, 3]`
    - `start = 0`
2. Duyệt qua toàn bộ mảng:
    - `i = 1`: `prefixMax[0] = 2 > suffixMin[1] = 1` -> không split.
    - `i = 2`: `prefixMax[1] = 4 > suffixMin[2] = 1` -> không split.
    - `i = 3`: `prefixMax[2] = 4 > suffixMin[3] = 3` -> không split.
3. Không tìm thấy điểm chia cắt nào! Toàn bộ mảng tạo thành duy nhất 1 khối liên thông từ `0` đến `3`.
4. Điền kết quả cực đại toàn mảng `prefixMax[3] = 4` cho mọi vị trí: `ans = [4, 4, 4, 4]`.
5. Kết quả hoàn toàn chính xác do các đỉnh được nối tuần hoàn thông qua nghịch thế.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Mảng giảm dần nghiêm ngặt):**
    - Đầu vào: `nums = [5, 4, 3, 2, 1]`
    - Mô tả: Mọi cặp chỉ số $a < b$ đều thỏa mãn `nums[a] > nums[b]`. Đồ thị là một đồ thị đầy đủ (clique) vô hướng cực mạnh. Mọi đỉnh đều liên thông trực tiếp với nhau.
    - Kết quả kỳ vọng: `[5, 5, 5, 5, 5]`

- **Case 2 (Độ dài mảng tối thiểu):**
    - Đầu vào: `nums = [10]`
    - Mô tả: Mảng chỉ có duy nhất 1 phần tử. Không thể thực hiện bất kỳ cú nhảy nào, kết quả chính là giá trị duy nhất.
    - Kết quả kỳ vọng: `[10]`

- **Case 3 (Mảng tăng dần nghiêm ngặt):**
    - Đầu vào: `nums = [1, 2, 3, 4]`
    - Mô tả: Không có bất kỳ cặp nghịch thế nào trong mảng. Đồ thị hoàn toàn không có cạnh nào. Mỗi đỉnh là một thành phần liên thông biệt lập.
    - Kết quả kỳ vọng: `[1, 2, 3, 4]`

- **Case 4 (Hai thung lũng liên thông lớn phân tách bởi đỉnh núi nhỏ):**
    - Đầu vào: `nums = [10, 5, 8, 20, 15, 18]`
    - Mô tả: Hai khối `[10, 5, 8]` và `[20, 15, 18]` độc lập với nhau. Ranh giới chia cắt ở `i = 3` do cực đại phần đầu là `10` nhỏ hơn cực tiểu phần sau là `15` (`10 <= 15`).
    - Kết quả kỳ vọng: `[10, 10, 10, 20, 20, 20]`

- **Case 5 (Mảng có các bậc thang lặp lại giá trị):**
    - Đầu vào: `nums = [3, 3, 1, 2, 4, 4]`
    - Mô tả: Mảng chứa các giá trị trùng lặp. Khối liên thông đầu tiên là `[3, 3, 1, 2]` có max là `3`, khối tiếp theo là `[4, 4]` có max là `4`. Điểm cắt ở `i = 4` do `prefixMax[3] = 3 <= suffixMin[4] = 4`.
    - Kết quả kỳ vọng: `[3, 3, 3, 3, 4, 4]`

---

**Tổng kết:** Vẻ đẹp của thiết kế giải pháp cho Jump Game IX nằm ở việc chuyển hóa một bài toán tìm thành phần liên thông đồ thị phức tạp thành một phép phân rã khối tuyến tính cực kỳ thanh thoát. Bằng cách áp dụng mảng cực đại tiền tố và cực tiểu hậu tố để định vị các điểm chia cắt, thuật toán đã triệt tiêu hoàn toàn sự bùng nổ tổ hợp, mang lại hiệu năng tối đa cùng độ chính xác tuyệt đối.
