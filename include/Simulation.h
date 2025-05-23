#ifndef SIMULATION_H
#define SIMULATION_H
#include "Constants.h"
#include <SFML/Graphics.hpp>

void drawResultText(sf::RenderWindow& window, const sf::Font font, const std::string text, const float textSize, const sf::Vector2f position) {
    sf::Text resultText(font, text);
    sf::FloatRect textRect;
    
    resultText.setCharacterSize(textSize);
    textRect = resultText.getLocalBounds();
    resultText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});

    resultText.setPosition(position);
    resultText.setStyle(sf::Text::Bold);
    resultText.setFillColor(sf::Color::White);

    resultText.setOutlineColor(sf::Color::Black);           // Outline color
    resultText.setOutlineThickness(2);                      

    window.draw(resultText);
}

template <typename LoopCondition, typename FooterPrinter, typename Func, typename... Args>
void createSimulation(int n, std::string algoName, ParticleSystem& ps, Func forceComputor, LoopCondition&& loopCondition, FooterPrinter&& footer, Args&&... args) {
    std::ostringstream oss;
    oss << n << "-Body Gravity Simulation (" << algoName <<")";

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), oss.str());
    const sf::Font font("assets/font.ttf");
    
    float totalTime = 0.0f;
    sf::Clock globalClock;

    sf::Text iterText(font, "", statTextSize);
    iterText.setPosition(WINDOW_TEXT_CORNER);
    iterText.setStyle(sf::Text::Bold);
    iterText.setOutlineColor(sf::Color::Black);          
    iterText.setOutlineThickness(1);  

    sf::Text timeText(font, "", statTextSize);
    timeText.setPosition(WINDOW_TEXT_CORNER2);
    timeText.setStyle(sf::Text::Bold);
    timeText.setOutlineColor(sf::Color::Black);         
    timeText.setOutlineThickness(1);  
   

    int iter = 1;
    
    while (true) {
        iter++;
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }

        window.clear(sf::Color::Black);
        sf::Clock frameClock;
        forceComputor(ps, std::forward<Args>(args)...);
        totalTime += frameClock.getElapsedTime().asMilliseconds(); 
        ps.updateAndDraw(window);
        iterText.setString("Iteration: " + std::to_string(iter));
        float seconds = globalClock.getElapsedTime().asSeconds();
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << seconds;
        std::string formattedTime = oss.str();  
        timeText.setString("Time Elapsed: " + formattedTime + "s");
        
        window.draw(iterText);
        window.draw(timeText);
        window.display();

        if (!loopCondition(iter, globalClock)) {
            
            std::vector<std::string> results = footer(n, iter - 1, totalTime, globalClock);
            drawResultText(window, font, results[0], headingTextSize, WINDOW_HEADING_TEXT_CENTER);
            drawResultText(window, font, results[1], resultTextSize, WINDOW_RESULT_TEXT_CENTER);
            drawResultText(window, font, results[2], resultTextSize, WINDOW_RESULT2_TEXT_CENTER);
            drawResultText(window, font, results[3], resultTextSize, WINDOW_RESULT3_TEXT_CENTER);
            drawResultText(window, font, results[4], resultTextSize, WINDOW_RESULT4_TEXT_CENTER);
            window.display();

            while (window.isOpen()) {
                std::optional<sf::Event> eventOpt = window.pollEvent();
                while (eventOpt.has_value()) {
                    const sf::Event& event = eventOpt.value();
                    if (event.is<sf::Event::Closed>()) window.close();
                    eventOpt = window.pollEvent();
                }
            }

            break;
        }
    }
}

template <typename Func, typename... Args>
void createIterSimulation(ParticleSystem& ps, Func forceComputor, Args&&... args, int iters = 0, std::string algoName = "") {
    createSimulation(
        ps.getSize(), algoName, ps, forceComputor,
        [iters](int i, const sf::Clock&) { return i <= iters || iters == 0; },
        [&algoName](int n, int iters, float totalTime, const sf::Clock&) -> std::vector<std::string> {
            std::ostringstream oss;

            std::vector<std::string> results;
            results.push_back(algoName);

            std::ostringstream oss1;
            oss1 << "No. of particles: " << n;
            results.push_back(oss1.str());

            std::ostringstream oss2;
            oss2 << "No. of iterations: " << iters;
            results.push_back(oss2.str());

            std::ostringstream oss3;
            oss3 << "Time taken: " << std::fixed << std::setprecision(2) << totalTime << " ms";
            results.push_back(oss3.str());

            std::ostringstream oss4;
            oss4 << "Average time per iteration: " << (totalTime / iters) << " ms/step";
            results.push_back(oss4.str());
            
            return results;
        },
        std::forward<Args>(args)...
    );
    
}

template <typename Func, typename... Args>
void createTimeSimulation(ParticleSystem& ps, Func forceComputor, Args&&... args, int ms = 0, std::string algoName = "") {
    createSimulation(
        ps.getSize(), algoName, ps, forceComputor,
        [ms](int, const sf::Clock& globalClock) { return globalClock.getElapsedTime().asMilliseconds() < ms || ms == 0; },
        [&algoName, ms](int n, int iters, float, const sf::Clock& globalClock) -> std::vector<std::string> {
            
            std::vector<std::string> results;
            results.push_back(algoName);

            std::ostringstream oss1;
            oss1 << "No. of particles: " << n;
            results.push_back(oss1.str());

            std::ostringstream oss2;
            oss2 << "Simulation time: " << ms << "ms";
            results.push_back(oss2.str());

            std::ostringstream oss3;
            oss3 << "Iterations completed: " << iters;
            results.push_back(oss3.str());

            std::ostringstream oss4;
            oss4 << "Real world time simulated: " << TIME_STEP * iters << " s";
            results.push_back(oss4.str());
            
            return results;
        },
        std::forward<Args>(args)...
    );

}

#endif