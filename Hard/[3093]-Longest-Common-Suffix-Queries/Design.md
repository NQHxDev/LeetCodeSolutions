# Tư duy thiết kế: Longest Common Suffix Queries

## Vấn đề
Cho hai mảng chuỗi ký tự `wordsContainer` và `wordsQuery`. Với mỗi chuỗi trong `wordsQuery`, chúng ta cần tìm một chuỗi trong `wordsContainer` sao cho:
- Chúng có hậu tố chung dài nhất (Longest Common Suffix).
- Nếu có nhiều chuỗi có cùng độ dài hậu tố chung dài nhất, ưu tiên chọn chuỗi có độ dài ngắn nhất.
- Nếu các chuỗi đó tiếp tục trùng độ dài, ưu tiên chọn chuỗi xuất hiện sớm hơn (chỉ số nhỏ hơn) trong `wordsContainer`.

Chúng ta cần tìm kiếm vị trí chỉ số kết quả cho mỗi truy vấn một cách nhanh chóng nhất.

---

## Giải pháp: Cây tiền tố đảo ngược (Trie on Reversed Strings)
Để trực quan hóa giải pháp này, hãy tưởng tượng bạn đang biên soạn một cuốn từ điển dành cho các nhà thơ để giúp họ tìm từ gieo vần (rhyming words). 
Trong cuốn từ điển thông thường, các từ được sắp xếp theo thứ tự chữ cái từ trái sang phải (tiền tố). Nếu muốn tìm những từ có vần cuối giống nhau (ví dụ: các từ kết thúc bằng "at" như "cat", "bat", "hat"), việc tra cứu sẽ vô cùng mất thời gian vì chúng nằm phân tán khắp nơi.

Để giải quyết, ta viết ngược tất cả các từ lại trước khi đưa vào từ điển:
- "cat" $\to$ "tac"
- "bat" $\to$ "tab"
- "hat" $\to$ "tah"
- "format" $\to$ "tamrof"

Bây giờ, tất cả các từ gieo vần "at" đều bắt đầu bằng cụm ký tự "ta". Bài toán tìm **hậu tố chung dài nhất** của một truy vấn lúc này chuyển thành bài toán tìm **tiền tố chung dài nhất** trên các chuỗi đảo ngược! Đây là bài toán kinh điển giải quyết hiệu quả bằng **Cây tiền tố (Trie)**.

Để giải bài toán này:
1. **Thiết kế nút của Trie (Trie Node):**
   Mỗi nút trong Trie đại diện cho một ký tự và lưu trữ thêm:
   - `best_index`: Chỉ số của từ tốt nhất trong `wordsContainer` đi qua nút này.
   - Để cập nhật `best_index`, tại mỗi nút ta so sánh từ mới chuẩn bị chèn với từ tốt nhất hiện tại:
     - Ưu tiên từ có độ dài ngắn hơn.
     - Nếu độ dài bằng nhau, ưu tiên từ có chỉ số nhỏ hơn (xuất hiện trước).
2. **Xây dựng Trie:**
   - Đầu tiên, ta tìm từ ngắn nhất và xuất hiện sớm nhất trong toàn bộ `wordsContainer` để làm câu trả lời mặc định cho nút gốc (Root) của Trie (dành cho trường hợp truy vấn không có chung bất kỳ hậu tố nào).
   - Duyệt qua từng từ trong `wordsContainer`, đảo ngược từ đó và thực hiện chèn (insert) vào Trie. Tại mỗi nút đi qua, ta cập nhật `best_index` theo quy tắc ưu tiên.
3. **Truy vấn:**
   - Với mỗi từ trong `wordsQuery`, ta đảo ngược từ đó và thực hiện tìm kiếm trên Trie từ nút gốc dọc theo các ký tự của từ truy vấn.
   - Ta đi sâu nhất có thể. Nút cuối cùng mà ta đi tới được trên Trie sẽ lưu trữ `best_index` chính là câu trả lời tối ưu nhất cho truy vấn đó.

---

## Tại sao tối ưu?
- **Thời gian tra cứu cực nhanh:** Việc xây dựng Trie mất thời gian tỉ lệ thuận với tổng số ký tự trong `wordsContainer`, tức $O(\sum |W_{container}|)$. Sau khi Trie được dựng xong, mỗi truy vấn trong `wordsQuery` chỉ mất thời gian tìm kiếm tuyến tính theo độ dài của chính chuỗi truy vấn đó, tức $O(|W_{query}|)$. Tổng thời gian chạy cho toàn bộ truy vấn là $O(\sum |W_{container}| + \sum |W_{query}|)$, tối ưu hơn rất nhiều so với cách so khớp thô bạo (Brute Force) có độ phức tạp $O(M \times N \times L)$.
- **Bộ nhớ hiệu quả:** Trie chia sẻ các tiền tố chung của các từ đảo ngược, giúp tiết kiệm bộ nhớ đáng kể so với việc lưu trữ độc lập tất cả các trạng thái hậu tố.

---

## Minh họa từng bước chạy
Xét `wordsContainer = ["abcd", "bcd", "xbcd"]`, `wordsQuery = ["cd", "bcd"]`.

1. **Khởi tạo và chọn từ tối ưu mặc định cho gốc:**
   - Độ dài các từ: `"abcd"` (4), `"bcd"` (3), `"xbcd"` (4).
   - Từ tối ưu nhất mặc định là `"bcd"` (độ dài 3, ngắn nhất) có chỉ số là `1`. Vậy `root->best_index = 1`.

2. **Chèn các từ đảo ngược vào Trie:**
   - Chèn `"dcba"` (đảo ngược của `"abcd"`, chỉ số 0):
     - Đi qua các nút: `d` $\to$ `c` $\to$ `b` $\to$ `a`. Do Trie trống, tất cả các nút này nhận `best_index = 0`.
   - Chèn `"dcb"` (đảo ngược của `"bcd"`, chỉ số 1):
     - Nút `d`: từ chỉ số 1 (`"bcd"`, dài 3) ngắn hơn từ chỉ số 0 (`"abcd"`, dài 4) $\to$ cập nhật `best_index = 1`.
     - Nút `c`: tương tự $\to$ cập nhật `best_index = 1`.
     - Nút `b`: tương tự $\to$ cập nhật `best_index = 1`.
   - Chèn `"dcbx"` (đảo ngược của `"xbcd"`, chỉ số 2):
     - So sánh từ chỉ số 2 (`"xbcd"`, dài 4) với từ hiện tại (`"bcd"`, dài 3) $\to$ không ngắn hơn, giữ nguyên `best_index = 1` tại các nút `d`, `c`, `b`. Tạo nút mới `x` có `best_index = 2`.

3. **Tra cứu truy vấn:**
   - Truy vấn `"cd"` $\to$ đảo ngược là `"dc"`:
     - Đi từ root $\to$ nút `d` (best = 1) $\to$ nút `c` (best = 1).
     - Kết quả: `1` (tương ứng `"bcd"`).
   - Truy vấn `"bcd"` $\to$ đảo ngược là `"dcb"`:
     - Đi từ root $\to$ nút `d` (best = 1) $\to$ nút `c` (best = 1) $\to$ nút `b` (best = 1).
     - Kết quả: `1` (tương ứng `"bcd"`).

---

## Các trường hợp kiểm thử bổ sung

### Trường hợp 1: Không có hậu tố chung nào
- **Đầu vào:**
  ```text
  wordsContainer = ["hello", "world"]
  wordsQuery = ["abc", "xyz"]
  ```
- **Mô tả:** Các từ truy vấn không chia sẻ bất kỳ chữ cái cuối nào với các từ trong container. Kết quả phải trả về chỉ số của từ ngắn nhất/xuất hiện trước trong container.
- **Đầu ra mong đợi:** `[0, 0]` (vì `"hello"` và `"world"` đều dài 5, ưu tiên `"hello"` chỉ số 0 xuất hiện trước).

### Trường hợp 2: Trùng độ dài hậu tố chung nhưng khác chiều dài từ
- **Đầu vào:**
  ```text
  wordsContainer = ["aple", "apple", "triple"]
  wordsQuery = ["ple"]
  ```
- **Mô tả:** Cả 3 từ trong container đều có hậu tố chung `"ple"` với truy vấn. Từ ngắn nhất là `"aple"` (độ dài 4).
- **Đầu ra mong đợi:** `[0]`

### Trường hợp 3: Trùng độ dài hậu tố chung và trùng cả chiều dài từ
- **Đầu vào:**
  ```text
  wordsContainer = ["cats", "bats", "hats"]
  wordsQuery = ["ats"]
  ```
- **Mô tả:** Cả 3 từ đều dài 4 ký tự và đều kết thúc bằng `"ats"`. Ưu tiên từ xuất hiện sớm nhất.
- **Đầu ra mong đợi:** `[0]`

---

**Tổng kết:**
Mô hình Cây tiền tố đảo ngược chuyển đổi bài toán tìm kiếm hậu tố phức tạp thành bài toán tìm kiếm tiền tố tuyến tính cực kỳ hiệu quả. Việc tính toán sẵn từ tối ưu nhất tại mỗi nút khi xây dựng cây giúp thời gian tra cứu đạt mức tối ưu tuyệt đối.
