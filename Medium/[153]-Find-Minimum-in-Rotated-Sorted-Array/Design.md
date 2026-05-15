# Tư duy thiết kế: Tìm "điểm gãy" trong một dãy số (Find Minimum in Rotated Sorted Array)

Bài toán tìm giá trị nhỏ nhất trong một mảng đã xoay (rotated sorted array) là một thử thách thú vị về việc vận dụng thuật toán Tìm kiếm nhị phân (Binary Search). Thay vì tìm một giá trị cụ thể, chúng ta đang đi tìm "điểm gãy" (pivot) — nơi mà trật tự sắp xếp tăng dần bị phá vỡ.

## Vấn đề: Giới hạn của việc tìm kiếm tuần tự

Cách tiếp cận đơn giản nhất là duyệt qua toàn bộ mảng từ đầu đến cuối để tìm phần tử nhỏ nhất. Độ phức tạp sẽ là $O(n)$. Tuy nhiên, với một mảng có hàng triệu phần tử, việc kiểm tra từng con số là một sự lãng phí tài nguyên, đặc biệt khi mảng ban đầu vốn dĩ đã được sắp xếp. Thách thức ở đây là làm sao để tìm được "kim đáy bể" chỉ trong $O(\log n)$ bước.

---

## Giải pháp: Kỹ thuật "Thu hẹp vùng nghi vấn" (Binary Search)

Hãy tưởng tượng mảng của chúng ta giống như một **Chiếc cầu thang bị gãy**. Bình thường, cầu thang luôn đi lên (sắp xếp tăng dần). Khi bị xoay, cầu thang sẽ có một đoạn đi lên, sau đó "rơi" thẳng xuống một điểm thấp hơn, rồi lại tiếp tục đi lên.

Nhiệm vụ của chúng ta là tìm cái **"điểm rơi"** đó.

Quy luật cốt lõi để thu hẹp vùng tìm kiếm:
- Nếu phần tử ở giữa (`mid`) vẫn đang **lớn hơn** phần tử ở cuối bên phải (`right`), chứng tỏ "điểm rơi" chắc chắn nằm ở nửa bên phải.
- Nếu phần tử ở giữa (`mid`) **nhỏ hơn hoặc bằng** phần tử ở cuối bên phải (`right`), chứng tỏ nửa bên phải đang ổn định (tăng dần), và "điểm rơi" có thể chính là `mid` hoặc nằm ở nửa bên trái.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Hiệu năng vượt trội:** Với $O(\log n)$, nếu mảng có 1 tỷ phần tử, chúng ta chỉ mất khoảng 30 lần kiểm tra. So với 1 tỷ lần của tìm kiếm tuần tự, đây là một sự cải thiện khổng lồ.
- **Tận dụng tối đa cấu trúc dữ liệu:** Chúng ta không bỏ qua việc mảng đã từng được sắp xếp, mà dùng chính tính chất đó để loại bỏ một nửa dữ liệu sau mỗi bước.
- **Tính ổn định:** Thuật toán luôn hội tụ về một điểm duy nhất là phần tử nhỏ nhất mà không cần xử lý quá nhiều điều kiện biên phức tạp.

---

## Mô phỏng luồng xử lý chi tiết

Hãy hình dung bạn đang đứng trên một con dốc và muốn tìm điểm thấp nhất. Bạn không đi từng bước mà dùng một **Chiếc ống nhòm** để nhìn vào điểm chính giữa (`mid`) và điểm cuối bên phải (`right`).

Ví dụ: `[4, 5, 6, 7, 0, 1, 2]`

- **Bước 1:** `left = 0` (4), `right = 6` (2), `mid = 3` (7).
	- Ta thấy: `nums[mid] (7) > nums[right] (2)`.
	- Suy luận: "Phía bên phải chắc chắn có một cú rơi vì 7 không thể đứng trước 2 trong một dãy tăng dần".
	- Hành động: Bỏ qua nửa trái, đặt `left = mid + 1` (vị trí số 0).

- **Bước 2:** `left = 4` (0), `right = 6` (2), `mid = 5` (1).
	- Ta thấy: `nums[mid] (1) < nums[right] (2)`.
	- Suy luận: "Đoạn từ 1 đến 2 đang tăng dần bình thường. Điểm thấp nhất có thể là số 1 hoặc nằm bên trái số 1".
	- Hành động: Giữ lại nửa trái, đặt `right = mid` (vị trí số 1).

- **Bước 3:** `left = 4` (0), `right = 5` (1), `mid = 4` (0).
	- Ta thấy: `nums[mid] (0) < nums[right] (1)`.
	- Hành động: Đặt `right = mid` (vị trí số 0).

- **Kết quả:** `left` gặp `right` tại vị trí giá trị `0`. Đó là điểm thấp nhất.

---

## Phân tích chuyên sâu Test Case: `[2, 3, 4, 5, 1]`

Trường hợp này mảng bị xoay ở gần cuối, hãy xem thuật toán xử lý thế nào:

1. **Khởi tạo:** `L = 0 (val 2)`, `R = 4 (val 1)`.
2. **Lần 1:** `mid = 2 (val 4)`. Vì `4 > 1`, điểm gãy nằm bên phải. `L = 3`.
3. **Lần 2:** `L = 3 (val 5)`, `R = 4 (val 1)`, `mid = 3 (val 5)`. Vì `5 > 1`, điểm gãy vẫn nằm bên phải. `L = 4`.
4. **Kết thúc:** `L == R == 4`. Giá trị tại đây là `1`.

**Điểm lưu ý:** Tại sao không so sánh `nums[mid]` với `nums[left]`?
Nếu mảng không bị xoay (ví dụ `[1, 2, 3, 4, 5]`), `nums[mid] > nums[left]` vẫn đúng, nhưng điểm nhỏ nhất lại nằm ở bên trái. So sánh với `nums[right]` giúp chúng ta luôn xác định được hướng của "cú rơi" một cách chính xác nhất.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử để đảm bảo tính bao quát của thuật toán:

- **Case 1 (Mảng không bị xoay):** `nums = [11, 13, 15, 17]` -> Kết quả: `11`
- **Case 2 (Mảng chỉ có 1 phần tử):** `nums = [10]` -> Kết quả: `10`
- **Case 3 (Mảng bị xoay đúng 1 lần):** `nums = [2, 1]` -> Kết quả: `1`
- **Case 4 (Xoay đưa số nhỏ nhất về giữa):** `nums = [4, 5, 1, 2, 3]` -> Kết quả: `1`
- **Case 5 (Mảng có 2 phần tử đã sắp xếp):** `nums = [1, 2]` -> Kết quả: `1`

---

**Tổng kết:** Bí quyết của bài toán này không nằm ở code, mà nằm ở việc chọn **"Điểm tựa"** để so sánh. Bằng cách so sánh với phần tử ở cuối bên phải, chúng ta luôn biết được mình đang ở "trên đỉnh" hay "dưới vực" của điểm xoay, từ đó thu hẹp vùng tìm kiếm một cách tự tin và chính xác.
