# Tư duy thiết kế: Lucky Number

## Vấn đề

Bài toán yêu cầu tìm số lượng số nguyên dương không vượt quá $n$ mà các chữ số cấu thành chỉ gồm `4` và `7`. Đây được định nghĩa là các "số may mắn".
Ràng buộc: $1 \le n \le 10^9$.

---

## Ý tưởng thiết kế

Hãy tưởng tượng bạn cần tìm các cuốn sách có số sê-ri đặc biệt chỉ chứa chữ số `4` và `7` trên một kệ sách dài từ 1 đến $n$. 

Thay vì đi kiểm tra từng cuốn sách một (tương tự thuật toán duyệt tuyến tính từ $1$ đến $n$), việc này sẽ cực kỳ tốn thời gian khi $n$ lên tới 1 tỷ. Thay vào đó, bạn có thể tự lập trước một tấm thẻ mục lục nhỏ ghi lại toàn bộ các số sê-ri đặc biệt này. Vì các số sê-ri đặc biệt này rất hiếm, tấm thẻ mục lục chỉ ghi nhận khoảng 1000 số.

Khi có một yêu cầu kiểm tra cho số $n$ bất kỳ, bạn chỉ cần rút tấm thẻ mục lục đã được sắp xếp thứ tự ra, áp dụng quy trình lật trang sách (tìm kiếm nhị phân) để xác định xem số $n$ nằm ở vị trí nào trong danh sách. Vị trí tìm thấy sẽ ngay lập tức cho biết có bao nhiêu số sê-ri thỏa mãn.

---

## Phân tích không gian tìm kiếm

Một số may mắn có độ dài $L$ chữ số sẽ có chính xác $2^L$ cách tạo lập (do mỗi vị trí chữ số chỉ có hai sự lựa chọn là `4` hoặc `7`).

Với giới hạn $n \le 10^9$, số may mắn lớn nhất có thể đạt được chỉ có tối đa 9 chữ số (vì số may mắn có 10 chữ số nhỏ nhất là `4444444444` đã lớn hơn $10^9$).

Tổng số lượng số may mắn nằm trong phạm vi từ $1$ đến $10^9$ là:
$$2^1 + 2^2 + 2^3 + \dots + 2^9 = 1022 \text{ số}$$

Với số lượng phần tử cực kỳ nhỏ như trên, việc sinh trước toàn bộ danh sách số may mắn là giải pháp tối ưu nhất.

---

## Giải thích chi tiết thuật toán

Giải pháp bao gồm hai giai đoạn chính:

Giai đoạn sinh danh sách số may mắn:
- Sử dụng thuật toán duyệt theo chiều rộng (BFS) với hàng đợi để sinh số.
- Bắt đầu đưa hai số nền tảng là `4` và `7` vào hàng đợi.
- Tại mỗi bước, rút một số $x$ từ hàng đợi ra, lưu vào danh sách kết quả, sau đó tạo ra hai số mới bằng cách ghép thêm chữ số `4` và `7` vào cuối:
  - $x_{new1} = x \times 10 + 4$
  - $x_{new2} = x \times 10 + 7$
- Nếu số mới sinh ra vẫn nhỏ hơn hoặc bằng giới hạn $10^9$, tiếp tục đưa số đó vào hàng đợi để làm cơ sở sinh các số lớn hơn.

Giai đoạn truy vấn:
- Sau khi kết thúc quá trình sinh, sắp xếp danh sách thu được theo thứ tự tăng dần.
- Dùng hàm tìm kiếm nhị phân `std::upper_bound` để xác định vị trí của phần tử đầu tiên lớn hơn $n$. Khoảng cách từ đầu danh sách đến vị trí này chính là số lượng số may mắn cần tìm.

---

## Mô phỏng từng bước chạy thực tế

Giả sử cần tìm số lượng số may mắn nhỏ hơn hoặc bằng $n = 50$:

- Bước 1: Khởi tạo hàng đợi với `[4, 7]`.
- Bước 2: Rút `4` khỏi hàng đợi, thêm vào danh sách kết quả. Sinh tiếp `44` và `47` đưa vào hàng đợi.
- Bước 3: Rút `7` khỏi hàng đợi, thêm vào danh sách kết quả. Sinh tiếp `74` và `77` đưa vào hàng đợi.
- Bước 4: Quá trình này tiếp tục lặp lại cho đến khi các số sinh ra vượt quá $10^9$.
- Bước 5: Sắp xếp danh sách kết quả ta được: `[4, 7, 44, 47, 74, 77, 444, 447, ...]`
- Bước 6: Với truy vấn $n = 50$, thuật toán tìm kiếm nhị phân xác định phần tử đầu tiên lớn hơn $50$ là `74`.
- Bước 7: Các phần tử đứng trước `74` là `[4, 7, 44, 47]`. Số lượng phần tử là $4$.

---

## Phân tích hiệu năng

Thời gian thực thi:
- Thời gian sinh danh sách: Chỉ mất tối đa $1022$ phép toán để sinh toàn bộ dữ liệu mẫu (thực thi trong chưa đầy $1$ mili giây).
- Thời gian truy vấn: Tìm kiếm nhị phân trên mảng có kích thước $1022$ chỉ tốn tối đa khoảng $10$ phép so sánh ($O(\log(1022))$).
- Tổng độ phức tạp thời gian: $O(2^L + \log(2^L))$ cho toàn bộ quá trình, hoàn toàn tối ưu và chạy tức thời.

Không gian bộ nhớ:
- Chỉ cần lưu trữ một mảng gồm 1022 số nguyên kiểu `long long`.
- Độ phức tạp không gian: $O(2^L)$ với $L \le 9$, tiêu tốn chưa đến $10$ KB bộ nhớ.

---

## Các trường hợp kiểm thử bổ sung

Trường hợp kiểm thử 1:
- Đầu vào: `4`
- Đầu ra: `1`
- Giải thích: Chỉ có duy nhất một số may mắn nhỏ hơn hoặc bằng 4 là số `4`.

Trường hợp kiểm thử 2:
- Đầu vào: `45`
- Đầu ra: `3`
- Giải thích: Các số may mắn thỏa mãn là `4`, `7`, `44`. Số tiếp theo là `47` đã lớn hơn 45.

Trường hợp kiểm thử 3:
- Đầu vào: `500`
- Đầu ra: `10`
- Giải thích: 
  - Nhóm có 1 chữ số: `4`, `7` (2 số)
  - Nhóm có 2 chữ số: `44`, `47`, `74`, `77` (4 số)
  - Nhóm có 3 chữ số $\le 500$: `444`, `447`, `474`, `477` (4 số)
  - Tổng cộng có $2 + 4 + 4 = 10$ số.

Trường hợp kiểm thử 4:
- Đầu vào: `1000000000` (1 tỷ)
- Đầu ra: `1022`
- Giải thích: Đây là giới hạn lớn nhất của đầu vào. Kết quả bao gồm toàn bộ số may mắn có từ 1 đến 9 chữ số.
