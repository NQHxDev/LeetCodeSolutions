# Tư duy thiết kế: Tìm kiếm "Sợi chỉ chung" dài nhất (Longest Common Prefix)

Longest Common Prefix (LCP) là bài toán tìm ra chuỗi ký tự bắt đầu giống nhau nhất giữa một tập hợp các từ. Đây là nền tảng cho các tính năng như tự động hoàn thành (Autocomplete) hay gợi ý tìm kiếm.

## Vấn đề: Tìm điểm dừng của sự tương đồng
Hãy tưởng tượng chúng ta có một nhóm các vận động viên đang chạy trên các đường chạy song song. Nhiệm vụ của chúng ta là tìm xem họ đã chạy cùng nhau được bao xa trước khi có ít nhất một người rẽ hướng khác hoặc dừng lại.

Nếu chúng ta so sánh từng cặp một cách ngẫu nhiên, chúng ta sẽ rất dễ bị rối và khó xác định được "khoảng cách chung" ngắn nhất mà tất cả mọi người đều đã đi qua.

---

## Giải pháp: Chiếc "Thước đo thu hẹp"
Cách tiếp cận tự nhiên và hiệu quả nhất là sử dụng chính từ đầu tiên làm một chiếc thước đo tiêu chuẩn, sau đó tinh chỉnh nó qua từng lần gặp gỡ.

- Ta giả định từ đầu tiên chính là phần chung dài nhất hiện có.
- Đem chiếc thước này đi so sánh với từ tiếp theo trong danh sách.
- Nếu từ tiếp theo không bắt đầu bằng chiếc thước này, chúng ta cắt bớt một ký tự ở cuối thước đo và thử lại cho đến khi nó khớp hoàn toàn với phần đầu của từ đó.
- Tiếp tục dùng chiếc thước đã bị thu hẹp này để đi so sánh với các từ còn lại trong danh sách.

---

## Tại sao đây là cách tiếp cận tối ưu?
Thay vì cố gắng xây dựng một kết quả mới từ đầu, chúng ta chọn cách loại trừ những phần không phù hợp.

- **Tối ưu hóa thời gian:** Nếu tại bất kỳ thời điểm nào chiếc thước đo bị thu hẹp đến mức trống rỗng, chúng ta có thể kết thúc bài toán ngay lập tức vì chắc chắn không còn điểm chung nào nữa.
- **Tiết kiệm bộ nhớ:** Chúng ta không cần tạo ra nhiều cấu trúc dữ liệu phức tạp, chỉ cần một biến duy nhất để lưu trữ và cập nhật trạng thái của chiếc thước đo.
- **Tính thực tế:** Tư duy này giúp máy tính không phải làm những việc thừa thãi khi đã biết chắc chắn kết quả không thể dài hơn hiện tại.

---

## Mô phỏng luồng xử lý
Giả sử chúng ta có danh sách: `["flower", "flow", "flight"]`

**Khởi tạo**
Thước đo ban đầu là `"flower"`.

**So sánh với "flow"**
- `"flower"` không phải là khởi đầu của `"flow"`.
- Cắt bớt ký tự cuối: `"flowe"` -> vẫn không khớp.
- Cắt bớt ký tự cuối: `"flow"` -> **Khớp!**
- Thước đo cập nhật thành `"flow"`.

**So sánh với "flight"**
- `"flow"` không phải là khởi đầu của `"flight"`.
- Cắt bớt ký tự cuối: `"flo"` -> vẫn không khớp.
- Cắt bớt ký tự cuối: `"fl"` -> **Khớp!**
- Thước đo cập nhật thành `"fl"`.

**Kết luận**
Sau khi đi hết danh sách, kết quả cuối cùng là `"fl"`.

---

**Tổng kết:** Bằng cách sử dụng tư duy "Cắt tỉa dần", chúng ta biến một bài toán so sánh phức tạp thành một quy trình tinh chỉnh đơn giản. Chiếc thước đo sẽ ngắn lại sau mỗi trở ngại, cuối cùng để lại giá trị chính xác nhất mà tất cả các thành viên trong nhóm đều chấp nhận được.
