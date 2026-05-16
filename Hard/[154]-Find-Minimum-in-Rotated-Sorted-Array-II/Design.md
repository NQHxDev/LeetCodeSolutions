# Tư duy thiết kế: Find Minimum in Rotated Sorted Array II

## Vấn đề

Bài toán yêu cầu chúng ta tìm phần tử nhỏ nhất trong một mảng đã được sắp xếp nhưng bị xoay (rotated) tại một điểm nào đó. Điều làm cho bài toán này trở nên "Hard" chính là sự xuất hiện của các **phần tử trùng lặp**. 

Thông thường, với một mảng xoay không có phần tử trùng lặp, chúng ta có thể dễ dàng dùng Tìm kiếm Nhị phân để xác định điểm gãy (pivot) chỉ trong `O(log N)`. Tuy nhiên, khi các con số giống hệt nhau xuất hiện ở cả hai đầu của khoảng tìm kiếm, chúng ta sẽ rơi vào trạng thái "mất phương hướng" vì không biết điểm gãy nằm ở bên trái hay bên phải của mình.

---

## Giải pháp

Hãy tưởng tượng bạn đang đi trên một **cầu thang bị cắt tầng và dịch chuyển**. Hầu hết các bậc thang đều đi lên, nhưng tại một điểm nào đó, nó đột ngột rơi xuống bậc thấp nhất rồi lại tiếp tục đi lên. Đặc biệt, cầu thang này có những đoạn **phẳng (plateaus)** - nơi nhiều bậc liên tiếp có cùng độ cao.

Chiến thuật tìm kiếm nhị phân biến thể như sau:

1.  **So sánh bậc hiện tại (`mid`) với bậc cuối cùng bên phải (`right`):**
    -   **Trường hợp `nums[mid] > nums[right]`:** Chắc chắn điểm rơi (giá trị nhỏ nhất) nằm ở bên phải của `mid`. Chúng ta tự tin bước sang phải: `left = mid + 1`.
    -   **Trường hợp `nums[mid] < nums[right]`:** Điểm rơi có thể chính là `mid` hoặc nằm bên trái của nó. Chúng ta thu hẹp phạm vi về bên trái: `right = mid`.
    -   **Trường hợp `nums[mid] == nums[right]`:** Đây là lúc chúng ta bị kẹt trên một đoạn phẳng. Chúng ta không biết điểm rơi nằm ở phía nào. 
2.  **Xử lý đoạn phẳng:** Thay vì nhảy một quãng dài, chúng ta chọn cách **lùi lại một bước một cách thận trọng** từ phía bên phải: `right--`. Hành động này giúp thu hẹp vùng tìm kiếm mà không làm mất đi giá trị nhỏ nhất, vì ngay cả khi `nums[right]` là giá trị nhỏ nhất, chúng ta vẫn còn một bản sao khác của nó tại `nums[mid]`.

---

## Tại sao tối ưu?

-   **Hiệu năng trung bình O(log N):** Trong hầu hết các trường hợp, chúng ta vẫn cắt đôi được không gian tìm kiếm sau mỗi bước, giữ nguyên sức mạnh của tìm kiếm nhị phân.
-   **Khả năng xử lý trường hợp xấu nhất O(N):** Khi mảng chứa toàn bộ các phần tử giống nhau (ví dụ: `[2, 2, 2, 2, 2]`), thuật toán sẽ phải lùi từng bước một. Đây là cái giá phải trả để đảm bảo tính chính xác khi có sự xuất hiện của các phần tử trùng lặp mà không có thuật toán nhị phân thuần túy nào vượt qua được.
-   **Tính an toàn:** Việc chỉ giảm `right` đi 1 đơn vị khi gặp phần tử trùng lặp đảm bảo rằng chúng ta không bao giờ "nhảy qua" điểm nhỏ nhất trong sự mơ hồ.

---

## Mô phỏng thực tế

Xét mảng: `nums = [2, 2, 2, 0, 1, 2, 2]`

1.  **Lần 1:** `left = 0`, `right = 6`, `mid = 3`. 
    -   `nums[3] = 0`, `nums[6] = 2`.
    -   Vì `0 < 2`, điểm nhỏ nhất nằm ở bên trái (bao gồm cả `mid`).
    -   Cập nhật: `right = 3`.
2.  **Lần 2:** `left = 0`, `right = 3`, `mid = 1`.
    -   `nums[1] = 2`, `nums[3] = 0`.
    -   Vì `2 > 0`, điểm nhỏ nhất chắc chắn nằm bên phải `mid`.
    -   Cập nhật: `left = 2`.
3.  **Lần 3:** `left = 2`, `right = 3`, `mid = 2`.
    -   `nums[2] = 2`, `nums[3] = 0`.
    -   Vì `2 > 0`, cập nhật: `left = 3`.
4.  **Kết thúc:** `left == right == 3`. Giá trị nhỏ nhất là `nums[3] = 0`.

---

## Các trường hợp kiểm thử mở rộng

1.  **Mảng toàn phần tử trùng lặp:**
    -   `nums = [1, 1, 1, 1, 1]`
    -   Kết quả: `1` (Thuật toán sẽ lùi `right` liên tục cho đến khi gặp `left`).
2.  **Điểm nhỏ nhất nằm ở ngay đầu hoặc cuối sau khi xoay:**
    -   `nums = [10, 1, 10, 10, 10]`
    -   Kết quả: `1` (Xử lý tốt việc giá trị nhỏ nhất bị kẹp giữa các phần tử lớn bằng nhau).
3.  **Mảng chỉ có 2 phần tử:**
    -   `nums = [3, 1]`
    -   Kết quả: `1`.
4.  **Mảng đã được sắp xếp và không bị xoay:**
    -   `nums = [1, 2, 3, 3, 3]`
    -   Kết quả: `1`.
