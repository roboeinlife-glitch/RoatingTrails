# RoatingTrails

# RotatingTrails

Một chương trình animation đẹp mắt được viết bằng **SFML** (Simple and Fast Multimedia Library).

Chương trình bắt đầu bằng việc từ từ kéo dài một đoạn thẳng trung tâm (AB) từ điểm giữa màn hình. 

Khi đạt độ dài tối đa, ba đoạn nhánh (BC, BD, BE) sẽ lần lượt dài ra từ điểm B. 

Cuối cùng, đoạn AB quay chậm quanh tâm, trong khi ba nhánh quay rất nhanh quanh điểm B, đồng thời để lại các đường trails tích tụ dần dần, tạo nên những hoa văn hình học phức tạp và hypnotic giống như spirograph.

## Tính năng nổi bật
- Hiệu ứng khởi tạo mượt mà (đoạn thẳng dài ra dần)
  
- Tốc độ quay độc lập (đoạn trung tâm chậm, ba nhánh quay nhanh hơn nhiều)
  
- Trails tích tụ vô hạn với độ mờ giảm dần tạo chiều sâu
  
- Màu sắc hoàn toàn tùy chỉnh riêng biệt (đoạn thẳng hiện tại và trails)
  
- Code C++ sạch sẽ, nhẹ nhàng, chỉ dùng SFML Graphics

## Yêu cầu
- SFML phiên bản 2.5 trở lên
- Trình biên dịch hỗ trợ C++11 (g++, clang++, MSVC...)

`sfml`, `cpp`, `animation`, `generative-art`, `trails`, `spirograph`, `visualization`, `hoa-van`, `hieu-ung`

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-2.5+-green.svg)
![License](https://img.shields.io/badge/license-MIT-orange.svg)

### 🛠️ Cài đặt trên Code::Blocks
1. Tải [SFML 2.5.x](https://www.sfml-dev.org/download.php)

2. Trong Code::Blocks: Settings → Compiler → Linker settings

3. Thêm: `sfml-graphics`, `sfml-window`, `sfml-system`

4. Mở `main.cpp` và nhấn F9 để chạy
   

[Demo](https://www.youtube.com/shorts/DocsPhlE9OU)

[Trở về trang chủ](https://github.com/roboeinlife-glitch)
