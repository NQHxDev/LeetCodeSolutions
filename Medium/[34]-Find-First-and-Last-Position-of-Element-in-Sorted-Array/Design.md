# Tư duy thiết kế: Xác định phạm vi phần tử (Find First and Last Position of Element in Sorted Array)

Việc tìm vị trí bắt đầu và kết thúc của một phần tử trong mảng đã được sắp xếp là một bài toán cơ bản nhưng đòi hỏi sự tinh tế trong việc tinh chỉnh thuật toán tìm kiếm nhị phân gốc để đạt được hiệu năng tối ưu.

## Vấn đề

Hãy tưởng tượng một thủ thư đang quản lý một kệ sách lớn chứa các cuốn sách được xếp thứ tự theo tên tác giả. Thủ thư muốn tìm khoảng vị trí từ cuốn sách đầu tiên đến cuốn sách cuối cùng của tác giả "Sherlock Holmes" trên kệ sách đó.

Nếu đi kiểm tra từng cuốn sách từ đầu kệ đến cuối kệ:
- Thao tác này tương đương với duyệt tuyến tính (Linear Search).
- Khi số lượng sách lên tới hàng ngàn cuốn, việc kiểm tra từng cuốn một sẽ tiêu tốn quá nhiều thời gian, dẫn đến độ phức tạp thời gian là $O(n)$.
- Chúng ta cần tận dụng thuộc tính kệ sách đã được sắp xếp sẵn để tìm kiếm nhanh hơn. Tuy nhiên, thuật toán tìm kiếm nhị phân thông thường chỉ trả về vị trí của một cuốn sách bất kỳ thuộc tác giả đó chứ không đảm bảo đó là cuốn đầu tiên hay cuốn cuối cùng.

---

## Giải pháp

Để giải quyết bài toán với độ phức tạp $O(\log n)$, chúng ta sẽ thực hiện hai lượt tìm kiếm nhị phân độc lập nhưng có mục tiêu cụ thể:

### Tìm vị trí bắt đầu (Biên trái)
- Tiến hành tìm kiếm nhị phân thông thường.
- Khi tìm thấy một vị trí `mid` có giá trị bằng `target`, thay vì dừng thuật toán, chúng ta tiếp tục thu hẹp phạm vi tìm kiếm sang nửa bên trái bằng cách gán `right = mid - 1` để kiểm tra xem có sự xuất hiện nào sớm hơn hay không.
- Ghi nhận vị trí `mid` này là vị trí bắt đầu tạm thời.

### Tìm vị trí kết thúc (Biên phải)
- Tiến hành tìm kiếm nhị phân thông thường.
- Khi tìm thấy vị trí `mid` có giá trị bằng `target`, chúng ta tiếp tục thu hẹp phạm vi tìm kiếm sang nửa bên phải bằng cách gán `left = mid + 1` để tìm xem có sự xuất hiện nào muộn hơn hay không.
- Ghi nhận vị trí `mid` này là vị trí kết thúc tạm thời.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian:** Giải pháp thực hiện hai lần tìm kiếm nhị phân độc lập. Mỗi lần tìm kiếm nhị phân trên mảng kích thước $n$ mất tối đa $O(\log n)$ bước. Tổng thời gian xử lý là $2 \times O(\log n) = O(\log n)$, đáp ứng hoàn hảo yêu cầu ràng buộc về hiệu năng của bài toán.
- **Tiết kiệm bộ nhớ:** Thuật toán chỉ sử dụng các biến con trỏ chỉ số như `left`, `right`, `mid` và hai biến lưu trữ kết quả biên. Không có cấu trúc dữ liệu bổ sung nào được khởi tạo, đảm bảo độ phức tạp không gian là $O(1)$.

---

## Mô phỏng luồng xử lý

Giả sử đầu vào là mảng `nums = [5, 7, 7, 8, 8, 10]` và `target = 8`.

### Lượt 1: Tìm kiếm vị trí bắt đầu
- Khởi tạo: `left = 0`, `right = 5`, `firstIdx = -1`.
- Bước 1: `mid = (0 + 5) / 2 = 2`. Giá trị `nums[2] = 7 < 8`. Dịch chuyển biên trái: `left = mid + 1 = 3`.
- Bước 2: `mid = (3 + 5) / 2 = 4`. Giá trị `nums[4] = 8 == 8`. Tìm thấy target! Ghi nhận `firstIdx = 4`. Tiếp tục tìm bên trái: `right = mid - 1 = 3`.
- Bước 3: `mid = (3 + 3) / 2 = 3`. Giá trị `nums[3] = 8 == 8`. Tìm thấy target! Ghi nhận `firstIdx = 3`. Tiếp tục tìm bên trái: `right = mid - 1 = 2`.
- Kết quả: Vòng lặp dừng vì `left (3) > right (2)`. Vị trí bắt đầu tìm được là `3`.

### Lượt 2: Tìm kiếm vị trí kết thúc
- Khởi tạo: `left = 0`, `right = 5`, `lastIdx = -1`.
- Bước 1: `mid = (0 + 5) / 2 = 2`. Giá trị `nums[2] = 7 < 8`. Dịch chuyển biên trái: `left = mid + 1 = 3`.
- Bước 2: `mid = (3 + 5) / 2 = 4`. Giá trị `nums[4] = 8 == 8`. Tìm thấy target! Ghi nhận `lastIdx = 4`. Tiếp tục tìm bên phải: `left = mid + 1 = 5`.
- Bước 3: `mid = (5 + 5) / 2 = 5`. Giá trị `nums[5] = 10 > 8`. Dịch chuyển biên phải: `right = mid - 1 = 4`.
- Kết quả: Vòng lặp dừng vì `left (5) > right (4)`. Vị trí kết thúc tìm được là `4`.

Kết quả cuối cùng thu được là đoạn chỉ số `[3, 4]`.

---

## Các trường hợp kiểm thử bổ sung

- **Trường hợp 1:** `nums = [2, 2, 2, 2, 2]`, `target = 2`
  - Mô tả: Toàn bộ phần tử trong mảng đều bằng `target`. Biên trái phải là chỉ số đầu tiên và biên phải phải là chỉ số cuối cùng.
  - Kết quả mong đợi: `[0, 4]`

- **Trường hợp 2:** `nums = [1, 3, 5, 7, 9]`, `target = 6`
  - Mô tả: Giá trị `target` nằm trong khoảng giá trị của mảng nhưng không tồn tại trong mảng.
  - Kết quả mong đợi: `[-1, -1]`

- **Trường hợp 3:** `nums = []`, `target = 0`
  - Mô tả: Kiểm tra tính ổn định của hệ thống với mảng rỗng đầu vào.
  - Kết quả mong đợi: `[-1, -1]`

- **Trường hợp 4:** `nums = [1, 2, 4, 4, 4, 5, 6, 7]`, `target = 4`
  - Mô tả: Giá trị `target` xuất hiện nhiều lần liên tục ở khoảng giữa của mảng.
  - Kết quả mong đợi: `[2, 4]`

- **Trường hợp 5:** `nums = [3, 3, 3, 4, 5, 6]`, `target = 3`
  - Mô tả: Giá trị `target` nằm ngay đầu mảng và xuất hiện nhiều lần liên tiếp.
  - Kết quả mong đợi: `[0, 2]`
