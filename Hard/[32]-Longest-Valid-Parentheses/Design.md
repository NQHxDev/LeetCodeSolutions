# Tư duy thiết kế: Longest Valid Parentheses

## Vấn đề

Cho một chuỗi ký tự chỉ chứa hai loại ký tự là `'('` và `')'`. Hãy tìm độ dài của chuỗi con chứa các cặp ngoặc hợp lệ dài nhất liên tục.
Ràng buộc: Độ dài chuỗi $s$ có thể lên tới $3 \times 10^4$.

---

## Ý tưởng thiết kế

Hãy tưởng tượng bạn đang kiểm tra độ chắc chắn của một cây cầu treo được xây dựng từ các nhịp xích móc nối tiếp nhau. 
- Mỗi dấu ngoặc mở `'('` đóng vai trò là một móc treo nhô ra từ bên trái.
- Mỗi dấu ngoặc đóng `')'` đóng vai trò là một vòng khoen khóa từ bên phải.
- Một nhịp cầu hợp lệ vững chắc được tạo ra khi một móc treo được ghép cặp hoàn hảo với một vòng khoen khóa ngay sau nó.

Để xác định được nhịp cầu hợp lệ liên tục dài nhất, bạn sử dụng một **ngăn xếp các điểm neo** (stack of anchor points) để ghi lại tọa độ (chỉ số index) của các điểm đứt gãy hoặc các móc treo chưa được ghép đôi:
- Ban đầu, ta đặt một điểm neo giả tưởng ở vị trí `-1` để đại diện cho điểm bắt đầu của cây cầu trước khi có bất kỳ móc treo nào.
- Khi gặp một móc treo `'('`, ta đẩy tọa độ của nó vào ngăn xếp để ghi nhớ vị trí.
- Khi gặp một vòng khoen `')'`, ta thực hiện lấy điểm neo trên cùng ra khỏi ngăn xếp (ghép cặp thành công).
  - Nếu trong ngăn xếp vẫn còn điểm neo khác: Nhịp cầu hợp lệ hiện tại sẽ kéo dài từ điểm neo ở đỉnh ngăn xếp cho tới vị trí hiện tại. Độ dài nhịp cầu được tính bằng: `chỉ số hiện tại - điểm neo ở đỉnh ngăn xếp`. Ta cập nhật độ dài kỷ lục nếu nhịp này dài hơn các nhịp trước đó.
  - Nếu ngăn xếp trống rỗng: Nghĩa là vòng khoen `')'` này bị thừa và trở thành một điểm đứt gãy mới của cây cầu. Ta lập tức đẩy chỉ số của vòng khoen này vào ngăn xếp để làm mốc neo mới cho các nhịp cầu phía sau.

---

## Phân tích không gian tìm kiếm

Chuỗi con hợp lệ có thể xuất hiện rải rác hoặc lồng nhau ở bất kỳ vị trí nào trong chuỗi.
Việc duyệt và tính toán trực tiếp độ dài hợp lệ thông qua việc lưu trữ chỉ số biên bằng ngăn xếp cho phép chúng ta tìm ra đáp án mà không cần duyệt lại các chuỗi con đã đi qua, giới hạn không gian tìm kiếm về dạng tuyến tính.

---

## Giải thích chi tiết thuật toán

Các bước thực hiện cụ thể:
1. Khởi tạo biến `maxLength = 0` để lưu độ dài lớn nhất và một ngăn xếp `std::stack<int> st` lưu trữ các chỉ số.
2. Đẩy điểm neo khởi tạo `-1` vào ngăn xếp `st`.
3. Duyệt qua từng ký tự `s[i]` tại chỉ số `i` từ `0` đến `n - 1`:
   - Nếu `s[i] == '('`: Đẩy chỉ số `i` vào ngăn xếp `st`.
   - Nếu `s[i] == ')'`:
     - Loại bỏ phần tử đỉnh ngăn xếp: `st.pop()`.
     - Nếu sau khi pop, ngăn xếp trở nên **trống rỗng**: Điều đó có nghĩa là dấu ngoặc đóng hiện tại không thể ghép đôi với bất kỳ dấu ngoặc mở nào trước đó. Ta đẩy chỉ số `i` vào ngăn xếp để làm điểm neo giới hạn mới.
     - Nếu ngăn xếp **không trống rỗng**: Cặp ngoặc đã được ghép đôi hợp lệ. Ta tính độ dài chuỗi hợp lệ hiện tại bằng công thức: `i - st.top()`, sau đó cập nhật `maxLength = max(maxLength, i - st.top())`.
4. Trả về giá trị `maxLength`.

---

## Mô phỏng từng bước chạy thực tế

Xét chuỗi đầu vào `s = ")()())"`:

- Khởi tạo: `st = [-1]`, `maxLength = 0`.
- Bước 1 (với `i = 0`, ký tự `')'`):
  - Pop phần tử đỉnh: ngăn xếp trở nên trống rỗng.
  - Đẩy chỉ số hiện tại `0` vào: `st = [0]`.
- Bước 2 (với `i = 1`, ký tự `'('`):
  - Đẩy chỉ số `1` vào ngăn xếp: `st = [0, 1]`.
- Bước 3 (với `i = 2`, ký tự `')'`):
  - Pop phần tử đỉnh: `st` còn lại `[0]`.
  - Tính độ dài: `2 - st.top() = 2 - 0 = 2`. Cập nhật `maxLength = max(0, 2) = 2`.
- Bước 4 (với `i = 3`, ký tự `'('`):
  - Đẩy chỉ số `3` vào ngăn xếp: `st = [0, 3]`.
- Bước 5 (với `i = 4`, ký tự `')'`):
  - Pop phần tử đỉnh: `st` còn lại `[0]`.
  - Tính độ dài: `4 - st.top() = 4 - 0 = 4`. Cập nhật `maxLength = max(2, 4) = 4`.
- Bước 6 (với `i = 5`, ký tự `')'`):
  - Pop phần tử đỉnh: ngăn xếp trở nên trống rỗng.
  - Đẩy chỉ số `5` vào: `st = [5]`.

Kết quả cuối cùng thu được là `maxLength = 4` (tương ứng với chuỗi con `"()()"` từ chỉ số 1 đến 4).

---

## Phân tích hiệu năng

Thời gian thực thi:
- Thuật toán chỉ thực hiện một lượt duyệt qua chuỗi từ đầu đến cuối.
- Các thao tác thêm, xóa và tra cứu trên ngăn xếp đều hoạt động trong thời gian hằng số $O(1)$.
- Độ phức tạp thời gian: $O(n)$, tối ưu và chạy cực kỳ nhanh ngay cả khi chiều dài chuỗi đạt mức tối đa.

Không gian bộ nhớ:
- Ngăn xếp có thể lưu trữ tối đa $n + 1$ phần tử trong trường hợp chuỗi chứa toàn dấu ngoặc mở `'('`.
- Độ phức tạp không gian: $O(n)$ bộ nhớ bổ trợ cho ngăn xếp.

---

## Các trường hợp kiểm thử bổ sung

Trường hợp kiểm thử 1:
- Đầu vào: `""` (chuỗi rỗng) hoặc `"))))"` (không có cặp ngoặc mở nào để ghép đôi)
- Đầu ra: `0`
- Giải thích: Không tạo thành bất kỳ chuỗi con hợp lệ nào.

Trường hợp kiểm thử 2:
- Đầu vào: `"(())"` (ngoặc lồng nhau)
- Đầu ra: `4`
- Giải thích: Toàn bộ chuỗi là một cặp ngoặc lồng nhau hợp lệ hoàn chỉnh.

Trường hợp kiểm thử 3:
- Đầu vào: `"())(())"` (các nhóm ngoặc bị phân tách bởi dấu ngoặc đóng thừa)
- Đầu ra: `4`
- Giải thích: Có hai nhóm ngoặc hợp lệ là `"()"` (độ dài 2) và `"(())"` (độ dài 4), giá trị lớn nhất là 4.

Trường hợp kiểm thử 4:
- Đầu vào: `"()((("` (chuỗi kết thúc bằng các dấu ngoặc mở thừa không có dấu đóng)
- Đầu ra: `2`
- Giải thích: Chỉ có nhóm `"()"` ở đầu là hợp lệ, các dấu ngoặc mở ở cuối bị bỏ qua vì không có đối tác ghép cặp.
