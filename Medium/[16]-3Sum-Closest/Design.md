# Tư duy thiết kế: 3Sum Closest

## Vấn đề

Bài toán yêu cầu chúng ta tìm bộ ba số trong một mảng sao cho tổng của chúng gần với giá trị `target` nhất. Khác với bài toán 3Sum truyền thống là đi tìm một con số tuyệt đối (bằng 0), bài toán này giống như một cuộc **truy đuổi sai số**. Chúng ta không cần sự hoàn hảo, chúng ta cần sự **tiệm cận**.

Thách thức ở đây là làm sao để quét qua các tổ hợp số một cách thông minh, sao cho khoảng cách giữa "tổng hiện tại" và "mục tiêu" ngày càng thu hẹp lại mà không cần phải kiểm tra tất cả các trường hợp (vốn sẽ tốn `O(n³)` thời gian).

---

## Giải pháp

Hãy tưởng tượng bạn đang ở một **trường bắn cung**. Mục tiêu (`target`) là tâm điểm của bia bắn. Bạn được giao nhiệm vụ chọn ra 3 mũi tên từ một bó tên có độ dài khác nhau, sao cho khi nối chúng lại, tổng chiều dài của chúng sẽ giúp bạn chạm gần tâm bia nhất có thể.

Để không phải loay hoay thử từng bộ ba một cách vô vọng, chúng ta thực hiện chiến thuật sau:

1.  **Sắp xếp bó tên:** Đầu tiên, hãy xếp các mũi tên theo thứ tự từ ngắn nhất đến dài nhất. Việc này giúp chúng ta biết rõ hướng cần điều chỉnh: muốn dài hơn thì lấy mũi tên bên phải, muốn ngắn lại thì lấy mũi tên bên trái.
2.  **Chọn một mũi tên làm mốc (`i`):** Chúng ta duyệt qua từng mũi tên một.
3.  **Kỹ thuật "Gọng kìm linh hoạt" (`left` và `right`):** Với hai vị trí còn lại, chúng ta đặt một tay vào mũi tên ngắn nhất (`left`) và một tay vào mũi tên dài nhất (`right`) trong phần còn lại của bó tên:
    -   **Đo khoảng cách:** Tính tổng chiều dài của 3 mũi tên. Nếu khoảng cách từ tổng này đến tâm bia nhỏ hơn kỷ lục trước đó, hãy ghi chú lại con số này vào sổ tay.
    -   **Điều chỉnh:** 
        -   Nếu tổng vẫn còn ngắn hơn khoảng cách đến bia: Hãy bỏ mũi tên ngắn (`left`) và chọn mũi tên tiếp theo dài hơn một chút (`left++`).
        -   Nếu tổng đã vượt quá khoảng cách đến bia: Hãy bỏ mũi tên dài (`right`) và chọn mũi tên đứng trước nó ngắn hơn một chút (`right--`).
        -   Nếu tổng bằng đúng `target`: Chúc mừng! Bạn đã trúng hồng tâm, hãy dừng cuộc chơi ngay lập tức và trả về kết quả.

---

## Tại sao tối ưu?

-   **Hiệu năng O(n²):** Thay vì thử sai vô định, việc sắp xếp cho phép chúng ta "thu hẹp vòng vây" một cách có tính toán. Với mỗi mũi tên mốc, chúng ta chỉ mất một lượt quét duy nhất từ hai đầu để tìm ra bộ ba tốt nhất đi kèm với nó.
-   **Tư duy tham lam (Greedy approach):** Việc di chuyển các con trỏ dựa trên việc so sánh với `target` giúp chúng ta loại bỏ hàng ngàn tổ hợp không khả thi mà không cần nhìn tới chúng.
-   **Sử dụng bộ nhớ tối thiểu:** Chúng ta chỉ cần một vài biến phụ để lưu trữ "kỷ lục" gần nhất, không cần thêm các cấu trúc dữ liệu phức tạp.

---

## Mô phỏng thực tế

Giả sử `nums = [-1, 2, 1, -4]`, `target = 1`.
Sắp xếp: `[-4, -1, 1, 2]`

1.  **Chọn mốc i = 0 (giá trị -4):**
    -   `left = 1 (-1)`, `right = 3 (2)`. Tổng = `-4 + (-1) + 2 = -3`. Khoảng cách tới `1` là `4`. (Kỷ lục mới: -3)
    -   Tổng `-3 < 1`, tăng `left`.
    -   `left = 2 (1)`, `right = 3 (2)`. Tổng = `-4 + 1 + 2 = -1`. Khoảng cách tới `1` là `2`. (Kỷ lục mới: -1)
2.  **Chọn mốc i = 1 (giá trị -1):**
    -   `left = 2 (1)`, `right = 3 (2)`. Tổng = `-1 + 1 + 2 = 2`. Khoảng cách tới `1` là `1`. (Kỷ lục mới: 2)

**Kết quả cuối cùng:** Tổng gần nhất là `2`.

---

## Các trường hợp kiểm thử mở rộng

1.  **Tổng đúng bằng Target:**
    -   `nums = [1, 1, 1]`, `target = 3`
    -   Kết quả: `3` (Dừng ngay khi thấy tổng bằng target).
2.  **Mảng có các số cực lớn:**
    -   `nums = [100, 200, 300]`, `target = 0`
    -   Kết quả: `600` (Khi target nằm ngoài phạm vi của mảng, tổng nhỏ nhất hoặc lớn nhất sẽ là kết quả).
3.  **Target nằm giữa các giá trị:**
    -   `nums = [-1, 0, 1, 1]`, `target = 100`
    -   Kết quả: `2` (Tổng lớn nhất có thể là `-1 + 1 + 1 = 1` hoặc `0 + 1 + 1 = 2`. Số 2 gần 100 hơn).
4.  **Mảng chứa nhiều số âm:**
    -   `nums = [-5, -4, -3, -2, -1]`, `target = -10`
    -   Kết quả: `-10` (Nếu có bộ ba cộng lại bằng đúng số âm đó).
