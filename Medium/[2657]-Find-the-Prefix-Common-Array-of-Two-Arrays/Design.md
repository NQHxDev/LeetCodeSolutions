# Thiết kế giải pháp cho bài Find the Prefix Common Array of Two Arrays

## Đặt vấn đề

Chúng ta cần tìm số lượng các phần tử chung xuất hiện trong các đoạn tiền tố từ chỉ số 0 đến $i$ của hai mảng hoán vị $A$ và $B$. Vì $A$ và $B$ là các hoán vị của các số từ $1$ đến $N$, mỗi số chỉ xuất hiện đúng một lần trong mỗi mảng.

Nếu sử dụng phương pháp duyệt thô, tại mỗi chỉ số $i$, chúng ta phải so sánh toàn bộ các phần tử từ đầu đến $i$ của cả hai mảng. Điều này đòi hỏi độ phức tạp thời gian lên tới $O(N^3)$ hoặc $O(N^2)$, không hiệu quả khi $N$ tăng lên.

## Giải pháp tối ưu

Để tối ưu hóa, chúng ta cần tránh việc tìm kiếm lặp đi lặp lại. Hãy liên tưởng đến việc sử dụng một chiếc sổ tay ghi nhớ.

Khi duyệt qua từng chỉ số từ đầu đến cuối mảng:
- Mỗi khi gặp một con số ở mảng $A$, ta lật trang tương ứng của con số đó trong sổ tay và đánh dấu một dấu tick (tăng tần suất xuất hiện lên 1).
- Tương tự, mỗi khi gặp một con số ở mảng $B$, ta cũng lật trang tương ứng và đánh dấu một dấu tick khác.
- Nếu một trang số nào đó nhận đủ 2 dấu tick (nghĩa là đã xuất hiện ở cả $A$ và $B$), điều đó chứng tỏ số đó là phần tử chung trong đoạn tiền tố hiện tại. Lúc này, ta chỉ cần tăng biến đếm số lượng phần tử chung lên 1.

Cách tiếp cận này giúp chuyển đổi từ việc tìm kiếm vất vả sang việc tra cứu nhanh chóng với độ phức tạp thời gian cho mỗi lần tra cứu là $O(1)$.

## Tại sao tối ưu?

Giải pháp này đạt được hiệu năng tối ưu nhờ vào:
- Độ phức tạp thời gian: $O(N)$. Chúng ta chỉ cần duyệt qua hai mảng đúng một lần. Mỗi thao tác kiểm tra và cập nhật sổ tay chỉ tốn thời gian hằng số $O(1)$.
- Độ phức tạp không gian: $O(N)$ để lưu trữ sổ tay ghi nhận tần suất của các số từ $1$ đến $N$. Điều này hoàn toàn xứng đáng để đổi lấy tốc độ xử lý nhanh nhất.

## Mô phỏng từng bước

Xét hai mảng hoán vị có độ dài $N = 4$:
- $A = [2, 4, 1, 3]$
- $B = [4, 3, 2, 1]$

Khởi tạo:
- Sổ tay ghi nhận tần suất: toàn bộ bằng 0.
- Số lượng phần tử chung hiện tại: 0.
- Mảng kết quả $C$ có độ dài 4.

Duyệt qua từng chỉ số $i$:

Tại $i = 0$:
- Phần tử của $A$ là $2$. Đánh dấu tần suất của $2$ tăng lên 1 (hiện tại là 1).
- Phần tử của $B$ là $4$. Đánh dấu tần suất của $4$ tăng lên 1 (hiện tại là 1).
- Không có trang nào đạt tần suất bằng 2.
- Số lượng phần tử chung hiện tại: 0. Kết quả: $C[0] = 0$.

Tại $i = 1$:
- Phần tử của $A$ là $4$. Tần suất của $4$ tăng lên 1 (hiện tại là 2). Vì tần suất đạt 2, tăng số lượng phần tử chung lên 1 (hiện tại là 1).
- Phần tử của $B$ là $3$. Tần suất của $3$ tăng lên 1 (hiện tại là 1).
- Số lượng phần tử chung hiện tại: 1. Kết quả: $C[1] = 1$.

Tại $i = 2$:
- Phần tử của $A$ là $1$. Tần suất của $1$ tăng lên 1 (hiện tại là 1).
- Phần tử của $B$ là $2$. Tần suất của $2$ tăng lên 1 (hiện tại là 2). Vì tần suất đạt 2, tăng số lượng phần tử chung lên 1 (hiện tại là 2).
- Số lượng phần tử chung hiện tại: 2. Kết quả: $C[2] = 2$.

Tại $i = 3$:
- Phần tử của $A$ là $3$. Tần suất của $3$ tăng lên 1 (hiện tại là 2). Vì tần suất đạt 2, tăng số lượng phần tử chung lên 1 (hiện tại là 3).
- Phần tử của $B$ là $1$. Tần suất của $1$ tăng lên 1 (hiện tại là 2). Vì tần suất đạt 2, tăng số lượng phần tử chung lên 1 (hiện tại là 4).
- Số lượng phần tử chung hiện tại: 4. Kết quả: $C[3] = 4$.

Kết quả cuối cùng thu được là mảng $C = [0, 1, 2, 4]$.

## Thử nghiệm với các trường hợp khác

Dưới đây là các trường hợp thử nghiệm độc lập để kiểm chứng logic thiết kế:

Trường hợp 1: Hai mảng giống hệt nhau
- Đầu vào:
   $A = [1, 2, 3, 5, 4]$
   $B = [1, 2, 3, 5, 4]$
- Đầu ra kỳ vọng: $[1, 2, 3, 4, 5]$

Trường hợp 2: Hai mảng đảo ngược hoàn toàn
- Đầu vào:
   $A = [5, 4, 3, 2, 1]$
   $B = [1, 2, 3, 4, 5]$
- Đầu ra kỳ vọng: $[0, 0, 1, 3, 5]$

Trường hợp 3: Hoán vị đan xen
- Đầu vào:
   $A = [1, 3, 5, 2, 4]$
   $B = [5, 4, 3, 2, 1]$
- Đầu ra kỳ vọng: $[0, 0, 2, 3, 5]$
