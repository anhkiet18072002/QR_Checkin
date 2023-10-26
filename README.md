# Tạo mã QR
Sử dụng file QR_Generatory.py
  - file này dùng để tạo mã QR với nội dung là QRID
# Quét mã QR, chụp hình khuôn mặt và lưu vào database
- Đầu tiên ta cần quét mã QR bằng file QR_San.py. File này sẽ quét mã QR và trả về data (tức QRID).
- Sau đó sử dung hàm check_available trong file retrivedata.py 
  Hàm này để kiếm tra data của mã QR vừa quét có được tạo trong danh sách không. Nếu không hợp lệ thì thông báo.
- Tiếp theo, sử dụng hàm check trong file retrivedata.py 
  Hàm này lấy các dữ liệu ứng với mã QR đó như: giới tính, họ tên. Để hệ thống có thể dọc tên và giới tính của khách mời.
  Kiếm tra facepath đã được lưu trong database chưa. Nếu chưa có nghĩa là vào lần đầu và sẽ họi file takeimage.py để chụp khuôn mặt và lưu facepath vào database.
# Facedetection
- file face_detection.py lấy hình từ database sau đó encoding khuôn mặt. Sau đó sẽ kiếm tra người vào có trong datase hay chưa. Nếu có thì xuất ra tên người đó, nếu chưa thì flag = 1 
- file sensor.ino chạy bằng chương trình arduino, dừng để điều khiển ESP32 kết nối và gửi message đến mqtt broker. Khi có người đi qua, hệ thống sẽ có giá trị là 0, khi không có người đi qua hệ thống sẽ có giá trị là 1.
- file mqtt.py là sự kết hợp của cả 2 file face_detection.py và sensor.ino. Kết nối và nhận giá trị từ mqtt broker, khi nhận giá trị là 0 có nghĩa là có người đi qua và nhận giá trị flag = 1 có nghĩa là người đó chưa có trong database thì hệ thống sẽ cảnh báo.
  

