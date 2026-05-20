# Thiết kế giải pháp cho bài Rotate List

## Đặt vấn đề

Chúng ta được cung cấp một danh sách liên kết đơn (Linked List) và một số nguyên $K$. Nhiệm vụ là dịch chuyển (xoay) danh sách sang phải $K$ vị trí. Điều này đồng nghĩa với việc đưa $K$ phần tử cuối cùng của danh sách lên đầu, giữ nguyên thứ tự tương đối của chúng.

Nếu giải quyết bằng cách duyệt tìm nút cuối cùng rồi ngắt và nối liên tục $K$ lần, chúng ta sẽ phải thao tác với con trỏ rất nhiều lần. Việc này không chỉ chạy chậm ($O(N \times K)$) mà còn rất dễ dẫn đến lỗi mất liên kết con trỏ.

## Giải pháp tối ưu

Để bài toán trở nên thú vị và dễ hình dung hơn, hãy nghĩ về một **chuỗi hạt vòng cổ**. 

Ban đầu, danh sách liên kết giống như một chuỗi hạt nằm thẳng trên bàn, có điểm đầu (`head`) và kết thúc bằng một nút rỗng (`nullptr`). 

Để xoay danh sách này mà không làm rối các con trỏ, chúng ta sẽ thực hiện 3 bước đơn giản sau:

### Bước 1: Nối chuỗi hạt thành một vòng tròn khép kín
Chúng ta cho hạt cuối cùng chỉ vào hạt đầu tiên (`tail->next = head`). Bây giờ, chuỗi hạt của chúng ta đã biến thành một chiếc vòng cổ tròn trịa. Chiếc vòng này không còn điểm đầu hay điểm cuối nữa, các hạt cứ nối đuôi nhau tuần hoàn.

### Bước 2: Tìm vị trí thích hợp để "cắt" chiếc vòng cổ
Xoay danh sách sang phải $K$ bước thực chất là chọn một hạt mới làm đầu chuỗi và ngắt liên kết của hạt đứng ngay trước nó.
* Vì xoay danh sách đi độ dài $N$ sẽ đưa danh sách về nguyên trạng, số bước xoay thực tế cần thực hiện chỉ là `k_thuc_te = K % N`.
* Hạt đuôi mới (New Tail) sẽ là hạt nằm ở vị trí thứ `N - k_thuc_te` (tính từ hạt đầu tiên ban đầu).
* Hạt đầu mới (New Head) chính là hạt đứng ngay sau hạt đuôi mới.

### Bước 3: Thực hiện cắt vòng và duỗi thẳng
Chúng ta chỉ cần đi tới vị trí hạt đuôi mới, lưu lại con trỏ của hạt đứng sau làm `head` mới, sau đó ngắt kết nối tại hạt đuôi mới (`new_tail->next = nullptr`). Danh sách đã được xoay thành công!

## Tại sao tối ưu?

Cách tiếp cận này mang lại hiệu năng lý tưởng nhất:
* Độ phức tạp thời gian: $O(N)$. Chúng ta chỉ cần đi qua danh sách một lần để đếm độ dài và nối vòng, sau đó đi thêm một phần của danh sách để tìm điểm cắt. Tổng số bước đi tỷ lệ tuyến tính với độ dài danh sách.
* Độ phức tạp không gian: $O(1)$. Chúng ta chỉ sử dụng một vài biến con trỏ tạm thời để ghi nhớ vị trí cắt, hoàn toàn không cần cấp phát thêm bộ nhớ mới.

## Mô phỏng từng bước

Giả sử chúng ta có danh sách: `1 -> 2 -> 3 -> 4 -> 5` và $K = 2$.

Bước 1: Tính độ dài $N$ và nối vòng
- Duyệt từ đầu đến cuối danh sách để đếm được độ dài $N = 5$.
- Con trỏ đuôi đang đứng tại hạt `5`. Nối hạt `5` về hạt `1` (`5 -> next = 1`).
- Lúc này vòng tròn là: `1 -> 2 -> 3 -> 4 -> 5 -> 1 -> ...`

Bước 2: Tìm vị trí cắt
- Tính số bước xoay thực tế: `k_thuc_te = 2 % 5 = 2`.
- Vị trí của hạt đuôi mới (New Tail) là: `N - k_thuc_te = 5 - 2 = 3` (tức là hạt mang giá trị `3`).
- Chúng ta đi từ hạt đầu (`1`) dịch chuyển thêm 2 bước nữa để đến hạt `3`.

Bước 3: Ngắt vòng
- Hạt đầu mới (New Head) sẽ là hạt đứng sau hạt `3`, tức là hạt `4`.
- Ngắt kết nối của hạt `3`: `3 -> next = nullptr`.
- Chuỗi hạt sau khi duỗi thẳng mới: `4 -> 5 -> 1 -> 2 -> 3`.

Kết quả chính xác là: `4 -> 5 -> 1 -> 2 -> 3`.

## Thử nghiệm với các trường hợp khác

Dưới đây là các trường hợp kiểm thử đặc biệt để xác minh thiết kế:

Trường hợp 1: Danh sách rỗng hoặc chỉ có một hạt
- Đầu vào:
   `head = [1]`
   `K = 99`
- Đầu ra kỳ vọng: `[1]` (Vì danh sách chỉ có 1 phần tử nên xoay bao nhiêu lần cũng không đổi).

Trường hợp 2: Số lần xoay là bội số của độ dài danh sách
- Đầu vào:
   `head = [1, 2, 3, 4]`
   `K = 8`
- Đầu ra kỳ vọng: `[1, 2, 3, 4]` (Vì `8 % 4 == 0`, danh sách quay lại trạng thái xuất phát ban đầu).

Trường hợp 3: Số lần xoay lớn hơn độ dài danh sách
- Đầu vào:
   `head = [10, 20, 30]`
   `K = 5`
- Đầu ra kỳ vọng: `[20, 30, 10]`
- Giải thích: Số lần xoay thực tế là `5 % 3 = 2`. Xoay 2 lần đưa 2 hạt cuối lên đầu, danh sách mới là `20 -> 30 -> 10`.
