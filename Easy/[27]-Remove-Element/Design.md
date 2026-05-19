# Tư duy thiết kế: Loại bỏ phần tử chỉ định (Remove Element)

Bài toán yêu cầu loại bỏ tất cả các phần tử có giá trị bằng `val` ra khỏi mảng số nguyên `nums` trực tiếp trên mảng cũ (in-place) với lượng bộ nhớ bổ sung là $O(1)$. Thứ tự các phần tử có thể thay đổi và chúng ta cần trả về số lượng phần tử còn lại khác `val`.

## Vấn đề: Sự lãng phí bộ nhớ và giới hạn thao tác ghi

Nếu không bị ràng buộc về bộ nhớ, giải pháp đơn giản nhất là lọc các phần tử khác `val` sang một mảng mới. Việc này tiêu tốn $O(n)$ không gian bộ nhớ.

Khi thực hiện tại chỗ (in-place) trên mảng gốc, thách thức là làm sao để dồn các phần tử hợp lệ về đầu mảng một cách nhanh chóng nhất. Nếu chúng ta dịch chuyển toàn bộ mảng phía sau lên mỗi khi tìm thấy một phần tử cần xóa, độ phức tạp thời gian sẽ lên tới $O(n^2)$ do thao tác sao chép dữ liệu quá nhiều lần. Do đó, chúng ta cần tìm một phương án tối ưu số lần ghi (write operations) vào mảng, đặc biệt là khi số lượng phần tử cần xóa có thể rất ít hoặc rất nhiều.

---

## Giải pháp: Hai hướng tiếp cận con trỏ tối ưu

Tùy thuộc vào phân bố dữ liệu cần xóa, chúng ta có hai cách tiếp cận bằng kỹ thuật hai con trỏ:

### Cách tiếp cận 1: Con trỏ nhanh và con trỏ chậm (Giữ nguyên thứ tự tương đối)

Hãy tưởng tượng bạn là một công nhân trên băng chuyền trái cây. Nhiệm vụ của bạn là loại bỏ tất cả các quả táo bị hỏng (đại diện bởi `val`) và dồn toàn bộ quả táo tốt về phía đầu băng chuyền.

- **Con trỏ chậm (`i`):** Đánh dấu vị trí trống để xếp quả táo tốt tiếp theo. Ban đầu bắt đầu từ vị trí số 0.
- **Con trỏ nhanh (`j`):** Dùng để duyệt qua từng quả táo trên băng chuyền từ đầu đến cuối.
- **Quy trình:** 
  - Khi quả táo ở vị trí `j` là quả tốt (khác `val`), ta nhấc nó đặt vào vị trí trống `i`, sau đó dịch vị trí trống `i` lên một bước (`i++`).
  - Khi gặp quả táo hỏng (bằng `val`), ta chỉ việc bỏ qua và đi tiếp.

### Cách tiếp cận 2: Con trỏ từ hai đầu (Tối ưu hóa thao tác ghi khi số phần tử cần xóa rất ít)

Trong trường hợp số lượng phần tử cần xóa rất ít (ví dụ mảng có 1 triệu phần tử nhưng chỉ có 2-3 phần tử cần xóa), cách tiếp cận 1 vẫn phải ghi lại tất cả các phần tử tốt vào vị trí của chúng. Cách tiếp cận 2 sẽ tối ưu thao tác này bằng cách đổi chỗ với phần tử ở cuối mảng.

- **Con trỏ trái (`i`):** Bắt đầu từ đầu mảng.
- **Con trỏ phải (`n`):** Đại diện cho độ dài hiện tại của mảng (bắt đầu từ cuối mảng).
- **Quy trình:**
  - Nếu `nums[i] == val`, ta lấy phần tử ở cuối mảng (`nums[n-1]`) đè vào vị trí `i` hiện tại, sau đó giảm độ dài mảng đi 1 (`n--`). Ta giữ nguyên con trỏ `i` để kiểm tra tiếp vì phần tử vừa chuyển từ cuối lên cũng có thể bằng `val`.
  - Nếu `nums[i] != val`, ta chỉ cần dịch con trỏ trái sang phải (`i++`).

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Hiệu năng thời gian:** Cả hai cách tiếp cận đều duyệt qua mảng tối đa 1 lần, đạt độ phức tạp thời gian $O(n)$.
- **Tiết kiệm bộ nhớ:** Xử lý trực tiếp trên mảng gốc, đạt độ phức tạp không gian $O(1)$.
- **Tối ưu hóa ghi thực tế:** Cách tiếp cận 2 giảm thiểu đáng kể số lần sao chép phần tử khi phần tử cần xóa xuất hiện thưa thớt, giúp chương trình chạy nhanh hơn trên các mảng lớn trong thực tế.

---

## Mô phỏng luồng xử lý chi tiết (Theo Cách tiếp cận 1)

Giả sử chúng ta có: `nums = [3, 2, 2, 3]`, `val = 3`

- **Khởi tạo:**
  - Con trỏ chậm `i = 0` (vị trí chờ nhận phần tử hợp lệ tiếp theo).
  - Con trỏ nhanh `j` bắt đầu chạy từ `0`.

- **Vòng lặp:**
  - **Lần 1 (j = 0):** `nums[j] (3) == val`.
    - Trùng với giá trị cần xóa. Bỏ qua. `i` vẫn bằng `0`.
  - **Lần 2 (j = 1):** `nums[j] (2) != val`.
    - Đây là phần tử hợp lệ.
    - Hành động: Ghi đè `nums[i] = nums[j]` (`nums[0] = 2`). Tăng `i` lên `1` (bây giờ `i = 1`).
    - Mảng hiện tại: `[2, 2, 2, 3]`.
  - **Lần 3 (j = 2):** `nums[j] (2) != val`.
    - Đây là phần tử hợp lệ.
    - Hành động: Ghi đè `nums[i] = nums[j]` (`nums[1] = 2`). Tăng `i` lên `2` (bây giờ `i = 2`).
    - Mảng hiện tại: `[2, 2, 2, 3]`.
  - **Lần 4 (j = 3):** `nums[j] (3) == val`.
    - Trùng với giá trị cần xóa. Bỏ qua. `i` vẫn bằng `2`.

- **Kết quả:**
  - Vòng lặp kết thúc. Trả về `i = 2` làm độ dài hợp lệ mới.
  - Các phần tử hợp lệ ở đầu mảng: `[2, 2]`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử để đảm bảo tính bao quát của thiết kế:

- **Case 1 (Mảng không chứa phần tử `val` nào):**
  - `nums = [1, 2, 3, 4]`, `val = 5`
  - Kết quả trả về: `4`
  - Trạng thái mảng: `[1, 2, 3, 4]`

- **Case 2 (Tất cả phần tử đều là `val`):**
  - `nums = [2, 2, 2]`, `val = 2`
  - Kết quả trả về: `0`
  - Trạng thái mảng: Trống ở đầu

- **Case 3 (Mảng trống):**
  - `nums = []`, `val = 1`
  - Kết quả trả về: `0`
  - Trạng thái mảng: `[]`

- **Case 4 (Mảng chỉ có 1 phần tử và nó khác `val`):**
  - `nums = [5]`, `val = 3`
  - Kết quả trả về: `1`
  - Trạng thái mảng: `[5]`

- **Case 5 (Phần tử `val` phân bố ở cả đầu và cuối):**
  - `nums = [3, 1, 2, 3]`, `val = 3`
  - Kết quả trả về: `2`
  - Trạng thái mảng: `[1, 2, 2, 3]` (Hai phần tử đầu tiên hợp lệ là `1` và `2`)

---

**Tổng kết:** Bài toán dọn dẹp phần tử tại chỗ được giải quyết tối ưu bằng tư duy chuyển dịch ranh giới hợp lệ. Dựa trên mật độ xuất hiện của phần tử cần xóa, việc lựa chọn cách tiếp cận di chuyển song song hay hoán đổi từ hai đầu sẽ giúp tối ưu hóa số lượng phép toán thực thi trên CPU.
