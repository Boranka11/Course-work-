cmake_minimum_required(VERSION 3.10)
project(car_advisor)

find_package(CURL REQUIRED)

# Убедитесь, что имя файла совпадает с вашим исходным кодом
add_executable(car_advisor carsdealer.cpp)

target_include_directories(car_advisor PRIVATE
    /usr/include/nlohmann_json
)

target_link_libraries(car_advisor PRIVATE
    CURL::libcurl
)
