

add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
	 
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Spaceship/Spaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Spaceship/Spaceship.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/PlayerSpaceship/PlayerSpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/PlayerSpaceship/PlayerSpaceship.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/Shooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Shooter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/BulletShooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/BulletShooter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Weapon/Bullet.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Weapon/Bullet.cpp

)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include 
)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME} )


function(copyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E	copy_directory 
	$<TARGET_FILE_DIR:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

copyLibDirToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

SET(RESOURCE_FOLDER_NAME "assets")
SET(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
	TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory
	${RESOURCE_SRC_DIR}
	$<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
	"config.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)
