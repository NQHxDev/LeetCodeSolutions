# Tư duy thiết kế: Valid Sudoku

## Vấn đề

Xác định xem một bảng Sudoku kích thước $9 \times 9$ đã được điền một phần có hợp lệ hay không. Chỉ cần kiểm tra các ô đã được điền số theo ba quy tắc:
- Mỗi hàng phải chứa các chữ số từ `1` đến `9` không trùng lặp.
- Mỗi cột phải chứa các chữ số từ `1` đến `9` không trùng lặp.
- Mỗi hộp $3 \times 3$ trong số 9 hộp của bảng phải chứa các chữ số từ `1` đến `9` không trùng lặp.

---

## Ý tưởng thiết kế

Hãy tưởng tượng bạn đang quản lý một tòa nhà văn phòng có 9 tầng (tương ứng với 9 hàng), 9 dãy phòng (tương ứng với 9 cột) và được chia thành 9 khu vực phòng ban lớn kích thước $3 \times 3$. Nhiệm vụ của bạn là kiểm tra xem việc phân bổ 9 loại thiết bị đặc chủng (được đánh số từ 1 đến 9) có xảy ra xung đột hay không. 

Để kiểm tra nhanh nhất, bạn chuẩn bị sẵn ba cuốn sổ tay ghi chép (logbooks):
- Cuốn sổ thứ nhất dùng để ghi nhận các thiết bị đã có ở mỗi tầng.
- Cuốn sổ thứ hai dùng để ghi nhận các thiết bị đã có ở mỗi dãy phòng.
- Cuốn sổ thứ ba dùng để ghi nhận các thiết bị đã có ở từng khu vực phòng ban lớn.

Khi đi kiểm tra từng phòng, nếu gặp một căn phòng tại tầng $r$, dãy $c$ đang lắp thiết bị $val$:
- Bạn chỉ cần mở các cuốn sổ tay ra tra cứu. Nếu thiết bị $val$ này đã được ghi nhận tại tầng $r$, hoặc tại dãy $c$, hoặc tại khu vực lớn tương ứng, bạn kết luận ngay việc phân bổ này vi phạm quy tắc (không hợp lệ).
- Nếu chưa có, bạn ghi nhận thông tin thiết bị này vào cả 3 cuốn sổ và tiếp tục kiểm tra phòng kế tiếp.
- Nếu kiểm tra toàn bộ tòa nhà mà không phát hiện xung đột, việc phân bổ là hoàn toàn hợp lệ.

---

## Giải thích chi tiết thuật toán

Để tối ưu hóa thời gian tra cứu, ta sử dụng các mảng đánh dấu hai chiều đóng vai trò là các cuốn sổ tay với thời gian truy cập hằng số $O(1)$:
- `rows[9][9]`: `rows[r][val]` lưu trạng thái chữ số `val + 1` đã xuất hiện ở hàng `r` hay chưa.
- `cols[9][9]`: `cols[c][val]` lưu trạng thái chữ số `val + 1` đã xuất hiện ở cột `c` hay chưa.
- `boxes[9][9]`: `boxes[b][val]` lưu trạng thái chữ số `val + 1` đã xuất hiện ở hộp thứ `b` hay chưa.

Công thức xác định chỉ số hộp $3 \times 3$ (được đánh số từ 0 đến 8 từ trái sang phải, từ trên xuống dưới) dựa vào tọa độ dòng `r` và cột `c`:
$$b = \lfloor r / 3 \rfloor \times 3 + \lfloor c / 3 \rfloor$$

Thuật toán duyệt qua từng ô `(r, c)` của bảng:
- Nếu ô trống (chứa ký tự `.`), ta bỏ qua.
- Nếu ô chứa chữ số ký tự `ch`:
  - Chuyển đổi ký tự thành chỉ số số nguyên: `val = ch - '1'` (giá trị từ 0 đến 8).
  - Tra cứu trạng thái: Nếu `rows[r][val]`, `cols[c][val]`, hoặc `boxes[b][val]` đã là `true`, lập tức kết luận bảng không hợp lệ và trả về `false`.
  - Nếu chưa xuất hiện, cập nhật trạng thái của cả ba mảng đánh dấu này thành `true`.
- Nếu duyệt xong toàn bộ 81 ô mà không gặp xung đột, trả về `true`.

---

## Mô phỏng từng bước chạy thực tế

Giả sử chúng ta duyệt qua một bảng Sudoku và gặp hai ô đã được điền như sau:
- Ô thứ nhất tại tọa độ `(0, 0)` chứa số `'5'`.
- Ô thứ hai tại tọa độ `(0, 2)` chứa số `'5'`.

Các bước xử lý của thuật toán:

1. Xét ô `(0, 0)` chứa số `'5'`:
   - Chỉ số hàng `r = 0`, cột `c = 0`.
   - Xác định chỉ số hộp: $b = \lfloor 0 / 3 \rfloor \times 3 + \lfloor 0 / 3 \rfloor = 0$.
   - Giá trị số nguyên tương ứng: `val = 5 - 1 = 4`.
   - Kiểm tra mảng đánh dấu: `rows[0][4]`, `cols[0][4]`, `boxes[0][4]` đều đang là `false`.
   - Cập nhật trạng thái: Đánh dấu `rows[0][4] = true`, `cols[0][4] = true`, `boxes[0][4] = true`.

2. Xét ô `(0, 2)` chứa số `'5'`:
   - Chỉ số hàng `r = 0`, cột `c = 2`.
   - Xác định chỉ số hộp: $b = \lfloor 0 / 3 \rfloor \times 3 + \lfloor 2 / 3 \rfloor = 0$.
   - Giá trị số nguyên tương ứng: `val = 5 - 1 = 4`.
   - Kiểm tra mảng đánh dấu: Phát hiện `rows[0][4]` đã là `true` (xung đột trên cùng hàng 0).
   - Kết luận: Thuật toán dừng ngay lập tức và trả về `false`.

---

## Phân tích hiệu năng

Thời gian thực thi:
- Bảng Sudoku luôn có kích thước cố định là $9 \times 9 = 81$ ô.
- Tại mỗi ô, việc tính toán chỉ số hộp và tra cứu/ghi nhận trong mảng hai chiều có độ phức tạp hằng số $O(1)$.
- Do đó, độ phức tạp thời gian tổng quát là $O(1)$ (chạy trong chưa đầy $0.1$ ms), tối ưu tuyệt đối.

Không gian bộ nhớ:
- Chúng ta chỉ sử dụng ba mảng đánh dấu kích thước cố định $9 \times 9$.
- Bộ nhớ tiêu thụ thực tế chỉ khoảng vài trăm byte.
- Độ phức tạp không gian: $O(1)$, tối ưu tuyệt đối.

---

## Các trường hợp kiểm thử bổ sung

Trường hợp kiểm thử 1:
- Đầu vào: Bảng hoàn toàn trống (tất cả các ô đều chứa ký tự `'.'`).
- Đầu ra: `true`
- Giải thích: Không có số nào được điền, do đó không xảy ra bất kỳ xung đột nào. Bảng mặc định hợp lệ.

Trường hợp kiểm thử 2:
- Đầu vào: Bảng có hai số giống nhau nằm trên cùng một cột, ví dụ ô `(0, 5)` chứa `'9'` và ô `(8, 5)` chứa `'9'`.
- Đầu ra: `false`
- Giải thích: Chữ số `'9'` xuất hiện hai lần trên cột 5.

Trường hợp kiểm thử 3:
- Đầu vào: Bảng có hai số giống nhau nằm trong cùng một hộp $3 \times 3$, ví dụ ô `(0, 0)` chứa `'3'` và ô `(2, 2)` chứa `'3'`.
- Đầu ra: `false`
- Giải thích: Cả hai ô đều thuộc hộp số 0 (góc trên cùng bên trái), dẫn đến trùng lặp chữ số trong cùng một hộp mặc dù chúng nằm ở các hàng và cột khác nhau.

Trường hợp kiểm thử 4:
- Đầu vào: Bảng chứa các chữ số từ `1` đến `9` được điền rải rác trên các ô, đảm bảo mỗi dòng, mỗi cột và mỗi hộp $3 \times 3$ chỉ chứa tối đa một chữ số thuộc mỗi loại.
- Đầu ra: `true`
- Giải thích: Bảng thỏa mãn toàn bộ 3 quy tắc hợp lệ của Sudoku.
