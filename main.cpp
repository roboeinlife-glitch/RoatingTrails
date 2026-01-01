#include <SFML/Graphics.hpp>
#include <cmath>
#include <deque>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 900;
const float PI = 3.14159265358979323846f;

// ==================== CÁC BIẾN MÀU - CHỈNH TẠI ĐÂY LÀ ĐỦ ====================
sf::Color colorLineAB      = sf::Color(0, 255, 100);   // Màu đoạn thẳng AB hiện tại (xanh lá neon)
sf::Color colorTrailAB     = sf::Color(255, 255, 255, 180);    // Màu trail của điểm B (xanh lá đậm hơn)

sf::Color colorLineBranches = sf::Color::White;       // Màu 3 đoạn thẳng BC, BD, BE hiện tại
sf::Color colorTrailBranches = sf::Color(255, 255, 255, 180); // Màu trail của C, D, E (trắng hơi trong suốt)
// =======================================================================

// Cấu trúc lưu điểm có màu cho trail
struct ColoredPoint {
    sf::Vector2f position;
    sf::Color color;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Beautiful Rotating Trails");
    window.setFramerateLimit(60);

    // Điểm cố định A (tâm màn hình)
    sf::Vector2f A(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    // Độ dài tối đa
    float maxRadiusAB = 60.0f;
    float currentRadiusAB = 0.0f;

    float maxLengthBranch = 50.0f;
    float currentLengthBranch = 0.0f;

    float growthSpeed = 2.0f;  // Tốc độ dài ra (pixel/frame)

    // Góc quay
    float angleAB = 0.0f;
    float angleBranches = 0.0f;

    // Tốc độ quay khi vào phase rotate
    float speedAB = 4.5f;
    float speedBranches = 20.0f;

    // Trails (tích tụ vô hạn)
    std::deque<ColoredPoint> trailB;
    std::deque<ColoredPoint> trailC;
    std::deque<ColoredPoint> trailD;
    std::deque<ColoredPoint> trailE;

    // Phase: 0 = grow AB, 1 = grow branches, 2 = rotate
    int phase = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // === XỬ LÝ PHASE ===
        if (phase == 0) {
            currentRadiusAB += growthSpeed;
            if (currentRadiusAB >= maxRadiusAB) {
                currentRadiusAB = maxRadiusAB;
                phase = 1;
            }
        } else if (phase == 1) {
            currentLengthBranch += growthSpeed;
            if (currentLengthBranch >= maxLengthBranch) {
                currentLengthBranch = maxLengthBranch;
                phase = 2;
            }
        } else if (phase == 2) {
            angleAB += speedAB * 0.01f;
            angleBranches += speedBranches * 0.01f;
        }

        // === TÍNH TOÁN VỊ TRÍ ===
        sf::Vector2f B = A + sf::Vector2f(cos(angleAB), sin(angleAB)) * currentRadiusAB;

        sf::Vector2f C = B + sf::Vector2f(cos(angleBranches),                  sin(angleBranches))                  * currentLengthBranch;
        sf::Vector2f D = B + sf::Vector2f(cos(angleBranches + 2*PI/3),         sin(angleBranches + 2*PI/3))         * currentLengthBranch;
        sf::Vector2f E = B + sf::Vector2f(cos(angleBranches + 4*PI/3),         sin(angleBranches + 4*PI/3))         * currentLengthBranch;

        // === THÊM VÀO TRAIL ===
        trailB.push_front({B, colorTrailAB});

        if (phase >= 1) {  // Chỉ thêm trail nhánh khi đã bắt đầu grow chúng
            trailC.push_front({C, colorTrailBranches});
            trailD.push_front({D, colorTrailBranches});
            trailE.push_front({E, colorTrailBranches});
        }

        // === VẼ ===
        window.clear(sf::Color::Black);

        // Hàm vẽ trail với hiệu ứng mờ dần
        auto drawTrail = [&](const std::deque<ColoredPoint>& trail) {
            if (trail.size() < 2) return;
            sf::VertexArray lines(sf::LinesStrip);
            for (size_t i = 0; i < trail.size(); ++i) {
                float alphaFactor = 1.0f - static_cast<float>(i) / trail.size();
                sf::Color c = trail[i].color;
                c.a = static_cast<sf::Uint8>(255 * alphaFactor * 1.0f);  // Điều chỉnh độ trong suốt tổng thể ở đây nếu cần
                lines.append(sf::Vertex(trail[i].position, c));
            }
            window.draw(lines);
        };

        drawTrail(trailB);
        if (phase >= 1) {
            drawTrail(trailC);
            drawTrail(trailD);
            drawTrail(trailE);
        }

        // Vẽ các đoạn thẳng hiện tại (đậm, không mờ)
        sf::VertexArray lineAB(sf::Lines, 2);
        lineAB[0] = sf::Vertex(A, colorLineAB);
        lineAB[1] = sf::Vertex(B, colorLineAB);
        window.draw(lineAB);

        if (phase >= 1) {
            sf::VertexArray lineBC(sf::Lines, 2);
            lineBC[0] = sf::Vertex(B, colorLineBranches);
            lineBC[1] = sf::Vertex(C, colorLineBranches);
            window.draw(lineBC);

            sf::VertexArray lineBD(sf::Lines, 2);
            lineBD[0] = sf::Vertex(B, colorLineBranches);
            lineBD[1] = sf::Vertex(D, colorLineBranches);
            window.draw(lineBD);

            sf::VertexArray lineBE(sf::Lines, 2);
            lineBE[0] = sf::Vertex(B, colorLineBranches);
            lineBE[1] = sf::Vertex(E, colorLineBranches);
            window.draw(lineBE);
        }

        // Vẽ điểm A và B để dễ nhìn (tùy chọn)
        /*sf::CircleShape pointA(10.f);
        pointA.setFillColor(sf::Color(0, 180, 0));
        pointA.setPosition(A - sf::Vector2f(6, 6));
        window.draw(pointA);*/

        sf::CircleShape pointB(5.f);
        pointB.setFillColor(colorLineAB);
        pointB.setPosition(B - sf::Vector2f(5, 5));
        window.draw(pointB);

        window.display();
    }

    return 0;
}
