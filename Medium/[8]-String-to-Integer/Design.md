# Tư duy thiết kế: String to Integer

## Vấn đề

Chúng ta cần xây dựng một bộ chuyển đổi chuỗi ký tự thành số nguyên 32-bit có dấu. Đầu vào là một chuỗi thô chứa nhiều tạp chất như khoảng trắng, ký tự đặc biệt, chữ cái xen kẽ, và các con số có kích thước vượt quá khả năng lưu trữ thông thường.

Hãy tưởng tượng chúng ta có một **Băng chuyền lọc quặng tự động**. Nguyên liệu thô (chuỗi đầu vào) đi qua băng chuyền chứa đầy tạp chất (khoảng trắng, chữ cái). Nhiệm vụ của hệ thống lọc là chiết xuất ra một thanh kim loại nguyên chất (số nguyên) đạt chuẩn kích thước quy định. Nếu lượng kim loại chiết xuất được quá lớn vượt quá sức chứa của thùng chứa tiêu chuẩn (tràn số 32-bit), hệ thống phải tự động cắt bớt để bảo vệ an toàn cho toàn bộ dây chuyền.

Nếu giải quyết bài toán bằng cách lưu trữ toàn bộ chữ số vào một chuỗi trung gian hoặc sử dụng kiểu dữ liệu lớn hơn (như `long long` trong C++) để tính toán rồi mới ép kiểu:
- **Hạn chế**: Cách làm này tiêu tốn thêm bộ nhớ không cần thiết để lưu trữ chuỗi phụ. Đồng thời, việc lạm dụng kiểu dữ liệu lớn hơn chỉ là giải pháp tạm thời và không thể mở rộng nếu bài toán yêu cầu chuyển đổi sang các số nguyên cực lớn vượt ngoài mọi kiểu dữ liệu nguyên thủy của ngôn ngữ.

Chìa khóa ở đây là xây dựng một bộ lọc một chiều (Single-pass Filter) xử lý từng ký tự theo thời gian thực và kiểm soát dòng chảy dữ liệu ngay tại chỗ để đảm bảo hiệu năng tối ưu nhất.

---

## Giải pháp

Quy trình lọc quặng được chia làm bốn giai đoạn nối tiếp nhau trên một lượt duyệt duy nhất:

### Giai đoạn lọc tạp chất đầu dòng

Băng chuyền bỏ qua mọi hạt bụi (khoảng trắng `' '`) xuất hiện ở đầu chuỗi. Ngay khi gặp ký tự đầu tiên không phải khoảng trắng, bộ lọc này sẽ đóng lại vĩnh viễn và không bao giờ hoạt động nữa.

### Giai đoạn xác định cực tính

Sau khi lọc bỏ khoảng trắng đầu dòng, ta kiểm tra xem ký tự hiện tại có phải là chỉ báo hướng của dòng điện hay không:
- Dấu trừ `'-'` xác định kết quả là số âm.
- Dấu cộng `'+'` xác định kết quả là số dương.
- Nếu không có dấu nào, mặc định là số dương.

Bộ nhận diện này chỉ hoạt động đúng một lần duy nhất tại vị trí bắt đầu của lõi quặng. Mọi dấu phát sinh sau đó đều bị coi là tạp chất và làm dừng băng chuyền.

### Giai đoạn tinh chế số nguyên

Hệ thống tiến hành chuyển đổi liên tục các ký tự số từ `'0'` đến `'9'` thành giá trị số tương ứng. Công thức tích lũy giá trị tại mỗi bước là:
$$\text{giá trị mới} = \text{giá trị hiện tại} \times 10 + \text{chữ số mới}$$

Quá trình tinh chế sẽ dừng ngay lập tức khi gặp bất kỳ ký tự không phải chữ số nào (ví dụ: chữ cái, ký hiệu, hoặc khoảng trắng giữa dòng).

### Giai đoạn kiểm soát áp suất chống tràn

Đây là bộ phận tối quan trọng. Trước khi thực hiện phép nhân với $10$ và cộng thêm chữ số mới, hệ thống phải dự đoán xem hành động này có làm nứt thùng chứa số nguyên 32-bit có dấu hay không (vượt quá giới hạn của `INT_MAX` hoặc `INT_MIN`).

Để tránh hành vi tràn số (gây lỗi hệ thống hệ điều hành), ta thực hiện so sánh gián tiếp trước khi tính toán thực tế:
- Gọi giới hạn trên là `INT_MAX` ($2147483647$).
- Nếu giá trị hiện tại lớn hơn `INT_MAX / 10` ($214748364$): Phép nhân với $10$ chắc chắn sẽ gây tràn số.
- Nếu giá trị hiện tại bằng đúng `INT_MAX / 10`:
  - Trường hợp số dương: Nếu chữ số mới lớn hơn $7$ (chữ số cuối của `INT_MAX`), hệ thống sẽ bị tràn và lập tức trả về `INT_MAX`.
  - Trường hợp số âm: Nếu chữ số mới lớn hơn $8$ (chữ số cuối của trị tuyệt đối `INT_MIN` là $-2147483648$), hệ thống sẽ bị tràn và lập tức trả về `INT_MIN`.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian tối đa ($O(N)$)**: Chuỗi chỉ được duyệt qua đúng một lần duy nhất từ trái sang phải. Không có bước quay lui, không có vòng lặp lồng nhau.
- **Tiết kiệm bộ nhớ tuyệt đối ($O(1)$)**: Thuật toán chỉ sử dụng một vài biến con trỏ chỉ số và biến lưu trữ trạng thái số nguyên hiện tại. Hoàn toàn không phát sinh thêm bất kỳ mảng hoặc chuỗi động nào khác.
- **An toàn tuyệt đối**: Việc kiểm tra tràn số chủ động trước khi thực hiện tính toán giúp loại bỏ hoàn toàn các lỗi undefined behavior trong C++, đảm bảo tính ổn định cực cao của chương trình trên mọi nền tảng phần cứng.

---

## Mô phỏng hành trình tinh chế

Hãy cùng theo dõi tiến trình xử lý đầu vào phức tạp sau: `s = "   -42abc"`

**Khởi tạo:**
- Con trỏ duyệt `index = 0`
- Biến dấu `sign = 1` (mặc định dương)
- Biến tích lũy `result = 0`

**Giai đoạn 1: Bỏ qua khoảng trắng**
- Ký tự tại `index = 0, 1, 2` đều là `' '`. Con trỏ dịch chuyển đến `index = 3`.

**Giai đoạn 2: Xác định dấu**
- Ký tự tại `index = 3` là `'-'`. Ta ghi nhận `sign = -1` và tăng `index = 4`.

**Giai đoạn 3 & 4: Chuyển đổi và kiểm soát tràn số**
- **Vòng lặp 1 (`index = 4`)**:
  - Ký tự là `'4'`. Giá trị số tương ứng là $4$.
  - Kiểm tra tràn số: `result` ($0$) nhỏ hơn `INT_MAX / 10` ($214748364$) $\rightarrow$ An toàn.
  - Tích lũy: `result = 0 * 10 + 4 = 4`. Tăng `index = 5`.
- **Vòng lặp 2 (`index = 5`)**:
  - Ký tự là `'2'`. Giá trị số tương ứng là $2$.
  - Kiểm tra tràn số: `result` ($4$) nhỏ hơn `INT_MAX / 10` ($214748364$) $\rightarrow$ An toàn.
  - Tích lũy: `result = 4 * 10 + 2 = 42`. Tăng `index = 6`.
- **Vòng lặp 3 (`index = 6`)**:
  - Ký tự là `'a'`. Đây không phải chữ số $\rightarrow$ Băng chuyền dừng hoạt động ngay lập tức.

**Kết quả cuối cùng:**
- Áp dụng dấu ghi nhận từ Giai đoạn 2: `result * sign = 42 * (-1) = -42`.
- Trả về `-42`.

---

## Các trường hợp kiểm thử mở rộng

Dưới đây là các kịch bản kiểm thử đặc biệt để chứng minh tính toàn diện của thiết kế:

### Thử thách khoảng trắng kết hợp số âm cực lớn vượt ngưỡng dưới
- **Đầu vào**: `s = "      -99999999999"`
- **Mô tả**: Chuỗi chứa nhiều khoảng trắng ở đầu, tiếp theo là một số âm có trị tuyệt đối vượt xa giới hạn dưới của kiểu dữ liệu 32-bit.
- **Tiến trình dự kiến**: Sau khi bỏ qua khoảng trắng và nhận diện dấu âm, giá trị tích lũy sẽ tăng dần đến khi vượt quá giới hạn an toàn. Hệ thống chống tràn phát hiện nguy cơ và chủ động khóa van an toàn.
- **Kết quả kỳ vọng**: `-2147483648` (`INT_MIN`)

### Thử thách các ký hiệu dấu liên tiếp trái luật
- **Đầu vào**: `s = "   +-12"`
- **Mô tả**: Sau khoảng trắng đầu dòng là dấu cộng `+` nối tiếp trực tiếp bởi dấu trừ `-`.
- **Tiến trình dự kiến**: Giai đoạn xác định dấu xử lý dấu `+` đầu tiên thành công và chuyển trạng thái sang giai đoạn chuyển đổi số. Ký tự tiếp theo gặp phải là `'-'` không phải chữ số, dẫn đến quy trình dừng lập tức.
- **Kết quả kỳ vọng**: `0`

### Thử thách chuỗi chứa nhiều chữ số không vô nghĩa và kết thúc bằng chữ cái
- **Đầu vào**: `s = "0000012345678abc"`
- **Mô tả**: Chuỗi bắt đầu bằng một chuỗi số `0` đứng đầu không mang giá trị toán học và kết thúc bằng các ký tự chữ cái phía sau.
- **Tiến trình dự kiến**: Các số `0` ở đầu được tích lũy nhưng giữ nguyên giá trị `0`, sau đó các số từ `1` đến `8` được nạp bình thường cho tới khi gặp chữ `'a'` thì quy trình dừng hẳn.
- **Kết quả kỳ vọng**: `12345678`

### Thử thách chuỗi trống không chứa bất kỳ chữ số nào
- **Đầu vào**: `s = "   -   "`
- **Mô tả**: Chuỗi chỉ có khoảng trắng và dấu âm đơn độc không đi kèm chữ số.
- **Tiến trình dự kiến**: Vượt qua khoảng trắng, xác định dấu âm, nhưng ký tự tiếp theo lại là khoảng trắng (không phải chữ số), quá trình dừng lại mà chưa tích lũy được giá trị số nào.
- **Kết quả kỳ vọng**: `0`

### Thử thách tiệm cận giới hạn trên của số 32-bit dương
- **Đầu vào**: `s = "2147483646"`
- **Mô tả**: Số dương có giá trị cực gần với `INT_MAX` ($2147483647$).
- **Tiến trình dự kiến**: Quá trình tích lũy chạy đến chữ số cuối cùng (`6`). Hệ thống kiểm tra so sánh gián tiếp `result == INT_MAX / 10` ($214748364 == 214748364$) và chữ số mới $6 \le 7$ nên cho phép tích lũy nốt chữ số này.
- **Kết quả kỳ vọng**: `2147483646`

---

**Tổng kết:** Bằng việc tổ chức hệ thống xử lý một chiều tuần tự, chặt chẽ kết hợp với cơ chế dự báo tràn số gián tiếp, giải pháp này giải quyết triệt để và an toàn mọi thách thức của quá trình ép kiểu từ chuỗi văn bản thô sang định dạng số nguyên tiêu chuẩn với hiệu năng tối ưu nhất.
