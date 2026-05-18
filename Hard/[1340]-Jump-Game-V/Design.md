# Tư duy thiết kế: Tầm nhìn watchtower và hành trình bước nhảy một chiều (Jump Game V)

Bài toán tìm đường đi dài nhất trên các cột mốc có độ cao khác nhau đại diện cho một mô hình đồ thị có hướng không chu trình (DAG - Directed Acyclic Graph) cực kỳ thú vị. Ở đây, mỗi vị trí đóng vai trò là một tháp canh (watchtower) có độ cao xác định. Từ một tháp cao, ta được phép thực hiện cú nhảy xuống các tháp thấp hơn kề cận trong dải khoảng cách cho trước, với điều kiện tầm nhìn giữa hai tháp không bị cản trở bởi bất kỳ tháp nào khác cao hơn hoặc bằng. Thách thức lớn nhất ở đây là việc tìm kiếm lộ trình có thể ghé thăm nhiều tháp canh nhất. Nếu áp dụng phương pháp tìm kiếm vét cạn (brute-force) thông thường, độ phức tạp lũy thừa ($O(2^n)$) sẽ ngay lập tức làm quá tải hệ thống.

## Vấn đề: Cảnh quan bị cản trở tầm nhìn và sự trùng lặp nhánh duyệt

Quy tắc bước nhảy cho phép ta nhảy từ chỉ số `i` sang `j` nếu:
- Khoảng cách nhảy nằm trong phạm vi cho phép: $|i - j| \le d$.
- Ô xuất phát phải cao hơn ô đích: `arr[i] > arr[j]`.
- Mọi ô trung gian giữa `i` và `j` đều phải thấp hơn ô xuất phát: `arr[k] < arr[i]` với mọi `k` nằm giữa `i` và `j` (không bị cản trở tầm nhìn).

Hai thách thức chính phát sinh:
- **Tầm nhìn bị cản trở:** Khi ta thử nhảy từ tháp `i` qua các tháp bên cạnh, ngay khi gặp một tháp `k` cao hơn hoặc bằng tháp `i` (`arr[k] >= arr[i]`), ta phải dừng ngay việc tìm kiếm theo hướng đó vì không thể nhảy "xuyên" qua hoặc nhảy "vượt" qua một tháp cao bằng hoặc hơn nó.
- **Sự chồng lấn các nhánh tính toán:** Một tháp canh thấp có thể được tiếp cận từ nhiều tháp canh cao khác nhau. Nếu mỗi lần tiếp cận, ta lại thực hiện tính toán lại hành trình tối đa xuất phát từ tháp thấp đó, thuật toán sẽ bị lặp lại vô số phép tính trùng lặp, khiến thời gian chạy bùng nổ lên mức lũy thừa.

---

## Giải pháp: Đồ thị một chiều và Quy hoạch động ghi nhớ (Memoized DFS)

Vì ta chỉ được phép nhảy từ tháp cao xuống tháp thấp hơn (`arr[i] > arr[j]`), chiều cao giảm dần sau mỗi bước nhảy sẽ đảm bảo rằng không bao giờ xuất hiện vòng lặp (chu trình). Đây chính là tính chất cốt lõi của **Đồ thị có hướng không chu trình (DAG)**. 

Hành trình tìm số bước nhảy dài nhất trên DAG có thể được giải quyết một cách hoàn hảo bằng **Quy hoạch động kết hợp tìm kiếm theo chiều sâu (Memoized DFS)**:

1. **Khái niệm trạng thái DP:** Ta định nghĩa `dp[i]` là số lượng tháp canh tối đa có thể ghé thăm nếu xuất phát từ tháp `i` (bao gồm chính tháp `i`, do đó giá trị mặc định tối thiểu là `1`).
2. **Hàm đệ quy thông minh:** Với mỗi tháp `i`:
   - Ta duyệt các bước nhảy sang bên phải `j` từ `i + 1` đến `i + d`. Nếu gặp bất kỳ tháp nào có `arr[j] >= arr[i]`, ta lập tức ngắt vòng lặp (break) vì tầm nhìn đã bị chặn. Ngược lại, nếu `arr[j] < arr[i]`, ta có thể nhảy tới `j` và tiếp tục hành trình:
     $$\text{dp}[i] = \max(\text{dp}[i], 1 + \text{dp}[j])$$
   - Ta làm tương tự với hướng nhảy sang bên trái `j` từ `i - 1` xuống `i - d`. Nếu gặp tháp có `arr[j] >= arr[i]`, ta lập tức ngắt vòng lặp. Ngược lại, ta cập nhật:
     $$\text{dp}[i] = \max(\text{dp}[i], 1 + \text{dp}[j])$$
3. **Cuốn sổ tay ghi nhớ (Memoization):** Mỗi khi tính xong `dp[i]`, ta lưu kết quả vào mảng `memo`. Lần sau nếu có tháp cao hơn nhảy tới `i`, ta chỉ việc tra cứu trực tiếp trong `memo[i]` với thời gian $O(1)$ mà không cần tính lại.
4. **Kết quả cuối cùng:** Đáp án của bài toán là giá trị lớn nhất trong mảng `dp`, đại diện cho lộ trình xuất phát từ tháp tối ưu nhất:
   $$\text{Result} = \max_{0 \le i < n} (\text{dp}[i])$$

---

## Tại sao tối ưu?

- **Hiệu năng tuyến tính thực tế ($O(n \times d)$):** Nhờ cơ chế ghi nhớ, mỗi trạng thái `dp[i]` chỉ được tính toán duy nhất một lần. Trong quá trình tính toán cho tháp `i`, ta kiểm tra tối đa `2 * d` tháp lân cận. Vì thế, tổng số thao tác tối đa trên toàn bộ chương trình chỉ là $O(n \times d)$. Với $n \le 1000$ và $d \le 100$, thuật toán chỉ mất chưa đầy $2 \times 10^5$ phép tính, chạy trong khoảng vài mili-giây, cực kỳ tối ưu.
- **Tiết kiệm không gian ($O(n)$):** Bộ nhớ bổ trợ cần dùng chỉ là mảng `memo` có kích thước $n$ và ngăn xếp đệ quy sâu tối đa là $n$, hoàn toàn tối giản.
- **Tự động hóa chặn nhánh thông minh:** Việc dừng vòng quét ngay khi gặp chướng ngại vật cao hơn hoặc bằng giúp thuật toán bỏ qua hàng loạt nhánh duyệt vô ích, gia tăng tốc độ xử lý trong thực tế.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ cụ thể:

Chuỗi đầu vào: `arr = [3, 2, 4, 1]` với `d = 2`. Độ dài `n = 4`.

### Khởi tạo cấu trúc
- Mảng ghi nhớ: `memo = [-1, -1, -1, -1]`

### Tiến trình duyệt

**Bước 1: Tính `dp[0]` (tháp có chiều cao 3)**
- **Nhảy sang phải trong phạm vi 2 bước (chỉ số 1, 2):**
   - Xét `j = 1` (chiều cao `2 < 3`): Hợp lệ! Tiếp tục gọi đệ quy `solve(1)`.
     - *Tính `dp[1]` (tháp có chiều cao 2):*
       - Nhảy sang phải trong phạm vi 2 bước (chỉ số 2, 3):
         - Xét `j = 2` (chiều cao `4 >= 2`): Bị chặn! Dừng quét hướng bên phải.
         - Xét `j = 3` (chiều cao `1 < 2`): Hợp lệ! Tiếp tục gọi đệ quy `solve(3)`.
           - *Tính `dp[3]` (tháp có chiều cao 1):* Không thể nhảy đi đâu vì nó thấp nhất. Trả về `1`. Lưu `memo[3] = 1`.
         - Cập nhật `dp[1] = \max(1, 1 + dp[3]) = 2`.
       - Nhảy sang trái (chỉ số 0): Xét `j = 0` (chiều cao `3 >= 2`): Bị chặn! Dừng quét hướng bên trái.
       - Trả về `dp[1] = 2`. Lưu `memo[1] = 2`.
     - Quay lại chỉ số `0`, cập nhật `dp[0] = \max(1, 1 + dp[1]) = 3`.
   - Xét `j = 2` (chiều cao `4 >= 3`): Bị chặn! Dừng quét hướng bên phải.
- **Nhảy sang trái:** Không có tháp nào bên trái.
- Trả về `dp[0] = 3`. Lưu `memo[0] = 3`.

**Bước 2: Tính `dp[1]` (chiều cao 2)**
- Đã được tính và lưu trong `memo[1] = 2`. Trả về `2` ngay lập tức.

**Bước 3: Tính `dp[2]` (chiều cao 4)**
- **Nhảy sang phải (chỉ số 3):**
   - Xét `j = 3` (chiều cao `1 < 4`): Hợp lệ! Gọi đệ quy `solve(3)`. Tra cứu nhanh `memo[3] = 1`.
   - Cập nhật `dp[2] = \max(1, 1 + 1) = 2`.
- **Nhảy sang trái trong phạm vi 2 bước (chỉ số 1, 0):**
   - Xét `j = 1` (chiều cao `2 < 4`): Hợp lệ! Tra cứu nhanh `memo[1] = 2`.
   - Cập nhật `dp[2] = \max(2, 1 + 2) = 3`.
   - Xét `j = 0` (chiều cao `3 < 4`): Hợp lệ! Tra cứu nhanh `memo[0] = 3`.
   - Cập nhật `dp[2] = \max(3, 1 + 3) = 4`.
- Trả về `dp[2] = 4`. Lưu `memo[2] = 4`.

**Bước 4: Tính `dp[3]` (chiều cao 1)**
- Đã được tính và lưu trong `memo[3] = 1`. Trả về `1` ngay lập tức.

### Kết quả cuối cùng
Ta tìm giá trị lớn nhất trong mảng `memo`:
$$\text{Result} = \max(3, 2, 4, 1) = 4$$
Lộ trình tối ưu nhất đi qua 4 tháp: `2 -> 0 -> 1 -> 3` (độ cao tương ứng: `4 -> 3 -> 2 -> 1`).

---

## Phân tích chuyên sâu Test Case: `arr = [5, 5, 5, 5]`, `d = 2`

Trường hợp tất cả các tháp canh có độ cao bằng nhau là một ví dụ minh họa cực kỳ rõ nét về tính năng chặn nhánh tầm nhìn của thiết kế:

1. Bắt đầu tính từ `dp[0]`:
   - Quét sang phải tại `j = 1`: Phát hiện `arr[1] == arr[0] == 5`. Điều kiện yêu cầu ô đích hoặc ô trung gian phải có chiều cao thấp hơn nghiêm ngặt (`arr[j] < arr[i]`).
   - Gặp tháp có độ cao bằng, thuật toán lập tức kích hoạt lệnh `break` dừng quét.
   - Kết quả: `dp[0] = 1`.
2. Lần lượt tất cả các tháp khác đều gặp trạng thái tương tự và trả về `1` ngay lập tức.
3. Kết quả trả về `1`. Thuật toán kết thúc chỉ sau $O(n)$ bước duyệt rỗng, không tốn bất kỳ thao tác đệ quy sâu hay quét thừa thãi nào.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Thung lũng đối xứng):**
   - Đầu vào: `arr = [4, 3, 2, 1, 2, 3, 4]`, `d = 1`
   - Mô tả: Từ hai đỉnh tháp cao nhất ở hai bên rìa, ta chỉ được nhảy mỗi bước 1 ô và độ cao phải giảm dần về phía đáy thung lũng (ở giữa có chiều cao `1`).
   - Kết quả kỳ vọng: `4` (Đường đi tối ưu: `0 -> 1 -> 2 -> 3` hoặc `6 -> 5 -> 4 -> 3`)

- **Case 2 (Độ dài mảng tối thiểu):**
   - Đầu vào: `arr = [10]`, `d = 5`
   - Mô tả: Chỉ có duy nhất 1 tháp canh, không thể nhảy đi đâu cả.
   - Kết quả kỳ vọng: `1`

- **Case 3 (Cạm bẫy tường chắn khổng lồ ở giữa):**
   - Đầu vào: `arr = [10, 8, 6, 20, 9, 7, 5]`, `d = 3`
   - Mô tả: Tháp `20` ở giữa phân chia mảng thành hai nửa biệt lập. Các tháp ở bên trái không thể nhảy vượt qua tháp `20` để sang bên phải và ngược lại.
   - Kết quả kỳ vọng: `3` (Đường đi tối ưu: `0 -> 1 -> 2` hoặc `4 -> 5 -> 6`)

- **Case 4 (Khoảng cách bước nhảy cực rộng):**
   - Đầu vào: `arr = [1, 2, 3, 4, 5]`, `d = 10`
   - Mô tả: Mọi tháp bên trái đều có chiều cao nhỏ hơn tháp bên phải, và khoảng cách nhảy cực lớn. Nhìn từ phải sang trái, tháp cao hơn có thể tự do chọn nhảy tới bất kỳ tháp nào bên trái vì không bị tháp nào cao hơn cản tầm nhìn.
   - Kết quả kỳ vọng: `5` (Đường đi tối ưu: `4 -> 3 -> 2 -> 1 -> 0`)

- **Case 5 (Mảng có các bậc thang đan xen chiều cao):**
   - Đầu vào: `arr = [10, 5, 12, 4, 15, 3]`, `d = 2`
   - Mô tả: Các phần tử đan xen cao thấp. Từ tháp `15` ta có thể nhảy tới `12` (khoảng cách 2) hoặc nhảy tới `3` (khoảng cách 1). Nếu nhảy tới `12`, từ `12` có thể tiếp tục nhảy tới `10` -> `5` -> `4`. Lộ trình dài nhất sẽ được bảo toàn thông qua quy hoạch động.
   - Kết quả kỳ vọng: `5` (Đường đi tối ưu: `4 (15) -> 2 (12) -> 0 (10) -> 1 (5) -> 3 (4)`)

---

**Tổng kết:** Bản chất bài toán Jump Game V là cuộc hành trình tối ưu hóa các lựa chọn một chiều. Bằng cách mô hình hóa bài toán dưới dạng đồ thị có hướng không chu trình (DAG) và áp dụng giải pháp Quy hoạch động ghi nhớ (Memoized DFS) với cơ chế chặn nhánh tầm nhìn sắc bén, chúng ta đã giải quyết bài toán độ khó Hard này một cách cực kỳ tinh gọn, mang lại hiệu năng tối đa cùng độ chính xác tuyệt đối.
