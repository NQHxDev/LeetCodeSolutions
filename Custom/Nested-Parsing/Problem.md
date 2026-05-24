# Phân Tích Cú Pháp Lồng Nhau (Nested Parsing)

## Bối Cảnh Lịch Sử & Đề Bài

Trong lập trình hoặc khi soạn thảo các tài liệu có cấu trúc, việc sử dụng dấu nháy đơn `'` để tạo các đoạn trích dẫn là một quy chuẩn rất phổ biến. Tuy nhiên, khi các trích dẫn này được lồng vào nhau nhiều cấp độ, việc xác định cấu trúc lồng nhau trở nên vô cùng quan trọng để đảm bảo tính hợp lệ của cú pháp.

Một cú pháp đơn giản để thể hiện cấu trúc này là sử dụng khái niệm **$k$-quote**, được định nghĩa đệ quy như sau:

* **$1$-quote:** Là một chuỗi bắt đầu bằng một dấu nháy đơn `'` và kết thúc bằng một dấu nháy đơn `'`, bên trong không chứa bất kỳ dấu nháy đơn nào khác.
  * *Ví dụ:* `'Nguyen Quang Hung'` là một $1$-quote hợp lệ.
* **$k$-quote (với $k > 1$):** Là một chuỗi bắt đầu bằng $k$ dấu nháy đơn liên tiếp và kết thúc bằng $k$ dấu nháy đơn liên tiếp. Bên trong chứa một chuỗi không rỗng gồm một hoặc nhiều $(k-1)$-quote liên tiếp, các $(k-1)$-quote này có thể được ngăn cách hoặc bao quanh bởi các ký tự không phải dấu nháy đơn.
  * *Ví dụ:* `''Nguyen Quang Hung 'đang' code 'nè'!''` là một $2$-quote hợp lệ (vì nó chứa hai $1$-quote là `'đang'` và `'nè'`).
  * *Ví dụ:* `''''Xin chào: '''Nguyen Quang Hung ''tham gia sự kiện 'IT Code War'''''''''` là một $4$-quote hợp lệ.

---

## Chi Tiết Bài Toán

Cho một chuỗi chứa các nhóm dấu nháy đơn được phân tách bởi các đoạn văn bản (không chứa dấu nháy). Cấu trúc của chuỗi này được mô tả thông qua một dãy gồm $N$ số nguyên dương $a_1, a_2, \dots, a_n$.

Dãy số này thể hiện rằng chuỗi bắt đầu bằng $a_1$ dấu nháy đơn, tiếp theo là một đoạn văn bản, rồi đến $a_2$ dấu nháy đơn, tiếp theo là đoạn văn bản, và cứ thế tiếp tục cho đến khi kết thúc bằng $a_n$ dấu nháy đơn ở cuối chuỗi.

**Nhiệm vụ:** Tìm số nguyên $k$ lớn nhất sao cho chuỗi được mô tả là một $k$-quote hợp lệ. Nếu chuỗi không phải là một $k$-quote hợp lệ với bất kỳ giá trị $k \ge 1$ nào, hãy in ra `no-quote`.

---

## Định Dạng Đầu Vào

* **Dòng đầu tiên:** Chứa một số nguyên dương $N$ là số lượng nhóm dấu nháy đơn.
* **Dòng thứ hai:** Chứa $N$ số nguyên dương $a_1, a_2, \dots, a_n$ phân tách nhau bởi khoảng trắng.

---

## Định Dạng Đầu Ra

* In ra một số nguyên $k$ lớn nhất tìm được, hoặc in ra chuỗi `no-quote` nếu không tồn tại $k$ thỏa mãn.

---

## Ràng Buộc Hệ Thống

* $2 \le N \le 10^5$ (Danh sách các nhóm dấu nháy có thể rất dài)
* $1 \le a_i \le 10^9$ (Số lượng dấu nháy trong một nhóm có thể lớn)

---

## Ví Dụ Minh Họa

### Ví dụ 1

#### Đầu vào mẫu 1
```text
6
2 1 1 1 1 2
```

#### Đầu ra mẫu 1
```text
2
```

#### Giải thích trực quan 1
Dãy mô tả chuỗi: `'' [văn bản] ' [văn bản] ' [văn bản] ' [văn bản] ' [văn bản] ''`
* Chuỗi bắt đầu và kết thúc bằng $2$ dấu nháy.
* Bên trong chứa hai phân đoạn dạng `[1, 1]` (là các $1$-quote) phân tách nhau bởi văn bản.
* Do đó, đây là một $2$-quote hợp lệ. Kết quả là `2`.

### Ví dụ 2

#### Đầu vào mẫu 2
```text
8
4 3 2 1 1 2 3 4
```

#### Đầu ra mẫu 2
```text
4
```

#### Giải thích trực quan 2
Dãy mô tả chuỗi có cấu trúc lồng nhau hoàn hảo từ ngoài vào trong:
* Nhóm ngoài cùng: Bắt đầu bằng $4$ và kết thúc bằng $4$.
* Nhóm bên trong: Bắt đầu bằng $3$ và kết thúc bằng $3$.
* Nhóm trong nữa: Bắt đầu bằng $2$ và kết thúc bằng $2$.
* Nhóm trong cùng: Bắt đầu bằng $1$ và kết thúc bằng $1$.
* Tất cả các cấp lồng nhau đều hợp lệ theo định nghĩa. Kết quả là `4`.

### Ví dụ 3

#### Đầu vào mẫu 3
```text
5
2 1 1 1 2
```

#### Đầu ra mẫu 3
```text
no-quote
```

#### Giải thích trực quan 3
Chuỗi bắt đầu bằng $2$ và kết thúc bằng $2$. Nhưng phần ruột bên trong chỉ chứa duy nhất một nhóm có $1$ dấu nháy đơn ở giữa. Theo định nghĩa, các cấu trúc bên trong phải là các $(k-1)$-quote hoàn chỉnh (tức là các nhóm phải đi kèm theo cặp để đóng mở hợp lệ như `[1, 1]`). Do đó chuỗi này không hợp lệ và trả về `no-quote`.
