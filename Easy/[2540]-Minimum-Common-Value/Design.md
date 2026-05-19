# Tư duy thiết kế: Tìm giá trị chung nhỏ nhất (Minimum Common Value)

Bài toán yêu cầu tìm giá trị nhỏ nhất xuất hiện trong cả hai mảng số nguyên đã được sắp xếp tăng dần. Nếu không có phần tử chung nào, kết quả trả về sẽ là -1. Đây là một bài toán kinh điển giúp tối ưu hóa việc đối chiếu dữ liệu giữa hai nguồn đã được chuẩn hóa.

## Vấn đề: Sự lãng phí của việc đối chiếu mọi cặp giá trị

Cách tiếp cận đơn giản nhất là lấy từng phần tử của mảng thứ nhất và đi tìm kiếm nó trong mảng thứ hai bằng cách duyệt tuần tự. Điều này dẫn đến độ phức tạp thời gian là $O(n \times m)$, nơi $n$ và $m$ là độ dài của hai mảng. 

Khi kích thước của cả hai mảng lên đến $10^5$, tổng số phép so sánh có thể lên tới $10^{10}$ phép tính, vượt quá giới hạn thời gian cho phép của hầu hết hệ thống máy tính hiện đại. Chúng ta cần tận dụng tính chất cực kỳ quan trọng của đề bài: **cả hai mảng đã được sắp xếp tăng dần**.

---

## Giải pháp: Kỹ thuật "Hai người leo thang" (Two Pointers)

Thay vì tìm kiếm mù quáng, chúng ta có thể sử dụng hai con trỏ hoạt động như hai người leo thang song song:

- **Khởi tạo:** Đặt hai con trỏ chỉ vào vị trí đầu tiên của mỗi mảng (các phần tử nhỏ nhất của từng mảng).
- **So sánh:**
  - Nếu hai giá trị tại hai con trỏ bằng nhau: Chúng ta đã tìm thấy giá trị chung đầu tiên. Vì ta duyệt từ đầu mảng (nhỏ nhất) đến cuối mảng (lớn nhất), nên giá trị chung đầu tiên gặp được chắc chắn là nhỏ nhất. Trả về giá trị này ngay lập tức.
  - Nếu giá trị ở mảng thứ nhất nhỏ hơn giá trị ở mảng thứ hai: Người ở mảng thứ nhất cần bước tiếp lên phía trước (tăng chỉ số con trỏ thứ nhất) để tìm kiếm các giá trị lớn hơn, có khả năng bằng với người kia.
  - Nếu giá trị ở mảng thứ nhất lớn hơn giá trị ở mảng thứ hai: Người ở mảng thứ hai cần bước tiếp lên phía trước (tăng chỉ số con trỏ thứ hai).
- **Điều kiện dừng:** Quá trình dừng lại khi một trong hai người đi hết con đường của mình (con trỏ vượt quá giới hạn mảng) mà vẫn không tìm thấy điểm chung nào. Lúc này, ta kết luận không có phần tử chung và trả về -1.

---

## Tại sao đây là cách tiếp cận tối ưu?

Phương pháp này mang lại hiệu quả vượt trội nhờ các yếu tố sau:

- **Độ phức tạp thời gian tối ưu:** Trong trường hợp xấu nhất, mỗi con trỏ đi qua mảng của nó tối đa một lần. Độ phức tạp thời gian chỉ là $O(n + m)$. Với $n, m = 10^5$, số phép so sánh tối đa chỉ khoảng $2 \times 10^5$, chạy trong tích tắc.
- **Không tốn thêm bộ nhớ:** Chúng ta chỉ sử dụng hai biến con trỏ để lưu trữ vị trí hiện tại. Độ phức tạp không gian là $O(1)$.
- **Tư duy loại biên thông minh:** Nhờ tính chất tăng dần, khi biết `nums1[i] < nums2[j]`, ta chắc chắn rằng `nums1[i]` không thể khớp với bất kỳ phần tử nào từ vị trí `j` trở đi của `nums2`. Do đó, việc loại bỏ `nums1[i]` ra khỏi danh sách xem xét là hoàn toàn chính xác và an toàn.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử chúng ta có hai mảng:
`nums1 = [2, 4, 6, 8]`
`nums2 = [1, 3, 4, 7]`

- **Bước 1:** Khởi tạo `i = 0` (trỏ vào `2` của `nums1`) và `j = 0` (trỏ vào `1` của `nums2`).
  - So sánh: `nums1[0] (2) > nums2[0] (1)`.
  - Hành động: Phần tử của `nums2` nhỏ hơn, cần dịch chuyển để đuổi kịp. Tăng `j` lên 1.

- **Bước 2:** `i = 0` (trỏ vào `2`), `j = 1` (trỏ vào `3`).
  - So sánh: `nums1[0] (2) < nums2[1] (3)`.
  - Hành động: Phần tử của `nums1` nhỏ hơn. Tăng `i` lên 1.

- **Bước 3:** `i = 1` (trỏ vào `4`), `j = 1` (trỏ vào `3`).
  - So sánh: `nums1[1] (4) > nums2[1] (3)`.
  - Hành động: Phần tử của `nums2` nhỏ hơn. Tăng `j` lên 1.

- **Bước 4:** `i = 1` (trỏ vào `4`), `j = 2` (trỏ vào `4`).
  - So sánh: `nums1[1] (4) == nums2[2] (4)`.
  - Hành động: Khớp nhau! Trả về kết quả `4`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử khác biệt so với các ví dụ mặc định trên LeetCode để kiểm tra tính toàn diện của thuật toán:

- **Case 1 (Không có phần tử chung):**
  - `nums1 = [1, 3, 5]`
  - `nums2 = [2, 4, 6]`
  - Kết quả: `-1` (Do các tập hợp hoàn toàn rời rạc)

- **Case 2 (Phần tử chung nhỏ nhất nằm ở ngay đầu tiên):**
  - `nums1 = [3, 5, 7]`
  - `nums2 = [3, 8, 9]`
  - Kết quả: `3` (Nhận biết ngay lập tức ở bước đầu tiên)

- **Case 3 (Phần tử chung nằm ở cuối của cả hai mảng):**
  - `nums1 = [1, 2, 5, 10]`
  - `nums2 = [4, 6, 8, 10]`
  - Kết quả: `10` (Hai con trỏ cùng di chuyển tới phần tử cuối)

- **Case 4 (Kích thước hai mảng cực kỳ chênh lệch):**
  - `nums1 = [15]`
  - `nums2 = [2, 5, 8, 11, 15, 20]`
  - Kết quả: `15` (Chạy chính xác khi một trong hai mảng chỉ có 1 phần tử)

- **Case 5 (Có nhiều phần tử chung):**
  - `nums1 = [2, 4, 6, 8]`
  - `nums2 = [4, 5, 6, 10]`
  - Kết quả: `4` (Có cả `4` và `6` chung, nhưng `4` là nhỏ nhất)

---

**Tổng kết:** Bằng việc biến đổi bài toán tìm kiếm tĩnh thành một cuộc đua leo thang động giữa hai con trỏ, chúng ta loại bỏ được vô số bước so sánh thừa thãi. Tính chất sắp xếp của mảng chính là chiếc la bàn giúp hai con trỏ tiến về phía trước một cách tự tin, đem lại giải pháp tối ưu nhất cho bài toán.
