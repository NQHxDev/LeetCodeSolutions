# Tư duy thiết kế: Nghệ thuật cân bằng bộ ba (3Sum)

Bài toán 3Sum yêu cầu chúng ta tìm tất cả các bộ ba số duy nhất trong một mảng sao cho tổng của chúng bằng 0. Đây là một bước tiến hóa từ bài toán Two Sum, đòi hỏi sự kết hợp khéo léo giữa kỹ thuật sắp xếp và chiến thuật "Gọng kìm" (Two Pointers) để tối ưu hóa hiệu năng.

## Vấn đề: Cái bẫy của sự kết hợp ngẫu nhiên

Nếu chúng ta sử dụng ba vòng lặp lồng nhau để kiểm tra mọi bộ ba có thể có, độ phức tạp sẽ là $O(n^3)$. Với một mảng có 3000 phần tử, máy tính phải thực hiện khoảng 27 tỷ phép tính — một con số không tưởng cho một bài toán tìm kiếm. 

Thách thức lớn hơn nữa chính là việc **loại bỏ các bộ trùng lặp**. Nếu mảng có nhiều số giống nhau, việc kiểm tra xem một bộ ba đã xuất hiện hay chưa bằng cách lưu trữ chúng vào một bảng băm sẽ tiêu tốn rất nhiều bộ nhớ và thời gian xử lý bổ sung.

---

## Giải pháp: Sắp xếp hàng ngũ và Chiến thuật "Gọng kìm"

Để giải quyết bài toán này một cách thanh thoát, chúng ta cần đưa mảng về trạng thái có trật tự (Sắp xếp). 

Hãy tưởng tượng bạn đang cố gắng chọn ra 3 người sao cho tổng cân nặng của họ bù trừ lẫn nhau. Nếu mọi người đứng lộn xộn, bạn sẽ phải thử từng người một. Nhưng nếu họ đứng **xếp hàng theo cân nặng từ nhỏ đến lớn**, bạn có thể áp dụng chiến thuật thông minh hơn:

1. **Cố định một "Trưởng nhóm":** Duyệt qua từng người trong hàng (gọi là `i`).
2. **Sử dụng gọng kìm:** Với "Trưởng nhóm" đã chọn, hai người còn lại sẽ được tìm kiếm từ hai đầu của đoạn còn lại trong hàng (gọi là `left` và `right`).
   - Nếu tổng quá lớn: Thu hẹp gọng kìm bên phải (`right--`) để giảm tổng.
   - Nếu tổng quá nhỏ: Tiến gọng kìm bên trái (`left++`) để tăng tổng.
   - Nếu vừa bằng 0: Ghi nhận bộ ba và tiếp tục thu hẹp cả hai đầu gọng kìm.

**Điểm mấu chốt để loại bỏ trùng lặp:** Vì hàng ngũ đã được sắp xếp, những người có cân nặng giống nhau sẽ đứng cạnh nhau. Chúng ta chỉ cần đơn giản là "bỏ qua" những người giống hệt người vừa được xét để đảm bảo bộ ba tìm được luôn là duy nhất.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Hiệu năng ấn tượng:** Việc sắp xếp mất $O(n \log n)$, và vòng lặp lồng gọng kìm mất $O(n^2)$. Tổng thể thuật toán đạt $O(n^2)$, nhanh hơn hàng nghìn lần so với cách tiếp cận thô sơ.
- **Tiết kiệm bộ nhớ:** Chúng ta không cần dùng bảng băm (HashSet) để kiểm tra trùng lặp, giúp giảm độ phức tạp không gian xuống còn $O(1)$ (không tính không gian dành cho kết quả).
- **Kiểm soát tuyệt đối:** Việc sắp xếp cho phép chúng ta biết chính xác hướng cần di chuyển để đạt được mục tiêu, thay vì mò mẫm trong bóng tối.

---

## Mô phỏng luồng xử lý chi tiết

Mảng ví dụ: `[-1, 0, 1, 2, -1, -4]`
**Bước 1: Sắp xếp:** `[-4, -1, -1, 0, 1, 2]`

**Bước 2: Cố định "Trưởng nhóm" đầu tiên (`i = 0`, giá trị `-4`):**
- Gọng kìm: `left = 1` (giá trị `-1`), `right = 5` (giá trị `2`).
- Tổng: `-4 + (-1) + 2 = -3` (Nhỏ hơn 0).
- Hành động: `left++` lên vị trí giá trị `-1`.
- ... Tiếp tục cho đến hết hàng, không tìm thấy bộ nào đi với `-4` để bằng 0.

**Bước 3: Cố định "Trưởng nhóm" tiếp theo (`i = 1`, giá trị `-1`):**
- Gọng kìm: `left = 2` (giá trị `-1`), `right = 5` (giá trị `2`).
- Tổng: `-1 + (-1) + 2 = 0`. **Khớp!** -> Ghi nhận `[-1, -1, 2]`.
- Thu hẹp gọng kìm: `left = 3` (giá trị `0`), `right = 4` (giá trị `1`).
- Tổng: `-1 + 0 + 1 = 0`. **Khớp!** -> Ghi nhận `[-1, 0, 1]`.

**Bước 4: Bỏ qua trùng lặp:**
- Khi `i` chuyển sang vị trí tiếp theo (cũng là `-1`), thuật toán thấy rằng giá trị này giống hệt "Trưởng nhóm" vừa xét ở Bước 3 nên sẽ **bỏ qua ngay lập tức** để tránh tìm lại các bộ đã có.

---

## Phân tích chuyên sâu Test Case: `[0, 0, 0, 0]`

Đây là trường hợp bẫy kinh điển. Nếu không có cơ chế bỏ qua trùng lặp, bạn sẽ trả về 4 bộ `[0, 0, 0]`.

1. **Sắp xếp:** Vẫn là `[0, 0, 0, 0]`.
2. **i = 0 (giá trị 0):** Tìm thấy bộ `[0, 0, 0]` tại `left=1, right=3`.
3. **i = 1 (giá trị 0):** Vì `nums[1] == nums[0]`, thuật toán bỏ qua.
4. **Kết quả:** Chỉ có duy nhất 1 bộ `[0, 0, 0]`.

---

## Test Case mở rộng

- **Case 1 (Mảng toàn số dương):** `nums = [1, 2, 3, 4]` -> Kết quả: `[]` (Không thể có tổng bằng 0).
- **Case 2 (Mảng có nhiều bộ trùng lặp):** `nums = [-2, 0, 0, 2, 2]` -> Kết quả: `[[-2, 0, 2]]`.
- **Case 3 (Mảng chỉ có 3 phần tử tổng bằng 0):** `nums = [-1, 0, 1]` -> Kết quả: `[[-1, 0, 1]]`.
- **Case 4 (Mảng rỗng hoặc ít hơn 3 phần tử):** `nums = [0]` -> Kết quả: `[]`.
- **Case 5 (Các số đối xứng cực đại):** `nums = [-5, 2, 3, 0, -2, -3]` -> Kết quả: `[[-5, 2, 3], [-3, 0, 3], [-2, 0, 2], [-3, 1, 2]]` (tùy thuộc vào các số cụ thể).

---

**Tổng kết:** Bài toán 3Sum là minh chứng cho việc chuyển đổi một bài toán tìm kiếm phức tạp thành một bài toán **điều phối có trật tự**. Kỹ thuật sắp xếp không chỉ giúp tăng tốc độ mà còn là chìa khóa để giải quyết vấn đề trùng lặp một cách tự nhiên nhất.
