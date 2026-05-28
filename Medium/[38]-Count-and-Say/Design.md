# Tư duy thiết kế: Count and Say

## Vấn đề
Dãy "Count and Say" là một chuỗi các ký tự số được tạo ra dựa trên nguyên tắc đọc và đếm (Run-Length Encoding - RLE) chuỗi số trước đó.
Quy luật thiết lập dãy số này như sau:
- Số thứ nhất $n = 1$: `"1"`
- Số thứ $n$ được tạo ra bằng cách đọc thành tiếng chuỗi thứ $n - 1$: gom các chữ số giống nhau đứng cạnh nhau thành từng nhóm, đếm số lượng của chữ số đó, sau đó ghép [số lượng] + [chữ số].

Yêu cầu bài toán là tìm chuỗi số ở vị trí thứ $n$ ($1 \le n \le 30$) với hiệu năng và độ rõ ràng của mã nguồn tốt nhất.

---

## Giải pháp: Mã hóa độ dài chạy lặp tương tác (Run-Length Encoding)
Hãy tưởng tượng một người phát thanh viên đang truyền đạt một bản danh sách gồm rất nhiều chữ số qua bộ đàm. Thay vì đọc từng số một cách chậm chạp và dễ nhầm lẫn như "một, một, một, hai, hai, một", họ sẽ nhóm các chữ số giống nhau đứng liền kề lại và đọc một cách tóm gọn hơn: "ba con số một, hai con số hai, một con số một".
Cách đọc này rút ngắn đáng kể độ dài của thông điệp mà vẫn giữ nguyên vẹn thông tin gốc. Đây chính là bản chất của thuật toán **Mã hóa độ dài chạy** (Run-Length Encoding).

Để tìm chuỗi ở vị trí thứ $n$, chúng ta xuất phát từ gốc $n = 1$ là `"1"` và thực hiện biến đổi $n - 1$ lần:
1. Với mỗi chuỗi hiện tại, ta dùng kỹ thuật hai con trỏ hoặc một vòng lặp đơn để duyệt qua từng ký tự từ trái sang phải:
   - Khởi tạo con trỏ chạy `i` từ đầu chuỗi.
   - Với mỗi vị trí `i`, ta đếm số lượng ký tự liên tiếp giống với ký tự `curr = word[i]` bằng cách dịch chuyển một biến chạy `j` về phía trước miễn là `word[j] == curr`.
   - Số lượng ký tự trùng nhau sẽ là `count = j - i`.
   - Ta nối chuỗi biểu diễn của `count` và ký tự `curr` vào chuỗi kết quả mới.
   - Cập nhật con trỏ `i = j` để tiếp tục xử lý nhóm ký tự tiếp theo.
2. Lặp lại quá trình này cho đến khi đạt được phần tử thứ $n$ của dãy.

---

## Tại sao tối ưu?
- **Thời gian chạy:** Độ dài của các chuỗi trong dãy "Count and Say" tăng lên theo hàm số mũ khi $n$ lớn dần. Tuy nhiên, giới hạn của bài toán rất nhỏ ($n \le 30$). Trong mỗi bước chuyển đổi từ chuỗi thứ $k$ sang chuỗi thứ $k+1$, thuật toán chỉ cần duyệt qua chuỗi thứ $k$ đúng một lần duy nhất với độ phức tạp tuyến tính $O(L)$ (trong đó $L$ là độ dài của chuỗi hiện tại). Do đó, tổng thời gian thực thi là cực kỳ nhanh chóng và không có bất kỳ thao tác dư thừa nào.
- **Không gian bộ nhớ:** Thuật toán chỉ cần giữ lại chuỗi của bước trước đó để tạo ra chuỗi của bước hiện tại, tránh việc phải lưu trữ toàn bộ các chuỗi từ $1$ đến $n - 1$. Độ phức tạp không gian bổ sung (ngoài chuỗi kết quả) chỉ là $O(1)$.

---

## Minh họa từng bước chạy
Giả sử ta cần tìm kết quả với $n = 4$.

- **Khởi tạo:** Với $n = 1$, chuỗi ban đầu là `"1"`.
- **Lần lặp 1 ($n = 2$):** Đọc chuỗi `"1"`
  - Ký tự `'1'` xuất hiện 1 lần liên tiếp.
  - Chuỗi mới tạo ra: `"11"`.
- **Lần lặp 2 ($n = 3$):** Đọc chuỗi `"11"`
  - Ký tự `'1'` xuất hiện 2 lần liên tiếp.
  - Chuỗi mới tạo ra: `"21"`.
- **Lần lặp 3 ($n = 4$):** Đọc chuỗi `"21"`
  - Duyệt vị trí thứ 0: ký tự `'2'` xuất hiện 1 lần liên tiếp $\to$ chuỗi mới nhận thêm `"12"`.
  - Duyệt vị trí tiếp theo: ký tự `'1'` xuất hiện 1 lần liên tiếp $\to$ chuỗi mới nhận thêm `"11"`.
  - Chuỗi mới tạo ra: `"1211"`.

Kết quả trả về cho $n = 4$ là `"1211"`.

---

## Các trường hợp kiểm thử bổ sung

### Trường hợp 1: Giá trị đầu vào nhỏ nhất (Trường hợp cơ bản)
- **Đầu vào:**
  ```text
  1
  ```
- **Mô tả:** Kiểm tra giá trị biên dưới của đầu vào.
- **Đầu ra mong đợi:** `"1"`

### Trường hợp 2: Giá trị trung bình của dãy số
- **Đầu vào:**
  ```text
  5
  ```
- **Mô tả:** Đọc chuỗi của bước 4 (`"1211"`). Ta nhóm: một chữ số `'1'`, một chữ số `'2'`, hai chữ số `'1'`.
- **Đầu ra mong đợi:** `"111221"`

### Trường hợp 3: Giá trị lớn hơn trong dãy số
- **Đầu vào:**
  ```text
  6
  ```
- **Mô tả:** Đọc chuỗi của bước 5 (`"111221"`). Ta nhóm: ba chữ số `'1'`, hai chữ số `'2'`, một chữ số `'1'`.
- **Đầu ra mong đợi:** `"312211"`

---

**Tổng kết:**
Bằng cách áp dụng mô hình mã hóa độ dài chạy trực tiếp thông qua kỹ thuật duyệt tuyến tính đơn giản, thuật toán giải quyết bài toán một cách tự nhiên, mạch lạc, dễ hiểu và cực kỳ tối ưu về cả bộ nhớ lẫn tốc độ xử lý.
