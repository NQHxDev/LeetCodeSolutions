# Tư duy thiết kế: Swap Nodes in Pairs

## Vấn đề

Chúng ta được cung cấp một danh sách liên kết. Nhiệm vụ là hoán đổi vị trí của từng cặp nút liền kề nhau và trả về đầu danh sách mới. Yêu cầu bắt buộc là không được thay đổi giá trị lưu trữ bên trong các nút (value), mà phải thực sự thay đổi vị trí vật lý của chúng bằng cách sắp xếp lại các mối liên kết con trỏ.

Hãy tưởng tượng bạn đang điều phối một **Đại hội khiêu vũ đôi**. Các vũ công đang xếp thành một hàng dọc, nắm tay nhau theo thứ tự chẵn lẻ để di chuyển vào lễ đường (danh sách liên kết). Ban tổ chức yêu cầu: cứ mỗi cặp vũ công đi liền kề nhau (Vũ công 1 và Vũ công 2, Vũ công 3 và Vũ công 4...) phải đổi vị trí cho nhau. 

Nếu chúng ta giải quyết bài toán một cách hời hợt:
- **Phương pháp tráo đổi bảng tên (Value Swap)**: Chúng ta chỉ đơn giản bảo hai vũ công đổi thẻ tên cho nhau mà đứng nguyên vị trí cũ.
  - *Hạn chế*: Cách làm này vi phạm nghiêm trọng luật chơi của đề bài ("without modifying the values in the list's nodes"). Trong lập trình thực tế, việc copy dữ liệu lớn của một nút (chứa nhiều thông tin phức tạp) thay vì chỉ thay đổi liên kết con trỏ 8-byte là cực kỳ kém hiệu quả và dễ gây lỗi đồng bộ dữ liệu.

Do đó, các vũ công bắt buộc phải thực hiện những động tác buông tay và nắm tay người mới để xoay chuyển vị trí vật lý của mình trên sàn nhảy.

---

## Giải pháp

Để giải quyết bài toán một cách sạch sẽ và không tốn bộ nhớ phụ, chúng ta sử dụng thiết kế **Con trỏ dịch chuyển và Đổi vai khiêu vũ**:

Chúng ta thiết lập một nút giả làm **Người dắt tay dẫn đầu** (Dummy Node) đứng trước đầu hàng. Người này giúp chúng ta dễ dàng quản lý việc thay đổi đầu danh sách mà không cần viết thêm các điều kiện kiểm tra rườm rà.

Tại mỗi bước, chúng ta tập trung vào một nhóm gồm 3 nhân vật:
1. **Người dắt tay phía trước** (`prev`): Đang đứng ngay trước cặp vũ công hiện tại và đang nắm tay vũ công thứ nhất.
2. **Vũ công thứ nhất** (`first`): Vũ công đứng trước trong cặp hiện tại.
3. **Vũ công thứ hai** (`second`): Vũ công đứng sau trong cặp hiện tại.

Quy trình buông tay và nắm tay để hoán đổi vị trí của cặp đôi diễn ra qua ba động tác nhịp nhàng sau:

- **Động tác 1 (Buông tay và kết nối hậu phương)**: Vũ công thứ nhất buông tay vũ công thứ hai ra, và nắm lấy tay của người đi đầu tiên trong cặp tiếp theo phía sau (`first->next = second->next`).
- **Động tác 2 (Xoay chuyển cặp đôi)**: Vũ công thứ hai nắm lấy tay của vũ công thứ nhất (`second->next = first`).
- **Động tác 3 (Kết nối tiền tuyến)**: Người dắt tay phía trước buông tay vũ công thứ nhất ra, và nắm lấy tay vũ công thứ hai (`prev->next = second`).

Sau khi hoán đổi xong, cặp đôi đã đổi chỗ thành công. Để chuẩn bị cho cặp tiếp theo, Người dắt tay dịch chuyển lên đứng ngay sau vũ công thứ nhất (lúc này đã nằm ở vị trí thứ hai của cặp) và tiếp tục thực hiện quy trình cho đến khi hết hàng khiêu vũ.

---

## Tại sao tối ưu?

- **Hiệu năng thời gian tuyệt đối ($O(N)$)**: Danh sách liên kết chỉ được duyệt qua đúng một lần duy nhất. Tại mỗi cặp, chúng ta chỉ tốn đúng 3 phép gán con trỏ thời gian hằng số $O(1)$.
- **Tiết kiệm bộ nhớ tối đa ($O(1)$)**: Toàn bộ quá trình hoán đổi liên kết diễn ra trực tiếp ngay trên bộ nhớ hiện tại. Thuật toán không tạo thêm bất kỳ nút danh sách mới nào, chỉ sử dụng 3 biến con trỏ tạm để lưu vết vị trí.
- **Tính an toàn cao**: Việc sử dụng Dummy Node giúp loại bỏ các lỗi tham chiếu con trỏ Null khi danh sách rỗng hoặc chỉ có một phần tử duy nhất.

---

## Mô phỏng điệu nhảy hoán vị

Hãy cùng quan sát cách hàng vũ công gồm 4 người `[1 -> 2 -> 3 -> 4]` thực hiện hoán đổi:

**Khởi tạo:**
- Nút giả `dummy` liên kết đến `1`.
- Con trỏ `prev` đặt tại `dummy`.

**Vòng lặp 1 (Xử lý cặp 1 và 2):**
- Xác định nhân vật: `first = 1`, `second = 2`.
- **Động tác 1**: `1` buông `2`, nắm lấy `3` (phía sau `2`).
  * Trạng thái liên kết: `1 -> 3`
- **Động tác 2**: `2` quay lại nắm lấy `1`.
  * Trạng thái liên kết: `2 -> 1 -> 3`
- **Động tác 3**: `dummy` (`prev`) buông `1`, nắm lấy `2`.
  * Trạng thái liên kết chung: `dummy -> 2 -> 1 -> 3 -> 4`
- **Dịch chuyển**: `prev` chuyển đến đứng tại `1` để chuẩn bị cho cặp tiếp theo.

**Vòng lặp 2 (Xử lý cặp 3 và 4):**
- Xác định nhân vật: `first = 3`, `second = 4`.
- **Động tác 1**: `3` buông `4`, nắm lấy phần tử trống phía sau `4` (`nullptr`).
  * Trạng thái liên kết: `3 -> nullptr`
- **Động tác 2**: `4` quay lại nắm lấy `3`.
  * Trạng thái liên kết: `4 -> 3 -> nullptr`
- **Động tác 3**: `1` (`prev`) buông `3`, nắm lấy `4`.
  * Trạng thái liên kết chung: `dummy -> 2 -> 1 -> 4 -> 3 -> nullptr`
- **Dịch chuyển**: `prev` chuyển đến đứng tại `3`.

**Kết thúc:**
- Phần tử phía sau `prev` (lúc này là `3`) là `nullptr` $\rightarrow$ Hết hàng.
- Trả về đầu danh sách mới là `dummy->next` (tức là nút `2`).
- Kết quả thu được: `[2 -> 1 -> 4 -> 3]`

---

## Các trường hợp kiểm thử mở rộng

Dưới đây là các kịch bản kiểm thử đặc thù giúp đánh giá tính toàn diện của giải pháp thiết kế:

### Thử thách danh sách có số lượng phần tử lẻ
- **Đầu vào**: `head = [1, 2, 3, 5, 7]`
- **Mô tả**: Danh sách có 5 phần tử.
- **Tiến trình dự kiến**: Cặp đầu `[1, 2]` đổi thành `[2, 1]`, cặp hai `[3, 5]` đổi thành `[5, 3]`. Phần tử cuối cùng `[7]` không có cặp liền kề phía sau nên được giữ nguyên liên kết và đứng yên ở cuối hàng.
- **Kết quả kỳ vọng**: `[2, 1, 5, 3, 7]`

### Thử thách danh sách tối giản hai phần tử
- **Đầu vào**: `head = [10, 20]`
- **Mô tả**: Danh sách chỉ gồm duy nhất một cặp đôi hoàn chỉnh.
- **Tiến trình dự kiến**: Thực hiện tráo đổi một lần duy nhất và kết thúc quy trình ngay lập tức.
- **Kết quả kỳ vọng**: `[20, 10]`

### Thử thách các giá trị trùng lặp tăng dần
- **Đầu vào**: `head = [1, 1, 2, 2, 3, 3]`
- **Mô tả**: Danh sách chứa các cặp số trùng lặp liên tục.
- **Tiến trình dự kiến**: Các con trỏ vật lý hoán đổi vị trí bình thường. Giá trị biểu diễn trực quan trên màn hình không đổi vì các phần tử trong cặp có giá trị giống nhau, nhưng cấu trúc con trỏ bên dưới đã được xoay chuyển hoàn toàn.
- **Kết quả kỳ vọng**: `[1, 1, 2, 2, 3, 3]`

### Thử thách danh sách rỗng và danh sách đơn tử
- **Đầu vào**: `head = []` hoặc `head = [9]`
- **Mô tả**: Danh sách không có phần tử nào hoặc chỉ có duy nhất một phần tử đứng một mình.
- **Tiến trình dự kiến**: Thuật toán kiểm tra điều kiện lặp phát hiện không có đủ một cặp (`first` hoặc `second` là `nullptr`), lập tức bỏ qua vòng lặp và trả về nguyên trạng ban đầu an toàn.
- **Kết quả kỳ vọng**: `[]` hoặc `[9]`

---

**Tổng kết:** Bằng việc sử dụng nút giả dẫn đầu và quy trình hoán vị ba động tác chuyển giao con trỏ linh hoạt, chúng ta đã giải quyết bài toán đổi chỗ cặp đôi một cách an toàn, tường minh và đạt hiệu suất tối đa mà không gây hao tốn tài nguyên bộ nhớ.
