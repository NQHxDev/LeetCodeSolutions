# Tư duy thiết kế: Kiểm tra tính hợp lệ của dấu ngoặc (Valid Parentheses)

Bài toán kiểm tra dấu ngoặc không chỉ là việc đếm số lượng, mà là việc đảm bảo tính thứ tự: Dấu ngoặc nào mở sau cùng thì phải được đóng lại đầu tiên.

## Vấn đề: Sự phụ thuộc vào thứ tự đóng mở

Khi chúng ta gặp các loại dấu ngoặc khác nhau như `()`, `[]`, `{}`, việc chỉ đếm số lượng mở và đóng là không đủ. Ví dụ, chuỗi `([)]` có đủ số lượng nhưng sai thứ tự. Thách thức ở đây là làm sao để "ghi nhớ" được dấu ngoặc vừa mở gần nhất để đối chiếu với dấu ngoặc đóng hiện tại.

---

## Giải pháp: Sử dụng Ngăn xếp (Stack)

Để giải quyết bài toán này, chúng ta sử dụng hình ảnh một **Chồng đĩa**: Bạn chỉ có thể lấy chiếc đĩa được đặt lên trên cùng sau cùng.

**Quy tắc hoạt động:**

1. **Gặp dấu mở:** Ta đặt nó lên trên cùng của chồng đĩa (Push vào Stack). Điều này tương tự như việc ghi lại một lời hứa: "Tôi vừa mở dấu này, hãy đợi dấu đóng tương ứng".
2. **Gặp dấu đóng:** Ta kiểm tra chiếc đĩa trên cùng của chồng (Top of Stack). 
   - Nếu nó khớp với dấu đóng hiện tại, nghĩa là lời hứa đã được thực hiện. Ta lấy chiếc đĩa đó ra (Pop).
   - Nếu nó không khớp hoặc chồng đĩa trống rỗng (không có lời hứa nào), chuỗi đó không hợp lệ.
3. **Kết thúc:** Nếu sau khi đi hết chuỗi mà chồng đĩa trống rỗng, nghĩa là mọi lời hứa đều đã được thực hiện.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Hiệu năng vượt trội:** Chúng ta chỉ cần đi qua chuỗi đúng một lần. Độ phức tạp thời gian là $O(N)$.
- **Tiết kiệm không gian:** Trong trường hợp xấu nhất (toàn dấu mở), chúng ta cần lưu trữ $N$ ký tự. Độ phức tạp không gian là $O(N)$.
- **Tính chính xác:** Stack phản ánh hoàn hảo cấu trúc LIFO (Last-In-First-Out), khớp chính xác với bản chất lồng nhau của các dấu ngoặc.

---

## Mô phỏng luồng xử lý chi tiết

Giả sử chuỗi đầu vào: `s = "{[]}"`

**Bước 1: Quét ký tự `{`**
- Đây là dấu mở. Đưa `{` vào ngăn xếp.
- Ngăn xếp: `[` `{` `]`

**Bước 2: Quét ký tự `[`**
- Đây là dấu mở. Đưa `[` vào ngăn xếp.
- Ngăn xếp: `[` `{`, `[` `]` (Ký tự `[` nằm trên cùng).

**Bước 3: Quét ký tự `]`**
- Đây là dấu đóng. Kiểm tra đỉnh ngăn xếp: Là `[`.
- Vì `[` khớp với `]`, ta lấy `[` ra khỏi ngăn xếp.
- Ngăn xếp: `[` `{` `]`

**Bước 4: Quét ký tự `}`**
- Đây là dấu đóng. Kiểm tra đỉnh ngăn xếp: Là `{`.
- Vì `{` khớp với `}`, ta lấy `{` ra khỏi ngăn xếp.
- Ngăn xếp: Trống.

**Kết luận:** Chuỗi kết thúc và ngăn xếp trống rỗng -> Trả về `true`.

---

## Test Case mở rộng

- **Case 1 (Lồng nhau nhiều lớp):** `s = "((((()))))"` -> Kết quả: `true`.
- **Case 2 (Đóng trước khi mở):** `s = "]]"` -> Kết quả: `false`.
- **Case 3 (Sai loại dấu ngoặc):** `s = "(]"` -> Kết quả: `false`.
- **Case 4 (Dư dấu mở):** `s = "([]"` -> Kết quả: `false`.
- **Case 5 (Chuỗi rỗng):** `s = ""` -> Kết quả: `true`.

---

**Tổng kết:** Bí quyết của bài toán này nằm ở việc sử dụng Ngăn xếp để duy trì tính thứ tự "vào sau ra trước". Chỉ khi mọi "lời hứa" mở ngoặc đều được đáp lại đúng lúc và đúng loại, chuỗi mới được coi là hợp lệ.
