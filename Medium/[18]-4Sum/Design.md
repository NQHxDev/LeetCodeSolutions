# Tư duy thiết kế: 4Sum

## Vấn đề

Bài toán yêu cầu tìm tất cả các bộ bốn số (quadruplets) duy nhất trong một mảng sao cho tổng của chúng bằng một giá trị `target` cho trước. Đây là một bài toán mở rộng của 2Sum và 3Sum, nơi độ phức tạp tăng dần theo số lượng con số cần chọn. Thách thức lớn nhất không chỉ là tìm ra tổng đúng, mà là làm sao để **loại bỏ các bộ trùng lặp** một cách hiệu quả mà không tốn thêm quá nhiều bộ nhớ.

---

## Giải pháp

Hãy tưởng tượng bạn đang **lập một đội đặc nhiệm gồm 4 người** từ một danh sách ứng viên, sao cho tổng chỉ số sức mạnh của họ phải đúng bằng `target`. 

Thay vì chọn ngẫu nhiên 4 người (tốn rất nhiều thời gian thử sai), chúng ta thực hiện các bước sau:

1.  **Sắp xếp đội hình:** Đầu tiên, hãy yêu cầu tất cả ứng viên đứng thành một hàng dọc theo thứ tự sức mạnh tăng dần. Việc sắp xếp này là "chìa khóa" để chúng ta có thể di chuyển một cách có hệ thống và dễ dàng nhận diện những người có sức mạnh giống nhau để bỏ qua.
2.  **Chọn 2 đội trưởng (`i` và `j`):** 
    -   Chúng ta dùng hai vòng lặp lồng nhau để cố định hai người đầu tiên.
    -   Mỗi khi chọn một người, nếu người đó giống hệt người trước đó ở cùng vị trí, chúng ta bỏ qua để tránh trùng lặp đội hình.
3.  **Kỹ thuật "Hai gọng kìm" (`left` và `right`):** Sau khi đã có 2 đội trưởng, chúng ta chỉ cần tìm 2 người còn lại trong khoảng giữa. Thay vì dùng thêm vòng lặp, chúng ta đặt hai người ở hai đầu khoảng còn lại:
    -   Nếu tổng quá thấp: Người ở bên trái (yếu hơn) bước lên một bậc.
    -   Nếu tổng quá cao: Người ở bên phải (mạnh hơn) lùi lại một bậc.
    -   Nếu tổng vừa đúng: Chúng ta ghi nhận đội hình này và yêu cầu cả hai người cùng di chuyển để tìm kiếm những sự kết hợp mới, đồng thời bỏ qua những người có sức mạnh tương tự.

4.  **Cắt tỉa nhánh (Pruning) - Quan trọng để tối ưu:**
    -   Nếu 4 người yếu nhất hiện tại đã có tổng lớn hơn `target`, chúng ta dừng cuộc tìm kiếm ở vị trí đó.
    -   Nếu đội trưởng hiện tại cộng với 3 người mạnh nhất cuối hàng vẫn nhỏ hơn `target`, chúng ta bỏ qua đội trưởng này vì họ không có cơ hội đạt được mục tiêu.

---

## Tại sao tối ưu?

-   **Thời gian O(n³):** Bằng cách sử dụng hai con trỏ cho hai vị trí cuối cùng, chúng ta giảm được một bậc lũy thừa so với cách tiếp cận 4 vòng lặp lồng nhau (O(n⁴)).
-   **Không gian O(1) hoặc O(log n):** Chúng ta không cần dùng bảng băm (Hash Map) để lưu trữ các bộ đã tìm thấy (vốn rất tốn bộ nhớ), mà tận dụng chính mảng đã sắp xếp để loại bỏ trùng lặp "tại chỗ".
-   **Cắt tỉa thông minh:** Các điều kiện kiểm tra sớm giúp thuật toán thoát khỏi những vòng lặp vô vọng, giúp thời gian thực tế nhanh hơn rất nhiều so với lý thuyết O(n³).

---

## Mô phỏng thực tế

Giả sử `nums = [1, 0, -1, 0, -2, 2]`, `target = 0`.
Sắp xếp: `[-2, -1, 0, 0, 1, 2]`

1.  **Cố định i = 0 (giá trị -2):**
    -   **Cố định j = 1 (giá trị -1):**
        -   Tìm 2 số sao cho tổng bằng `0 - (-2) - (-1) = 3`.
        -   Hai con trỏ ở `0, 0, 1, 2`. Tìm thấy `1 + 2 = 3`.
        -   Bộ 1: `[-2, -1, 1, 2]`.
    -   **Cố định j = 2 (giá trị 0):**
        -   Tìm 2 số sao cho tổng bằng `0 - (-2) - 0 = 2`.
        -   Hai con trỏ ở `0, 1, 2`. Tìm thấy `0 + 2 = 2`.
        -   Bộ 2: `[-2, 0, 0, 2]`.
2.  **Cố định i = 1 (giá trị -1):**
    -   ... (Tiếp tục quá trình tương tự) ...

---

## Các trường hợp kiểm thử mở rộng

1.  **Mảng có ít hơn 4 phần tử:** 
    -   `nums = [1, 2, 3]`, `target = 6`
    -   Kết quả: `[]` (Không đủ người để lập đội).
2.  **Tất cả phần tử giống nhau:**
    -   `nums = [2, 2, 2, 2, 2]`, `target = 8`
    -   Kết quả: `[[2, 2, 2, 2]]` (Chỉ lấy một bộ duy nhất nhờ cơ chế bỏ qua trùng lặp).
3.  **Target là số âm cực lớn hoặc dương cực lớn:**
    -   `nums = [1, 2, 3, 4]`, `target = 100`
    -   Kết quả: `[]` (Cắt tỉa nhánh sẽ giúp dừng lại ngay lập tức).
4.  **Mảng chứa các số đối nhau:**
    -   `nums = [-3, -2, -1, 0, 1, 2, 3]`, `target = 0`
    -   Kết quả: Tìm được nhiều bộ đối xứng như `[-3, -2, 2, 3]`, `[-3, -1, 1, 3]`, v.v.
