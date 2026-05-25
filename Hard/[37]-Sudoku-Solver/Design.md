# Tư duy thiết kế: Sudoku Solver

## Vấn đề

Giải một bảng Sudoku kích thước $9 \times 9$ bằng cách điền vào các ô trống (được biểu diễn bằng ký tự `'.'`). Bảng Sudoku đầu vào được đảm bảo luôn có duy nhất một lời giải hợp lệ.

---

## Ý tưởng thiết kế

Hãy tưởng tượng bạn là một nhà tổ chức sự kiện đang xếp chỗ ngồi cho các vị khách VIP (được đánh số từ 1 đến 9) vào một phòng tiệc gồm 9 dãy bàn ngang (hàng), 9 dãy bàn dọc (cột) và chia thành 9 khu vực gia đình (hộp $3 \times 3$). Một số vị khách đã ngồi sẵn vào vị trí cố định của họ.

Để xếp chỗ cho các ghế còn trống mà không gây ra bất kỳ xung đột nào, bạn áp dụng chiến thuật **Quay lui (Backtracking - Thử và Sai)**:
- Bạn đi tới từng chiếc ghế trống theo thứ tự.
- Tại mỗi chiếc ghế, bạn thử xếp lần lượt các vị khách từ 1 đến 9. Nếu xếp vị khách nào mà không vi phạm quy tắc (không trùng số ở cùng hàng, cùng cột, và cùng khu vực), bạn cho vị khách đó tạm thời ngồi lại đó và di chuyển sang chiếc ghế trống tiếp theo.
- Nếu đến một chiếc ghế nào đó mà bạn đã thử xếp tất cả các vị khách từ 1 đến 9 nhưng đều vi phạm quy tắc, điều đó chứng tỏ cách xếp chỗ ở một vài ghế trước đó đã bị sai. Bạn lập tức quay lại chiếc ghế trống ngay trước đó, mời vị khách đang ngồi ở đó đứng lên (quay lui), thử xếp vị khách có số lớn hơn cho ghế này, rồi tiếp tục đi tiếp.
- Cứ lặp đi lặp lại như vậy, khi tất cả các ghế trống đều được lấp đầy hợp lệ, bạn đã hoàn thành việc xếp chỗ cho phòng tiệc.

---

## Phân tích không gian tìm kiếm

Mỗi ô trống trong số tối đa 81 ô của bảng Sudoku có thể nhận một trong 9 giá trị từ `1` đến `9`. Do đó, không gian tìm kiếm tối đa của bài toán trong trường hợp xấu nhất là $9^{81}$. 

Tuy nhiên, nhờ vào các ràng buộc chặt chẽ của luật chơi Sudoku (mỗi số chỉ xuất hiện một lần trên hàng, cột, hộp), số lượng nhánh tìm kiếm thực tế bị cắt tỉa (pruning) đi rất nhanh chóng. Điều này giúp thuật toán quay lui hoạt động cực kỳ hiệu quả và hoàn thành trong thời gian rất ngắn.

---

## Giải thích chi tiết thuật toán

Để tối ưu hóa thời gian kiểm tra tính hợp lệ khi thử điền một số, ta sử dụng ba mảng đánh dấu hai chiều để quản lý trạng thái trong thời gian hằng số $O(1)$:
- `rows[9][9]`: `rows[r][val]` là `true` nếu chữ số `val + 1` đã được điền ở hàng `r`.
- `cols[9][9]`: `cols[c][val]` là `true` nếu chữ số `val + 1` đã được điền ở cột `c`.
- `boxes[9][9]`: `boxes[b][val]` là `true` nếu chữ số `val + 1` đã được điền ở hộp thứ `b`.

Chỉ số hộp $b$ (từ 0 đến 8) của ô `(r, c)` được tính theo công thức:
$$b = \lfloor r / 3 \rfloor \times 3 + \lfloor c / 3 \rfloor$$

Quy trình thực hiện:
- **Bước 1 (Khởi tạo):** Duyệt qua toàn bộ bảng ban đầu. Với mỗi ô `(r, c)` có sẵn chữ số `ch`, ta đánh dấu `rows[r][ch - '1'] = cols[c][ch - '1'] = boxes[b][ch - '1'] = true`.
- **Bước 2 (Tìm kiếm quay lui):** Hàm đệ quy `solve(r, c)` thực hiện điền số:
  - Nếu `r == 9`, ta đã điền xong toàn bộ bảng hợp lệ, trả về `true`.
  - Nếu `c == 9`, ta chuyển sang dòng tiếp theo: gọi `solve(r + 1, 0)`.
  - Nếu ô `(r, c)` đã có sẵn số, ta chuyển sang ô tiếp theo: gọi `solve(r, c + 1)`.
  - Nếu ô `(r, c)` là ô trống `'.'`:
    - Thử điền lần lượt chữ số `d` từ `1` đến `9` (`val = d - 1`):
      - Nếu `rows[r][val]`, `cols[c][val]`, và `boxes[b][val]` đều là `false`:
        - Điền chữ số `d` vào ô `(r, c)`.
        - Đánh dấu trạng thái của số `d` ở hàng, cột, hộp là `true`.
        - Gọi đệ quy `solve(r, c + 1)`. Nếu đệ quy trả về `true` (tìm thấy lời giải), dừng toàn bộ quá trình và trả về `true`.
        - Nếu đệ quy trả về `false` (nhánh này thất bại), thực hiện **quay lui**: Đặt lại ô `(r, c) = '.'` và xóa đánh dấu trạng thái thành `false` để thử chữ số tiếp theo.
    - Nếu thử hết cả 9 chữ số mà không có số nào thỏa mãn, trả về `false`.

---

## Mô phỏng từng bước chạy thực tế

Giả sử tại ô trống đầu tiên `(0, 2)` thuộc hộp `0`, thuật toán cần chọn số điền vào:

- Thử số `1`: Phát hiện hàng 0 đã có sẵn số 1 (`rows[0][0] == true`). Bỏ qua.
- Thử số `2`: Hàng 0, cột 2 và hộp 0 đều chưa có số 2.
  - Tạm thời điền `'2'` vào ô `(0, 2)`.
  - Đánh dấu `rows[0][1] = cols[2][1] = boxes[0][1] = true`.
  - Tiến sang ô tiếp theo `(0, 3)`.
- Giả sử sau khi đi sâu vào các nhánh đệ quy tiếp theo, thuật toán gặp một ô trống khác không thể điền bất kỳ số nào từ 1 đến 9. Nhánh đệ quy này trả về `false`.
- Thuật toán quay lui về ô `(0, 2)`:
  - Khôi phục ô `(0, 2)` về lại ký tự `'.'`.
  - Xóa đánh dấu trạng thái: đặt `rows[0][1] = cols[2][1] = boxes[0][1] = false`.
  - Tiếp tục thử số `3` cho ô `(0, 2)` và lặp lại quá trình.

---

## Phân tích hiệu năng

Thời gian thực thi:
- Nhờ cấu trúc mảng đánh dấu hai chiều, việc kiểm tra và cập nhật trạng thái diễn ra trong thời gian hằng số $O(1)$.
- Kỹ thuật cắt tỉa nhánh (pruning) giúp giảm thiểu số lượng phép thử xuống mức tối thiểu.
- Độ phức tạp thời gian: $O(9^m)$ với $m$ là số lượng ô trống, nhưng thời gian thực thi thực tế vô cùng nhanh (chỉ từ $1$ đến $10$ ms), đáp ứng hoàn hảo các giới hạn thời gian.

Không gian bộ nhớ:
- Ngăn xếp đệ quy có độ sâu tối đa bằng số lượng ô của bảng Sudoku là 81.
- Ba mảng đánh dấu hai chiều chiếm lượng bộ nhớ không đáng kể (vài trăm byte).
- Độ phức tạp không gian: $O(1)$ (hoặc $O(81)$ cho ngăn xếp đệ quy), cực kỳ tiết kiệm bộ nhớ.

---

## Các trường hợp kiểm thử bổ sung

Trường hợp kiểm thử 1:
- Đầu vào: Bảng Sudoku gần như đã được giải xong (chỉ còn duy nhất 1 ô trống).
- Đầu ra: Ô trống được điền đúng chữ số còn thiếu duy nhất đảm bảo tính hợp lệ.

Trường hợp kiểm thử 2:
- Đầu vào: Bảng Sudoku hoàn toàn trống (tất cả 81 ô đều là `'.'`).
- Đầu ra: Tạo ra một bảng Sudoku hoàn thành hợp lệ (đáp án đầu tiên tìm thấy).

Trường hợp kiểm thử 3:
- Đầu vào: Bảng Sudoku có cấu trúc đối xứng khó, yêu cầu nhiều bước đệ quy thử sai sâu trước khi tìm ra lời giải chính xác.
- Đầu ra: Bảng Sudoku được giải đúng và hoàn chỉnh.
