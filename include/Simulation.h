#ifndef SIMULATION_H
#define SIMULATION_H

template <typename LoopCondition, typename FooterPrinter, typename Func, typename... Args>
void createSimulation(int n, ParticleSystem& ps, Func forceComputor, LoopCondition&& loopCondition, FooterPrinter&& footer, Args&&... args) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "N-Body Gravity Simulation (Barnes Hut)");
    float totalTime = 0.0f;
    const sf::Font font("assets/times.ttf");

    sf::Text iterText(font, "hello");
    iterText.setCharacterSize(14);
    iterText.setStyle(sf::Text::Bold);
    iterText.setFillColor(sf::Color::White);

    sf::Text timeText(font, "hello");
    timeText.setCharacterSize(14);
    sf::Vector2f timePos = {0, 20};
    timePos += iterText.getPosition();
    timeText.setPosition(timePos);
    timeText.setStyle(sf::Text::Bold);
    timeText.setFillColor(sf::Color::White);

    int iter = 1;
    sf::Clock globalClock;

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
            std::string output = footer(n, iter, totalTime, globalClock);

            sf::Text outText(font, output);
            outText.setCharacterSize(14);
            sf::FloatRect textRect = outText.getLocalBounds();
            outText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
               textRect.position.y + textRect.size.y / 2.0f});

            outText.setPosition(WINDOW_CENTER);
            outText.setStyle(sf::Text::Bold);
            outText.setFillColor(sf::Color::White);


            window.draw(outText);
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
void createIterSimulation(ParticleSystem& ps, Func forceComputor, Args&&... args, int iters = 0) {
    createSimulation(
        ps.getSize(), ps, forceComputor,
        [iters](int i, const sf::Clock&) { return i <= iters; },
        [](int n, int iters, float totalTime, const sf::Clock&) -> std::string {
            std::ostringstream oss;
            oss << "Barnes Hut for " << n << " objects for " << iters - 1
                << " steps took " << std::fixed << std::setprecision(2) << totalTime
                << " ms (avg = " << (totalTime / iters) << " ms/step)";
            return oss.str();
        },
        std::forward<Args>(args)...
    );
    
}

template <typename Func, typename... Args>
void createTimeSimulation(ParticleSystem& ps, Func forceComputor, Args&&... args, int ms = 0) {
    createSimulation(
        ps.getSize(), ps, forceComputor,
        [ms](int, const sf::Clock& globalClock) { return globalClock.getElapsedTime().asMilliseconds() < ms; },
        [ms](int n, int iters, float, const sf::Clock& globalClock) -> std::string {
            std::ostringstream oss;
            oss << "Barnes Hut for " << n << " objects for " << ms
                << " time completed " << iters << " iterations (real world time = "
                << (TIME_STEP * iters) << " s)\n";
            return oss.str();
        },
        std::forward<Args>(args)...
    );

}

#endif