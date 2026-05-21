# Tư duy thiết kế: Next Permutation

## Vấn đề: Cơn gió xáo trộn tối giản

Hãy tưởng tượng chúng ta có một hàng các thẻ bài mang số đặt cạnh nhau để tạo thành một số nguyên lớn (ví dụ: `13542`). Nhiệm vụ của chúng ta là hoán đổi vị trí các thẻ bài này để tạo ra **số nguyên nhỏ nhất nhưng phải lớn hơn số hiện tại**.
Trong trường hợp các quân bài đã được xếp theo thứ tự giảm dần tuyệt đối (như `54321`), không thể tạo ra số nào lớn hơn được nữa. Lúc này, chúng ta phải đưa chúng về trạng thái nhỏ nhất có thể (sắp xếp tăng dần thành `12345`).

Nếu sử dụng cách **Vét cạn (Brute Force)**:
- Ta tạo ra tất cả các hoán vị có thể có của dãy thẻ bài, sắp xếp chúng theo thứ tự tăng dần, tìm vị trí của dãy hiện tại rồi lấy dãy tiếp theo.
- **Hệ quả cực đoan**: Nếu dãy thẻ bài dài khoảng 100 phần tử, số lượng hoán vị sẽ lên tới $100!$ (một con số lớn khủng khiếp vượt xa số hạt cát trong vũ trụ). Máy tính sẽ ngay lập tức bị tê liệt và treo máy (TLE). 

Chúng ta cần tìm ra một quy luật dịch chuyển thông minh, trực tiếp biến đổi trên dãy hiện tại với độ phức tạp tối thiểu và không dùng thêm bộ nhớ đệm.

---

## Giải pháp: Điểm chùng núi đồi và sự xoay chuyển đuôi

Để tạo ra một con số lớn hơn tiếp theo với **sự xáo trộn nhỏ nhất**, chúng ta phải thực hiện thay đổi ở các chữ số nằm càng xa về phía bên phải (hàng đơn vị, hàng chục) càng tốt.
Quy trình được thực hiện qua các bước tự nhiên sau:

**Bước 1: Đi tìm "Điểm Chùng" của sườn dốc (từ phải sang trái)**
Hãy tưởng tượng chúng ta đang đi bộ ngược từ đầu hàng thẻ bài bên phải sang bên trái.
- Khi đi ngược như vậy, thông thường các con số sẽ tăng dần lên (như đi lên dốc: `2 -> 4 -> 5`).
- Ngay khi gặp một thẻ bài đột ngột nhỏ hơn thẻ bài đứng ngay trước đó (ví dụ đang từ `5` bước xuống `3`), chúng ta đã tìm thấy **Điểm Chùng** (ký hiệu là `i`). 
Tại sao Điểm Chùng này lại quan trọng? Vì toàn bộ phần đuôi nằm bên phải Điểm Chùng đang được sắp xếp theo thứ tự giảm dần hoàn hảo (tức là đã đạt trạng thái lớn nhất, không thể xáo trộn phần đuôi này để tạo ra số lớn hơn được nữa). Muốn số lớn hơn, ta bắt buộc phải thay đổi thẻ bài tại Điểm Chùng này.

**Bước 2: Tìm "Người Kế Vị" thích hợp nhất**
Bây giờ, chúng ta cần tìm một thẻ bài ở phần đuôi bên phải để thay thế cho thẻ bài tại Điểm Chùng.
- Thẻ bài thay thế này phải **lớn hơn** thẻ bài tại Điểm Chùng, nhưng phải là **thẻ bài nhỏ nhất có thể** trong số những thẻ lớn hơn đó (để số mới tăng lên ít nhất).
- Vì phần đuôi đang giảm dần từ trái sang phải, ta chỉ cần đi ngược từ phải sang trái lần nữa, thẻ bài đầu tiên lớn hơn Điểm Chùng chính là **Người Kế Vị** tốt nhất (ký hiệu là `j`).

**Bước 3: Hoán đổi vị trí**
Hoán đổi thẻ bài tại Điểm Chùng (`i`) và thẻ bài Người Kế Vị (`j`). Lúc này, con số tổng thể chắc chắn đã lớn hơn số ban đầu.

**Bước 4: Lật ngược phần đuôi để đạt mức tối giản**
Sau khi hoán đổi, phần đuôi bên phải vẫn đang giữ thứ tự giảm dần (giá trị lớn nhất của phần đuôi).
- Để số tổng thể là nhỏ nhất có thể, chúng ta phải lật ngược phần đuôi này lại thành tăng dần (giá trị nhỏ nhất).
- Vì phần đuôi vốn đã được sắp xếp giảm dần, chúng ta không cần dùng thuật toán sắp xếp phức tạp nào cả! Chỉ cần **lật ngược (reverse)** toàn bộ phần đuôi này ngay tại chỗ. Đây là phép toán cực kỳ nhanh và tiết kiệm tài nguyên.

*Lưu ý:* Nếu ở Bước 1 ta đi hết hàng từ phải sang trái mà không tìm thấy bất kỳ Điểm Chùng nào (dãy giảm dần hoàn toàn), ta chỉ cần lật ngược cả mảng để đưa về dãy tăng dần nhỏ nhất.

---

## Tại sao cách tiếp cận này lại hiệu quả?

- **Hiệu suất tuyến tính xuất sắc ($O(N)$)**: Chúng ta chỉ duyệt qua mảng tối đa 3 lần (tìm Điểm Chùng, tìm Người Kế Vị, và lật ngược phần đuôi). Với mảng 100 phần tử, máy tính xử lý chỉ trong vài nano giây.
- **Không tốn bộ nhớ đệm ($O(1)$)**: Mọi thao tác hoán đổi và lật ngược đều được thực hiện trực tiếp trên mảng gốc, giúp tối ưu hóa bộ nhớ tuyệt đối.
- **Tính thẩm mỹ của thuật toán**: Không cần dùng các hàm sắp xếp phức tạp như QuickSort hay MergeSort, việc đảo ngược đuôi giúp giữ nguyên tính chất tăng dần mong muốn chỉ bằng cách đổi chỗ các phần tử đối xứng.

---

## Mô phỏng bước chân leo núi

Hãy cùng theo dõi quá trình biến đổi dãy thẻ bài: `[1, 3, 5, 4, 2]`

- **Bước 1: Tìm Điểm Chùng từ phải qua trái**
  - Bắt đầu từ số `2`.
  - `2 -> 4` (đang lên dốc).
  - `4 -> 5` (đang lên dốc).
  - `5 -> 3` (xuống dốc!). Phát hiện số `3` nhỏ hơn số `5` đứng trước nó.
  - Vậy Điểm Chùng là số `3` (chỉ mục `i = 1`).

- **Bước 2: Tìm Người Kế Vị lớn hơn `3` từ phải qua trái**
  - Xét số `2`: Không lớn hơn `3`.
  - Xét số `4`: Lớn hơn `3`! Chọn luôn số `4` làm Người Kế Vị (chỉ mục `j = 3`).

- **Bước 3: Hoán đổi Điểm Chùng và Người Kế Vị**
  - Hoán đổi vị trí của `3` và `4`.
  - Dãy thẻ bài trở thành: `[1, 4, 5, 3, 2]`.

- **Bước 4: Đảo ngược phần đuôi phía sau Điểm Chùng**
  - Phần đuôi phía sau chỉ mục `i = 1` là `[5, 3, 2]`.
  - Đảo ngược phần đuôi này thành: `[2, 3, 5]`.
  - Dãy thẻ bài cuối cùng: `[1, 4, 2, 3, 5]`.

---

## Các trường hợp kiểm thử mở rộng

- **Thử thách đổ đèo hoàn toàn (Dãy giảm dần)**:
  - Đầu vào: `[5, 4, 3, 2, 1]`
  - Mô tả: Không có bất kỳ Điểm Chùng nào. Thuật toán sẽ đảo ngược toàn bộ mảng để đưa về trạng thái tăng dần khởi đầu.
  - Kết quả kỳ vọng: `[1, 2, 3, 4, 5]`

- **Thử thách leo dốc liên tục (Dãy tăng dần)**:
  - Đầu vào: `[1, 2, 3, 4, 5]`
  - Mô tả: Điểm Chùng nằm ngay sát đuôi là số `4` (ở hàng chục), Người Kế Vị là `5`. Chỉ cần hoán đổi hai số này và đảo ngược đuôi độ dài 1.
  - Kết quả kỳ vọng: `[1, 2, 3, 5, 4]`

- **Thử thách thung lũng trùng lặp (Dãy có các số giống nhau)**:
  - Đầu vào: `[1, 5, 1]`
  - Mô tả: Điểm Chùng là số `1` đầu tiên. Số đầu tiên lớn hơn `1` từ phải qua trái là số `5`. Hoán đổi thành `[5, 1, 1]`, sau đó đảo ngược phần đuôi `[1, 1]` vẫn giữ nguyên `[1, 1]`.
  - Kết quả kỳ vọng: `[5, 1, 1]`

- **Thử thách cao nguyên bằng phẳng (Có nhiều số trùng nhau ở đỉnh dốc)**:
  - Đầu vào: `[2, 3, 3, 2]`
  - Mô tả: Đi ngược từ phải sang trái: `2 -> 3` (lên dốc), `3 -> 3` (bằng phẳng), `3 -> 2` (xuống dốc!). Điểm Chùng là `2` ở vị trí đầu tiên. Người Kế Vị đầu tiên lớn hơn `2` từ phải sang là số `3` (ở chỉ mục 2). Hoán đổi thành `[3, 3, 2, 2]`, sau đó đảo ngược đuôi `[3, 2, 2]` thành `[2, 2, 3]`.
  - Kết quả kỳ vọng: `[3, 2, 2, 3]`

---

**Tổng kết:** Bằng cách áp dụng tư duy hình học trực quan về sườn dốc núi đồi, chúng ta nhanh chóng xác định được Điểm Chùng và Người Kế Vị tối ưu. Phép đảo ngược phần đuôi ngay sau đó mang lại một cấu trúc hoán vị kế tiếp nhỏ nhất một cách nhanh chóng và trang nhã nhất.
