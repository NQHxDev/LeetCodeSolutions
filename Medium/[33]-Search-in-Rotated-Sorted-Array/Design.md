# Tư duy thiết kế: Search in Rotated Sorted Array

## Vấn đề: Cuốn từ điển bị xé rời và ghép ngược

Hãy tưởng tượng chúng ta có một cuốn từ điển dày cộp, trong đó mọi từ vựng đã được sắp xếp theo thứ tự bảng chữ cái hoàn hảo từ A đến Z. Đột nhiên, ai đó xé cuốn từ điển ra làm hai phần tại một trang ngẫu nhiên, rồi đem phần sau đặt lên trước phần trước. Kết quả là cuốn từ điển bây giờ bắt đầu từ chữ M đến Z, rồi nhảy ngược về A đến L.

Nhiệm vụ của chúng ta là tìm kiếm một từ cụ thể (`target`) trong cuốn từ điển bị ghép ngược này, và phải tìm được nhanh nhất có thể. Đề bài yêu cầu thuật toán chạy trong thời gian $O(\log N)$, tức là mỗi bước quyết định phải loại bỏ được một nửa số trang chưa xem.

Nếu sử dụng cách **Duyệt tuyến tính (Linear Scan)**:
- Ta lật từng trang từ đầu đến cuối cuốn từ điển cho đến khi tìm thấy từ cần tìm.
- **Hệ quả**: Với cuốn từ điển 5.000 trang, trường hợp xấu nhất ta phải lật qua toàn bộ 5.000 trang. Cách làm này quá chậm chạp, vi phạm yêu cầu $O(\log N)$ của đề bài và không tận dụng được tính chất đã sắp xếp sẵn có.

Điểm mấu chốt cần nhận ra: Mặc dù cuốn từ điển đã bị xáo trộn, nó không hề hỗn loạn hoàn toàn. Bên trong nó vẫn tồn tại hai nửa liên tục được sắp xếp tăng dần. Chúng ta có thể khai thác tính chất trật tự còn sót lại này để thực hiện tìm kiếm nhị phân.

---

## Giải pháp: Kính lúp hai mặt và phép phán đoán nửa sáng

Thay vì lật từng trang một, chúng ta sử dụng một chiếc **Kính lúp hai mặt** đặt ở chính giữa cuốn từ điển. Chiếc kính lúp này giúp chúng ta quan sát được cả hai nửa cuốn sách cùng lúc và đưa ra phán đoán thông minh: nửa nào đang giữ trật tự hoàn hảo, và từ ta cần tìm có thể nằm ở nửa nào.

**Nguyên lý vàng**: Trong một mảng đã sắp xếp rồi bị xoay, khi ta chia đôi tại bất kỳ điểm nào, luôn luôn có ít nhất một nửa giữ nguyên thứ tự tăng dần. Đây chính là "nửa sáng" mà chúng ta có thể tin tưởng hoàn toàn.

**Bước 1: Đặt kính lúp vào chính giữa**
Khởi tạo hai mốc đánh dấu `left` (trang đầu) và `right` (trang cuối). Tính vị trí giữa `mid` để đặt kính lúp. Nếu `nums[mid]` chính là `target`, ta đã tìm thấy ngay lập tức.

**Bước 2: Nhận diện "Nửa sáng" (nửa được sắp xếp)**
- Nếu `nums[left] <= nums[mid]`: Nửa bên trái đang giữ trật tự tăng dần hoàn hảo. Đây là Nửa sáng bên trái.
- Ngược lại: Nửa bên phải chắc chắn đang giữ trật tự tăng dần. Đây là Nửa sáng bên phải.

**Bước 3: Phán đoán target nằm ở đâu**
Khi đã biết nửa nào là Nửa sáng, ta kiểm tra xem `target` có nằm trong khoảng giá trị của Nửa sáng đó hay không:
- Nếu `target` nằm trong phạm vi của Nửa sáng, ta thu hẹp phạm vi tìm kiếm vào nửa đó (vì ta chắc chắn target ở đây).
- Nếu `target` nằm ngoài phạm vi Nửa sáng, ta chuyển sang tìm ở nửa còn lại (nửa bị xáo trộn, nhưng khi chia tiếp thì lại xuất hiện Nửa sáng mới).

**Bước 4: Lặp lại cho đến khi tìm thấy hoặc hết trang**
Mỗi vòng lặp loại bỏ đúng một nửa cuốn từ điển. Quá trình dừng lại khi `left` vượt qua `right` (hết trang để lật, trả về `-1` tức là không tìm thấy).

---

## Tại sao cách tiếp cận này lại hiệu quả?

- **Tốc độ Logarit ($O(\log N)$)**: Mỗi vòng lặp loại bỏ chính xác một nửa không gian tìm kiếm. Với mảng 5.000 phần tử, ta chỉ cần tối đa khoảng 13 lần đặt kính lúp (vì $\log_2(5000) \approx 12.3$). So với 5.000 lần lật trang thủ công, đây là sự cải thiện vượt bậc.
- **Không tốn bộ nhớ phụ ($O(1)$)**: Toàn bộ quá trình diễn ra trực tiếp trên mảng gốc, chỉ sử dụng ba biến con trỏ `left`, `right`, `mid`. Không cần cấp phát thêm bất kỳ cấu trúc dữ liệu phụ nào.
- **Không cần tìm điểm xoay trước**: Một số cách tiếp cận khác tìm điểm xoay (pivot) trước rồi mới tìm kiếm nhị phân (hai lượt duyệt). Cách tiếp cận Nửa sáng của chúng ta gộp cả hai bước vào một vòng lặp duy nhất, giảm số lần so sánh xuống còn một nửa.

---

## Mô phỏng hành trình tìm kiếm

Hãy cùng theo dõi việc tìm kiếm `target = 0` trong cuốn từ điển bị xoay: `[4, 5, 6, 7, 0, 1, 2]`

**Vòng lặp thứ nhất:**
- `left = 0`, `right = 6`, `mid = 3`. Kính lúp đặt tại `nums[3] = 7`.
- `target (0) != 7`, chưa tìm thấy.
- Nhận diện Nửa sáng: `nums[0] = 4 <= nums[3] = 7` → Nửa trái `[4, 5, 6, 7]` là Nửa sáng.
- `target = 0` có nằm trong khoảng `[4, 7]` không? Không (vì `0 < 4`).
- Kết luận: `target` chắc chắn nằm ở nửa phải. Thu hẹp: `left = 4`.

**Vòng lặp thứ hai:**
- `left = 4`, `right = 6`, `mid = 5`. Kính lúp đặt tại `nums[5] = 1`.
- `target (0) != 1`, chưa tìm thấy.
- Nhận diện Nửa sáng: `nums[4] = 0 <= nums[5] = 1` → Nửa trái `[0, 1]` là Nửa sáng.
- `target = 0` có nằm trong khoảng `[0, 1]` không? Có (vì `0 >= 0` và `0 < 1`).
- Kết luận: `target` nằm ở nửa trái. Thu hẹp: `right = 4`.

**Vòng lặp thứ ba:**
- `left = 4`, `right = 4`, `mid = 4`. Kính lúp đặt tại `nums[4] = 0`.
- `target (0) == 0`. Tìm thấy!
- Trả về chỉ mục `4`.

Chỉ mất đúng 3 lần đặt kính lúp thay vì phải lật qua 5 trang nếu duyệt tuyến tính.

---

## Các trường hợp kiểm thử mở rộng

- **Thử thách điểm xoay nằm ở đầu mảng (Mảng chưa bị xoay thực sự)**:
  - Đầu vào: `nums = [1, 2, 3, 4, 5]`, `target = 4`
  - Mô tả: Mảng vẫn giữ nguyên thứ tự tăng dần. Thuật toán hoạt động như tìm kiếm nhị phân truyền thống.
  - Kết quả kỳ vọng: `3`

- **Thử thách mục tiêu nằm ngay điểm gãy**:
  - Đầu vào: `nums = [6, 7, 1, 2, 3, 4, 5]`, `target = 1`
  - Mô tả: Số `1` nằm chính xác tại vị trí mà cuốn từ điển bị xé rời. Thuật toán phải nhận diện đúng nửa nào chứa nó.
  - Kết quả kỳ vọng: `2`

- **Thử thách ma (Target không tồn tại)**:
  - Đầu vào: `nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 3`
  - Mô tả: Số `3` không hề xuất hiện trong mảng. Kính lúp sẽ thu hẹp cho đến khi `left` vượt qua `right` mà không tìm thấy kết quả nào.
  - Kết quả kỳ vọng: `-1`

- **Thử thách mảng tối giản (Chỉ có một phần tử)**:
  - Đầu vào: `nums = [1]`, `target = 0`
  - Mô tả: Cuốn từ điển chỉ có đúng một trang. Kính lúp đặt xuống, so sánh một lần duy nhất và kết luận ngay.
  - Kết quả kỳ vọng: `-1`

---

**Tổng kết:** Bằng cách khai thác nguyên lý "luôn tồn tại ít nhất một Nửa sáng" trong mảng xoay, chúng ta biến một bài toán tìm kiếm tưởng chừng hỗn loạn thành một quy trình phán đoán nhị phân mạch lạc và tối ưu. Mỗi bước quyết định đều loại bỏ đúng một nửa không gian tìm kiếm, đạt được tốc độ logarit xuất sắc mà đề bài yêu cầu.
