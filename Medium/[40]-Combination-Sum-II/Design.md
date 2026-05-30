# Tư duy thiết kế: Combination Sum II

## Vấn đề

Chúng ta cần tìm tất cả các tổ hợp số duy nhất từ một mảng `candidates` sao cho tổng của chúng bằng một số `target` cho trước. Bài toán đi kèm với hai điều kiện ràng buộc quan trọng:
- Mỗi số trong mảng `candidates` chỉ được sử dụng tối đa một lần trong mỗi tổ hợp.
- Kết quả không được chứa các tổ hợp trùng lặp.

Khó khăn lớn nhất ở đây là mảng `candidates` có thể chứa các phần tử có giá trị giống nhau. Nếu sinh tổ hợp một cách thông thường, chúng ta sẽ rất dễ tạo ra các tổ hợp trùng lặp về mặt giá trị, và việc sử dụng các cấu trúc dữ liệu như `std::set` để lọc trùng sau khi sinh sẽ cực kỳ tốn kém về cả thời gian lẫn bộ nhớ.

---

## Giải pháp

Hãy tưởng tượng bạn đang đi mua sắm trong một cửa hàng quà lưu niệm với một số tiền cố định trong ví là `target`.
- Các món đồ trên kệ có giá tiền tương ứng là các phần tử trong mảng `candidates`. Bạn chỉ được mua mỗi món đồ vật lý trên kệ tối đa một lần.
- Cửa hàng có thể có nhiều món đồ khác nhau nhưng có cùng giá tiền (ví dụ: hai chiếc bút cùng giá 2 đồng).
- Bạn muốn tìm tất cả các giỏ hàng độc nhất vô nhị (không trùng lặp về danh sách giá tiền các món đồ bên trong) sao cho tổng giá trị đúng bằng số tiền trong ví.

Để giải quyết bài toán này một cách hệ thống, chúng ta áp dụng thuật toán **Quay lui (Backtracking)** kết hợp với hai kỹ thuật cốt lõi:

**Sắp xếp danh sách kệ hàng trước khi chọn**
- Đầu tiên, chúng ta sắp xếp mảng `candidates` theo thứ tự tăng dần. Việc này giúp các món đồ có cùng mức giá nằm cạnh nhau, tạo tiền đề để loại bỏ trùng lặp và cắt tỉa nhánh cận một cách dễ dàng.

**Loại bỏ các món đồ trùng lặp ở cùng một bước chọn**
- Khi đang cân nhắc chọn món đồ tiếp theo cho giỏ hàng tại một bước cụ thể:
  - Nếu chúng ta gặp một món đồ có giá trùng với món đồ ngay trước nó ở cùng cấp độ chọn, và chúng ta đã không chọn món đồ trước đó, ta sẽ bỏ qua món đồ hiện tại.
  - Lý do là vì nếu chọn món đồ hiện tại, nó sẽ tạo ra những tổ hợp hoàn toàn giống hệt như tổ hợp mà món đồ trước đó có thể tạo ra.
  - *Lưu ý:* Chúng ta vẫn được phép chọn các món đồ trùng nhau nếu chúng nằm ở các cấp độ đệ quy sâu hơn (tương đương việc mua cả hai món đồ cùng giá trong cùng một giỏ hàng).

**Dừng sớm khi món đồ quá đắt (Nhánh cận)**
- Vì kệ hàng đã được sắp xếp tăng dần, nếu tại bất kỳ thời điểm nào chúng ta gặp một món đồ có giá lớn hơn số tiền còn lại trong ví, chúng ta có thể chắc chắn rằng tất cả các món đồ phía sau cũng sẽ đắt hơn số tiền còn lại.
- Lúc này, ta lập tức dừng việc tìm kiếm ở nhánh đó và quay lui, giúp tiết kiệm tối đa số bước duyệt.

---

## Tại sao tối ưu?

- Tránh sinh trùng lặp chủ động: Việc bỏ qua các phần tử trùng lặp ngay trong vòng lặp của bước Backtracking giúp chúng ta chỉ sinh ra các tổ hợp duy nhất. Độ phức tạp thời gian giảm đi rất nhiều so với việc sinh tất cả rồi mới lọc trùng.
- Cắt tỉa nhánh cận hiệu quả: Nhờ mảng đã sắp xếp, điều kiện `candidates[i] > remaining_target` cho phép ta kết thúc vòng lặp sớm bằng từ khóa `break` thay vì tiếp tục chạy hết mảng, giảm đáng kể số trạng thái cần duyệt trong cây quyết định.
- Độ phức tạp không gian: Chỉ sử dụng một mảng tạm thời để lưu tổ hợp hiện tại và bộ nhớ ngăn xếp đệ quy tỉ lệ thuận với độ sâu của cây quyết định (tối đa là số phần tử của `candidates`).

---

## Mô phỏng chạy thực tế

Giả sử `candidates = [2, 1, 2]`, `target = 3`.

- Bước 1: Sắp xếp mảng thành `[1, 2, 2]`.
- Bước 2: Bắt đầu hàm quay lui với giỏ hàng rỗng `[]` và ví tiền `remaining = 3`.
- Bước 3: Xét cấp độ chọn thứ nhất (chọn phần tử đầu tiên cho giỏ hàng):
  - Thử chọn số ở chỉ số 0 (giá trị 1):
    - Giỏ hàng lúc này: `[1]`, số tiền còn lại: `3 - 1 = 2`.
    - Đệ quy xuống cấp độ tiếp theo để chọn phần tử thứ hai từ các chỉ số còn lại `{1, 2}` (các giá trị `[2, 2]`):
      - Thử chọn số ở chỉ số 1 (giá trị 2):
        - Giỏ hàng lúc này: `[1, 2]`, số tiền còn lại: `2 - 2 = 0`.
        - Tìm thấy một tổ hợp hợp lệ! Lưu `[1, 2]` vào kết quả.
        - Quay lui: Bỏ 2 ra khỏi giỏ, giỏ hàng về lại `[1]`, tiền còn lại: 2.
      - Thử chọn số ở chỉ số 2 (giá trị 2):
        - Vì số này có giá trị trùng với số ở chỉ số 1 và cả hai đều ở cùng cấp độ chọn thứ hai, ta bỏ qua để tránh trùng lặp với tổ hợp `[1, 2]` đã tìm thấy trước đó.
    - Quay lui: Bỏ 1 ra khỏi giỏ, giỏ hàng về lại `[]`, tiền còn lại: 3.
  - Thử chọn số ở chỉ số 1 (giá trị 2):
    - Giỏ hàng lúc này: `[2]`, số tiền còn lại: `3 - 2 = 1`.
    - Đệ quy xuống cấp độ tiếp theo để chọn phần tử từ chỉ số `{2}` (giá trị `[2]`):
      - Thử chọn số ở chỉ số 2 (giá trị 2):
        - Giá trị 2 lớn hơn tiền còn lại (1). Vì mảng đã sắp xếp, ta dừng vòng lặp chọn này (cắt tỉa nhánh cận).
    - Quay lui: Bỏ 2 ra khỏi giỏ, giỏ hàng về lại `[]`, tiền còn lại: 3.
  - Thử chọn số ở chỉ số 2 (giá trị 2):
    - Trùng với số ở chỉ số 1 tại cùng cấp độ chọn thứ nhất, ta bỏ qua.

Kết quả cuối cùng thu được duy nhất một tổ hợp hợp lệ là `[[1, 2]]`.

---

## Các trường hợp kiểm thử mở rộng

Dưới đây là các trường hợp kiểm thử bổ sung để bạn tự kiểm chứng khi tự code:

### Trường hợp kiểm thử 1
- **Đầu vào:**
  ```text
  5
  2 5 2 1 2
  5
  ```
- **Giải thích:**
  - Sau khi sắp xếp ta có `[1, 2, 2, 2, 5]`.
  - Các tổ hợp không trùng lặp có tổng bằng 5 là:
    - Chọn số 1 và hai số 2 bất kỳ: `[1, 2, 2]`.
    - Chọn số 5: `[5]`.
- **Đầu ra mong đợi:**
  ```text
  [[1 2 2]
  [5]]
  ```

### Trường hợp kiểm thử 2
- **Đầu vào:**
  ```text
  7
  10 1 2 7 6 1 5
  8
  ```
- **Giải thích:**
  - Sau khi sắp xếp ta có `[1, 1, 2, 5, 6, 7, 10]`.
  - Các tổ hợp duy nhất có tổng bằng 8 là:
    - `[1, 1, 6]`
    - `[1, 2, 5]`
    - `[1, 7]`
    - `[2, 6]`
- **Đầu ra mong đợi:**
  ```text
  [[1 1 6]
  [1 2 5]
  [1 7]
  [2 6]]
  ```

### Trường hợp kiểm thử 3
- **Đầu vào:**
  ```text
  3
  3 3 3
  6
  ```
- **Giải thích:**
  - Có ba số 3. Mặc dù ta có thể chọn các số 3 ở các vị trí khác nhau để tạo thành tổng bằng 6, nhưng tất cả các tổ hợp đó đều có giá trị là `[3, 3]`. Để tránh trùng lặp, đầu ra chỉ được chứa duy nhất một tổ hợp này.
- **Đầu ra mong đợi:**
  ```text
  [[3 3]]
  ```
