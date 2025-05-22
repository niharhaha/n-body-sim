#include "ParticleSystem.h"
#include "Forces.h"
#include <iostream>
#include <SFML/Graphics.hpp>   // For sf::RenderWindow, sf::Text, sf::Font, sf::Color

void benchmarkBarnesHut(int size = 10000, int iters = 5000) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "N-Body Gravity Simulation (Barnes Hut)");

    ParticleSystem ps;
    ps.createRandomSystem(size);   
    ps.addParticle(1e18f, {500, 500}, {-5, -15}, 15, {180, 14, 77});
    ps.addParticle(1e18f, {200, 500}, {-5, -15}, 15, {180, 14, 77});
    
    float totalTime = 0.0f;
    const sf::Font font("assets/times.ttf");


    sf::Text iterText(font, "hello");
    iterText.setCharacterSize(14);
    iterText.setStyle(sf::Text::Bold);
    iterText.setFillColor(sf::Color::White);
 

    for (int i = 0; i < iters; i++) {
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }
        window.clear(sf::Color::Black);
        sf::Clock clock;
        auto forces = computeBarnesHutForces(ps.getParticles());
        totalTime += clock.getElapsedTime().asMilliseconds(); 
        ps.updateAndDraw(window, forces);

        iterText.setString("Iteration: " + std::to_string(i));
        window.draw(iterText);

        window.display();
    }

    std::cout << "Barnes Hut for " << size << " objects for " << iters << " steps took " << totalTime << " ms (avg = " << (totalTime / iters) << " ms/step)\n";
    // window.close();
}

void benchmarkBruteForce(int size = 100, int iters = 1000) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "N-Body Gravity Simulation (Brute Force)");

    ParticleSystem ps;
    ps.createRandomSystem(size);   
    ps.addParticle(1e18f, {500, 500});
 
    
    float totalTime = 0.0f;
    for (int i = 0; i < iters; i++) {
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }
        window.clear(sf::Color::Black);
        sf::Clock clock;
        auto forces = computeBruteForces(ps.getParticles());
        totalTime += clock.getElapsedTime().asMilliseconds(); 
        ps.updateAndDraw(window, forces);
        window.display();
    }

    std::cout << "Brute Force for " << size << " objects for " << iters << " steps took " << totalTime << " ms (avg = " << (totalTime / iters) << " ms/step)\n";
    // window.close();
}