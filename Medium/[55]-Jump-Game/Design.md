# Tư tư duy thiết kế: Tầm quét năng lượng và hành trình vượt chướng ngại vật (Jump Game)

Bài toán di chuyển trên mảng dựa theo bước nhảy tối đa tại từng vị trí là một bài toán nền tảng, mở đường cho hàng loạt bài toán tối ưu hóa phức tạp hơn trong chuỗi Jump Game. Ở đây, mỗi phần tử đại diện cho sức mạnh hay "năng lượng" giúp ta phóng về phía trước. Mục tiêu duy nhất là xác định xem từ vạch xuất phát, ta có thể chạm tới vạch đích ở cuối mảng hay không. Thách thức lớn nhất là tìm ra một giải pháp cực kỳ tinh gọn, tránh được việc sa vào các nhánh tính toán đệ quy phức tạp hoặc các phép thử sai lầm làm tốn tài nguyên hệ thống.

## Vấn đề: Cạm bẫy của việc đi sâu vào chi tiết và sự bùng nổ tổ hợp

Tại mỗi vị trí `i`, con số `nums[i]` cho phép ta chọn nhảy bất kỳ khoảng cách nào từ `1` đến `nums[i]` bước. 

Nếu ta giải quyết bằng cách thử mọi bước nhảy có thể (quay lui/Backtracking hoặc DFS):
- **Bùng nổ tổ hợp:** Ở mỗi ô, số lượng lựa chọn bước nhảy là rất lớn. Việc thử từng nhánh nhảy để xem nhánh nào dẫn tới đích sẽ tạo ra một cây quyết định khổng lồ với độ phức tạp thời gian lên tới lũy thừa ($O(2^n)$).
- **Quy hoạch động thông thường ($O(n^2)$):** Ta có thể cải tiến bằng cách dùng mảng ghi nhớ để lưu trạng thái "có thể tới đích từ ô này hay không". Tuy nhiên, với mỗi ô ta vẫn phải quét qua toàn bộ các ô trong tầm nhảy của nó, dẫn tới thời gian chạy là $O(n^2)$. Khi kích thước mảng lên tới $10^4$ hoặc $10^5$, thuật toán này sẽ ngay lập tức bị lỗi quá thời gian chạy (Time Limit Exceeded).

---

## Giải pháp: Tầm quét năng lượng tối đa (Greedy Algorithm)

Để đạt được sự tối ưu tuyệt đối, ta cần chuyển đổi góc nhìn từ việc **"thử từng bước nhảy cụ thể"** sang việc **"quản lý tầm với xa nhất khả dĩ"**. Đây chính là tư duy Tham lam (Greedy).

Hãy tưởng tượng bạn đang đi trong bóng tối và mỗi ô `i` có một **"đèn pin chiếu sáng"** với tầm xa là `nums[i]`. Tầm chiếu sáng xa nhất mà bạn mở khóa được từ vạch xuất phát đến hiện tại được ghi nhận bởi biến `maxReachable`.

1. **Khởi hành:** Bắt đầu tại ô `0`. Tầm quét năng lượng ban đầu là `maxReachable = 0`.
2. **Tịnh tiến và tra cứu:** Ta đi qua từng ô `i` từ đầu đến cuối mảng:
   - **Ranh giới bóng tối:** Nếu tại một vị trí bất kỳ, ta thấy `i > maxReachable`, nghĩa là ta đã bước vào vùng bóng tối hoàn toàn mà không có luồng ánh sáng nào từ các bước trước chiếu tới được. Ta lập tức kết luận không thể đi tiếp và trả về `false`.
   - **Nạp năng lượng:** Nếu `i <= maxReachable` (vị trí hiện tại an toàn), ta nhặt chiếc đèn pin tại ô `i` này để mở rộng tầm chiếu sáng. Tầm quét xa nhất mới sẽ là giá trị lớn nhất giữa tầm quét cũ và tầm quét từ ô hiện tại:
     $$\text{maxReachable} = \max(\text{maxReachable}, i + \text{nums}[i])$$
3. **Vượt vạch đích sớm (Early Exit):** Tại mỗi bước, nếu tầm quét năng lượng đã chạm hoặc vượt quá vạch đích (`maxReachable >= n - 1`), ta lập tức trả về `true` mà không cần duyệt tiếp phần còn lại của mảng.

---

## Tại sao tối ưu?

- **Hiệu năng siêu tốc ($O(n)$ Time Complexity):** Ta chỉ cần duyệt qua mảng đúng một lần duy nhất từ trái sang phải. Không có đệ quy, không có vòng lặp lồng nhau. Thời gian thực thi tỉ lệ tuyến tính với số lượng phần tử $n$, chạy trong tích tắc ngay cả với $n = 10^5$.
- **Tiết kiệm bộ nhớ tuyệt đối ($O(1)$ Space Complexity):** Thuật toán chỉ sử dụng duy nhất một biến nguyên `maxReachable` để lưu trữ trạng thái tầm quét, hoàn toàn không tốn thêm bất kỳ mảng phụ trợ hay cấu trúc dữ liệu nào.
- **Triết lý tham lam hoàn hảo:** Thay vì quan tâm làm sao để nhảy từng bước cụ thể, ta chỉ quan tâm đến giới hạn xa nhất có thể đạt được. Giới hạn này luôn tăng hoặc giữ nguyên, đảm bảo tính đúng đắn tuyệt đối của kết quả.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua hai kịch bản cụ thể:

### Kịch bản thành công: `nums = [2, 3, 1, 1, 4]` với `n = 5`
Mục tiêu là chạm tới chỉ số `4`.

- **Khởi tạo:** `maxReachable = 0`
- **Duyệt `i = 0`:**
   - Vị trí hiện tại hợp lệ (`0 <= maxReachable`).
   - Cập nhật tầm quét: $\text{maxReachable} = \max(0, 0 + 2) = 2$.
   - Tiếp tục duyệt vì `2 < 4`.
- **Duyệt `i = 1`:**
   - Vị trí hiện tại hợp lệ (`1 <= maxReachable`).
   - Cập nhật tầm quét: $\text{maxReachable} = \max(2, 1 + 3) = 4$.
   - **Phát hiện đích:** Tầm quét đã chạm đích (`4 >= 4`). Thuật toán dừng ngay lập tức và trả về `true`.

### Kịch bản thất bại: `nums = [3, 2, 1, 0, 4]` với `n = 5`
Mục tiêu là chạm tới chỉ số `4`.

- **Khởi tạo:** `maxReachable = 0`
- **Duyệt `i = 0`:**
   - Hợp lệ (`0 <= maxReachable`).
   - Cập nhật: $\text{maxReachable} = \max(0, 0 + 3) = 3$.
- **Duyệt `i = 1`:**
   - Hợp lệ (`1 <= maxReachable`).
   - Cập nhật: $\text{maxReachable} = \max(3, 1 + 2) = 3$.
- **Duyệt `i = 2`:**
   - Hợp lệ (`2 <= maxReachable`).
   - Cập nhật: $\text{maxReachable} = \max(3, 2 + 1) = 3$.
- **Duyệt `i = 3`:**
   - Hợp lệ (`3 <= maxReachable`).
   - Cập nhật: $\text{maxReachable} = \max(3, 3 + 0) = 3$.
- **Duyệt `i = 4`:**
   - **Chạm ranh giới bóng tối:** Ta thấy `i > maxReachable` (`4 > 3`). Ô số `4` hoàn toàn nằm ngoài tầm quét năng lượng của tất cả các ô phía trước.
   - Thuật toán dừng lại và trả về `false`.

---

## Phân tích chuyên sâu Test Case: `nums = [0, 2, 3]`, `n = 3`

Test case này minh họa trực quan cách thuật toán phát hiện sự bế tắc ngay từ vạch xuất phát:

1. Khởi tạo: `maxReachable = 0`.
2. Duyệt `i = 0`: Hợp lệ. Cập nhật `maxReachable = \max(0, 0 + 0) = 0`.
3. Duyệt `i = 1`: Phát hiện `i > maxReachable` (`1 > 0`). Vạch xuất phát có tầm nhảy là `0` khiến ta bị kẹt cứng ngay tại chỗ, không thể bước lên bất kỳ ô nào tiếp theo.
4. Thuật toán trả về `false` ngay lập tức tại chỉ số `1`, ngăn chặn mọi tính toán vô ích sau đó.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Mảng toàn số không ở giữa):**
   - Đầu vào: `nums = [2, 0, 0, 0, 4]`
   - Mô tả: Từ chỉ số `0`, bước nhảy tối đa là `2`, đưa ta tới tối đa chỉ số `2`. Nhưng tại chỉ số `1` và `2` đều có giá trị `0`, khiến ta bị kẹt và không bao giờ vượt qua được hố sâu ba số `0` liên tiếp để tới chỉ số `4`.
   - Kết quả kỳ vọng: `false`

- **Case 2 (Độ dài mảng tối thiểu):**
   - Đầu vào: `nums = [0]`
   - Mô tả: Mảng chỉ có duy nhất 1 phần tử. Ta đã đứng sẵn ở đích ngay từ đầu.
   - Kết quả kỳ vọng: `true`

- **Case 3 (Bước nhảy vừa khít chạm đích):**
   - Đầu vào: `nums = [1, 1, 1, 1, 0]`
   - Mô tả: Mỗi ô chỉ có đúng năng lượng nhảy 1 bước. Ta phải di chuyển tuần tự qua từng ô để chạm tới đích cuối cùng (nơi có năng lượng `0`).
   - Kết quả kỳ vọng: `true` (Hành trình: `0 -> 1 -> 2 -> 3 -> 4`)

- **Case 4 (Sức mạnh nhảy cực đại từ đầu):**
   - Đầu vào: `nums = [10, 0, 0, 0, 0, 0]`
   - Mô tả: Ngay từ vạch xuất phát ta đã sở hữu nguồn năng lượng cực đại, một cú nhảy phóng thẳng vượt qua mọi chướng ngại vật để về đích.
   - Kết quả kỳ vọng: `true`

- **Case 5 (Mảng zic-zac năng lượng giảm dần):**
   - Đầu vào: `nums = [4, 3, 2, 1, 0, 0]`
   - Mô tả: Năng lượng tại các ô giảm dần về `0`. Từ `0` nhảy tới `4` (năng lượng `0`), hoặc nhảy tới `3` (năng lượng `1 -> 4 -> 0`). Dù nhảy thế nào cũng sẽ bị kẹt tại chỉ số `4` vì ô này có năng lượng `0` và đích cuối cùng là chỉ số `5`.
   - Kết quả kỳ vọng: `false`

---

**Tổng kết:** Vẻ đẹp của bài toán Jump Game nằm ở sự đơn giản nhưng chứa đựng tư duy thiết kế sâu sắc. Thay vì bị cuốn vào việc tìm kiếm các tổ hợp đường đi chi tiết phức tạp, thuật toán chỉ tập trung quản lý giới hạn năng lượng xa nhất. Phương pháp tiếp cận tham lam (Greedy) này đã mang lại một lời giải hoàn hảo, đạt hiệu năng tuyệt đối cả về thời gian lẫn không gian bộ nhớ.
