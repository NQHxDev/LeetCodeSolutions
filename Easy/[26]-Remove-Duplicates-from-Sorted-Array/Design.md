# Tư duy thiết kế: Loại bỏ phần tử trùng lặp trong mảng đã sắp xếp (Remove Duplicates from Sorted Array)

Bài toán yêu cầu loại bỏ các phần tử trùng lặp khỏi một mảng đã được sắp xếp tăng dần sao cho mỗi phần tử chỉ xuất hiện duy nhất một lần. Ràng buộc quan trọng nhất là chúng ta phải thực hiện việc này **trực tiếp trên mảng cũ (in-place)** với lượng bộ nhớ bổ sung là $O(1)$, sau đó trả về độ dài mới của phần tử độc bản.

## Vấn đề: Thách thức của việc dọn dẹp tại chỗ

Thông thường, cách đơn giản nhất để loại bỏ trùng lặp là sử dụng một mảng mới hoặc một cấu trúc dữ liệu lưu giữ các giá trị độc bản (như Set/Hash Map), sau đó sao chép ngược lại. Tuy nhiên, việc này sẽ tiêu tốn thêm bộ nhớ tỷ lệ thuận với số lượng phần tử của mảng ($O(n)$).

Khi hệ thống yêu cầu xử lý trực tiếp trên mảng ban đầu ($O(1)$ bộ nhớ phụ), chúng ta không thể "xóa" phần tử theo cách thông thường vì các phần tử trong mảng nằm liên tiếp nhau trên bộ nhớ vật lý. Việc xóa và dịch chuyển các phần tử phía sau lên mỗi khi gặp trùng lặp sẽ tốn thời gian $O(n^2)$. Do đó, chúng ta cần một giải pháp thông minh hơn để gom các phần tử độc bản về đầu mảng chỉ trong một lần duyệt duy nhất.

---

## Giải pháp: Kỹ thuật "Thủ thư dồn sách" (Two Pointers)

Hãy tưởng tượng bạn là một người thủ thư đang sắp xếp một hàng sách trên giá hẹp theo thứ tự bảng chữ cái. Một số cuốn sách bị trùng lặp tiêu đề và bạn muốn dồn những cuốn độc bản về phía bên trái của giá sách.

Thay vì lấy các cuốn sách ra một chiếc bàn khác để lọc, bạn dùng hai vị trí đánh dấu:
- **Vị trí ghi nhận (`i`):** Đánh dấu ranh giới của các cuốn sách độc bản đã được sắp xếp đúng vị trí. Ban đầu, cuốn sách đầu tiên (`nums[0]`) luôn là độc bản, nên ta đặt ranh giới này tại vị trí số 0.
- **Vị trí duyệt tìm (`j`):** Chạy dọc theo hàng sách từ vị trí số 1 đến cuối giá để tìm kiếm những cuốn sách mới.

Quy trình thực hiện:
- Di chuyển con trỏ duyệt `j` từ trái sang phải.
- Tại mỗi cuốn sách ở vị trí `j`, ta so sánh nó với cuốn sách độc bản cuối cùng đã được ghi nhận ở vị trí `i` (`nums[i]`).
- Nếu cuốn sách tại `j` giống hệt cuốn sách tại `i`: Đây là cuốn trùng lặp, ta chỉ cần bỏ qua và tiếp tục di chuyển `j` sang cuốn tiếp theo.
- Nếu cuốn sách tại `j` khác cuốn sách tại `i`: Đây là một cuốn sách độc bản mới!
  - Ta mở rộng ranh giới độc bản bằng cách dịch chuyển `i` lên một vị trí (`i++`).
  - Đặt cuốn sách mới tìm thấy này vào vị trí `i` vừa mở rộng đó (`nums[i] = nums[j]`).
- Sau khi duyệt hết hàng sách, toàn bộ các phần tử từ vị trí `0` đến `i` sẽ chứa các giá trị độc bản theo đúng thứ tự. Số lượng phần tử độc bản lúc này sẽ là `i + 1`.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Tiết kiệm tối đa bộ nhớ:** Thuật toán không sử dụng thêm bất kỳ mảng phụ hay cấu trúc dữ liệu phức tạp nào. Chỉ cần 2 biến con trỏ chạy trên mảng gốc, đạt độ phức tạp không gian $O(1)$.
- **Hiệu năng thời gian vượt trội:** Chỉ cần duy nhất 1 vòng lặp để con trỏ `j` quét qua mảng từ đầu đến cuối. Độ phức tạp thời gian đạt $O(n)$, tối ưu tuyệt đối vì chúng ta bắt buộc phải xem qua mỗi phần tử ít nhất một lần.
- **Tận dụng tính chất sắp xếp:** Vì mảng đã được sắp xếp, các phần tử trùng lặp chắc chắn sẽ đứng cạnh nhau. Do đó, ta chỉ cần so sánh phần tử hiện tại với phần tử độc bản cuối cùng được ghi nhận ở vị trí `i` mà không cần tìm kiếm ngược lại toàn bộ mảng.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử chúng ta có mảng đầu vào: `nums = [1, 1, 2, 2, 3]`

- **Khởi tạo:**
  - Đặt con trỏ ghi nhận `i = 0` (đại diện cho phần tử độc bản đầu tiên là `1`).
  - Con trỏ duyệt `j` bắt đầu từ `1`.

- **Vòng lặp:**
  - **Lần 1 (j = 1):** So sánh `nums[j] (1)` và `nums[i] (1)`.
    - Thấy trùng lặp. Không hành động gì. Con trỏ `j` tăng lên `2`.
  - **Lần 2 (j = 2):** So sánh `nums[j] (2)` và `nums[i] (1)`.
    - Thấy khác nhau! Đây là phần tử mới.
    - Hành động: Tăng `i` lên `1` (bây giờ `i = 1`), ghi đè `nums[1] = nums[2]` (giá trị `2`).
    - Mảng hiện tại: `[1, 2, 2, 2, 3]`. Con trỏ `j` tăng lên `3`.
  - **Lần 3 (j = 3):** So sánh `nums[j] (2)` và `nums[i] (2)`.
    - Thấy trùng lặp. Không hành động gì. Con trỏ `j` tăng lên `4`.
  - **Lần 4 (j = 4):** So sánh `nums[j] (3)` và `nums[i] (2)`.
    - Thấy khác nhau! Đây là phần tử mới.
    - Hành động: Tăng `i` lên `2` (bây giờ `i = 2`), ghi đè `nums[2] = nums[4]` (giá trị `3`).
    - Mảng hiện tại: `[1, 2, 3, 2, 3]`. Con trỏ `j` tăng lên `5` (kết thúc vòng lặp).

- **Kết quả:**
  - Trả về độ dài mới là `i + 1 = 3`.
  - Phần mảng hợp lệ phía trước là `[1, 2, 3]`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử khác biệt so với các ví dụ mặc định trên LeetCode để kiểm tra độ ổn định và tính chính xác của thuật toán:

- **Case 1 (Mảng không có phần tử trùng lặp nào):**
  - `nums = [1, 2, 3, 4]`
  - Kết quả trả về: `4`
  - Trạng thái mảng: `[1, 2, 3, 4]` (Không có sự thay đổi nào)

- **Case 2 (Tất cả các phần tử đều trùng lặp):**
  - `nums = [5, 5, 5, 5]`
  - Kết quả trả về: `1`
  - Trạng thái mảng: `[5, 5, 5, 5]` (Chỉ giữ lại duy nhất số `5` ở vị trí đầu tiên)

- **Case 3 (Mảng chỉ có đúng 1 phần tử):**
  - `nums = [9]`
  - Kết quả trả về: `1`
  - Trạng thái mảng: `[9]` (Xử lý chính xác trường hợp biên tối thiểu)

- **Case 4 (Mảng có cả số âm và số dương):**
  - `nums = [-5, -5, -2, 0, 0, 3]`
  - Kết quả trả về: `4`
  - Trạng thái mảng: `[-5, -2, 0, 3, 0, 3]` (Dồn các giá trị độc bản `[-5, -2, 0, 3]` về đầu)

- **Case 5 (Mảng có các nhóm trùng lặp phân bố lệch):**
  - `nums = [1, 2, 3, 3, 3]`
  - Kết quả trả về: `3`
  - Trạng thái mảng: `[1, 2, 3, 3, 3]` (Dồn các giá trị độc bản `[1, 2, 3]` về đầu)

---

**Tổng kết:** Bằng cách biến đổi quá trình lọc dữ liệu thành việc di chuyển của hai con trỏ trên cùng một trục tọa độ, chúng ta đã biến một thao tác có thể tốn kém về bộ nhớ hoặc thời gian thành một quá trình dọn dẹp tại chỗ cực kỳ nhanh chóng. Ranh giới độc bản sẽ được mở rộng từng bước một cách an toàn dựa trên tính chất tuần tự vốn có của dữ liệu đầu vào.
