# Tư duy thiết kế: Count the Number of Special Characters II

## Vấn đề
Bài toán yêu cầu chúng ta đếm số lượng chữ cái "đặc biệt" trong một chuỗi `word`. Một chữ cái được coi là đặc biệt nếu:
- Nó xuất hiện trong chuỗi ở cả hai định dạng: chữ thường (ví dụ: 'a') và chữ hoa (ví dụ: 'A').
- Tất cả các lần xuất hiện của chữ thường đó phải nằm trước lần xuất hiện đầu tiên của chữ hoa cùng loại.

Chúng ta cần tìm ra số lượng chữ cái đáp ứng cả hai điều kiện trên với hiệu năng tối ưu nhất.

---

## Giải pháp: Quản lý mốc thời gian qua chỉ số mảng cố định
Để trực quan hóa bài toán này, hãy tưởng tượng một hệ thống kiểm soát ra vào bằng thẻ từ tại một tòa nhà:
- Mỗi nhân viên (tương ứng với một chữ cái tiếng Anh) có hai loại thẻ: Thẻ vào (chữ thường, ví dụ: 'a') và Thẻ ra (chữ hoa, ví dụ: 'A').
- Quy định an toàn của tòa nhà yêu cầu: Một nhân viên chỉ được coi là "hợp lệ" (đặc biệt) nếu họ đã thực hiện cả hành động quẹt Thẻ vào và Thẻ ra, đồng thời **tất cả** các lần quẹt Thẻ vào đều phải diễn ra trước lần quẹt Thẻ ra đầu tiên.
- Nếu nhân viên đó quẹt Thẻ vào *sau* khi đã quẹt Thẻ ra lần đầu tiên, họ lập tức vi phạm quy định.

Để hiện thực hóa logic này một cách tối ưu, ta sử dụng hai mảng lưu trữ chỉ số có kích thước cố định là 26:
- `last_lower`: Lưu trữ chỉ số (vị trí) xuất hiện **cuối cùng** của ký tự thường. Ban đầu tất cả phần tử được khởi tạo bằng `-1`.
- `first_upper`: Lưu trữ chỉ số (vị trí) xuất hiện **đầu tiên** của ký tự hoa. Ban đầu tất cả phần tử được khởi tạo bằng `-1`.

Quy trình hoạt động:
1. Duyệt qua chuỗi `word` từ đầu đến cuối (với chỉ số `i` từ `0` đến `n - 1`):
   - Nếu ký tự hiện tại là chữ thường: Cập nhật vị trí cuối cùng của nó trong `last_lower`. Do duyệt từ trái sang phải, giá trị tại đây sẽ tự động lưu lại vị trí muộn nhất.
   - Nếu ký tự hiện tại là chữ hoa: Kiểm tra xem đã ghi nhận vị trí đầu tiên của nó trong `first_upper` chưa (giá trị có bằng `-1` không). Nếu chưa, ghi nhận chỉ số `i` hiện tại.
2. Sau khi duyệt xong chuỗi, tiến hành kiểm tra cho 26 chữ cái (tương ứng chỉ số từ `0` đến `25`):
   - Một chữ cái chỉ hợp lệ nếu cả hai mảng `last_lower` và `first_upper` tại vị trí đó đều khác `-1` (đã xuất hiện cả hai định dạng thường và hoa) và `last_lower[i] < first_upper[i]` (lần xuất hiện chữ thường cuối cùng diễn ra trước lần xuất hiện chữ hoa đầu tiên).
3. Đếm số lượng chữ cái thỏa mãn và trả về kết quả.

---

## Tại sao tối ưu?
- **Thời gian chạy tối ưu:** Thuật toán chỉ duyệt qua chuỗi đúng một lần để xây dựng thông tin vị trí các ký tự, sau đó lặp qua một mảng cố định gồm 26 phần tử để kiểm tra kết quả. Do đó, độ phức tạp thời gian là $O(N)$ với $N$ là độ dài của chuỗi `word`. Đây là tiệm cận thời gian tối thiểu vì chúng ta bắt buộc phải đọc qua tất cả ký tự trong chuỗi nhất định một lần để xác định vị trí của chúng.
- **Không gian bộ nhớ tối giản:** Hai mảng phụ trợ `last_lower` và `first_upper` có kích thước không đổi là 26, hoàn toàn độc lập với độ dài chuỗi đầu vào. Do đó, độ phức tạp không gian là $O(1)$.

---

## Minh họa từng bước chạy
Xét chuỗi đầu vào: `word = "aaAbcBC"`

Bước 1: Khởi tạo `last_lower` và `first_upper` gồm 26 phần tử có giá trị `-1`.

Bước 2: Duyệt qua chuỗi `word`:
- `i = 0`, ký tự `'a'`: `last_lower['a' - 'a'] = 0`
- `i = 1`, ký tự `'a'`: `last_lower['a' - 'a'] = 1`
- `i = 2`, ký tự `'A'`: `first_upper['A' - 'a'] = 2` (do trước đó là `-1`)
- `i = 3`, ký tự `'b'`: `last_lower['b' - 'a'] = 3`
- `i = 4`, ký tự `'c'`: `last_lower['c' - 'a'] = 4`
- `i = 5`, ký tự `'B'`: `first_upper['B' - 'a'] = 5` (do trước đó là `-1`)
- `i = 6`, ký tự `'C'`: `first_upper['C' - 'a'] = 6` (do trước đó là `-1`)

Bước 3: Duyệt qua 26 chữ cái để kiểm tra điều kiện:
- Ký tự `'a'`: `last_lower[0] = 1` và `first_upper[0] = 2`. Điều kiện `1 < 2` thỏa mãn $\to$ `count = 1`.
- Ký tự `'b'`: `last_lower[1] = 3` và `first_upper[1] = 5`. Điều kiện `3 < 5` thỏa mãn $\to$ `count = 2`.
- Ký tự `'c'`: `last_lower[2] = 4` và `first_upper[2] = 6`. Điều kiện `4 < 6` thỏa mãn $\to$ `count = 3`.
- Các chữ cái còn lại không xuất hiện đủ cả hai định dạng (hoặc không xuất hiện) nên không thỏa mãn.

Kết quả trả về: `3`.

---

## Các trường hợp kiểm thử bổ sung

### Trường hợp 1: Chuỗi chứa chữ thường xuất hiện sau chữ hoa cùng loại
- **Đầu vào:**
  ```text
  aAbBa
  ```
- **Mô tả:** Chữ thường `'a'` xuất hiện ở cuối chuỗi (chỉ số 4), sau chữ hoa `'A'` (chỉ số 1).
- **Đầu ra mong đợi:** `1` (chỉ có `'b'` hợp lệ vì `'b'` ở chỉ số 2 và `'B'` ở chỉ số 3, còn `'a'` có `'a'` cuối cùng ở chỉ số 4 lớn hơn `'A'` đầu tiên ở chỉ số 1).

### Trường hợp 2: Ký tự hoa xuất hiện trước ký tự thường cùng loại
- **Đầu vào:**
  ```text
  AaBb
  ```
- **Mô tả:** Chữ hoa `'A'` xuất hiện trước chữ thường `'a'`, chữ hoa `'B'` xuất hiện trước chữ thường `'b'`.
- **Đầu ra mong đợi:** `0`

### Trường hợp 3: Chuỗi dài không chứa bất kỳ chữ cái đặc biệt nào thỏa mãn
- **Đầu vào:**
  ```text
  xyzXYZz
  ```
- **Mô tả:** Ký tự `'z'` xuất hiện ở dạng thường tại cuối chuỗi sau khi đã có chữ hoa `'Z'`. Các ký tự `'x'`, `'y'` thỏa mãn.
- **Đầu ra mong đợi:** `2` (chỉ `'x'` và `'y'` thỏa mãn).

### Trường hợp 4: Chuỗi rỗng hoặc chỉ có một định dạng ký tự
- **Đầu vào:**
  ```text
  abcdefg
  ```
- **Mô tả:** Chỉ chứa chữ thường, không có chữ hoa nào.
- **Đầu ra mong đợi:** `0`

---

**Tổng kết:**
Bằng việc sử dụng cấu trúc lưu trữ mốc thời gian (chỉ số) cuối cùng của chữ thường và đầu tiên của chữ hoa, ta đã giải quyết bài toán với độ phức tạp tối ưu tuyệt đối $O(N)$ thời gian và $O(1)$ không gian. Logic được thiết kế ngắn gọn, tường minh và loại bỏ được các thao tác kiểm tra rườm rà.
