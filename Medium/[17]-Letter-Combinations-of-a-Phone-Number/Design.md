# Tư duy thiết kế: Tổ hợp chữ cái từ số điện thoại (Letter Combinations of a Phone Number)

Bài toán chuyển đổi dãy số điện thoại thành các tổ hợp chữ cái tương ứng là một ví dụ điển hình về việc duyệt toàn bộ không gian trạng thái (State Space Search). Thách thức lớn nhất ở đây là tạo ra mọi tổ hợp khả thi mà không bỏ sót và không bị lặp.

## Vấn đề: Sự bùng nổ tổ hợp lựa chọn

Trên bàn phím điện thoại cổ điển, mỗi chữ số từ 2 đến 9 đại diện cho một nhóm gồm 3 hoặc 4 chữ cái. Khi người dùng nhập vào một chuỗi chữ số, số lượng tổ hợp chữ cái có thể được tạo ra sẽ tăng lên theo cấp số nhân (hàm mũ).

Nếu chỉ sử dụng các vòng lặp `for` lồng nhau một cách thủ công, chúng ta sẽ gặp bế tắc khi chiều dài chuỗi đầu vào thay đổi động. Chúng ta cần một cơ chế linh hoạt để tự động mở rộng số lượng vòng lặp tương ứng với số lượng chữ số được nhập vào.

---

## Giải pháp: Tra cứu thông tin và Quay lui (Backtracking)

Để giải quyết bài toán này, chúng ta kết hợp hai công cụ:

1. **Sổ tay tra cứu (Mapping Table):** Sử dụng một cấu trúc dữ liệu tĩnh (như mảng chuỗi) đóng vai trò như một cuốn sổ tay tra cứu nhanh từ chữ số sang cụm chữ cái tương ứng. Việc này chuyển đổi hành vi tìm kiếm phức tạp thành thao tác tra cứu hằng số $O(1)$.
2. **Thuật toán Quay lui (Backtracking):** Hãy tưởng tượng bạn đang khám phá một mê cung có nhiều lối rẽ. Tại mỗi ngã rẽ (chữ số hiện tại), bạn chọn thử một con đường (chữ cái đầu tiên), tiếp tục đi sâu vào trong để chọn các chữ cái tiếp theo. Khi đi đến đường cụt (hoàn thành một tổ hợp có độ dài bằng chuỗi số ban đầu), bạn ghi lại tổ hợp này vào danh sách kết quả. Sau đó, bạn **quay lui (backtrack)** lại ngã rẽ trước đó để thử con đường khác.

**Quy tắc hoạt động:**
- **Trạng thái dừng:** Nếu độ dài của tổ hợp chữ cái hiện tại bằng độ dài chuỗi chữ số ban đầu, ta lưu tổ hợp này lại và kết thúc nhánh duyệt.
- **Tiến trình duyệt:** Lấy danh sách các chữ cái tương ứng với chữ số hiện tại từ sổ tay tra cứu. Với mỗi chữ cái, ta thêm vào tổ hợp tạm thời và gọi đệ quy để xử lý chữ số tiếp theo, sau đó rút chữ cái đó ra để thử chữ cái khác.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Không gian trạng thái tối thiểu:** Backtracking chỉ tạo ra các tổ hợp hợp lệ và đi trực tiếp tới kết quả mà không thực hiện bất kỳ phép toán thừa hay trùng lặp nào.
- **Độ phức tạp thời gian:** $O(4^N)$ trong trường hợp xấu nhất (khi tất cả các chữ số đều đại diện cho 4 chữ cái như 7 và 9), với $N$ là độ dài chuỗi số. Đây là giới hạn dưới bắt buộc vì chúng ta bắt buộc phải sinh ra toàn bộ kết quả đầu ra.
- **Độ phức tạp không gian:** $O(N)$ do độ sâu của ngăn xếp đệ quy tối đa chỉ bằng độ dài của chuỗi đầu vào, cực kỳ tiết kiệm bộ nhớ so với việc sinh tổ hợp bằng khử đệ quy (BFS/Queue).

---

## Mô phỏng luồng xử lý chi tiết

Giả sử chuỗi đầu vào: `digits = "23"`
Sổ tay tra cứu: `2 -> "abc"`, `3 -> "def"`

Hành trình đệ quy quay lui sẽ diễn ra như sau:

**Bước 1: Bắt đầu tại chỉ số 0 (Chữ số '2')**
- Nhóm chữ cái tương ứng: `"abc"`
- Chọn `'a'`: Tổ hợp hiện tại là `"a"`. Tiến tới chỉ số 1.

**Bước 2: Xử lý chỉ số 1 (Chữ số '3')**
- Nhóm chữ cái tương ứng: `"def"`
- Chọn `'d'`: Tổ hợp hiện tại là `"ad"`. Tiến tới chỉ số 2 (Đạt độ dài yêu cầu). Lưu `"ad"`.
- Quay lui: Bỏ `'d'`, chọn `'e'`: Tổ hợp hiện tại là `"ae"`. Lưu `"ae"`.
- Quay lui: Bỏ `'e'`, chọn `'f'`: Tổ hợp hiện tại là `"af"`. Lưu `"af"`.
- Quay lui: Bỏ `'f'`. Hết lựa chọn tại chỉ số 1, quay lui về chỉ số 0.

**Bước 3: Trở lại chỉ số 0**
- Bỏ `'a'`, chọn `'b'`: Tổ hợp hiện tại là `"b"`. Tiến tới chỉ số 1.
- Chọn lần lượt `'d'`, `'e'`, `'f'` để sinh ra và lưu các tổ hợp: `"bd"`, `"be"`, `"bf"`.
- Quay lui về chỉ số 0, bỏ `'b'`, chọn `'c'`.
- Tiếp tục tương tự để sinh ra và lưu: `"cd"`, `"ce"`, `"cf"`.

**Kết quả cuối cùng:** `["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]`

---

## Test Case mở rộng

Các trường hợp kiểm thử dưới đây được thiết kế độc lập nhằm kiểm tra toàn diện hoạt động của thuật toán:

- **Case 1 (Chuỗi rỗng):** `digits = ""` -> Kết quả: `[]` (Thuật toán cần xử lý biên để tránh trả về một danh sách chứa chuỗi rỗng `[""]`).
- **Case 2 (Chữ số có 4 ký tự liên tiếp):** `digits = "7"` -> Kết quả: `["p", "q", "r", "s"]` (Đảm bảo cấu trúc dữ liệu ánh xạ chính xác số lượng ký tự khác nhau của từng phím).
- **Case 3 (Độ dài tối đa của bài toán):** `digits = "234"` -> Kết quả gồm 27 tổ hợp từ `"adg"` đến `"cfi"` (Kiểm tra khả năng đệ quy sâu mà không bị tràn bộ nhớ).
- **Case 4 (Chữ số lặp lại):** `digits = "22"` -> Kết quả: `["aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"]` (Đảm bảo việc quay lui hoạt động độc lập trên từng vị trí dù giá trị trùng nhau).

---

**Tổng kết:** Bằng cách biến việc tìm kiếm thành tra cứu bảng tĩnh và áp dụng kỹ thuật đệ quy quay lui, chúng ta đã giải quyết bài toán sinh tổ hợp động một cách tự nhiên, thanh thoát và tối ưu nhất về mặt tài nguyên hệ thống.
