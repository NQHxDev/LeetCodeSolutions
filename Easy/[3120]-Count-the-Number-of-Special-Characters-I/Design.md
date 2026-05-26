# Tài Liệu Thiết Kế Thuật Toán: Count the Number of Special Characters I

## Bản Chất Tập Hợp Và Sự Đối Xứng Chữ Cái

Chúng ta có thể hình dung bài toán này tương tự như một sự kiện có hai danh sách check-in tại cổng ra vào:
*   Danh sách A: Dành cho các khách hàng viết tên bằng chữ thường.
*   Danh sách B: Dành cho các khách hàng viết tên bằng chữ hoa.

Mục tiêu là đếm xem có bao nhiêu người đăng ký hợp lệ ở **cả hai** danh sách. Một người chỉ được tính là "đặc biệt" và đếm tối đa một lần nếu họ xuất hiện đồng thời trong Danh sách A và Danh sách B, bất kể số lần họ ra vào (check-in) là bao nhiêu.

---

## Giải Pháp: Sử Dụng Mảng Đánh Dấu Tần Suất Cố Định

Để giải quyết bài toán một cách tối ưu, ta sử dụng hai mảng đánh dấu kích thước cố định đại diện cho 26 chữ cái tiếng Anh:
1.  **Đánh dấu chữ thường**: Một mảng boolean `has_lower` gồm 26 phần tử (tương ứng với các chữ cái từ 'a' đến 'z').
2.  **Đánh dấu chữ hoa**: Một mảng boolean `has_upper` gồm 26 phần tử (tương ứng với các chữ cái từ 'A' đến 'Z').

Quy trình thực hiện:
1.  Duyệt qua từng ký tự `ch` trong chuỗi `word`:
    *   Nếu `ch` là chữ thường (`'a' <= ch && ch <= 'z'`): Đánh dấu vị trí tương ứng trong mảng `has_lower` là `true` (chỉ số bằng `ch - 'a'`).
    *   Nếu `ch` là chữ hoa (`'A' <= ch && ch <= 'Z'`): Đánh dấu vị trí tương ứng trong mảng `has_upper` là `true` (chỉ số bằng `ch - 'A'`).
2.  Khởi tạo biến đếm `count = 0`.
3.  Duyệt qua 26 chỉ số đại diện cho 26 chữ cái (từ $0$ đến $25$):
    *   Nếu cả `has_lower[i]` và `has_upper[i]` đều có giá trị `true`, tăng biến đếm `count` lên 1.
4.  Trả về `count`.

---

## Tại Sao Tối Ưu?

*   **Thời gian thực thi:** Thuật toán chỉ cần duyệt qua chuỗi `word` đúng một lần để đánh dấu tần suất. Sau đó, thực hiện vòng lặp cố định 26 lần để kiểm tra kết quả. Do đó độ phức tạp thời gian là $O(N)$ với $N$ là độ dài chuỗi. Đây là mức tối ưu tuyệt đối vì ta bắt buộc phải xem toàn bộ chuỗi ít nhất một lần.
*   **Không gian bộ nhớ:** Việc sử dụng các mảng boolean kích thước 26 chỉ chiếm một lượng bộ nhớ hằng số cực kỳ nhỏ và cố định, không phụ thuộc vào độ dài của chuỗi đầu vào. Độ phức tạp không gian là $O(1)$.

---

## Minh Họa Từng Bước Chạy

Xét chuỗi đầu vào: `word = "abAcBa"`

Bước 1: Khởi tạo các mảng đánh dấu 26 phần tử với giá trị `false`.

Bước 2: Duyệt qua từng ký tự và đánh dấu:
*   Ký tự `'a'`: `has_lower[0] = true`
*   Ký tự `'b'`: `has_lower[1] = true`
*   Ký tự `'A'`: `has_upper[0] = true`
*   Ký tự `'c'`: `has_lower[2] = true`
*   Ký tự `'B'`: `has_upper[1] = true`
*   Ký tự `'a'`: `has_lower[0] = true`

Bước 3: Duyệt kiểm tra 26 chữ cái:
*   Chỉ số $0$ (chữ cái 'a'): Cả `has_lower[0]` và `has_upper[0]` đều `true` $\to$ `count = 1`.
*   Chỉ số $1$ (chữ cái 'b'): Cả `has_lower[1]` and `has_upper[1]` đều `true` $\to$ `count = 2`.
*   Chỉ số $2$ (chữ cái 'c'): Chỉ có `has_lower[2] = true`, `has_upper[2] = false` $\to$ giữ nguyên.
*   Các chỉ số khác đều `false`.

Kết quả trả về: `2`.

---

## Các Trường Hợp Kiểm Thử Bổ Sung

### Trường hợp 1: Chuỗi rỗng hoặc không có chữ cái đặc biệt nào

*   **Đầu vào:**
    ```text
    abcdef
    ```
*   **Mô tả:** Chuỗi chỉ chứa chữ thường, không có bất kỳ chữ in hoa nào.
*   **Đầu ra mong đợi:** `0`

### Trường hợp 2: Tất cả các chữ cái đều xuất hiện cả dạng thường và hoa

*   **Đầu vào:**
    ```text
    aAbBcCdD
    ```
*   **Mô tả:** Có 4 cặp ký tự 'A'/'a', 'B'/'b', 'C'/'c', 'D'/'d'.
*   **Đầu ra mong đợi:** `4`

### Trường hợp 3: Sự xuất hiện lặp lại nhiều lần của các ký tự đặc biệt

*   **Đầu vào:**
    ```text
    aAaaaaAAAAAAa
    ```
*   **Mô tả:** Chỉ có ký tự 'A'/'a' xuất hiện nhiều lần ở cả hai dạng thường và hoa.
*   **Đầu ra mong đợi:** `1`
