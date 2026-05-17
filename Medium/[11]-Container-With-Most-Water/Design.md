# Tư duy thiết kế: Container With Most Water

Bài toán tìm bể chứa nước có dung tích lớn nhất (Container With Most Water) là một bài toán tối ưu hóa hình học kinh điển. Đây là một minh chứng xuất sắc cho việc áp dụng tư duy thuật toán để giảm độ phức tạp thời gian từ mức bình phương $O(n^2)$ xuống mức tuyến tính $O(n)$ thông qua kỹ thuật Hai con trỏ (Two Pointers) co hẹp vùng tìm kiếm.

## Vấn đề: Cái bẫy của việc so sánh mọi cặp vách ngăn

Hãy tưởng tượng chúng ta có một hàng các tấm vách gỗ đứng xếp song song nhau với các độ cao khác nhau. Nhiệm vụ của chúng ta là chọn ra hai tấm vách gỗ để làm thành hai thành của một bể chứa nước sao cho lượng nước trữ được là nhiều nhất.

Lượng nước chứa được trong bể phụ thuộc vào hai yếu tố chính:
- **Chiều rộng:** Khoảng cách giữa hai tấm vách gỗ.
- **Chiều cao:** Được giới hạn bởi **tấm vách gỗ thấp hơn** trong hai tấm (vì nếu nước dâng cao hơn tấm vách thấp này, nước sẽ bị tràn ra ngoài).

Cách tiếp cận ngây thơ nhất là duyệt qua tất cả các cặp vách ngăn có thể ghép lại, tính dung tích của từng bể rồi tìm ra giá trị lớn nhất.
Tuy nhiên, việc ghép đôi ngẫu nhiên này có độ phức tạp thời gian lên tới $O(n^2)$. Với một số lượng vách ngăn lên tới hàng chục nghìn, việc thử mọi cặp vách là một sự lãng phí tài nguyên khổng lồ, khiến chương trình bị quá tải và không thể đáp ứng trong thời gian thực.

---

## Giải pháp: Chiến thuật "Gọng kìm co hẹp" (Two Pointers)

Để tìm ra giải pháp tối ưu, chúng ta có thể áp dụng chiến thuật **"Gọng kìm co hẹp" (Two Pointers)** đi từ hai biên vào giữa.

Hãy bắt đầu bằng việc chọn hai tấm vách ở xa nhau nhất: Tấm ngoài cùng bên trái (`left = 0`) và tấm ngoài cùng bên phải (`right = n - 1`). Cặp vách này mang lại cho chúng ta **chiều rộng bể chứa lớn nhất có thể**.

Bây giờ, để tìm kiếm một bể chứa có dung tích lớn hơn, chúng ta buộc phải dịch chuyển các vách ngăn vào phía trong. Khi dịch chuyển vào trong, chiều rộng của bể chắc chắn sẽ bị giảm đi 1 đơn vị sau mỗi bước. Do đó, cơ hội duy nhất để dung tích bể tăng lên là chúng ta phải tìm được các **tấm vách gỗ mới cao hơn rất nhiều** để bù đắp cho phần chiều rộng đã mất.

Quy tắc co hẹp gọng kìm:
- **Nếu tấm vách bên trái (`left`) thấp hơn tấm vách bên phải (`right`):** 
  Ta dịch con trỏ bên trái vào trong (`left++`). Tại sao? Bởi vì nếu ta giữ nguyên tấm vách thấp bên trái này và dịch chuyển tấm vách bên phải vào trong, chiều rộng sẽ giảm đi, trong khi chiều cao tối đa của bể vẫn bị giới hạn bởi tấm vách thấp bên trái đó (hoặc thậm chí còn thấp hơn nữa). Do đó, dung tích bể chắc chắn sẽ bị giảm. Cách duy nhất để cải thiện là loại bỏ tấm vách thấp bên trái để đi tìm tấm vách cao hơn.
- **Nếu tấm vách bên phải (`right`) thấp hơn hoặc bằng tấm vách bên trái (`left`):**
  Ta dịch con trỏ bên phải vào trong (`right--`) với lập luận hoàn toàn tương tự.

Bằng cách luôn dịch chuyển tấm vách thấp hơn, thuật toán đảm bảo chúng ta không bao giờ bỏ sót bất kỳ cấu hình bể chứa tối ưu nào, đồng thời thu hẹp vùng tìm kiếm một cách cực kỳ thông minh.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Hiệu năng vượt trội (O(n) Time Complexity):** Chúng ta chỉ cần một vòng lặp duy nhất chạy từ hai đầu mút và gặp nhau ở giữa. Mỗi tấm vách chỉ được duyệt qua đúng một lần. Với một mảng có 1 triệu phần tử, thuật toán chỉ mất tối đa 1 triệu phép so sánh cơ bản thay vì 1.000 tỷ phép so sánh của cách tiếp cận ngây thơ.
- **Không tốn thêm bộ nhớ (O(1) Space Complexity):** Chúng ta chỉ sử dụng đúng hai biến con trỏ (`left`, `right`) và một biến lưu trữ dung tích lớn nhất (`max_area`). Hoàn toàn không tốn bất kỳ bộ nhớ phụ trợ nào khác.
- **Tính hội tụ chặt chẽ:** Thuật toán luôn kết thúc khi hai con trỏ gặp nhau, đảm bảo tính chính xác tuyệt đối mà không cần xử lý các điều kiện biên phức tạp.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ cụ thể:

Mảng độ cao: `height = [2, 1, 8, 6, 2, 5]`

```text
Chỉ số (Index):  0    1    2    3    4    5
Độ cao (Value): [2,   1,   8,   6,   2,   5]
```

- **Bước 1:** `left = 0 (độ cao 2)`, `right = 5 (độ cao 5)`.
  - Chiều rộng: `5 - 0 = 5`.
  - Chiều cao giới hạn: `min(2, 5) = 2`.
  - Dung tích bể: `5 * 2 = 10`. Cập nhật `max_area = 10`.
  - So sánh: Vì vách bên trái (`2`) thấp hơn vách bên phải (`5`), ta dịch con trỏ trái vào trong: `left = 1`.

- **Bước 2:** `left = 1 (độ cao 1)`, `right = 5 (độ cao 5)`.
  - Chiều rộng: `5 - 1 = 4`.
  - Chiều cao giới hạn: `min(1, 5) = 1`.
  - Dung tích bể: `4 * 1 = 4`. `max_area` giữ nguyên là `10`.
  - So sánh: Vì vách trái (`1`) thấp hơn vách phải (`5`), ta dịch con trỏ trái: `left = 2`.

- **Bước 3:** `left = 2 (độ cao 8)`, `right = 5 (độ cao 5)`.
  - Chiều rộng: `5 - 2 = 3`.
  - Chiều cao giới hạn: `min(8, 5) = 5`.
  - Dung tích bể: `3 * 5 = 15`. Cập nhật `max_area = 15`.
  - So sánh: Vì vách phải (`5`) thấp hơn vách trái (`8`), ta dịch con trỏ phải: `right = 4`.

- **Bước 4:** `left = 2 (độ cao 8)`, `right = 4 (độ cao 2)`.
  - Chiều rộng: `4 - 2 = 2`.
  - Chiều cao giới hạn: `min(8, 2) = 2`.
  - Dung tích bể: `2 * 2 = 4`. `max_area` giữ nguyên là `15`.
  - So sánh: Vì vách phải (`2`) thấp hơn vách trái (`8`), ta dịch con trỏ phải: `right = 3`.

- **Bước 5:** `left = 2 (độ cao 8)`, `right = 3 (độ cao 6)`.
  - Chiều rộng: `3 - 2 = 1`.
  - Chiều cao giới hạn: `min(8, 6) = 6`.
  - Dung tích bể: `1 * 6 = 6`. `max_area` giữ nguyên là `15`.
  - So sánh: Vì vách phải (`6`) thấp hơn vách trái (`8`), ta dịch con trỏ phải: `right = 2`.

- **Kết thúc:** Hai con trỏ gặp nhau (`left == right == 2`). Vòng lặp dừng. 
- **Kết quả:** Dung tích bể chứa lớn nhất tìm được là `15` (được tạo bởi vách ngăn chỉ số `2` độ cao `8` và vách ngăn chỉ số `5` độ cao `5`).

---

## Phân tích chuyên sâu: Tính đúng đắn về mặt toán học của việc di chuyển vách ngắn hơn

Nhiều người thường thắc mắc: *"Liệu việc bỏ qua tấm vách ngắn hơn có làm chúng ta bỏ lỡ một bể chứa tốt hơn được ghép từ tấm vách đó với một tấm vách khác ở bên trong không?"*

Hãy chứng minh điều này bằng toán học:
Giả sử ta có hai vách ngăn ở hai vị trí `L` và `R`, với `height[L] < height[R]`.
Dung tích bể hiện tại là:
$$\text{Area} = (R - L) \times \height[L]$$

Nếu chúng ta giữ lại vách ngắn `L` và dịch chuyển vách dài `R` sang một vị trí mới `R'` ở phía trong (`L < R' < R`):
- Chiều rộng mới chắc chắn giảm: `R' - L < R - L`.
- Chiều cao mới của bể sẽ là `min(height[L], height[R'])`. Giá trị này chắc chắn **không thể vượt quá** `height[L]` (vì nó bị chặn trên bởi `height[L]`).
- Do đó, dung tích bể mới:
  $$\text{Area'} = (R' - L) \times \min(\height[L], \height[R']) \le (R' - L) \times \height[L] < (R - L) \times \height[L] = \text{Area}$$

Như vậy, bất kỳ bể chứa nào được tạo ra bằng cách ghép vách `L` với một vách nằm bên trong đều chắc chắn có dung tích **nhỏ hơn** bể chứa hiện tại. Vì thế, việc loại bỏ hoàn toàn vách ngắn `L` ra khỏi danh sách xem xét là một quyết định toán học hoàn toàn chính xác và an toàn tuyệt đối.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử đặc trưng giúp khẳng định tính toàn diện của thiết kế:

- **Case 1 (Thung lũng sâu với hai bức tường biên cực cao):**
  - Đầu vào: `height = [10, 1, 1, 1, 10]`
  - Mô tả: Hai cột biên ngoài cùng vô cùng cao (`10`) và các cột ở giữa rất thấp (`1`). Cặp tối ưu chắc chắn là hai cột ngoài cùng.
  - Kết quả kỳ vọng: `40` (khoảng cách `4` nhân độ cao `10`)

- **Case 2 (Độ cao tăng dần đều - Chiều cao bù đắp khoảng cách):**
  - Đầu vào: `height = [1, 2, 3, 4, 5]`
  - Mô tả: Các cột tăng dần đều. Dung tích lớn nhất sẽ đạt được ở khu vực giữa mảng nơi có sự cân bằng tốt nhất giữa chiều rộng và chiều cao vách ngăn.
  - Kết quả kỳ vọng: `6` (ghép cặp chỉ số `1` độ cao `2` với chỉ số `4` độ cao `5` tạo ra `2 * 3 = 6`, hoặc ghép chỉ số `2` độ cao `3` với chỉ số `4` độ cao `5` tạo ra `3 * 2 = 6`).

- **Case 3 (Cột cao nhất đơn độc ở chính giữa):**
  - Đầu vào: `height = [2, 1, 20, 1, 2]`
  - Mô tả: Cột ở giữa rất cao (`20`), nhưng vì các cột xung quanh quá thấp, nó không thể ghép với cột nào khác để tạo ra dung tích vượt trội. Bể nước tốt nhất vẫn được tạo bởi hai cột biên ngoài cùng.
  - Kết quả kỳ vọng: `8` (khoảng cách `4` nhân độ cao giới hạn `2`)

- **Case 4 (Bể nước bậc thang đối xứng hoàn hảo):**
  - Đầu vào: `height = [5, 10, 2, 10, 5]`
  - Mô tả: Cột tốt nhất là ở vị trí `1` (độ cao `10`) và vị trí `3` (độ cao `10`).
  - Kết quả kỳ vọng: `20` (khoảng cách `2` nhân độ cao `10`)

- **Case 5 (Mảng tối thiểu chỉ có 2 cột biên):**
  - Đầu vào: `height = [100, 80]`
  - Mô tả: Trường hợp giới hạn dưới chỉ có đúng 2 phần tử, bể nước duy nhất có dung tích tạo bởi hai cột này.
  - Kết quả kỳ vọng: `80` (khoảng cách `1` nhân độ cao giới hạn `80`)

---

**Tổng kết:** Bài toán Container With Most Water dạy cho chúng ta một bài học sâu sắc về việc tận dụng các quy luật hình học và toán học để loại bỏ các trường hợp thừa một cách thông minh. Bằng cách luôn dịch chuyển tấm vách thấp hơn, chúng ta vừa bảo toàn được tính đúng đắn của lời giải, vừa chuyển đổi một thuật toán cồng kềnh thành một chương trình chạy trong cái nháy mắt.
