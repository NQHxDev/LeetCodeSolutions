# Tư duy thiết kế: Tìm kiếm sự đối xứng từ "Tâm điểm" (Longest Palindromic Substring)

Longest Palindromic Substring là bài toán tìm ra chuỗi con dài nhất có tính chất đối xứng (đọc xuôi hay ngược đều giống nhau). Đây là một bài toán kinh điển để rèn luyện tư duy tối ưu hóa từ việc quan sát đặc điểm hình học của dữ liệu.

## Vấn đề: Cái bẫy của việc kiểm tra từng chuỗi con

Nếu chúng ta liệt kê tất cả các chuỗi con có thể có ($O(n^2)$ chuỗi) và với mỗi chuỗi lại đi kiểm tra xem nó có đối xứng hay không ($O(n)$), tổng thời gian sẽ là $O(n^3)$. Với một chuỗi dài 1000 ký tự, máy tính sẽ phải thực hiện hàng tỷ phép tính — một con số quá lớn cho một bài toán đơn giản.

---

## Giải pháp: Kỹ thuật "Mở rộng từ tâm" (Expand Around Center)

Thay vì đi tìm từng chuỗi rồi mới kiểm tra đối xứng, chúng ta hãy lật ngược vấn đề: **Một chuỗi đối xứng luôn được hình thành bằng cách mở rộng đều ra hai bên từ một "trung tâm".**

Hãy tưởng tượng bạn đặt một chiếc gương tại một vị trí trong chuỗi:

- **Tâm đơn (Lẻ):** Gương đặt ngay tại một ký tự (ví dụ: trong `aba`, tâm là `b`).
- **Tâm đôi (Chẵn):** Gương đặt ở khe giữa hai ký tự (ví dụ: trong `abba`, tâm là khe giữa hai chữ `b`).

Chúng ta chỉ cần duyệt qua từng vị trí (có $2n-1$ tâm như vậy), từ mỗi tâm ta mở rộng sang hai bên miễn là các ký tự còn giống nhau.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Giảm độ phức tạp:** Chúng ta chỉ mất $O(n)$ vị trí tâm, và mỗi lần mở rộng mất tối đa $O(n)$. Tổng cộng là $O(n^2)$, nhanh hơn rất nhiều so với $O(n^3)$.
- **Không tốn bộ nhớ phụ:** Khác với phương pháp Quy hoạch động (Dynamic Programming) tốn $O(n^2)$ bộ nhớ để lưu bảng, cách này chỉ tốn $O(1)$ bộ nhớ bổ sung vì chúng ta chỉ lưu lại vị trí bắt đầu và độ dài lớn nhất.
- **Tính trực quan:** Nó mô phỏng đúng bản chất vật lý của sự đối xứng — mọi thứ đều bắt nguồn từ một trục giữa.

---

## Mô phỏng luồng xử lý chi tiết
Hãy hình dung chúng ta sử dụng một chiếc **Compa** có hai chân (gọi là chân Trái và chân Phải). Tại mỗi vị trí trong chuỗi, chúng ta đặt Compa xuống và bắt đầu mở rộng hai chân ra hai phía miễn là hai ký tự tại đầu chân Compa vẫn giống nhau.

Chuỗi ví dụ: `b a b a d` (Chỉ số: 0, 1, 2, 3, 4)

### Trường hợp 1: Đối xứng lẻ (Tâm là 1 ký tự)
Giả sử ta đặt Compa tại vị trí chỉ số 1 (ký tự `'a'`):

- **Bước 1:** Chân Trái = 1, chân Phải = 1. Cả hai cùng chỉ vào `'a'`. (Khớp)
- **Bước 2:** Mở rộng chân Trái sang 0, chân Phải sang 2. Ta có `s[0]` là `'b'` và `s[2]` là `'b'`. (Khớp vì `'b' == 'b'`) -> Chuỗi hiện tại: `"bab"`.
- **Bước 3:** Mở rộng chân Trái sang -1 (vượt biên), chân Phải sang 3. Vì chân Trái đã ra ngoài biên nên **Dừng lại**.
- **Kết quả tại tâm này:** `"bab"`.

### Trường hợp 2: Đối xứng chẵn (Tâm là khe giữa 2 ký tự)
Giả sử ta đặt Compa tại khe giữa chỉ số 1 (`'a'`) và 2 (`'b'`):

- **Bước 1:** Chân Trái = 1 (`'a'`), chân Phải = 2 (`'b'`).
- **Kiểm tra:** `'a'` khác `'b'`. Không khớp ngay từ đầu. -> **Dừng lại ngay**.
- **Kết quả tại tâm này:** Rỗng (hoặc chỉ tính là các ký tự đơn lẻ).

### Trường hợp 3: Một ví dụ khác về tâm lẻ tại chỉ số 2 (ký tự `'b'`)
- **Bước 1:** Chân Trái = 2, chân Phải = 2. Cùng chỉ vào `'b'`. (Khớp)
- **Bước 2:** Mở rộng chân Trái sang 1 (`'a'`), chân Phải sang 3 (`'a'`). Khớp! -> Chuỗi hiện tại: `"aba"`.
- **Bước 3:** Mở rộng chân Trái sang 0 (`'b'`), chân Phải sang 4 (`'d'`). Khác nhau! (`'b' != 'd'`) -> **Dừng lại**.
- **Kết quả tại tâm này:** `"aba"`.

**Kết luận:** Qua các lần đặt Compa tại tất cả các vị trí (bao gồm cả ký tự và khe giữa), chúng ta ghi lại chuỗi có độ dài lớn nhất tìm được (ở đây là `"bab"` hoặc `"aba"`).

---

## Phân tích chuyên sâu Test Case: `abbcccbbb`
Trường hợp này giúp minh họa cách thuật toán "vượt qua" các cụm ký tự giống nhau để tìm thấy chuỗi đối xứng cực dài.

Chuỗi: `a b b c c c b b b`
Chỉ số: `0 1 2 3 4 5 6 7 8`

**Thử thách:** Tại sao kết quả lại là `"bbcccbb"`? Hãy xem khi Compa đặt tại **chỉ số 4** (ký tự `'c'` ở giữa):

1. **Bước 1 (L=4, R=4):** Cả hai chỉ vào `'c'`. (Khớp) -> Chuỗi: `"c"`
2. **Bước 2 (L=3, R=5):** `s[3]` là `'c'`, `s[5]` là `'c'`. (Khớp) -> Chuỗi: `"ccc"`
3. **Bước 3 (L=2, R=6):** `s[2]` là `'b'`, `s[6]` là `'b'`. (Khớp) -> Chuỗi: `"bcccb"`
4. **Bước 4 (L=1, R=7):** `s[1]` là `'b'`, `s[7]` là `'b'`. (Khớp) -> Chuỗi: `"bbcccbb"`
5. **Bước 5 (L=0, R=8):** `s[0]` là `'a'`, `s[8]` là `'b'`. (Khác nhau!) -> **Dừng lại**.

**Kết quả tại tâm này:** `"bbcccbb"` (Độ dài 7).

---

**Lưu ý về các tâm khác:**
- Tại khe giữa 7 và 8 (`b|b`): Sẽ tìm được `"bb"`.
- Tại tâm 7 (`b`): Sẽ tìm được `"bbb"` (từ 6 đến 8).
- Nhưng tất cả đều ngắn hơn chuỗi độ dài 7 mà chúng ta vừa tìm thấy ở trên.

---

## Test Case mở rộng

Dưới đây là một số trường hợp kiểm thử đặc biệt ngoài các ví dụ cơ bản:

- **Case 1 (Toàn bộ ký tự giống nhau):** `s = "aaaaa"` -> Kết quả: `"aaaaa"`
- **Case 2 (Không có đối xứng dài hơn 1):** `s = "abcde"` -> Kết quả: `"a"`
- **Case 3 (Đối xứng toàn chuỗi):** `s = "racecar"` -> Kết quả: `"racecar"`
- **Case 4 (Nhiều tâm đối xứng chồng lấp):** `s = "abbcccbbb"` -> Kết quả: `"bbcccbb"`
- **Case 5 (Đối xứng chẵn nằm ở cuối):** `s = "baab"` -> Kết quả: `"baab"`

---

**Tổng kết:** Tư duy "Mở rộng từ tâm" giúp chúng ta tận dụng tối đa đặc điểm đối xứng để loại bỏ các bước kiểm tra thừa thãi. Đây là minh chứng cho việc hiểu rõ bản chất dữ liệu có thể giúp tối ưu thuật toán một cách tự nhiên mà không cần đến các cấu trúc dữ liệu phức tạp.
