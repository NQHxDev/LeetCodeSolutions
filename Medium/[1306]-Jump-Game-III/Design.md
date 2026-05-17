# Tư duy thiết kế: Bản đồ lò cò và hành trình tìm kho báu (Jump Game III)

Bài toán di chuyển trên mảng dựa theo giá trị của từng phần tử là một dạng bài toán tìm kiếm đường đi trên đồ thị ẩn. Mỗi vị trí trong mảng đóng vai trò như một nút (node), và các bước nhảy hợp lệ đóng vai trò là các cạnh (edge) liên kết các nút đó lại với nhau. Thách thức lớn nhất ở đây là tìm ra con đường ngắn nhất dẫn đến ô có giá trị 0 mà không bị sa vào những vòng lặp vô tận.

## Vấn đề: Cái bẫy của những vòng lặp vô tận

Hãy tưởng tượng bạn được đặt vào một con đường gồm nhiều ô vuông kề nhau. Tại mỗi ô, bạn chỉ được phép nhảy tiến hoặc lùi một số bước đúng bằng con số ghi trên ô đó. Mục tiêu là đặt chân lên một ô có số 0.

Nếu chúng ta chỉ đơn giản là thử mọi cách nhảy tiến và lùi, chúng ta sẽ sớm đối mặt với hai vấn đề nghiêm trọng:

- **Chu kỳ lặp vô hạn:** Nếu ô thứ 2 yêu cầu nhảy sang ô thứ 4, và ô thứ 4 lại yêu cầu nhảy ngược về ô thứ 2, chúng ta sẽ nhảy qua nhảy lại mãi mãi nếu không có cơ chế ghi nhớ.
- **Sự bùng nổ của các nhánh tìm kiếm:** Cứ mỗi bước đi, số lượng nhánh tìm kiếm lại nhân đôi (tiến hoặc lùi). Nếu không loại bỏ các nhánh đã từng đi qua, thuật toán sẽ bị quá tải về thời gian xử lý ($O(2^n)$).

---

## Giải pháp: Chiến thuật "Lật úp" ô lò cò (DFS/BFS kết hợp Đảo dấu)

Để giải quyết bài toán này một cách triệt để, chúng ta có thể coi đây là một bài toán duyệt đồ thị bằng phương pháp Duyệt theo chiều sâu (DFS) hoặc Duyệt theo chiều rộng (BFS).

Thông thường, để ghi nhớ những vị trí đã đi qua, chúng ta sẽ cần mang theo một "cuốn sổ tay" — tức là một mảng đánh dấu `visited` hoặc một bảng băm `std::unordered_set`. Việc này sẽ làm tốn thêm $O(n)$ không gian bộ nhớ phụ trợ.

Tuy nhiên, có một giải pháp thông minh hơn giúp ta tiết kiệm được cuốn sổ tay này: **Chiến thuật "Lật úp" ô lò cò (In-place Negation)**.

- Khi ta đứng ở ô `i`, ta kiểm tra xem con số ghi trên ô đó là gì.
- Nếu là `0`, chúc mừng, ta đã tìm thấy kho báu!
- Nếu là một số âm, nghĩa là ô này đã được "lật úp" (đã từng đi qua). Ta lập tức quay đầu để tránh đi vào vòng lặp.
- Nếu là một số dương hợp lệ, ta tiến hành "lật úp" nó bằng cách đổi dấu của giá trị đó thành số âm (ví dụ: `arr[i] = -arr[i]`).
- Sau đó, ta tiếp tục khám phá hai hướng nhảy từ ô này bằng cách sử dụng giá trị gốc (lấy trị tuyệt đối `abs(arr[i])` để biết khoảng cách nhảy):
    - Hướng tiến: `i + abs(arr[i])`
    - Hướng lùi: `i - abs(arr[i])`

Nhờ việc đổi dấu này, bản thân mảng đầu vào đóng vai trò là cấu trúc dữ liệu lưu trữ trạng thái đã duyệt, giúp triệt tiêu hoàn toàn chi phí bộ nhớ phụ trợ.

---

## Tại sao đây là cách tiếp cận tối ưu?

- **Tiết kiệm bộ nhớ tối đa (O(1) Auxiliary Space):** Bằng cách tận dụng các giá trị âm để đánh dấu trạng thái đã duyệt, ta không cần khởi tạo thêm bất kỳ cấu trúc dữ liệu nào. Bộ nhớ phụ trợ duy nhất chỉ là ngăn xếp gọi hàm (recursion stack) của DFS trong trường hợp tệ nhất là $O(n)$.
- **Tốc độ xử lý tuyến tính (O(n) Time Complexity):** Mỗi ô vuông trong mảng chỉ được duyệt qua tối đa một lần. Nếu quay lại một ô đã đi qua, thuật toán sẽ dừng ngay lập tức nhờ điều kiện kiểm tra số âm, đảm bảo không có bất kỳ bước tính toán thừa thãi nào.
- **Cực kỳ tinh gọn:** Logic thuật toán được gói gọn trong vài dòng code đệ quy vô cùng trong sáng và dễ bảo trì.

---

## Mô phỏng luồng xử lý chi tiết

Hãy cùng quan sát cách thuật toán vận hành qua một ví dụ cụ thể:

Mảng xuất phát: `arr = [4, 2, 3, 0, 3, 1, 2]` với `start = 5`

```text
Chỉ số (Index):   0    1    2    3    4    5    6
Giá trị (Value): [4,   2,   3,   0,   3,   1,   2]
```

- **Bước 1:** Bắt đầu tại `start = 5`.
    - Giá trị tại đây là `1` (khác 0, chưa duyệt).
    - Đánh dấu đã duyệt bằng cách lật úp: `arr[5] = -1`.
    - Hai hướng có thể nhảy:
        - Nhảy lùi: `5 - 1 = 4`
        - Nhảy tiến: `5 + 1 = 6`
    - Chúng ta sẽ rẽ vào nhánh nhảy lùi trước (khám phá chỉ số `4`).

- **Bước 2:** Di chuyển tới chỉ số `4`.
    - Giá trị tại đây là `3` (khác 0, chưa duyệt).
    - Đánh dấu đã duyệt bằng cách lật úp: `arr[4] = -3`.
    - Hai hướng có thể nhảy:
        - Nhảy lùi: `4 - 3 = 1`
        - Nhảy tiến: `4 + 3 = 7` (Vượt ra ngoài biên mảng -> Loại bỏ).
    - Tiếp tục khám phá nhánh nhảy lùi hợp lệ (khám phá chỉ số `1`).

- **Bước 3:** Di chuyển tới chỉ số `1`.
    - Giá trị tại đây là `2` (khác 0, chưa duyệt).
    - Đánh dấu đã duyệt bằng cách lật úp: `arr[1] = -2`.
    - Hai hướng có thể nhảy:
        - Nhảy lùi: `1 - 2 = -1` (Vượt ra ngoài biên mảng -> Loại bỏ).
        - Nhảy tiến: `1 + 2 = 3`
    - Tiếp tục khám phá nhánh nhảy tiến duy nhất hợp lệ (khám phá chỉ số `3`).

- **Bước 4:** Di chuyển tới chỉ số `3`.
    - Giá trị tại đây là `0`!
    - **Kết quả:** Đã chạm đến đích thành công. Nhánh đệ quy dừng lại và trả về `true` cho toàn bộ chuỗi tìm kiếm.

---

## Phân tích chuyên sâu Test Case: `arr = [3, 0, 2, 1, 2]`, `start = 2`

Trường hợp này không thể dẫn tới đích `0`, hãy xem thuật toán phát hiện và ngăn chặn vòng lặp như thế nào:

```text
Chỉ số (Index):   0    1    2    3    4
Giá trị (Value): [3,   0,   2,   1,   2]
```

1. **Khởi đầu:** `start = 2`. Giá trị là `2`. Đánh dấu `arr[2] = -2`. Nhảy sang trái tới `0` hoặc sang phải tới `4`.
2. **Khám phá nhánh trái (chỉ số 0):** Giá trị là `3`. Đánh dấu `arr[0] = -3`. Chỉ nhảy được sang phải tới chỉ số `3` (vì sang trái ra ngoài biên).
3. **Tại chỉ số 3:** Giá trị là `1`. Đánh dấu `arr[3] = -1`. Nhảy sang trái tới `2` hoặc sang phải tới `4`.
    - Nhánh nhảy sang trái tới `2`: Phát hiện `arr[2] == -2` (đã duyệt) -> Trả về `false`.
    - Nhánh nhảy sang phải tới `4`: Giá trị tại `4` là `2`. Đánh dấu `arr[4] = -2`. Nhảy sang trái tới `2` (đã duyệt -> `false`) hoặc sang phải tới `6` (ngoài biên -> `false`). Nhánh này thất bại.
4. **Khám phá nhánh phải từ gốc (chỉ số 4):**
    - Khi nhánh trái quay lui hoàn toàn with kết quả `false`, ta tiếp tục thử nhánh phải từ gốc ban đầu là chỉ số `4`.
    - Tuy nhiên, chỉ số `4` lúc này đã bị đánh dấu là `-2` từ quá trình duyệt nhánh trái trước đó.
    - Nhờ dấu hiệu này, thuật toán lập tức bỏ qua mà không cần duyệt lại, trả về `false` ngay lập tức.
5. **Kết quả:** Không có con đường nào từ `2` dẫn tới vạch đích `1` (giá trị `0`). Thuật toán kết thúc an toàn và trả về `false`.

---

## Test Case mở rộng

Dưới đây là các trường hợp kiểm thử tùy biến giúp chứng minh tính toàn diện của thiết kế:

- **Case 1 (Vạch xuất phát cực kỳ thuận lợi):**
    - Đầu vào: `arr = [2, 0, 1, 0, 2]`, `start = 2`
    - Mô tả: Từ chỉ số `2` (giá trị `1`), ta nhảy sang trái 1 bước là tới chỉ số `1` (giá trị `0`), hoặc nhảy sang phải 1 bước là tới chỉ số `3` (giá trị `0`).
    - Kết quả kỳ vọng: `true`

- **Case 2 (Đứng sẵn tại vạch đích):**
    - Đầu vào: `arr = [0]`, `start = 0`
    - Mô tả: Mảng chỉ có duy nhất một phần tử và nó chính là đích đến.
    - Kết quả kỳ vọng: `true`

- **Case 3 (Bị kẹt trong chu trình vô hạn không có lối thoát):**
    - Đầu vào: `arr = [2, 2, 2, 0, 3]`, `start = 0`
    - Mô tả: Các bước nhảy chỉ có thể di chuyển luân phiên giữa các chỉ số `0 -> 2 -> 4 -> 2 -> 0...` mà không bao giờ chạm được tới chỉ số `3` (nơi có giá trị `0`).
    - Kết quả kỳ vọng: `false`

- **Case 4 (Nhảy zic-zac liên tục để về đích):**
    - Đầu vào: `arr = [1, 2, 3, 2, 1, 0]`, `start = 0`
    - Mô tả: Hành trình di chuyển sẽ là `0 -> 1 -> 3 -> 5` (đích). Một chuỗi các bước nhảy tiến lùi nhịp nhàng.
    - Kết quả kỳ vọng: `true`

- **Case 5 (Mảng hoàn toàn không chứa bất kỳ mục tiêu 0 nào):**
    - Đầu vào: `arr = [1, 2, 1, 2]`, `start = 1`
    - Mô tả: Không có bất kỳ phần tử nào bằng `0` trong mảng, thuật toán sẽ duyệt qua mọi ô khả dĩ rồi tự động kết luận thất bại.
    - Kết quả kỳ vọng: `false`

---

**Tổng kết:** Vẻ đẹp của bài toán Jump Game III nằm ở việc chúng ta chuyển đổi một bài toán di chuyển tưởng chừng như hỗn loạn thành một mô hình đồ thị tuần tự và chặt chẽ. Bằng cách áp dụng khéo léo kỹ thuật đổi dấu trực tiếp trên mảng dữ liệu đầu vào, chúng ta vừa loại bỏ triệt để nguy cơ rơi vào các vòng lặp vô tận, vừa đạt được sự tối ưu hóa tuyệt đối về cả thời gian chạy lẫn không gian bộ nhớ.
