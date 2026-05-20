# Thiết kế giải pháp cho bài Rotated Digits

## Đặt vấn đề

Chúng ta cần đếm xem có bao nhiêu số nguyên trong khoảng từ $1$ đến $N$ là số "tốt" (good number) sau khi xoay ngược chúng 180 độ. Một số được định nghĩa là số tốt nếu nó thỏa mãn đồng thời hai điều kiện sau khi xoay:
1. Số mới tạo ra vẫn phải là một số hợp lệ trong hệ thập phân.
2. Số mới phải khác với số ban đầu.

Nếu chúng ta phải xoay một số lớn một cách trực quan, việc xoay toàn bộ chữ số sẽ rất phức tạp. Hãy đi tìm bản chất toán học của các chữ số khi bị xoay ngược 180 độ để giải quyết vấn đề một cách dễ dàng nhất.

## Giải pháp tối ưu

Để bài toán trở nên thú vị và dễ tiếp thu, hãy tưởng tượng chúng ta viết các chữ số từ 0 đến 9 lên các thẻ bài rồi xoay ngược chúng lại. Ta có thể phân loại 10 chữ số này thành 3 nhóm rõ rệt dựa trên "phản ứng" của chúng:

### Nhóm 1: Nhóm gương bất biến (0, 1, 8)
Đây là các chữ số có tính đối xứng tâm hoặc đối xứng trục ngang. Khi bạn xoay ngược chúng 180 độ, chúng vẫn giữ nguyên hình dạng và giá trị ban đầu.
* $0 \rightarrow 0$
* $1 \rightarrow 1$
* $8 \rightarrow 8$

### Nhóm 2: Nhóm đổi diện mạo (2, 5, 6, 9)
Đây là những chữ số kỳ diệu. Khi xoay ngược, chúng biến đổi thành một chữ số hợp lệ khác:
* $2 \leftrightarrow 5$
* $6 \leftrightarrow 9$

### Nhóm 3: Nhóm hạt sạn lỗi (3, 4, 7)
Khi xoay ngược các chữ số này, chúng biến dạng hoàn toàn thành những ký tự không có nghĩa trong toán học thập phân.
* 3, 4, 7 bị lỗi.

### Quy tắc nhận diện số tốt
Từ sự phân loại trực quan trên, một số $X$ được coi là số "tốt" nếu và chỉ nếu:
* **Không chứa bất kỳ chữ số nào thuộc Nhóm hạt sạn** (3, 4, 7). Nếu có dù chỉ một chữ số này, toàn bộ số đó sẽ bị lỗi sau khi xoay.
* **Chứa ít nhất một chữ số thuộc Nhóm đổi diện mạo** (2, 5, 6, 9). Điều này đảm bảo sau khi xoay, số mới chắc chắn sẽ khác số ban đầu. Nếu số đó chỉ toàn các chữ số của Nhóm gương bất biến (ví dụ số 18, 108), số sau khi xoay vẫn giống hệt số cũ, không thỏa mãn yêu cầu khác biệt.

Với giới hạn $N \le 10^4$, chúng ta chỉ cần chạy một vòng lặp từ 1 đến $N$, phân tách từng chữ số của mỗi số để kiểm tra theo hai quy tắc trên. Cách làm này vô cùng đơn giản, dễ đọc và chạy trong chưa đầy 1 mili-giây.

*(Lưu ý mở rộng: Nếu N cực kỳ lớn cỡ $10^9$, ta sẽ áp dụng phương pháp quy hoạch động chữ số - Digit DP để giải quyết trong thời gian cực ngắn $O(\log N)$).*

## Tại sao tối ưu?

Phương pháp phân tích chữ số này tối ưu vì:
* Độ phức tạp thời gian: $O(N \log N)$ (hoặc $O(N)$ số lượng chữ số). Với mỗi số, ta chỉ mất tối đa 5 phép chia lấy dư để kiểm tra toàn bộ các chữ số của nó. Với $N = 10^4$, số phép tính cực kỳ nhỏ.
* Độ phức tạp không gian: $O(1)$. Chỉ dùng một vài biến đếm và cờ hiệu logic (boolean), không tiêu tốn bộ nhớ lưu trữ.

## Mô phỏng từng bước

Giả sử chúng ta cần kiểm tra các số với $N = 10$. Ta duyệt từ 1 đến 10:

* Số 1: Chỉ chứa nhóm gương bất biến $\rightarrow$ Không phải số tốt.
* Số 2: Chứa chữ số nhóm đổi diện mạo (2) $\rightarrow$ **Là số tốt** (xoay thành 5).
* Số 3: Chứa chữ số lỗi (3) $\rightarrow$ Bị loại.
* Số 4: Chứa chữ số lỗi (4) $\rightarrow$ Bị loại.
* Số 5: Chứa chữ số nhóm đổi diện mạo (5) $\rightarrow$ **Là số tốt** (xoay thành 2).
* Số 6: Chứa chữ số nhóm đổi diện mạo (6) $\rightarrow$ **Là số tốt** (xoay thành 9).
* Số 7: Chứa chữ số lỗi (7) $\rightarrow$ Bị loại.
* Số 8: Chỉ chứa nhóm gương bất biến $\rightarrow$ Không phải số tốt.
* Số 9: Chứa chữ số nhóm đổi diện mạo (9) $\rightarrow$ **Là số tốt** (xoay thành 6).
* Số 10: Chứa 1 (gương bất biến) và 0 (gương bất biến) $\rightarrow$ Không phải số tốt.

Tổng số lượng số tốt từ 1 đến 10 là 4 số (2, 5, 6, 9).

## Thử nghiệm với các trường hợp khác

Dưới đây là các trường hợp thử nghiệm độc lập để xác minh tính đúng đắn của thuật toán:

Trường hợp 1: Kiểm tra khoảng lớn hơn 10
- Đầu vào: $N = 12$
- Điểm kiểm tra: Số 11 chỉ có {1} (loại), số 12 chứa {1, 2} (hợp lệ vì chứa 2).
- Đầu ra kỳ vọng: 5 (gồm các số tốt: 2, 5, 6, 9, 12).

Trường hợp 2: Số nhỏ
- Đầu vào: $N = 3$
- Đầu ra kỳ vọng: 1 (Chỉ có số 2 là tốt).

Trường hợp 3: Số chứa chữ số lỗi kết hợp chữ số đổi diện mạo
- Đầu vào: Kiểm tra số 23
- Phân tích: Có chữ số 2 (nhóm đổi diện mạo) nhưng lại có chữ số 3 (nhóm lỗi). Theo quy tắc, số 23 phải bị loại.
- Kết quả kỳ vọng: Không đếm số 23 là số tốt.
