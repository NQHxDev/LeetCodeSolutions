# Tư duy thiết kế: Combination Sum

## Vấn đề
Cho một mảng các số nguyên phân biệt `candidates` và một số nguyên mục tiêu `target`. Nhiệm vụ của chúng ta là tìm tất cả các tổ hợp duy nhất từ các phần tử của mảng sao cho tổng của chúng bằng đúng `target`.
Quy tắc đặc biệt:
- Một phần tử trong `candidates` có thể được chọn nhiều lần không giới hạn.
- Các tổ hợp phải là duy nhất. Ví dụ `[2, 3, 2]` và `[2, 2, 3]` được coi là cùng một tổ hợp và chỉ được giữ lại một tổ hợp (thông thường được chuẩn hóa theo thứ tự không giảm).

Chúng ta cần thiết kế giải pháp tìm kiếm toàn diện nhưng hiệu quả nhất.

---

## Giải pháp: Tìm kiếm quay lui kết hợp nhánh cận (Backtracking with Pruning)
Để dễ hình dung giải pháp này, hãy tưởng tượng bạn đang đứng trước một máy bán nước tự động và cần thanh toán chính xác một số tiền là `target` (ví dụ: 7 đồng) bằng các đồng xu mệnh giá có trong túi của bạn (ví dụ: các đồng mệnh giá 2 đồng, 3 đồng...). Bạn có số lượng xu không giới hạn cho mỗi mệnh giá.

Để thử tất cả các cách thanh toán, bạn sẽ áp dụng một chiến lược lựa chọn có hệ thống (Cây quyết định):
Tại mỗi bước quyết định đối với đồng xu hiện tại, bạn có 2 lựa chọn:
1. **Lựa chọn 1 (Nhận thêm xu hiện tại):** Bạn bỏ đồng xu này vào khay thanh toán. Số tiền cần trả còn lại giảm đi mệnh giá đồng xu. Vì số lượng xu là không giới hạn, bạn vẫn đứng ở mệnh giá này và có quyền chọn tiếp nó ở lượt sau.
2. **Lựa chọn 2 (Bỏ qua xu hiện tại):** Bạn không lấy thêm đồng xu mệnh giá này nữa và chuyển sang mệnh giá tiếp theo trong túi. Quyết định này giúp chúng ta không bao giờ quay lại dùng mệnh giá cũ trong nhánh này, từ đó triệt tiêu hoàn toàn việc tạo ra các tổ hợp trùng lặp thứ tự như `[2, 3, 2]` và `[2, 2, 3]`.

Trong quá trình chọn:
- Nếu số tiền còn lại bằng đúng `0`: Bạn đã thanh toán thành công! Lưu lại tổ hợp này.
- Nếu số tiền còn lại nhỏ hơn `0` (vượt quá số tiền cần trả) hoặc bạn đã duyệt hết tất cả mệnh giá trong túi: Lựa chọn hiện tại thất bại. Bạn thực hiện **quay lui** (Backtrack) bằng cách rút đồng xu vừa bỏ vào ra khỏi khay và thử một hướng đi khác.

---

## Tại sao tối ưu?
- **Thuật toán quay lui hiệu quả:** Bằng việc chia nhánh quyết định thành "chọn tiếp phần tử hiện tại" hoặc "chuyển sang phần tử tiếp theo", chúng ta duyệt qua toàn bộ không gian trạng thái của bài toán mà không bao giờ sinh trùng lặp, tiết kiệm bộ nhớ và thời gian lọc kết quả trùng.
- **Tối ưu hóa bằng nhánh cận (Pruning):** Nếu chúng ta sắp xếp mảng `candidates` theo thứ tự tăng dần trước khi thực hiện quay lui, ta có thể dừng việc tìm kiếm ngay lập tức khi giá trị của phần tử hiện tại lớn hơn số tiền còn lại cần đạt được. Điều này giúp loại bỏ (cắt tỉa) rất nhiều nhánh tìm kiếm vô ích, tăng tốc độ xử lý vượt trội.

---

## Minh họa từng bước chạy
Xét `candidates = [2, 3, 6, 7]` và `target = 7`.

Hãy theo dõi một phần của cây quyết định để thấy cách tìm ra tổ hợp `[2, 2, 3]`:
1. Bắt đầu tại chỉ số 0 (giá trị 2), `target = 7`.
   - Chọn 2 $\to$ tổ hợp hiện tại: `[2]`, `target = 5`.
2. Vẫn ở chỉ số 0 (giá trị 2):
   - Chọn 2 $\to$ tổ hợp hiện tại: `[2, 2]`, `target = 3`.
3. Vẫn ở chỉ số 0 (giá trị 2):
   - Chọn 2 $\to$ tổ hợp hiện tại: `[2, 2, 2]`, `target = 1`.
4. Vẫn ở chỉ số 0 (giá trị 2):
   - Chọn 2 $\to$ tổ hợp hiện tại: `[2, 2, 2, 2]`, `target = -1` (vượt quá, quay lui về bước 3).
   - Bỏ qua 2, chuyển sang chỉ số 1 (giá trị 3):
     - Chọn 3 $\to$ tổ hợp hiện tại: `[2, 2, 2, 3]`, `target = -2` (vượt quá, quay lui).
     - Bỏ qua 3, chuyển sang chỉ số 2 (giá trị 6) $\to$ `target = 1 - 6 = -5` (quay lui)...
5. Quay lui về bước 2 (`[2, 2]`, `target = 3`):
   - Bỏ qua 2, chuyển sang chỉ số 1 (giá trị 3):
     - Chọn 3 $\to$ tổ hợp hiện tại: `[2, 2, 3]`, `target = 3 - 3 = 0`. Thành công! Lưu lại `[2, 2, 3]`.

Quá trình tiếp tục tương tự và sẽ tìm thêm được tổ hợp `[7]`.

---

## Các trường hợp kiểm thử bổ sung

### Trường hợp 1: Không có tổ hợp nào thỏa mãn
- **Đầu vào:**
  ```text
  candidates = [2, 4], target = 3
  ```
- **Mô tả:** Mọi phần tử đều lớn hơn `target` hoặc không thể tạo tổng lẻ từ các số chẵn.
- **Đầu ra mong đợi:** `[]` (rỗng)

### Trường hợp 2: Target trùng khớp với phần tử nhỏ nhất và có thể chia hết
- **Đầu vào:**
  ```text
  candidates = [3, 5], target = 9
  ```
- **Mô tả:** Chỉ có tổ hợp sử dụng 3 lần số `3` là thỏa mãn.
- **Đầu ra mong đợi:** `[[3, 3, 3]]`

### Trường hợp 3: Chứa phần tử lớn hơn target
- **Đầu vào:**
  ```text
  candidates = [2, 3, 5, 8], target = 5
  ```
- **Mô tả:** Có phần tử `8` lớn hơn `target`. Các tổ hợp hợp lệ: `[2, 3]`, `[5]`. Phần tử `8` sẽ bị cắt tỉa nhánh cận ngay lập tức.
- **Đầu ra mong đợi:** `[[2, 3], [5]]`

---

**Tổng kết:**
Thuật toán Backtracking kết hợp Pruning là giải pháp hoàn hảo để quét toàn bộ không gian tổ hợp của bài toán này. Bằng cách thiết kế cây quyết định thông minh, ta vừa đảm bảo tìm đủ mọi trường hợp, vừa ngăn chặn trùng lặp và tối ưu hóa thời gian chạy thông qua cắt tỉa các nhánh không khả thi.
