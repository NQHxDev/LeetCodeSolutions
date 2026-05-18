# Tư duy thiết kế: Cửa sổ quét một chiều và khoảng cách bước nhảy giới hạn (Jump Game VII)

Bài toán di chuyển trên chuỗi nhị phân với khoảng cách bước nhảy bị giới hạn dưới (`minJump`) và giới hạn trên (`maxJump`) đại diện cho một nhóm bài toán quy hoạch động hoặc duyệt đồ thị trên không gian một chiều. Ở đây, các ô có giá trị `'0'` là những phiến đá an toàn để bước lên, còn các ô `'1'` là những cạm bẫy phủ đầy rêu trơn trượt. Thách thức lớn nhất ở đây là khoảng cách nhảy không cố định mà là một dải phạm vi rộng. Nếu sử dụng các phương pháp tìm kiếm thông thường, ta sẽ liên tục bị rơi vào cái bẫy trùng lặp vùng quét, khiến thuật toán bị quá tải thời gian chạy ($O(n^2)$).

## Vấn đề: Cơn ác mộng vùng quét trùng lặp

Khi đứng ở một ô an toàn `i`, ta được phép nhảy tới bất kỳ ô `j` nào nằm trong dải khoảng cách từ `i + minJump` đến `i + maxJump` với điều kiện `s[j] == '0'`.

Nếu ta dùng cách duyệt nhánh thông thường (như Queue BFS chuẩn không tối ưu hoặc DFS):
- Giả sử tại bước trước, ta đứng ở ô `2` và quét các ô trong khoảng `[5, 10]`.
- Tại bước tiếp theo, ta đứng ở ô `3` và lại quét các ô trong khoảng `[6, 11]`.
- Vùng chồng lấn `[6, 10]` bị kiểm tra lại một lần nữa. Khi kích thước chuỗi lên tới $10^5$ và khoảng cách `maxJump - minJump` lớn, số lần quét trùng lặp sẽ tích lũy thành một phép tính khổng lồ $O(n \times (maxJump - minJump))$, dẫn đến lỗi quá thời gian chạy (Time Limit Exceeded).

---

## Giải pháp: Thanh giới hạn không lùi (BFS kết hợp Con trỏ chặn dưới)

Để triệt tiêu hoàn toàn sự trùng lặp, ta xây dựng một thuật toán Duyệt theo chiều rộng (BFS) cải tiến, sử dụng một **"thanh giới hạn không lùi" (Non-backtracking pointer)**.

1. **Khái niệm "Thanh giới hạn" (`maxVisited`):** Ta duy trì một biến `maxVisited` để ghi nhớ chỉ số lớn nhất mà ta từng xem xét hoặc đưa vào hàng đợi. Ban đầu, `maxVisited = 0`.
2. **Cơ chế quét thông minh:** Khi lấy một phần tử `curr` ra khỏi hàng đợi BFS, tầm nhảy hợp lệ của nó là từ `curr + minJump` đến `curr + maxJump`. Thay vì quét toàn bộ dải này, ta chỉ bắt đầu quét từ:
   $$\text{start} = \max(\text{curr} + \text{minJump}, \text{maxVisited} + 1)$$
   cho đến cuối dải $\min(\text{curr} + \text{maxJump}, n - 1)$.
3. **Cập nhật thanh giới hạn:** Ngay sau khi quét xong dải này, ta dịch chuyển thanh chặn dưới lên vị trí xa nhất có thể để các bước sau không bao giờ quét lại vùng này nữa:
   $$\text{maxVisited} = \max(\text{maxVisited}, \text{curr} + \text{maxJump})$$
4. **Kết quả:** Nhờ cơ chế này, mỗi phiến đá trên đường đi chỉ được kiểm tra đúng một lần duy nhất. Con trỏ quét luôn tịnh tiến về phía trước và không bao giờ quay đầu lại.

---

## Tại sau tối ưu?

- **Độ phức tạp thời gian tuyến tính ($O(n)$):** Nhờ thanh giới hạn `maxVisited`, ta đảm bảo rằng vòng lặp duyệt các phần tử đích chỉ chạy qua mỗi chỉ số của chuỗi `s` tối đa một lần. Tổng số bước tính toán trên toàn bộ thuật toán tỷ lệ thuận với độ dài của chuỗi $n$, triệt tiêu hoàn toàn sự phụ thuộc vào độ rộng của dải bước nhảy `maxJump - minJump`.
- **Độ phức tạp không gian ($O(n)$):** Bộ nhớ bổ trợ duy nhất là hàng đợi BFS dùng để lưu trữ các vị trí có thể đi tới, trong trường hợp xấu nhất là $O(n)$.
- **Logic trong sáng và tự nhiên:** BFS tìm kiếm theo chiều rộng giúp lan tỏa cơ hội tiếp cận đích một cách tuần tự. Nếu hàng đợi trống rỗng trước khi chạm tới đích `n - 1`, ta lập tức kết luận không thể tới đích.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát thuật toán vận hành qua một ví dụ thực tế:

Chuỗi đầu vào: `s = "011010"`, `minJump = 2`, `maxJump = 3`. Độ dài `n = 6`.
Đích đến: Chỉ số `5` (ký tự `'0'`).

### Khởi tạo cấu trúc

- Hàng đợi BFS: `q = [0]`
- Thanh giới hạn xa nhất đã xem xét: `maxVisited = 0`

### Các bước duyệt

**Bước 1: Xét phần tử `curr = 0`**
- Lấy `curr = 0` ra khỏi hàng đợi.
- Dải nhảy lý thuyết của `0` là: `[0 + 2, 0 + 3] = [2, 3]`.
- Vị trí bắt đầu quét thực tế: $\text{start} = \max(2, \text{maxVisited} + 1) = \max(2, 1) = 2$.
- Ta quét từ chỉ số `2` đến `3`:
   - Tại chỉ số `2`: `s[2] = '1'` (đá trơn) -> bỏ qua.
   - Tại chỉ số `3`: `s[3] = '0'` (đá an toàn) -> đưa `3` vào hàng đợi.
- Cập nhật thanh giới hạn: $\text{maxVisited} = \max(0, 0 + 3) = 3$.
- Trạng thái hiện tại: `q = [3]`, `maxVisited = 3`.

**Bước 2: Xét phần tử `curr = 3`**
- Lấy `curr = 3` ra khỏi hàng đợi.
- Dải nhảy lý thuyết của `3` là: `[3 + 2, 3 + 3] = [5, 6]`. Vì `n = 6`, dải thực tế giới hạn bởi biên mảng là `[5, 5]`.
- Vị trí bắt đầu quét thực tế: $\text{start} = \max(5, \text{maxVisited} + 1) = \max(5, 4) = 5$.
- Ta quét từ chỉ số `5` đến `5`:
   - Tại chỉ số `5`: `s[5] = '0'` (đá an toàn) -> đưa `5` vào hàng đợi.
- Cập nhật thanh giới hạn: $\text{maxVisited} = \max(3, 3 + 3) = 6$.
- Trạng thái hiện tại: `q = [5]`, `maxVisited = 6`.

**Bước 3: Phát hiện đích**
- Khi chuẩn bị lấy phần tử tiếp theo từ hàng đợi, ta thấy phần tử `5` chính là đích đến (`n - 1`).
- **Kết quả:** Thuật toán dừng lại và trả về `true`.

---

## Phân tích chuyên sâu Test Case: `s = "01101110"` với `minJump = 2`, `maxJump = 3`

Hãy xem trường hợp không thể tới đích này bị thuật toán phát hiện và ngăn chặn như thế nào:

```text
Chỉ số (Index):   0    1    2    3    4    5    6    7
Ký tự (Value):   [0,   1,   1,   0,   1,   1,   1,   0]
```

1. **Khởi đầu:** Hàng đợi `q = [0]`, thanh giới hạn `maxVisited = 0`.
2. **Duyệt `curr = 0`:**
   - Dải quét lý thuyết và thực tế: `[2, 3]`.
   - Tại `2`: `s[2] = '1'` -> bỏ qua.
   - Tại `3`: `s[3] = '0'` -> đưa `3` vào hàng đợi.
   - Cập nhật `maxVisited = \max(0, 3) = 3`.
   - Kết thúc lượt: `q = [3]`, `maxVisited = 3`.
3. **Duyệt `curr = 3`:**
   - Dải quét lý thuyết: `[3 + 2, 3 + 3] = [5, 6]`.
   - Vị trí bắt đầu quét thực tế: $\text{start} = \max(5, \text{maxVisited} + 1) = \max(5, 4) = 5$.
   - Quét từ `5` đến `6`:
     - Tại `5`: `s[5] = '1'` -> bỏ qua.
     - Tại `6`: `s[6] = '1'` -> bỏ qua.
   - Cập nhật `maxVisited = \max(3, 3 + 3) = 6`.
   - Kết thúc lượt: hàng đợi trống rỗng `q = []`, `maxVisited = 6`.
4. **Kết quả:** Hàng đợi rỗng và ta chưa bao giờ chạm tới đích `7`. Thuật toán kết thúc an toàn và trả về `false`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc biệt tự thiết kế nhằm xác minh tính đúng đắn và hiệu năng của thuật toán:

- **Case 1 (Chuỗi toàn đá trơn ở giữa):**
   - Đầu vào: `s = "0111110"`, `minJump = 2`, `maxJump = 3`
   - Mô tả: Khoảng cách từ `0` tới đích `6` quá rộng, và toàn bộ các ô ở giữa đều là `'1'`. Ta không thể tìm được điểm tựa nào để nhảy qua.
   - Kết quả kỳ vọng: `false`

- **Case 2 (Độ dài chuỗi tối thiểu):**
   - Đầu vào: `s = "00"`, `minJump = 1`, `maxJump = 1`
   - Mô tả: Chuỗi chỉ có 2 phần tử và cả hai đều là `'0'`, bước nhảy cho phép là đúng 1 bước.
   - Kết quả kỳ vọng: `true`

- **Case 3 (Nhảy vượt biên giới hạn nhưng có thể chạm đích theo nhánh khác):**
   - Đầu vào: `s = "0011100"`, `minJump = 3`, `maxJump = 5`
   - Mô tả: Từ `0` ta có thể nhảy một bước cực đại tới `5` (giá trị `'0'`), sau đó từ `5` ta không thể nhảy tiếp vì `5 + 3 = 8 > 6` (ngoài biên). Tuy nhiên, ta có con đường khác: từ `0` nhảy tới `1` (giá trị `'0'`), từ `1` nhảy tới `6` (đích) vì khoảng cách là `5` (hợp lệ).
   - Kết quả kỳ vọng: `true` (Đường đi tối ưu: `0 -> 1 -> 6`)

- **Case 4 (Cạm bẫy trùng lặp dải quét cực lớn):**
   - Đầu vào: `s = "0000000000"`, `minJump = 1`, `maxJump = 9`
   - Mô tả: Chuỗi toàn số `'0'`, dải bước nhảy cực rộng. Đây là bài test kiểm tra xem thuật toán có bị lặp lại vùng quét hay không. Với cơ chế thanh giới hạn chặn dưới, mỗi ô chỉ được duyệt qua đúng 1 lần.
   - Kết quả kỳ vọng: `true`

- **Case 5 (Mảng có đích đến là đá trơn trượt):**
   - Đầu vào: `s = "001101"`, `minJump = 2`, `maxJump = 4`
   - Mô tả: Ký tự cuối cùng của chuỗi là `'1'`, đây là một ô trơn trượt. Theo định nghĩa bài toán, ta không bao giờ có thể đứng an toàn trên một ô trơn trượt ở đích.
   - Kết quả kỳ vọng: `false`

---

**Tổng kết:** Vẻ đẹp của thiết kế giải pháp cho Jump Game VII nằm ở việc biến đổi từ một phép toán duyệt dải chồng lấn phức tạp thành một hành trình tịnh tiến một chiều mượt mà. Bằng cách kết hợp cấu trúc hàng đợi của BFS với thanh chặn dưới không quay đầu `maxVisited`, thuật toán đã triệt tiêu hoàn toàn các phép tính trùng lặp, bảo đảm hiệu năng tối đa mà vẫn giữ được tính đơn giản, sáng rõ của mã nguồn.
