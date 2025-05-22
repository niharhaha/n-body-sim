#include "ParticleSystem.h"
#include "Forces.h"
#include <iostream>
#include <SFML/Graphics.hpp>   // For sf::RenderWindow, sf::Text, sf::Font, sf::Color
#include "ThreadPool.h"

void benchmarkBarnesHut(int size = 10000, int iters = 5000) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "N-Body Gravity Simulation (Barnes Hut)");

    ParticleSystem ps;
    ps.createRandomSystem(size);   
    // ps.addParticle(1e18f, {500, 500}, {-5, -15}, 15, {180, 14, 77});
    ps.addParticle(1e18f, {200, 500}, {-5, -15}, 15, {180, 14, 77});
    
    float totalTime = 0.0f;
    const sf::Font font("assets/times.ttf");


    sf::Text iterText(font, "hello");
    iterText.setCharacterSize(14);
    iterText.setStyle(sf::Text::Bold);
    iterText.setFillColor(sf::Color::White);
 
    ThreadPool pool;
    for (int i = 0; i < iters; i++) {
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }
        window.clear(sf::Color::Black);
        sf::Clock clock;
        computeThreadPoolBarnesHutForces(ps.getParticles(), ps.getForces(), pool);
        totalTime += clock.getElapsedTime().asMilliseconds(); 
        ps.updateAndDraw(window);

        iterText.setString("Iteration: " + std::to_string(i));
        window.draw(iterText);

        window.display();
    }

    std::cout << "Barnes Hut for " << size << " objects for " << iters << " steps took " << totalTime << " ms (avg = " << (totalTime / iters) << " ms/step)\n";
    // window.close();
}
