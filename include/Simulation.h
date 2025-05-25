#ifndef SIMULATION_H
#define SIMULATION_H
#include "Constants.h"
#include <SFML/Graphics.hpp>

void drawResultText(sf::RenderWindow& window, const sf::Font font, const std::string text, const float textSize, const sf::Vector2f position) {
    sf::Text resultText(font, text);
    sf::FloatRect textRect;
    
    resultText.setCharacterSize(textSize);
    textRect = resultText.getLocalBounds();
    resultText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f}); // Center the text

    resultText.setPosition(position); // Text properties
    resultText.setStyle(sf::Text::Bold);
    resultText.setFillColor(sf::Color::White);
    resultText.setOutlineColor(sf::Color::Black);  
    resultText.setOutlineThickness(2);                      

    window.draw(resultText); // Draw the text on input window
}

// Generic simulation runner
template <typename LoopCondition, typename FooterPrinter, typename Func, typename... Args>
void createSimulation(int n, std::string algoName, ParticleSystem& ps, Func forceComputor, LoopCondition&& loopCondition, FooterPrinter&& footer, Args&&... args) {
    std::ostringstream oss; // Window header
    oss << n << "-Body Gravity Simulation (" << algoName << ")";

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), oss.str()); // Create window
    const sf::Font font("assets/font.ttf"); // Load the font
    
    float totalTime = 0.0f; // Global time-keeping
    sf::Clock globalClock;

    sf::Text iterText(font, "", statTextSize); // Iteration text initialization
    iterText.setPosition(WINDOW_TEXT_CORNER);
    iterText.setStyle(sf::Text::Bold);
    iterText.setOutlineColor(sf::Color::Black);          
    iterText.setOutlineThickness(1);  

    sf::Text timeText(font, "", statTextSize); // Timer text initialization
    timeText.setPosition(WINDOW_TEXT_CORNER2);
    timeText.setStyle(sf::Text::Bold);
    timeText.setOutlineColor(sf::Color::Black);         
    timeText.setOutlineThickness(1);  
   
    int iter = 1; // Iterations counter
    std::optional<sf::Event> eventOpt;
    while (true) {
        iter++;
        eventOpt = window.pollEvent();
        while (eventOpt.has_value()) { // Check if window was closed
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }

        window.clear(sf::Color::Black); // Clear window to draw new frame

        sf::Clock frameClock; // Frame time-keeping
        forceComputor(ps, std::forward<Args>(args)...); // Apply the forces, update particle positions
        totalTime += frameClock.getElapsedTime().asMilliseconds(); 
         
        // Update stat texts
        iterText.setString("Iteration: " + std::to_string(iter));
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << globalClock.getElapsedTime().asSeconds();
        timeText.setString("Time Elapsed: " + oss.str() + "s");
        
        ps.updateAndDraw(window); // Draw the updates
        window.draw(iterText);
        window.draw(timeText);
        
        window.display(); // Display the new frame

        if (!loopCondition(iter, globalClock)) { // Check if simulation has ended
            
            // Draw and display the results 
            std::vector<std::string> results = footer(n, iter - 1, totalTime, globalClock);
            drawResultText(window, font, results[0], headingTextSize, WINDOW_HEADING_TEXT_CENTER);
            drawResultText(window, font, results[1], resultTextSize, WINDOW_RESULT_TEXT_CENTER);
            drawResultText(window, font, results[2], resultTextSize, WINDOW_RESULT2_TEXT_CENTER);
            drawResultText(window, font, results[3], resultTextSize, WINDOW_RESULT3_TEXT_CENTER);
            drawResultText(window, font, results[4], resultTextSize, WINDOW_RESULT4_TEXT_CENTER);
            window.display();

            while (window.isOpen()) { // Check if window was closed
                eventOpt = window.pollEvent(); 
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

// Create a iteration-based simulation
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

// Create a time-based simulation
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
            oss4 << "Frames per second: " << iters / (ms / 1000.0) << " fps";
            results.push_back(oss4.str());
            
            return results;
        },
        std::forward<Args>(args)...
    );

}

#endif