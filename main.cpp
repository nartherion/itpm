#include <string>

#include <fmt/format.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <gauss/gauss.hpp>

void render_input_table(gauss::matrix_t &m)
{
    if (!ImGui::BeginTable("equation system", m.front().size()))
        return;

    const std::size_t h = m.size();
    const std::size_t l = m.front().size();

    for (std::size_t row = 0; row < h; ++row)
    {
        ImGui::TableNextRow();
        for (std::size_t column = 0; column < l; ++column)
        {
            ImGui::TableSetColumnIndex(column);

            const std::string label = (column == l - 1) ?
                fmt::format("b{}", row + 1) : fmt::format("x{}{}", row + 1, column  + 1);

            ImGui::InputDouble(label.c_str(), &m[row][column]);
        }
    }

    ImGui::EndTable();
}

std::string on_solve(gauss::matrix_t &m)
{
    std::string message;

    const gauss::result_t result = gauss::elimination(m);
    if (std::holds_alternative<std::vector<double>>(result))
    {
        message = "solutions: ";

        for (const double x : std::get<std::vector<double>>(result))
            fmt::format_to(std::back_inserter(message), "{} ", x);

        message.pop_back();
    }
    else if (std::holds_alternative<gauss::error_code>(result))
    {
        switch (std::get<gauss::error_code>(result))
        {
            case gauss::error_code::inconsistent_system:
                message = "error: inconsistent system";
                break;

            case gauss::error_code::infinite_solutions:
                message = "error: system has infinite solutions";
                break;
        }
    }

    return message;
}

int main()
{
    constexpr std::size_t system_size = 3;
    gauss::matrix_t m(system_size, std::vector<double>(system_size + 1));

    sf::RenderWindow window(sf::VideoMode(640, 480), "gaussian elimination");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        return EXIT_FAILURE;

    sf::Clock delta_clock;
    std::string buffer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, delta_clock.restart());
        ImGui::Begin("gaussian elimination");

        render_input_table(m);

        if (ImGui::Button("solve"))
            buffer = on_solve(m);

        if (!buffer.empty())
            ImGui::Text("%s", buffer.c_str());

        ImGui::End();
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return EXIT_SUCCESS;
}

