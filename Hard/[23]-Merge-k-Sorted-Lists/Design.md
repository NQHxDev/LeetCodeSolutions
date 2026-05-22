# Tư duy thiết kế: Merge k Sorted Lists

## Vấn đề

Chúng ta được cung cấp $k$ danh sách liên kết đã được sắp xếp theo thứ tự tăng dần. Nhiệm vụ là hợp nhất tất cả chúng thành một danh sách liên kết duy nhất được sắp xếp hoàn chỉnh.

Hãy tưởng tượng bạn là **Trưởng ga của một Cảng hàng hóa quốc tế**. Tại cảng, có $k$ băng chuyền hàng hóa đang chạy song song (mỗi băng chuyền là một danh sách liên kết). Trên mỗi băng chuyền, các thùng hàng đã được sắp xếp ngăn nắp theo mã số từ nhỏ đến lớn (tăng dần). Nhiệm vụ của bạn là dẫn tất cả các thùng hàng này về một băng chuyền chính duy nhất sao cho toàn bộ kiện hàng đi ra đều được sắp xếp hoàn hảo theo thứ tự mã số.

Nếu chúng ta giải quyết bằng các phương pháp thông thường:
- **Phương pháp thu gom rồi sắp xếp lại (Collect and Sort)**: Chúng ta dỡ tất cả các thùng hàng từ $k$ băng chuyền xuống một bãi đất trống, sau đó gọi xe cẩu sắp xếp lại toàn bộ từ đầu.
  - *Hạn chế*: Cách làm này cực kỳ lãng phí thời gian và năng lượng ($O(N \log N)$ với $N$ là tổng số thùng hàng) vì nó vứt bỏ hoàn toàn một tài sản vô giá: các băng chuyền con vốn dĩ đã được sắp xếp sẵn từ trước.
- **Phương pháp quét tuyến tính thủ công (Naive Merge)**: Bạn cử một nhân viên đứng ở ngã rẽ của $k$ băng chuyền. Người này liên tục nhìn vào $k$ thùng hàng đi đầu của tất cả các băng chuyền, tìm ra thùng hàng có mã số nhỏ nhất, gạt nó vào băng chuyền chính, rồi lặp lại quy trình.
  - *Hạn chế*: Mỗi lần chọn ra một thùng hàng, nhân viên phải so sánh đồng thời giữa tất cả $k$ đầu băng chuyền. Tổng số lần so sánh sẽ lên tới $O(N \cdot k)$. Khi số lượng băng chuyền $k$ tăng lên hàng nghìn, nhân viên này sẽ bị quá tải lập tức, gây ách tắc toàn bộ cảng hàng hóa.

Do đó, chúng ta cần những thiết kế thông minh hơn để tối ưu hóa quy trình hợp nhất này.

---

## Giải pháp

Để đạt được hiệu năng vượt trội, chúng ta có hai chiến thuật thiết kế xuất sắc:

### Chiến thuật Chia để trị (Divide and Conquer) - Giải đấu loại trực tiếp

Thay vì bắt một người phải quản lý và hợp nhất cả $k$ băng chuyền cùng một lúc, chúng ta tổ chức một giải đấu loại trực tiếp (tương tự như vòng chung kết bóng đá):
- **Vòng 1**: Hợp nhất Băng chuyền 1 với Băng chuyền 2 thành một băng chuyền mới. Hợp nhất Băng chuyền 3 với Băng chuyền 4... Cứ thế ghép cặp song song. Sau vòng này, số lượng băng chuyền cần quản lý giảm đi một nửa (chỉ còn $k/2$ băng chuyền).
- **Vòng 2**: Tiếp tục ghép cặp và hợp nhất các băng chuyền chiến thắng ở vòng trước. Số băng chuyền giảm xuống còn $k/4$.
- Quy trình lặp lại cho đến khi chỉ còn lại đúng một băng chuyền duy nhất.

Mỗi trận đấu ghép cặp giữa hai danh sách liên kết đơn lẻ được thực hiện cực kỳ đơn giản và nhanh chóng bằng thuật toán Hợp nhất hai danh sách đã sắp xếp (Merge Two Sorted Lists) chỉ tốn thời gian tuyến tính $O(L_1 + L_2)$.

### Chiến thuật Hàng đợi ưu tiên (Priority Queue) - Chiếc cân điện tử thông minh

Chúng ta đặt một chiếc cân điện tử tự động cân bằng (Min-Heap) tại giao điểm của các băng chuyền:
- Đầu tiên, ta chỉ lấy đúng $k$ thùng hàng đứng đầu của $k$ băng chuyền đặt lên chiếc cân này.
- Chiếc cân điện tử sẽ ngay lập tức chỉ ra thùng hàng có mã số nhỏ nhất trong thời gian cực ngắn nhờ cấu trúc cây nhị phân.
- Ta lấy thùng hàng nhỏ nhất đó xếp vào băng chuyền chính. 
- Ngay sau đó, ta lấy thùng hàng tiếp theo của *chính băng chuyền vừa bị lấy mất thùng* đặt lên cân để thay thế. Chiếc cân sẽ tự động cân bằng lại.
- Lặp lại cho đến khi tất cả các băng chuyền đều trống rỗng.

---

## Tại sao tối ưu?

Cả hai chiến thuật trên đều mang lại hiệu năng vượt bậc so với các giải pháp thông thường:

- **Tốc độ Logarit vượt trội ($O(N \log k)$)**: 
  * Với *Chia để trị*: Giải đấu loại trực tiếp có chiều cao cây đấu là $\log_2 k$ vòng. Ở mỗi vòng đấu, tổng số thùng hàng được xử lý và di chuyển qua các trận đấu luôn là $N$. Vì vậy, tổng thời gian hoạt động là $O(N \log k)$.
  * Với *Hàng đợi ưu tiên*: Mỗi lần chiếc cân điện tử lấy ra phần tử nhỏ nhất và tự cân bằng lại chỉ tốn thời gian $O(\log k)$. Với tổng số $N$ thùng hàng cần xử lý, tổng thời gian là $O(N \log k)$.
- **Tiết kiệm bộ nhớ**:
  * *Chia để trị*: Nếu triển khai bằng vòng lặp (Iterative), thuật toán chỉ tái cấu trúc lại các liên kết con trỏ sẵn có trên bộ nhớ mà không cần cấp phát thêm bất kỳ nút danh sách mới nào. Độ phức tạp bộ nhớ phụ đạt mức lý tưởng $O(1)$.
  * *Hàng đợi ưu tiên*: Chiếc cân điện tử tại mọi thời điểm chỉ chứa tối đa $k$ phần tử đại diện cho $k$ băng chuyền, bộ nhớ phụ tốn tối đa là $O(k)$.

---

## Mô phỏng hành trình đấu loại trực tiếp

Hãy cùng quan sát cách chiến thuật **Chia để trị** hợp nhất $k = 4$ danh sách sau:
`L1 = [1, 4]`, `L2 = [2, 5]`, `L3 = [3, 6]`, `L4 = [0, 7]`

**Khởi tạo:**
- Danh sách ban đầu: `[L1, L2, L3, L4]`

**Vòng đấu thứ nhất:**
- **Trận 1**: Hợp nhất `L1 = [1, 4]` và `L2 = [2, 5]`
  * So sánh đầu danh sách: $1 < 2 \rightarrow$ lấy $1$.
  * So sánh tiếp theo: $4 > 2 \rightarrow$ lấy $2$.
  * So sánh tiếp theo: $4 < 5 \rightarrow$ lấy $4$.
  * Còn lại phần tử $5 \rightarrow$ lấy nốt $5$.
  * Kết quả Trận 1: `L12 = [1, 2, 4, 5]`
- **Trận 2**: Hợp nhất `L3 = [3, 6]` và `L4 = [0, 7]`
  * Kết quả Trận 2: `L34 = [0, 3, 6, 7]`
- Danh sách sau Vòng 1: `[L12, L34]` (Số danh sách đã giảm từ 4 xuống 2).

**Vòng đấu thứ hai (Chung kết):**
- **Trận 3**: Hợp nhất `L12 = [1, 2, 4, 5]` và `L34 = [0, 3, 6, 7]`
  * So sánh đầu danh sách: $1 > 0 \rightarrow$ lấy $0$.
  * So sánh tiếp theo: $1 < 3 \rightarrow$ lấy $1$.
  * So sánh tiếp theo: $2 < 3 \rightarrow$ lấy $2$.
  * So sánh tiếp theo: $4 > 3 \rightarrow$ lấy $3$.
  * So sánh tiếp theo: $4 < 6 \rightarrow$ lấy $4$.
  * So sánh tiếp theo: $5 < 6 \rightarrow$ lấy $5$.
  * Còn lại `[6, 7]` ở danh sách hai $\rightarrow$ nạp nốt `[6, 7]`.
  * Kết quả chung cuộc: `[0, 1, 2, 3, 4, 5, 6, 7]`

Chỉ sau 2 vòng đấu ghép cặp song song, toàn bộ dữ liệu đã được hợp nhất hoàn hảo.

---

## Các trường hợp kiểm thử mở rộng

Dưới đây là các kịch bản kiểm thử đặc trưng nhằm chứng minh tính ổn định của thiết kế:

### Thử thách các đoàn tàu lệch pha giá trị hoàn toàn
- **Đầu vào**: `lists = [[1, 2, 3], [10, 11], [100, 101, 102]]`
- **Mô tả**: Các danh sách có khoảng giá trị tách biệt hoàn toàn và nằm ở các phân khúc khác nhau.
- **Tiến trình dự kiến**: Thuật toán ghép nối tuần tự mà không gặp bất kỳ xung đột nào về hoán vị phần tử, các danh sách lớn sẽ được nối đuôi vào sau một cách trơn tru.
- **Kết quả kỳ vọng**: `[1, 2, 3, 10, 11, 100, 101, 102]`

### Thử thách danh sách rỗng xen kẽ
- **Đầu vào**: `lists = [[], [1, 5], [], [2, 4], []]`
- **Mô tả**: Có nhiều danh sách rỗng nằm xen kẽ giữa các danh sách có giá trị thực tế.
- **Tiến trình dự kiến**: Thiết kế phải xử lý an toàn trường hợp danh sách rỗng bằng cách bỏ qua chúng ngay từ đầu, tránh các lỗi truy cập vùng nhớ con trỏ Null (Null Pointer Dereference).
- **Kết quả kỳ vọng**: `[1, 2, 4, 5]`

### Thử thách các giá trị trùng lặp mật độ cao
- **Đầu vào**: `lists = [[2, 2, 2], [2, 2], [2, 2, 2, 2]]`
- **Mô tả**: Tất cả các danh sách con đều chỉ chứa duy nhất một giá trị là số 2 nhưng với số lượng phần tử khác nhau.
- **Tiến trình dự kiến**: Thuật toán duy trì tính ổn định của cấu trúc liên kết, đếm đúng số lượng phần tử xuất hiện và liên kết chúng thành một chuỗi duy nhất dài hơn.
- **Kết quả kỳ vọng**: `[2, 2, 2, 2, 2, 2, 2, 2, 2]`

### Thử thách chênh lệch kích thước cực đại
- **Đầu vào**: `lists = [[1, 2, 3, 4, 5, 6, 7], [0], [8]]`
- **Mô tả**: Một danh sách rất dài và nhiều danh sách siêu ngắn chỉ có 1 phần tử.
- **Tiến trình dự kiến**: Việc chia đôi ghép cặp vẫn diễn ra bình thường. Các danh sách ngắn sẽ nhanh chóng được tích hợp vào danh sách lớn mà không làm suy giảm hiệu năng hệ thống.
- **Kết quả kỳ vọng**: `[0, 1, 2, 3, 4, 5, 6, 7, 8]`

---

**Tổng kết:** Bằng cách áp dụng tư duy chia để trị hoặc tận dụng hàng đợi ưu tiên, chúng ta đã chuyển đổi một bài toán hợp nhất phức tạp thành một quy trình phối hợp nhịp nhàng có độ phức tạp thời gian tối ưu $O(N \log k)$. Các mối liên kết của danh sách liên kết được tái cấu trúc linh hoạt ngay trên bộ nhớ mà không phát sinh chi phí hao tổn tài nguyên hệ thống.
