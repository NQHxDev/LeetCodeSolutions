# Tư duy thiết kế: Tìm vị trí xuất hiện đầu tiên của chuỗi con (Find the Index of the First Occurrence in a String)

Việc đối chiếu chuỗi con trong chuỗi cha là một bài toán nền tảng, rèn luyện tư duy tối ưu hóa số lượng phép so sánh ký tự và quản lý cửa sổ tìm kiếm hiệu quả.

## Vấn đề

Hãy tưởng tượng một biên tập viên đang đọc một bài báo dài (`haystack`) để tìm vị trí xuất hiện đầu tiên của một từ khóa cụ thể (`needle`), ví dụ như từ "bánh mì".

Vì từ khóa có độ dài cố định, người đọc sẽ quét mắt qua bài báo. Khi bắt gặp chữ cái đầu tiên "b", người đọc sẽ dừng lại để đối chiếu các ký tự tiếp theo xem có khớp hoàn toàn với cụm "bánh mì" hay không. Nếu có bất kỳ ký tự nào không khớp (ví dụ: đọc thành "bánh quy"), họ sẽ ngay lập tức bỏ qua cửa sổ này và tiếp tục quét chữ cái "b" tiếp theo trong văn bản.

Trong lập trình, việc so sánh chuỗi đòi hỏi thiết kế một cơ chế đối chiếu tối giản để tránh so sánh lặp đi lặp lại những ký tự không cần thiết, giúp tiết kiệm tối đa thời gian xử lý khi văn bản đầu vào có kích thước lớn.

---

## Giải pháp

Thuật toán tối ưu và trực quan nhất để giải quyết bài toán này là sử dụng phương pháp **Cửa sổ trượt với cơ chế ngắt sớm (Sliding Window with Early Termination)**:

### Giới hạn phạm vi quét
Gọi `h` là độ dài chuỗi `haystack` và `n` là độ dài chuỗi `needle`. Nếu phần còn lại của `haystack` có độ dài nhỏ hơn `n`, việc so sánh chắc chắn sẽ thất bại. Do đó, chỉ số bắt đầu quét `i` chỉ cần chạy trong khoảng từ `0` đến `h - n`.

### Đối chiếu từng ký tự trong cửa sổ
Tại mỗi chỉ số `i` thuộc phạm vi quét, ta mở một cửa sổ có độ dài `n` trên `haystack` để so sánh với `needle`:
- Duyệt qua từng ký tự tương ứng từ `0` đến `n - 1`.
- Nếu phát hiện ký tự tại `haystack[i + j]` khác với `needle[j]`, ta thực hiện **ngắt sớm** (break) khỏi vòng lặp hiện tại và dịch cửa sổ sang chỉ số tiếp theo `i + 1`.
- Nếu hoàn thành việc duyệt qua toàn bộ cửa sổ mà không gặp ký tự khác biệt nào, ta trả về chỉ số `i` ngay lập tức.

### Trả về kết quả khi không tìm thấy
Nếu đã duyệt qua toàn bộ phạm vi quét mà không tìm thấy cửa sổ nào khớp hoàn toàn, thuật toán trả về `-1`.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian:** 
  - Trong trường hợp trung bình, nhờ cơ chế ngắt sớm, thuật toán sẽ bỏ qua cửa sổ hiện tại ngay khi gặp ký tự không khớp đầu tiên, giúp tốc độ thực tế tiệm cận độ phức tạp $O(h)$.
  - Trong trường hợp xấu nhất (các chuỗi chứa nhiều ký tự lặp lại như `haystack = "aaaaaaab"`, `needle = "aaab"`), độ phức tạp thời gian tối đa là $O(h \times n)$. Tuy nhiên, đối với các trường hợp dữ liệu thực tế thông thường, thuật toán này đạt tốc độ thực thi rất nhanh.
- **Tiết kiệm bộ nhớ:** Độ phức tạp không gian là $O(1)$ vì thuật toán chỉ sử dụng các biến đếm chỉ số mà không khởi tạo thêm bất kỳ cấu trúc dữ liệu bổ sung nào.

---

## Mô phỏng luồng xử lý

Giả sử chuỗi cha `haystack = "sadbutsad"` và chuỗi con `needle = "sad"`.
Độ dài `h = 9`, `n = 3`. Phạm vi quét của chỉ số `i` là từ `0` đến `9 - 3 = 6`.

### Chỉ số i = 0
- So sánh `haystack[0]` với `needle[0]` ('s' == 's') $\rightarrow$ khớp.
- So sánh `haystack[1]` với `needle[1]` ('a' == 'a') $\rightarrow$ khớp.
- So sánh `haystack[2]` với `needle[2]` ('d' == 'd') $\rightarrow$ khớp.
- Đã duyệt hết độ dài `n = 3` và toàn bộ ký tự đều khớp. Trả về `0` và dừng thuật toán.

Giả sử chuỗi cha `haystack = "leetcode"` và chuỗi con `needle = "leeto"`.
Độ dài `h = 8`, `n = 5`. Phạm vi quét của chỉ số `i` là từ `0` đến `8 - 5 = 3`.

### Chỉ số i = 0
- So sánh lần lượt các ký tự tại `j = 0, 1, 2, 3` $\rightarrow$ đều khớp ('l', 'e', 'e', 't').
- So sánh tại `j = 4`: `haystack[4] = 'c'` khác `needle[4] = 'o'` $\rightarrow$ Không khớp. Ngắt sớm và chuyển sang `i = 1`.

### Chỉ số i = 1
- So sánh `haystack[1] = 'e'` khác `needle[0] = 'l'` $\rightarrow$ Không khớp. Ngắt sớm và chuyển sang `i = 2`.

### Chỉ số i = 2
- So sánh `haystack[2] = 'e'` khác `needle[0] = 'l'` $\rightarrow$ Không khớp. Ngắt sớm và chuyển sang `i = 3`.

### Chỉ số i = 3
- So sánh `haystack[3] = 't'` khác `needle[0] = 'l'` $\rightarrow$ Không khớp. Ngắt sớm.

Kết thúc phạm vi quét mà không có vị trí nào khớp. Trả về `-1`.

---

## Các trường hợp kiểm thử bổ sung

- **Trường hợp 1:** `haystack = "mississippi"`, `needle = "issip"`
  - Mô tả: Từ khóa xuất hiện một phần tương ứng trước đó (`issi` trước `issip`), kiểm tra khả năng phục hồi trạng thái so sánh của thuật toán.
  - Kết quả mong đợi: `4`

- **Trường hợp 2:** `haystack = "hello"`, `needle = "ll"`
  - Mô tả: Từ khóa xuất hiện ở đoạn giữa của chuỗi gốc.
  - Kết quả mong đợi: `2`

- **Trường hợp 3:** `haystack = "abc"`, `needle = "abcd"`
  - Mô tả: Độ dài từ khóa lớn hơn độ dài của chuỗi gốc.
  - Kết quả mong đợi: `-1`

- **Trường hợp 4:** `haystack = "aaa"`, `needle = "a"`
  - Mô tả: Từ khóa xuất hiện nhiều lần liên tiếp, cần kiểm tra việc lấy vị trí xuất hiện đầu tiên.
  - Kết quả mong đợi: `0`

- **Trường hợp 5:** `haystack = "a"`, `needle = "a"`
  - Mô tả: Cả chuỗi gốc và từ khóa đều chỉ có độ dài bằng 1 và trùng khớp.
  - Kết quả mong đợi: `0`
