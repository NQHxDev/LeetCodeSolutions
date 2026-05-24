# Tư duy thiết kế: Đảo ngược danh sách liên kết theo nhóm (Reverse Nodes in k-Group)

Việc đảo ngược các nhóm phần tử trong danh sách liên kết là một thử thách thú vị, rèn luyện khả năng quản lý con trỏ và tổ chức liên kết cấu trúc dữ liệu một cách chặt chẽ.

## Vấn đề

Hãy tưởng tượng một đoàn tàu gồm nhiều toa nối tiếp nhau. Chúng ta được giao nhiệm vụ sắp xếp lại đoàn tàu này theo từng phân đoạn có độ dài cố định là $k$. Với mỗi nhóm gồm đúng $k$ toa, ta tiến hành tháo các khớp nối, đảo ngược thứ tự các toa trong nhóm đó, rồi nối chúng lại với nhau. Nếu phân đoạn cuối cùng ở đuôi tàu không có đủ $k$ toa, ta sẽ giữ nguyên thứ tự của chúng mà không đảo ngược.

Trong cấu trúc danh sách liên kết, khó khăn lớn nhất là việc thay đổi các liên kết (`next`) giữa các nút mà không làm mất dấu vết các phần tử đứng trước và đứng sau của nhóm hiện tại, đồng thời đảm bảo không tốn thêm bộ nhớ bổ sung để lưu trữ giá trị của các nút.

---

## Giải pháp

Để giải quyết bài toán với hiệu năng tối ưu, chúng ta có thể sử dụng phương pháp duyệt và đảo ngược trực tiếp trên các liên kết con trỏ theo các bước sau:

### Kiểm tra độ dài phân đoạn
Trước khi đảo ngược bất kỳ nhóm nào, ta cần duyệt trước $k$ bước từ vị trí hiện tại để xác định xem có đủ $k$ nút hay không. Nếu không đủ, ta giữ nguyên và kết thúc quá trình.

### Đảo ngược nhóm phần tử
Khi đã xác định có đủ $k$ phần tử, ta thực hiện đảo ngược thứ tự liên kết của $k$ nút này bằng cách sử dụng các con trỏ tạm thời (`prev`, `curr`, `next_node`).

### Nối lại các nhóm
- Đầu của nhóm sau khi đảo ngược (vốn là nút thứ $k$ ban đầu) phải được nối với nhóm đứng trước nó.
- Đuôi của nhóm sau khi đảo ngược (vốn là nút thứ nhất ban đầu) phải được nối với phần đầu của nhóm tiếp theo.
- Để quản lý dễ dàng liên kết ở nhóm đầu tiên, ta sử dụng một nút giả (Dummy Node) làm điểm tựa ban đầu.

Quá trình này lặp đi lặp lại cho đến khi không còn đủ $k$ phần tử để đảo ngược.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian:** Độ phức tạp thời gian là $O(n)$ vì chúng ta chỉ duyệt qua mỗi nút của danh sách liên kết tối đa hai lần: một lần để kiểm tra xem có đủ $k$ phần tử hay không, và một lần để thực hiện đảo ngược.
- **Tiết kiệm bộ nhớ:** Độ phức tạp không gian là $O(1)$. Thuật toán hoàn toàn thực hiện biến đổi tại chỗ (in-place) bằng cách thay đổi các liên kết con trỏ `next`, không cần cấp phát thêm bộ nhớ cho mảng phụ hay sử dụng ngăn xếp đệ quy sâu.

---

## Mô phỏng luồng xử lý

Giả sử danh sách liên kết ban đầu là `1 -> 2 -> 3 -> 4 -> 5` và nhóm có độ dài `k = 2`.
Sử dụng một nút giả `Dummy` đứng trước danh sách: `Dummy -> 1 -> 2 -> 3 -> 4 -> 5`.
Con trỏ `groupPrev` ban đầu chỉ vào `Dummy`.

### Nhóm thứ nhất
- Kiểm tra từ `groupPrev` xem có đủ 2 nút hay không: `1` và `2` (đủ). Nút `groupNext` tạm thời chỉ vào nút tiếp theo là `3`.
- Thực hiện đảo ngược đoạn `1 -> 2` thành `2 -> 1`.
- Nối liên kết: `groupPrev->next` chỉ vào `2`, và nút `1` nối với `groupNext` (tức là `3`).
- Danh sách tạm thời: `Dummy -> 2 -> 1 -> 3 -> 4 -> 5`.
- Cập nhật `groupPrev = 1` (đuôi của nhóm vừa đảo ngược).

### Nhóm thứ hai
- Kiểm tra từ `groupPrev` xem có đủ 2 nút hay không: `3` và `4` (đủ). Nút `groupNext` tạm thời chỉ vào nút tiếp theo là `5`.
- Thực hiện đảo ngược đoạn `3 -> 4` thành `4 -> 3`.
- Nối liên kết: `groupPrev->next` chỉ vào `4`, và nút `3` nối với `groupNext` (tức là `5`).
- Danh sách tạm thời: `Dummy -> 2 -> 1 -> 4 -> 3 -> 5`.
- Cập nhật `groupPrev = 3`.

### Nhóm thứ ba
- Kiểm tra từ `groupPrev` xem có đủ 2 nút hay không: chỉ còn duy nhất nút `5` (không đủ 2).
- Giữ nguyên phần còn lại.

Kết quả cuối cùng thu được là: `2 -> 1 -> 4 -> 3 -> 5`.

---

## Các trường hợp kiểm thử bổ sung

- **Trường hợp 1:** Danh sách `[1, 2, 3, 4, 5]`, `k = 1`
  - Mô tả: Khi $k = 1$, không có sự thay đổi nào về thứ tự các nút. Danh sách đầu ra phải giữ nguyên như danh sách đầu vào.
  - Kết quả mong đợi: `[1, 2, 3, 4, 5]`

- **Trường hợp 2:** Danh sách `[1, 2, 3]`, `k = 4`
  - Mô tả: Độ dài của danh sách nhỏ hơn $k$. Toàn bộ danh sách phải được giữ nguyên.
  - Kết quả mong đợi: `[1, 2, 3]`

- **Trường hợp 3:** Danh sách `[1, 2, 3, 4, 5, 6]`, `k = 3`
  - Mô tả: Độ dài danh sách chia hết cho $k$. Tất cả các nhóm đều được đảo ngược hoàn toàn.
  - Kết quả mong đợi: `[3, 2, 1, 6, 5, 4]`

- **Trường hợp 4:** Danh sách `[10]`, `k = 2`
  - Mô tả: Danh sách chỉ có một phần tử duy nhất, nhỏ hơn $k$.
  - Kết quả mong đợi: `[10]`

- **Trường hợp 5:** Danh sách `[1, 2, 3, 4, 5, 6, 7]`, `k = 3`
  - Mô tả: Độ dài danh sách không chia hết cho $k$. Nhóm cuối cùng `[7]` có độ dài nhỏ hơn 3 nên được giữ nguyên.
  - Kết quả mong đợi: `[3, 2, 1, 6, 5, 4, 7]`
