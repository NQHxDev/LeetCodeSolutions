# Thiết kế giải pháp cho bài Rotate Function

## Đặt vấn đề

Chúng ta được cung cấp một mảng số nguyên `nums` có độ dài $N$. Khi xoay mảng, ta thu được các phiên bản xoay vòng của mảng đó. Với mỗi phiên bản xoay, ta tính giá trị của một hàm số bằng cách nhân mỗi phần tử với chỉ số tương ứng của nó (từ 0 đến $N-1$) rồi cộng tổng lại. Nhiệm vụ của chúng ta là tìm ra giá trị lớn nhất trong số các tổng này.

Nếu tính toán trực tiếp giá trị hàm số cho mỗi phép xoay một cách riêng biệt, ta sẽ cần thực hiện một vòng lặp tính tổng kích thước $N$ cho mỗi lần xoay. Với $N$ lần xoay, độ phức tạp thuật toán sẽ lên tới $O(N^2)$. Khi $N$ lớn (ví dụ $10^5$), chương trình sẽ chạy cực kỳ chậm và bị quá thời gian (Time Limit Exceeded).

## Giải pháp tối ưu

Để tối ưu hóa bài toán từ $O(N^2)$ xuống còn $O(N)$, chúng ta cần tìm ra quy luật liên hệ giữa các bước xoay liên tiếp để tránh việc tính toán lại từ đầu. Hãy cùng sử dụng một hình ảnh liên tưởng trực quan sau:

### Hình ảnh liên tưởng: Xếp hộp trên bậc thang số điểm
Hãy tưởng tượng chúng ta có $N$ chiếc hộp nặng nhẹ khác nhau xếp trên một cầu thang từ bậc 0 đến bậc $N-1$. Số điểm thưởng của mỗi hộp bằng **trọng lượng của nó nhân với số bậc thang** mà nó đang đứng. Tổng điểm của chúng ta chính là giá trị hàm xoay.

Khi chúng ta "xoay" mảng, điều này tương đương với việc dịch chuyển cầu thang:
* **Tất cả các hộp (ngoại trừ hộp ở đỉnh cao nhất)**: Đều được đẩy lên thêm đúng 1 bậc (chỉ số nhân tăng thêm 1). Do đó, điểm thưởng của mỗi hộp này được cộng thêm đúng bằng trọng lượng của chính nó.
* **Hộp đang đứng ở bậc cao nhất ($N-1$)**: Không thể đi lên nữa mà bị rơi thẳng xuống bậc dưới cùng là bậc 0. Điểm của nó lập tức biến thành 0.

### Tính toán sự thay đổi điểm số (Recurrence Relation)
Nếu toàn bộ các hộp đều được tăng thêm 1 bậc, tổng điểm tăng thêm sẽ đúng bằng **tổng trọng lượng của tất cả các hộp** (gọi là $S$).
Tuy nhiên, hộp ở đỉnh (trọng lượng là $W_{top}$) thực tế không được tăng bậc mà bị rơi về 0. Thay vì nhận thêm điểm là $1 \times W_{top}$ (như các hộp khác) và giữ nguyên điểm ở đỉnh là $(N-1) \times W_{top}$, nó bị mất hoàn toàn phần điểm cũ. 

Sự chênh lệch điểm số thực tế giữa lượt xoay mới và lượt xoay cũ là:
$$\text{Điểm\_mới} = \text{Điểm\_cũ} + S - N \times W_{top}$$

Công thức này cho phép chúng ta tính toán điểm số của lượt xoay tiếp theo từ lượt xoay trước đó chỉ bằng một phép tính đơn giản với độ phức tạp $O(1)$!

## Tại sao tối ưu?

Cách giải này mang lại hiệu năng vượt trội:
* Độ phức tạp thời gian: $O(N)$. Chúng ta chỉ cần đi qua mảng một lần để tính tổng ban đầu $F(0)$ và tổng giá trị mảng $S$. Sau đó, ta tính các giá trị $F(1)$ đến $F(N-1)$ tiếp theo bằng công thức quy luật trên, mỗi bước tốn $O(1)$.
* Độ phức tạp không gian: $O(1)$. Chúng ta chỉ cần một vài biến số để lưu trữ tổng mảng, điểm số hiện tại và điểm số lớn nhất, không cần tốn thêm bộ nhớ lưu trữ trung gian.

## Mô phỏng từng bước

Xét mảng đầu vào: `nums = [4, 3, 2, 6]` (độ dài $N = 4$).

Bước 1: Tính tổng giá trị mảng $S$ và điểm ban đầu $F(0)$
* Tổng mảng: $S = 4 + 3 + 2 + 6 = 15$
* Điểm ban đầu: $F(0) = 0 \times 4 + 1 \times 3 + 2 \times 2 + 3 \times 6 = 0 + 3 + 4 + 18 = 25$
* Gán giá trị lớn nhất tạm thời: `max_val = 25`

Bước 2: Dùng công thức quy luật để tính điểm các bước tiếp theo
* **Lần xoay 1**: Hộp ở đỉnh cũ là hộp cuối mảng `nums[3] = 6`.
  * $F(1) = F(0) + S - N \times \text{nums}[3] = 25 + 15 - 4 \times 6 = 40 - 24 = 16$
  * Cập nhật `max_val = max(25, 16) = 25`
* **Lần xoay 2**: Hộp ở đỉnh cũ chuyển sang phần tử sát cuối `nums[2] = 2`.
  * $F(2) = F(1) + S - N \times \text{nums}[2] = 16 + 15 - 4 \times 2 = 31 - 8 = 23$
  * Cập nhật `max_val = max(25, 23) = 25`
* **Lần xoay 3**: Hộp ở đỉnh cũ chuyển sang `nums[1] = 3`.
  * $F(3) = F(2) + S - N \times \text{nums}[1] = 23 + 15 - 4 \times 3 = 38 - 12 = 26$
  * Cập nhật `max_val = max(25, 26) = 26`

Kết quả cực đại tìm được là 26.

## Thử nghiệm với các trường hợp khác

Dưới đây là các trường hợp kiểm thử độc lập giúp kiểm chứng thiết kế:

Trường hợp 1: Mảng gồm toàn các số giống nhau
- Đầu vào: `nums = [5, 5, 5, 5]` ($N = 4$, $S = 20$)
- Điểm xuất phát: $F(0) = 0 \times 5 + 1 \times 5 + 2 \times 5 + 3 \times 5 = 30$
- Tính toán:
  * $F(1) = 30 + 20 - 4 \times 5 = 30$
  * $F(2) = 30 + 20 - 4 \times 5 = 30$
  * $F(3) = 30 + 20 - 4 \times 5 = 30$
- Đầu ra kỳ vọng: 30

Trường hợp 2: Mảng có chứa số âm
- Đầu vào: `nums = [-2, 1, -3]` ($N = 3$, $S = -4$)
- Điểm xuất phát: $F(0) = 0 \times (-2) + 1 \times 1 + 2 \times (-3) = -5$
- Tính toán:
  * $F(1) = -5 + (-4) - 3 \times (-3) = 0$
  * $F(2) = 0 + (-4) - 3 \times 1 = -7$
- Đầu ra kỳ vọng: 0

Trường hợp 3: Mảng tăng dần đơn điệu
- Đầu vào: `nums = [1, 2, 3]` ($N = 3$, $S = 6$)
- Điểm xuất phát: $F(0) = 0 \times 1 + 1 \times 2 + 2 \times 3 = 8$
- Tính toán:
  * $F(1) = 8 + 6 - 3 \times 3 = 5$
  * $F(2) = 5 + 6 - 3 \times 2 = 5$
- Đầu ra kỳ vọng: 8
