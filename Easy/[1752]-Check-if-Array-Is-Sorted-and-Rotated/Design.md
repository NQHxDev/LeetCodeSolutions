# Tư duy thiết kế: Vòng tròn tăng dần (Check if Array Is Sorted and Rotated)

Kiểm tra một mảng có được sắp xếp tăng dần và bị xoay vòng hay không là một bài toán thú vị. Nó rèn luyện tư duy nhận diện tính tuần hoàn và cách tối ưu hóa không gian lưu trữ bằng cách tận dụng cấu trúc vòng tròn của dữ liệu.

## Vấn đề

Hãy tưởng tượng chúng ta có một băng chuyền vòng tròn chứa các hộp hàng. Theo quy chuẩn, các hộp hàng này ban đầu được xếp theo thứ tự cân nặng tăng dần. Tuy nhiên, vì băng chuyền chuyển động liên tục, điểm bắt đầu hiện tại có thể nằm ở bất kỳ vị trí nào.

Nếu chúng ta đi dọc băng chuyền để kiểm tra xem hàng có được xếp đúng thứ tự hay không:
- Cách thông thường là thử xoay mảng về vị trí gốc (vị trí có phần tử nhỏ nhất làm đầu) rồi kiểm tra tính tăng dần của nó. Việc dịch chuyển mảng này yêu cầu tạo mảng mới hoặc dịch chuyển phần tử, dẫn đến tiêu tốn bộ nhớ bổ sung hoặc tăng độ phức tạp thời gian.
- Nếu kiểm tra trực tiếp mà không hiểu quy luật vòng tròn, ta sẽ dễ bị bối rối khi gặp điểm "gãy" (nơi giá trị đột ngột giảm xuống).

---

## Giải pháp

Để giải quyết bài toán một cách tối ưu, chúng ta hãy thay đổi góc nhìn từ việc "sắp xếp lại" sang việc "đếm số điểm gãy".

Trong một mảng tăng dần đã bị xoay vòng, do tính chất tuần hoàn, nếu chúng ta coi mảng là một vòng tròn khép kín (phần tử cuối cùng kết nối với phần tử đầu tiên):
- Một mảng tăng dần hoàn hảo sẽ chỉ có tối đa **một điểm gãy** duy nhất (nơi phần tử đứng trước lớn hơn phần tử đứng sau). Điểm gãy này chính là ranh giới giữa phần tử lớn nhất và phần tử nhỏ nhất của mảng ban đầu.
- Nếu mảng hoàn toàn bằng nhau hoặc đã được sắp xếp tăng dần mà không xoay, số điểm gãy sẽ là 0 hoặc 1 (điểm gãy xuất hiện ở vị trí nối giữa phần tử cuối và phần tử đầu).
- Nếu số lượng điểm gãy lớn hơn 1, mảng chắc chắn không thể được tạo ra từ việc xoay một mảng đã sắp xếp.

Do đó, thuật toán chỉ cần duyệt qua mảng một lần, so sánh từng phần tử với phần tử kế tiếp của nó (bao gồm cả việc nối phần tử cuối với phần tử đầu bằng phép toán chia lấy dư `%`). Nếu số lần vi phạm tính chất `nums[i] <= nums[i+1]` vượt quá 1, chúng ta kết luận ngay là `false`.

---

## Tại sao tối ưu?

Phương pháp này tối ưu hoàn toàn về cả không gian và thời gian:
- **Thời gian xử lý:** $O(n)$ vì chúng ta chỉ duyệt qua mảng đúng một lần duy nhất.
- **Không gian lưu trữ:** $O(1)$ vì chúng ta chỉ sử dụng một biến đếm số điểm gãy mà không tạo thêm mảng phụ hay thực hiện các thao tác dịch chuyển phần tử phức tạp.

---

## Mô phỏng luồng xử lý

Với `nums = [3, 4, 5, 1, 2]` (độ dài `n = 5`):

1. **So sánh `nums[0]` và `nums[1]` (`3` và `4`):**
   - $3 \le 4$: Hợp lệ.
2. **So sánh `nums[1]` và `nums[2]` (`4` và `5`):**
   - $4 \le 5$: Hợp lệ.
3. **So sánh `nums[2]` và `nums[3]` (`5` và `1`):**
   - $5 > 1$: Điểm gãy! (Số điểm gãy = 1)
4. **So sánh `nums[3]` và `nums[4]` (`1` và `2`):**
   - $1 \le 2$: Hợp lệ.
5. **So sánh `nums[4]` và `nums[0]` (`2` và `3` - Vòng lặp cuối):**
   - $2 \le 3$: Hợp lệ.

Tổng số điểm gãy phát hiện: `1` (nhỏ hơn hoặc bằng 1).
**Kết luận:** Trả về `true`.

---

## Các trường hợp kiểm thử bổ sung

Dưới đây là một số trường hợp kiểm thử khác biệt để xác minh thuật toán:

- **Trường hợp 1:** `nums = [1, 1, 1]`
  - Mô tả: Mảng gồm các phần tử bằng nhau. Không có bất kỳ điểm gãy nào (số điểm gãy = 0).
  - Kết quả mong đợi: `true`

- **Trường hợp 2:** `nums = [4, 5, 6, 7, 0, 1, 2]`
  - Mô tả: Mảng tăng dần được xoay tại vị trí của số 7. Có 1 điểm gãy giữa `7` và `0`.
  - Kết quả mong đợi: `true`

- **Trường hợp 3:** `nums = [3, 5, 2, 4]`
  - Mô tả: Xuất hiện 2 điểm gãy: giữa `5` và `2` (chỉ số 1 sang 2), và giữa `4` và `3` (vòng từ cuối về đầu).
  - Kết quả mong đợi: `false`

- **Trường hợp 4:** `nums = [10, 20, 30, 40, 5, 8]`
  - Mô tả: Mảng tăng dần được xoay tại vị trí của số 40. Có 1 điểm gãy duy nhất giữa `40` và `5`.
  - Kết quả mong đợi: `true`

- **Trường hợp 5:** `nums = [1, 2, 3, 2]`
  - Mô tả: Mảng có 2 điểm gãy: giữa `3` và `2` (chỉ số 2 sang 3) và giữa `2` và `1` (vòng từ cuối về đầu).
  - Kết quả mong đợi: `false`
