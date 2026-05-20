# Thiết kế giải pháp cho bài Rotate String

## Đặt vấn đề

Hãy tưởng tượng bạn có một chuỗi ký tự $S$. Thao tác xoay (rotate) chuỗi nghĩa là bạn lấy ký tự đầu tiên bên trái và chuyển nó xuống cuối cùng bên phải. Ví dụ: từ "abcde", sau 1 lần xoay ta được "bcdea", xoay tiếp lần nữa ta được "cdeab".

Câu hỏi đặt ra là: Cho trước chuỗi xuất phát $S$ và chuỗi mục tiêu $Goal$, liệu ta có thể xoay $S$ một số lần để biến nó thành $Goal$ hay không?

Nếu thực hiện mô phỏng xoay từng ký tự một cách thủ công, ta sẽ phải dịch chuyển chuỗi liên tục và so sánh. Cách làm này không những viết code phức tạp mà còn tốn nhiều thời gian xử lý khi chuỗi dài.

## Giải pháp tối ưu

Để tiếp cận bài toán này một cách trực quan và dễ hiểu nhất, hãy tưởng tượng chúng ta viết chuỗi "abcde" lên một **vòng tròn giấy** (hoặc một chiếc vòng tay). 

Khi bạn xoay chiếc vòng này, các ký tự vẫn giữ nguyên thứ tự tuần hoàn của chúng, chỉ là điểm bắt đầu đọc của bạn thay đổi. 
* Nếu bắt đầu đọc từ vị trí số 0: ta thấy "abcde"
* Bắt đầu đọc từ vị trí số 1: ta thấy "bcdea"
* Bắt đầu đọc từ vị trí số 2: ta thấy "cdeab"

Làm thế nào để trải phẳng chiếc vòng tròn này ra thành một đường thẳng trong bộ nhớ máy tính mà vẫn giữ được tính liên tục của vòng xoay? 

Giải pháp cực kỳ đơn giản: Hãy ghép hai chuỗi $S$ lại với nhau ($S + S$).
Với $S =$ "abcde", chuỗi kép $S + S$ sẽ là "abcdeabcde".

Khi nhìn vào chuỗi kép này, bạn sẽ nhận ra một điều kỳ diệu: **mọi trạng thái xoay có thể có của $S$ đều xuất hiện dưới dạng một chuỗi con nằm bên trong $S + S$**.
* "abcde" nằm ở chỉ số 0: **abcde**abcde
* "bcdea" nằm ở chỉ số 1: a**bcdea**bcde
* "cdeab" nằm ở chỉ số 2: ab**cdeab**cde

Như vậy, thay vì phải xoay và so sánh từng bước, bài toán xoay chuỗi lúc này chỉ đơn giản là bài toán kiểm tra xem chuỗi $Goal$ có phải là con của chuỗi kép $S + S$ hay không.

## Tại sao tối ưu?

Phương pháp này tối ưu tuyệt đối về cả tư duy lẫn hiệu năng nhờ:
* Tiết kiệm thời gian: Ta không cần thực hiện bất kỳ vòng lặp dịch chuyển ký tự nào. Phép kiểm tra chuỗi con trong các ngôn ngữ lập trình hiện đại đã được tối ưu hóa cực tốt.
* Độ phức tạp thời gian: $O(N)$ với $N$ là độ dài của chuỗi.
* Độ phức tạp không gian: $O(N)$ để lưu trữ chuỗi nhân đôi $S + S$.

*Lưu ý quan trọng*: Trước khi kiểm tra chuỗi con, ta cần đảm bảo độ dài của hai chuỗi $S$ và $Goal$ phải bằng nhau. Nếu độ dài khác nhau, chắc chắn không thể xoay để khớp được.

## Mô phỏng từng bước

Giả sử đầu vào là:
- $S =$ "abcde"
- $Goal =$ "cdeab"

Bước 1: So sánh độ dài
- Độ dài của $S$ là 5, độ dài của $Goal$ là 5. Hai độ dài bằng nhau, ta tiếp tục xử lý.

Bước 2: Tạo chuỗi kép $S + S$
- $S + S =$ "abcde" + "abcde" = "abcdeabcde"

Bước 3: Tìm kiếm chuỗi $Goal$ trong chuỗi kép
- Ta tìm kiếm cụm từ "cdeab" trong "abcdeabcde".
- Vị trí tìm thấy là từ chỉ số 2: ab[cdeab]cde.
- Vì tìm thấy chuỗi con, kết luận kết quả là True.

## Thử nghiệm với các trường hợp khác

Dưới đây là các trường hợp kiểm thử độc lập để xác minh tính đúng đắn của thiết kế:

Trường hợp 1: Độ dài chuỗi không khớp
- Đầu vào:
   $S =$ "abc"
   $Goal =$ "ab"
- Đầu ra kỳ vọng: False (Vì độ dài khác nhau thì không thể xoay để khớp).

Trường hợp 2: Chuỗi chỉ có một ký tự
- Đầu vào:
   $S =$ "a"
   $Goal =$ "a"
- Đầu ra kỳ vọng: True (Xoay 0 lần vẫn là chính nó).

Trường hợp 3: Chuỗi chứa ký tự lặp lại tuần hoàn
- Đầu vào:
   $S =$ "abab"
   $Goal =$ "baba"
- Đầu ra kỳ vọng: True (Vì "abababab" chứa "baba").

Trường hợp 4: Ký tự giống nhau nhưng sai thứ tự vòng tròn
- Đầu vào:
   $S =$ "abcd"
   $Goal =$ "adcb"
- Đầu ra kỳ vọng: False (Mặc dù có cùng tập hợp ký tự nhưng thứ tự quay vòng đã bị thay đổi, "abcdabcd" không chứa "adcb").
